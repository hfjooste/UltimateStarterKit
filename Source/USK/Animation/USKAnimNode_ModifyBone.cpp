// Created by Henry Jooste

#include "USKAnimNode_ModifyBone.h"

#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"
#include "BoneControllers/AnimNode_ModifyBone.h"

/**
 * @brief Create a new instance of the animation node
 */
FUSKAnimNode_ModifyBone::FUSKAnimNode_ModifyBone()
	: Translation(FVector::ZeroVector)
	, Rotation(FRotator::ZeroRotator)
	, Scale(FVector(1.0f))
	, TranslationMode(BMM_Ignore)
	, RotationMode(BMM_Ignore)
	, ScaleMode(BMM_Ignore)
	, TranslationSpace(BCS_ComponentSpace)
	, RotationSpace(BCS_ComponentSpace)
	, ScaleSpace(BCS_ComponentSpace)
{
}

/**
 * @brief Evaluate the skeletal control
 * @param Output The output pose
 * @param OutBoneTransforms The output bone transforms
 */
void FUSKAnimNode_ModifyBone::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output,
	TArray<FBoneTransform>& OutBoneTransforms)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(EvaluateSkeletalControl_AnyThread)
	check(OutBoneTransforms.Num() == 0);

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();

	const FCompactPoseBoneIndex CompactPoseBoneToModify = BoneToModify.GetCompactPoseIndex(BoneContainer);
	FTransform NewBoneTM = Output.Pose.GetComponentSpaceTransform(CompactPoseBoneToModify);
	const FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

	if (ScaleMode != BMM_Ignore)
	{
		FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, ScaleSpace);

		if (ScaleMode == BMM_Additive)
		{
			NewBoneTM.SetScale3D(NewBoneTM.GetScale3D() * Scale);
		}
		else
		{
			NewBoneTM.SetScale3D(Scale);
		}

		FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, ScaleSpace);
	}

	if (RotationMode != BMM_Ignore)
	{
		FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, RotationSpace);

		const FQuat BoneQuat(Rotation);
		if (RotationMode == BMM_Additive)
		{	
			NewBoneTM.SetRotation(BoneQuat * NewBoneTM.GetRotation());
		}
		else
		{
			NewBoneTM.SetRotation(BoneQuat);
		}

		FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, RotationSpace);
	}
	
	if (TranslationMode != BMM_Ignore)
	{
		FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, TranslationSpace);

		if (TranslationMode == BMM_Additive)
		{
			NewBoneTM.AddToTranslation(Translation);
		}
		else
		{
			NewBoneTM.SetTranslation(Translation);
		}

		FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, TranslationSpace);
	}
	
	OutBoneTransforms.Add( FBoneTransform(BoneToModify.GetCompactPoseIndex(BoneContainer), NewBoneTM) );

	TRACE_ANIM_NODE_VALUE(Output, TEXT("Target"), BoneToModify.BoneName);
}

/**
 * @brief Check if the node is valid to evaluate
 * @param Skeleton The skeleton to check
 * @param RequiredBones The required bones to check
 * @return A boolean value indicating whether the node is valid to evaluate
 */
bool FUSKAnimNode_ModifyBone::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) 
{
	return BoneToModify.IsValidToEvaluate(RequiredBones);
}

/**
 * @brief Initialize the bone references
 * @param RequiredBones The required bones
 */
void FUSKAnimNode_ModifyBone::InitializeBoneReferences(const FBoneContainer& RequiredBones) 
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(InitializeBoneReferences)
	BoneToModify.BoneName = Bone;
	BoneToModify.Initialize(RequiredBones);
}
