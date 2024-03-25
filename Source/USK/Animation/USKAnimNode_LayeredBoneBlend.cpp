// Created by Henry Jooste

#include "USKAnimNode_LayeredBoneBlend.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"
#include "Animation/AnimationPoseData.h"
#include "Runtime/Launch/Resources/Version.h"

#define DEFAULT_SOURCEINDEX 0xFF

/**
 * @brief Create a new instance of the animation node
 */
FUSKAnimNode_LayeredBoneBlend::FUSKAnimNode_LayeredBoneBlend()
		: BlendMode(EUSKLayeredBoneBlendMode::BranchFilter)
		, bMeshSpaceRotationBlend(false)
		, bMeshSpaceScaleBlend(false)
		, CurveBlendOption(ECurveBlendOption::Override)
		, bBlendRootMotionBasedOnRootBone(true)
		, bHasRelevantPoses(false)
		, LODThreshold(INDEX_NONE)
		, RequiredBonesSerialNumber(0)
{
}

/**
 * @brief Initialize the animation node
 * @param Context The initialization context used during animation tree initialization
 */
void FUSKAnimNode_LayeredBoneBlend::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Initialize_AnyThread)
	
	FAnimNode_Base::Initialize_AnyThread(Context);
	const int NumPoses = BlendPoses.Num();
	checkSlow(BlendWeights.Num() == NumPoses);

	BasePose.Initialize(Context);
	if (NumPoses > 0)
	{		
		for (int ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
		{
			BlendPoses[ChildIndex].Initialize(Context);
		}
	}
}

/**
 * @brief Cache all bones that are required by this node
 * @param Context The context used when RequiredBones array changed and cached bones indices have to be refreshed
 */
void FUSKAnimNode_LayeredBoneBlend::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(CacheBones_AnyThread)
	BasePose.CacheBones(Context);

	const int NumPoses = BlendPoses.Num();
	for(int ChildIndex = 0; ChildIndex < NumPoses; ChildIndex++)
	{
		BlendPoses[ChildIndex].CacheBones(Context);
	}

	UpdateCachedBoneData(Context.AnimInstanceProxy->GetRequiredBones(), Context.AnimInstanceProxy->GetSkeleton());
}

/**
 * @brief Update the animation node
 * @param Context The update context used during animation tree update
 */
void FUSKAnimNode_LayeredBoneBlend::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Update_AnyThread)
	bHasRelevantPoses = false;
	int RootMotionBlendPose = -1;
	float RootMotionWeight = 0.0f;
	const float RootMotionClearWeight = bBlendRootMotionBasedOnRootBone ? 0.0f : 1.0f;

	if (IsLODEnabled(Context.AnimInstanceProxy))
	{
		GetEvaluateGraphExposedInputs().Execute(Context);

		for (int32 ChildIndex = 0; ChildIndex < BlendPoses.Num(); ++ChildIndex)
		{
			const float ChildWeight = BlendWeights[ChildIndex];
			if (!FAnimWeight::IsRelevant(ChildWeight))
			{
				continue;
			}

			if (!bHasRelevantPoses)
			{
				UpdateCachedBoneData(Context.AnimInstanceProxy->GetRequiredBones(),
					Context.AnimInstanceProxy->GetSkeleton());

				FAnimationRuntime::UpdateDesiredBoneWeight(DesiredBoneBlendWeights,
					CurrentBoneBlendWeights, BlendWeights);
				bHasRelevantPoses = true;

				if (bBlendRootMotionBasedOnRootBone && CurrentBoneBlendWeights.Num() > 0)
				{
					const float NewRootMotionWeight = CurrentBoneBlendWeights[0].BlendWeight;
					if(NewRootMotionWeight > ZERO_ANIMWEIGHT_THRESH)
					{
						RootMotionWeight = NewRootMotionWeight;
						RootMotionBlendPose = CurrentBoneBlendWeights[0].SourceIndex;
					}
				}
			}

			const float ThisPoseRootMotionWeight = ChildIndex == RootMotionBlendPose
				? RootMotionWeight
				: RootMotionClearWeight;
			const FAnimationUpdateContext AnimationUpdateContext = Context.FractionalWeightAndRootMotion(
				ChildWeight, ThisPoseRootMotionWeight);
			BlendPoses[ChildIndex].Update(AnimationUpdateContext);
		}
	}
	
	const float BaseRootMotionWeight = 1.0f - RootMotionWeight;
	if (BaseRootMotionWeight < ZERO_ANIMWEIGHT_THRESH)
	{
		BasePose.Update(Context.FractionalWeightAndRootMotion(1.0f, BaseRootMotionWeight));
	}
	else
	{
		BasePose.Update(Context);
	}

	TRACE_ANIM_NODE_VALUE(Context, TEXT("Num Poses"), BlendPoses.Num());
}

