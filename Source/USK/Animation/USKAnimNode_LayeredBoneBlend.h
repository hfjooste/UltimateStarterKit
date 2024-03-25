// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimData/BoneMaskFilter.h"
#include "USKLayeredBoneBlendMode.h"
#include "USKAnimNode_LayeredBoneBlend.generated.h"

/**
 * @brief Animation node used to modify a bone
 */
USTRUCT(BlueprintInternalUseOnly)
struct USK_API FUSKAnimNode_LayeredBoneBlend : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
	
	/**
	 * @brief The name of the bone that should be modified
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation",
		meta=(PinShownByDefault))
	FName Bone;

	/**
	 * @brief Whether to blend bone rotations in mesh space or in local space
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation",
		meta=(PinShownByDefault))
	bool bMeshSpaceRotationBlend;

	/**
	 * @brief Whether to blend bone scales in mesh space or in local space
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation",
		meta=(PinShownByDefault))
	bool bMeshSpaceScaleBlend;

	/**
	 * @brief Should we incorporate the per-bone blend weight of the root bone when lending root motion?
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation",
		meta=(PinShownByDefault))
	bool bBlendRootMotionBasedOnRootBone;

	/**
	 * @brief The source pose
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation")
	FPoseLink BasePose;

	/**
	 * @brief Each layer's blended pose
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Ultimate Starter Kit|Animation",
		meta=(BlueprintCompilerGeneratedDefaults))
	TArray<FPoseLink> BlendPoses;
	
	/**
	 * @brief Whether to use branch filters or a blend mask to specify an input pose per-bone influence
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation")
	EUSKLayeredBoneBlendMode BlendMode;

	/** 
	 * @brief The blend masks to use for our layer inputs. Allows the use of per-bone alphas
	 */
	UPROPERTY(EditAnywhere, EditFixedSize, Category = "Ultimate Starter Kit|Animation",
		meta=(UseAsBlendMask=true))
	TArray<UBlendProfile*> BlendMasks;

	/** 
	 * @brief Configuration for the parts of the skeleton to blend for each layer
	 */
	UPROPERTY(EditAnywhere, EditFixedSize, Category = "Ultimate Starter Kit|Animation")
	TArray<FInputBlendPose> LayerSetup;

	/**
	 * @brief The weights of each layer
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Ultimate Starter Kit|Animation",
		meta=(BlueprintCompilerGeneratedDefaults, PinShownByDefault))
	TArray<float> BlendWeights;

	/**
	 * @brief Defines how to blend the layers together
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation")
	TEnumAsByte<ECurveBlendOption::Type> CurveBlendOption;
	
	/**
 	 * @brief Max LOD that this node is allowed to run
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation",
		meta = (DisplayName = "LOD Threshold"))
	int LODThreshold;

	/**
	 * @brief Do we have a relevant pose?
	 */
	bool bHasRelevantPoses;

	/**
	 * @brief Create a new instance of the animation node
	 */
	FUSKAnimNode_LayeredBoneBlend();

	/**
	 * @brief Initialize the animation node
	 * @param Context The initialization context used during animation tree initialization
	 */
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;

	/**
	 * @brief Cache all bones that are required by this node
	 * @param Context The context used when RequiredBones array changed and cached bones indices have to be refreshed
	 */
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;

	/**
	 * @brief Update the animation node
	 * @param Context The update context used during animation tree update
	 */
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	/**
	 * @brief Evaluate the animation node
	 * @param Output The evaluation context used during animation tree evaluation
	 */
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;

	/**
	 * @brief Get the LOD threshold for this node
	 * @return The LOD threshold for this node
	 */
	virtual int GetLODThreshold() const override;

	/**
	 * @brief Add a pose
	 */
	void AddPose();

	/**
	 * @brief Remove a pose
	 * @param PoseIndex The index of the pose to remove
	 */
	void RemovePose(int PoseIndex);

	/**
	 * @brief Set the blend mask for the specified input pose
	 * @param InPoseIndex The index of the pose to update
	 * @param InBlendMask The blend mask to set
	 */
	void SetBlendMask(int InPoseIndex, UBlendProfile* InBlendMask);

	/**
	 * @brief Invalidate the cached per-bone blend weights from the skeleton
	 */
	void InvalidatePerBoneBlendWeights();

	/**
	 * @brief Invalidates the cached bone data so it is recalculated the next time this node is updated
	 */
	void InvalidateCachedBoneData();

	/**
	 * @brief Check whether per-bone blend weights are valid according to the skeleton
	 * @param InSkeleton The skeleton to check
	 * @return A boolean value indicating whether per-bone blend weights are valid according to the skeleton
	 */
	bool ArePerBoneBlendWeightsValid(const USkeleton* InSkeleton) const;

	/**
	 * @brief Rebuild cache per bone blend weights from the skeleton
	 * @param InSkeleton The skeleton to rebuild the per bone blend weights from
	 */
	void RebuildPerBoneBlendWeights(const USkeleton* InSkeleton);

protected:
	/**
	 * @brief Per-bone weights for the skeleton
	 */
	UPROPERTY()
	TArray<FPerBoneBlendWeight>	PerBoneBlendWeights;

	/**
	 * @brief GUID for the skeleton used to determine whether the PerBoneBlendWeights need rebuilding
	 */
	UPROPERTY()
	FGuid SkeletonGuid;

	/**
	 * @brief GUID for virtual bones used to determine whether the PerBoneBlendWeights need rebuilding
	 */
	UPROPERTY()
	FGuid VirtualBoneGuid;

	/**
	 * @brief The desired per-bone blend weights
	 */
	TArray<FPerBoneBlendWeight> DesiredBoneBlendWeights;

	/**
	 * @brief The current per-bone blend weights
	 */
	TArray<FPerBoneBlendWeight> CurrentBoneBlendWeights;

	/**
	 * @brief The curve indices for each pose
	 */
	TArray<uint8> CurvePoseSourceIndices;

	/**
	 * @brief Serial number of the required bones container
	 */
	int RequiredBonesSerialNumber;

private:
	/**
	 * @brief Was the bones initialized?
	 */
	bool bBonesInitialized;
	
	/**
	 * @brief Update cached data if required
	 * @param RequiredBones The required bones
	 * @param Skeleton A reference to the skeleton
	 */
	void UpdateCachedBoneData(const FBoneContainer& RequiredBones, const USkeleton* Skeleton);

	/**
	 * @brief Update the bone names
	 */
	void UpdateBoneName();
};