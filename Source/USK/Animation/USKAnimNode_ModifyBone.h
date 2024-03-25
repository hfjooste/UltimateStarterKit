// Created by Henry Jooste

#pragma once

#include "BoneControllers/AnimNode_ModifyBone.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "USKAnimNode_ModifyBone.generated.h"

/**
 * @brief Animation node used to modify a bone
 */
USTRUCT(BlueprintInternalUseOnly)
struct USK_API FUSKAnimNode_ModifyBone : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The name of the bone that should be modified
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation",
		meta=(PinShownByDefault))
	FName Bone;

	/**
	 * @brief The bone that should be modified
	 */
	FBoneReference BoneToModify;

	/**
	 * @brief New translation of bone to apply
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation|Translation",
		meta=(PinShownByDefault))
	FVector Translation;

	/**
	 * @brief Whether and how to modify the translation of the bone
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Translation")
	TEnumAsByte<EBoneModificationMode> TranslationMode;

	/**
	 * @brief Reference frame to apply translation in
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Translation")
	TEnumAsByte<EBoneControlSpace> TranslationSpace;

	/**
	 * @brief New rotation of bone to apply
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation|Rotation",
		meta=(PinShownByDefault))
	FRotator Rotation;

	/**
	 * @brief Whether and how to modify the translation of the bone
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Rotation")
	TEnumAsByte<EBoneModificationMode> RotationMode;

	/**
	 * @brief Reference frame to apply rotation in
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Rotation")
	TEnumAsByte<EBoneControlSpace> RotationSpace;

	/**
	 * @brief New scale of bone to apply
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Animation|Scale",
		meta=(PinShownByDefault))
	FVector Scale;

	/**
	 * @brief Whether and how to modify the translation of this bone
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Scale")
	TEnumAsByte<EBoneModificationMode> ScaleMode;

	/**
	 * @brief Reference frame to apply scale in
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation|Scale")
	TEnumAsByte<EBoneControlSpace> ScaleSpace;

	/**
	 * @brief Create a new instance of the animation node
	 */
	FUSKAnimNode_ModifyBone();

	/**
	 * @brief Evaluate the skeletal control
	 * @param Output The output pose
	 * @param OutBoneTransforms The output bone transforms
	 */
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;

	/**
	 * @brief Check if the node is valid to evaluate
	 * @param Skeleton The skeleton to check
	 * @param RequiredBones The required bones to check
	 * @return A boolean value indicating whether the node is valid to evaluate
	 */
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;

private:
	/**
	 * @brief Initialize the bone references
	 * @param RequiredBones The required bones
	 */
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
};