/**
 * @brief Evaluate the animation node
 * @param Output The evaluation context used during animation tree evaluation
 */
void FUSKAnimNode_LayeredBoneBlend::Evaluate_AnyThread(FPoseContext& Output)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(Evaluate_AnyThread)
	ANIM_MT_SCOPE_CYCLE_COUNTER(BlendPosesInGraph, !IsInGameThread());

	const int NumPoses = BlendPoses.Num();
	if (NumPoses == 0 || !bHasRelevantPoses)
	{
		BasePose.Evaluate(Output);
		return;
	}

	FPoseContext BasePoseContext(Output);
	BasePose.Evaluate(BasePoseContext);

	TArray<FCompactPose> TargetBlendPoses;
	TargetBlendPoses.SetNum(NumPoses);

	TArray<FBlendedCurve> TargetBlendCurves;
	TargetBlendCurves.SetNum(NumPoses);

#if ENGINE_MAJOR_VERSION == 4
	TArray<FStackCustomAttributes> TargetBlendAttributes;
	TargetBlendAttributes.SetNum(NumPoses);
#else
	TArray<UE::Anim::FStackAttributeContainer> TargetBlendAttributes;
	TargetBlendAttributes.SetNum(NumPoses);
#endif

	for (int ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
	{
		if (!FAnimWeight::IsRelevant(BlendWeights[ChildIndex]))
		{
			TargetBlendPoses[ChildIndex].ResetToRefPose(BasePoseContext.Pose.GetBoneContainer());
			TargetBlendCurves[ChildIndex].InitFrom(Output.Curve);
			continue;
		}

		FPoseContext CurrentPoseContext(Output);
        BlendPoses[ChildIndex].Evaluate(CurrentPoseContext);

        TargetBlendPoses[ChildIndex].MoveBonesFrom(CurrentPoseContext.Pose);
        TargetBlendCurves[ChildIndex].MoveFrom(CurrentPoseContext.Curve);
        TargetBlendAttributes[ChildIndex].MoveFrom(CurrentPoseContext.CustomAttributes);
	}

	TArray<uint16> const* CurveUIDFinder = Output.Curve.UIDToArrayIndexLUT;
	for (USkeleton::AnimCurveUID UIDIndex = 0; UIDIndex < CurveUIDFinder->Num(); ++UIDIndex)
	{
		const int CurvePoseIndex = Output.Curve.GetArrayIndexByUID(UIDIndex);
		if (!CurvePoseSourceIndices.IsValidIndex(CurvePoseIndex))
		{
			continue;
		}

		const int SourceIndex = CurvePoseSourceIndices[CurvePoseIndex];
		if (SourceIndex == DEFAULT_SOURCEINDEX)
		{
			continue;
		}

#if ENGINE_MAJOR_VERSION == 4 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION == 0)
		BasePoseContext.Curve.Set(UIDIndex, 0.0f);
#else
		BasePoseContext.Curve.InvalidateCurveWeight(UIDIndex);
#endif
		
		for (int ChildIndex = 0; ChildIndex < NumPoses; ++ChildIndex)
		{
			if (SourceIndex != ChildIndex)
			{
#if ENGINE_MAJOR_VERSION == 4 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION == 0)
				TargetBlendCurves[ChildIndex].Set(UIDIndex, 0.0f);
#else
				TargetBlendCurves[ChildIndex].InvalidateCurveWeight(UIDIndex);
#endif
			}
		}
	}

	FAnimationRuntime::EBlendPosesPerBoneFilterFlags BlendFlags =
		FAnimationRuntime::EBlendPosesPerBoneFilterFlags::None;
	if (bMeshSpaceRotationBlend)
	{
		BlendFlags |= FAnimationRuntime::EBlendPosesPerBoneFilterFlags::MeshSpaceRotation;
	}
	if (bMeshSpaceScaleBlend)
	{
		BlendFlags |= FAnimationRuntime::EBlendPosesPerBoneFilterFlags::MeshSpaceScale;
	}

	FAnimationPoseData AnimationPoseData(Output);
	FAnimationRuntime::BlendPosesPerBoneFilter(BasePoseContext.Pose, TargetBlendPoses, BasePoseContext.Curve,
		TargetBlendCurves, BasePoseContext.CustomAttributes, TargetBlendAttributes, AnimationPoseData,
		CurrentBoneBlendWeights, BlendFlags, CurveBlendOption);
}

