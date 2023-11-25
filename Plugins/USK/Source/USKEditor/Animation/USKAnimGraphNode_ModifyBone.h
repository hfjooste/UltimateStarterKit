// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_ModifyBone.h"
#include "USK/Animation/USKAnimNode_ModifyBone.h"
#include "USKAnimGraphNode_ModifyBone.generated.h"

/**
 * @brief Animation graph node used to modify a bone
 */
UCLASS()
class USKEDITOR_API UUSKAnimGraphNode_ModifyBone : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_UCLASS_BODY()
	
	/**
	 * @brief The animation node used to modify the bone
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation")
	FUSKAnimNode_ModifyBone Node;

	/**
	 * @brief Get the node title
	 * @param TitleType The type of title displayed by the node
	 * @return The node title
	 */
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	/**
	 * @brief Get the category used by the node
	 * @return The category used by the node
	 */
	virtual FString GetNodeCategory() const override;

	/**
	 * @brief Get the tooltip text displayed by the node
	 * @return The tooltip text displayed by the node
	 */
	virtual FText GetTooltipText() const override;

protected:
	/**
	 * @brief Validate the animation node during compilation
	 * @param ForSkeleton The skeleton the node is being compiled for
	 * @param MessageLog The message log to output any errors/warnings to
	 */
	virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;

	/**
	 * @brief Get the editor mode used by the node
	 * @return The editor mode used by the node
	 */
	virtual FEditorModeID GetEditorMode() const override;

	/**
	 * @brief Copy the node data to the preview node
	 * @param InPreviewNode The preview node to copy the data to
	 */
	virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;

	/**
	 * @brief Copy the pin defaults to the node data
	 * @param InPin The pin to copy the defaults from
	 */
	virtual void CopyPinDefaultsToNodeData(UEdGraphPin* InPin) override;

	/**
	 * @brief Get the controller description
	 * @return The controller description
	 */
	virtual FText GetControllerDescription() const override;

	/**
	 * @brief Get the animation node
	 * @return A reference to the animation node
	 */
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override;

private:
	/**
	 * @brief The cached node titles
	 */
	FNodeTitleTextTable CachedNodeTitles;
};