// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimGraphNode_BlendListBase.h"
#include "USK/Animation/USKAnimNode_LayeredBoneBlend.h"
#include "USKAnimGraphNode_LayeredBoneBlend.generated.h"

/**
 * @brief Animation graph node used to blend multiple poses together
 */
UCLASS()
class USKEDITOR_API UUSKAnimGraphNode_LayeredBoneBlend : public UAnimGraphNode_BlendListBase
{
	GENERATED_UCLASS_BODY()

	/**
	 * @brief The animation node used to blend multiple poses together
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Animation")
	FUSKAnimNode_LayeredBoneBlend Node;

	/**
	 * @brief Perform any object-specific cleanup required immediately after loading an object
	 */
	virtual void PostLoad() override;

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
	 * @brief Called when a property on this object has been modified externally
	 * @param PropertyChangedEvent The event containing information about the property that was changed
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * @brief Validate the animation node during compilation
	 * @param ForSkeleton The skeleton the node is being compiled for
	 * @param MessageLog The message log to output any errors/warnings to
	 */
	virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;

	/**
	 * @brief Preload required assets including those referenced on pins
	 */
	virtual void PreloadRequiredAssets() override;
};