/**
 * @brief Get the LOD threshold for this node
 * @return The LOD threshold for this node
 */
int FUSKAnimNode_LayeredBoneBlend::GetLODThreshold() const
{
	return LODThreshold;
}

/**
 * @brief Add a pose
 */
void FUSKAnimNode_LayeredBoneBlend::AddPose()
{
	BlendWeights.Add(1.f);
	new (BlendPoses) FPoseLink();

	if (BlendMode == EUSKLayeredBoneBlendMode::BlendMask) 
	{ 
		BlendMasks.Add(nullptr);
		return;
	}

	new (LayerSetup) FInputBlendPose();
}

/**
 * @brief Remove a pose
 * @param PoseIndex The index of the pose to remove
 */
void FUSKAnimNode_LayeredBoneBlend::RemovePose(const int PoseIndex)
{
	BlendWeights.RemoveAt(PoseIndex);
    BlendPoses.RemoveAt(PoseIndex);

    if (BlendMasks.IsValidIndex(PoseIndex)) 
    { 
    	BlendMasks.RemoveAt(PoseIndex); 
    }

    if (LayerSetup.IsValidIndex(PoseIndex)) 
    { 
    	LayerSetup.RemoveAt(PoseIndex); 
    }
}

/**
 * @brief Set the blend mask for the specified input pose
 * @param InPoseIndex The index of the pose to update
 * @param InBlendMask The blend mask to set
 */
void FUSKAnimNode_LayeredBoneBlend::SetBlendMask(const int32 InPoseIndex, UBlendProfile* InBlendMask)
{
	check(BlendMode == EUSKLayeredBoneBlendMode::BlendMask);
	check(BlendPoses.IsValidIndex(InPoseIndex));
	check(BlendMasks.IsValidIndex(InPoseIndex));

	BlendMasks[InPoseIndex] = InBlendMask;
	InvalidatePerBoneBlendWeights();
}

/**
 * @brief Invalidate the cached per-bone blend weights from the skeleton
 */
void FUSKAnimNode_LayeredBoneBlend::InvalidatePerBoneBlendWeights()
{
	RequiredBonesSerialNumber = 0;
	SkeletonGuid = FGuid();
	VirtualBoneGuid = FGuid();
}

/**
 * @brief Invalidates the cached bone data so it is recalculated the next time this node is updated
 */
void FUSKAnimNode_LayeredBoneBlend::InvalidateCachedBoneData()
{
	RequiredBonesSerialNumber = 0;
}

/**
 * @brief Check whether per-bone blend weights are valid according to the skeleton
 * @param InSkeleton The skeleton to check
 * @return A boolean value indicating whether per-bone blend weights are valid according to the skeleton
 */
bool FUSKAnimNode_LayeredBoneBlend::ArePerBoneBlendWeightsValid(const USkeleton* InSkeleton) const
{
	return IsValid(InSkeleton) && InSkeleton->GetGuid() == SkeletonGuid &&
		InSkeleton->GetVirtualBoneGuid() == VirtualBoneGuid;
}

/**
 * @brief Rebuild cache per bone blend weights from the skeleton
 * @param InSkeleton The skeleton to rebuild the per bone blend weights from
 */
void FUSKAnimNode_LayeredBoneBlend::RebuildPerBoneBlendWeights(const USkeleton* InSkeleton)
{
	if (!IsValid(InSkeleton))
	{
		return;
	}

#if ENGINE_MAJOR_VERSION == 4	
	FAnimationRuntime::CreateMaskWeights(PerBoneBlendWeights, LayerSetup, InSkeleton);
#else
	if (BlendMode == EUSKLayeredBoneBlendMode::BranchFilter)
	{		
		FAnimationRuntime::CreateMaskWeights(PerBoneBlendWeights, LayerSetup, InSkeleton);	
	}
	else
	{
		FAnimationRuntime::CreateMaskWeights(PerBoneBlendWeights, BlendMasks, InSkeleton);
	}
#endif

	SkeletonGuid = InSkeleton->GetGuid();
	VirtualBoneGuid = InSkeleton->GetVirtualBoneGuid();
}

/**
 * @brief Update cached data if required
 * @param RequiredBones The required bones
 * @param Skeleton A reference to the skeleton
 */
void FUSKAnimNode_LayeredBoneBlend::UpdateCachedBoneData(const FBoneContainer& RequiredBones, const USkeleton* Skeleton)
{
#if ENGINE_MAJOR_VERSION >= 5
	if (RequiredBones.GetSerialNumber() == RequiredBonesSerialNumber)
	{
		return;
	}
#endif

	if (!ArePerBoneBlendWeightsValid(Skeleton) || !bBonesInitialized)
	{
		UpdateBoneName();
		RebuildPerBoneBlendWeights(Skeleton);
	}

	const TArray<FBoneIndexType>& RequiredBoneIndices = RequiredBones.GetBoneIndicesArray();
	const int NumRequiredBones = RequiredBoneIndices.Num();
	DesiredBoneBlendWeights.SetNumZeroed(NumRequiredBones);
	for (int RequiredBoneIndex = 0; RequiredBoneIndex < NumRequiredBones; RequiredBoneIndex++)
	{
		const int SkeletonBoneIndex = RequiredBones.GetSkeletonIndex(FCompactPoseBoneIndex(RequiredBoneIndex));
		if (ensure(SkeletonBoneIndex != INDEX_NONE))
		{
			DesiredBoneBlendWeights[RequiredBoneIndex] = PerBoneBlendWeights[SkeletonBoneIndex];
		}
	}
	
	CurrentBoneBlendWeights.Reset(DesiredBoneBlendWeights.Num());
	CurrentBoneBlendWeights.AddZeroed(DesiredBoneBlendWeights.Num());
	FAnimationRuntime::UpdateDesiredBoneWeight(DesiredBoneBlendWeights,
		CurrentBoneBlendWeights, BlendWeights);

	TArray<uint16> const& CurveUIDFinder = RequiredBones.GetUIDToArrayLookupTable();
	const int CurveUIDCount = CurveUIDFinder.Num();
	const int TotalCount = FBlendedCurve::GetValidElementCount(&CurveUIDFinder);
	if (TotalCount > 0)
	{
		CurvePoseSourceIndices.Reset(TotalCount);
		CurvePoseSourceIndices.Init(DEFAULT_SOURCEINDEX, TotalCount);

		for (int UIDIndex = 0; UIDIndex < CurveUIDCount; ++UIDIndex)
		{
			const int CurrentPoseIndex = CurveUIDFinder[UIDIndex];
			if (CurrentPoseIndex == MAX_uint16)
			{
				continue;
			}

			const SmartName::UID_Type CurveUID = static_cast<SmartName::UID_Type>(UIDIndex);
			const FCurveMetaData* CurveMetaData = Skeleton->GetCurveMetaData(CurveUID);
			if (CurveMetaData == nullptr)
			{
				continue;
			}

			const TArray<FBoneReference>& LinkedBones = CurveMetaData->LinkedBones;
			for (int LinkedBoneIndex = 0; LinkedBoneIndex < LinkedBones.Num(); ++LinkedBoneIndex)
			{
				FCompactPoseBoneIndex CompactPoseIndex = LinkedBones[LinkedBoneIndex].GetCompactPoseIndex(RequiredBones);
				if (CompactPoseIndex == INDEX_NONE)
				{
					continue;
				}

				if (DesiredBoneBlendWeights[CompactPoseIndex.GetInt()].BlendWeight > 0.f)
                {
#if ENGINE_MAJOR_VERSION == 4
					CurvePoseSourceIndices[CurrentPoseIndex] =
						DesiredBoneBlendWeights[CompactPoseIndex.GetInt()].SourceIndex;
#else
					CurvePoseSourceIndices[CurrentPoseIndex] =
						IntCastChecked<uint8>(DesiredBoneBlendWeights[CompactPoseIndex.GetInt()].SourceIndex);
#endif
                }
			}
		}
	}
	else
	{
		CurvePoseSourceIndices.Reset();
	}

#if ENGINE_MAJOR_VERSION >= 5
	RequiredBonesSerialNumber = RequiredBones.GetSerialNumber();
#endif
}

/**
 * @brief Update the bone names
 */
void FUSKAnimNode_LayeredBoneBlend::UpdateBoneName()
{
	if (Bone == NAME_None)
	{
		return;
	}

	bBonesInitialized = true;
	for (int PoseIndex = 0; PoseIndex < LayerSetup.Num(); ++PoseIndex)
	{
		for (int BranchIndex = 0; BranchIndex < LayerSetup[PoseIndex].BranchFilters.Num(); ++BranchIndex)
		{
			LayerSetup[PoseIndex].BranchFilters[BranchIndex].BoneName = Bone;
		}	
	}
}
