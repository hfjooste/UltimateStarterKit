// Created by Henry Jooste

#include "USKAnimGraphNode_LayeredBoneBlend.h"
#include "ToolMenus.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ScopedTransaction.h"
#include "AnimNodes/AnimNode_LayeredBoneBlend.h"
#include "Kismet2/CompilerResultsLog.h"

/**
 * @brief Create a new instance of the animation node
 * @param ObjectInitializer The initializer used during the UObject creation
 */
UUSKAnimGraphNode_LayeredBoneBlend::UUSKAnimGraphNode_LayeredBoneBlend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Node.AddPose();
}

/**
 * @brief Perform any object-specific cleanup required immediately after loading an object
 */
void UUSKAnimGraphNode_LayeredBoneBlend::PostLoad()
{
	Super::PostLoad();

#if ENGINE_MAJOR_VERSION >= 5
	if (Node.BlendMode != EUSKLayeredBoneBlendMode::BlendMask)
	{
		return;
	}

	const int NumBlendMasks = Node.BlendMasks.Num();
    for (int MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
    {
    	UBlendProfile* BlendMask = Node.BlendMasks[MaskIndex];
    	if (IsValid(BlendMask))
    	{
    		BlendMask->ConditionalPostLoad();
    	}
    }
#endif
}

/**
 * @brief Get the node title
 * @param TitleType The type of title displayed by the node
 * @return The node title
 */
FText UUSKAnimGraphNode_LayeredBoneBlend::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("[USK] Layered Bone Blend");
}

/**
 * @brief Get the category used by the node
 * @return The category used by the node
 */
FString UUSKAnimGraphNode_LayeredBoneBlend::GetNodeCategory() const
{
	return "Ultimate Starter Kit";
}

/**
 * @brief Get the tooltip text displayed by the node
 * @return The tooltip text displayed by the node
 */
FText UUSKAnimGraphNode_LayeredBoneBlend::GetTooltipText() const
{
	return FText::FromString("Layered blend per bone");
}

/**
 * @brief Called when a property on this object has been modified externally
 * @param PropertyChangedEvent The event containing information about the property that was changed
 */
void UUSKAnimGraphNode_LayeredBoneBlend::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
#if ENGINE_MAJOR_VERSION >= 5
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_LayeredBoneBlend, BlendMode))
	{
		FScopedTransaction Transaction(FText::FromString("USK_ChangeBlendMode"));
		Modify();

		const int NumPoses = Node.BlendPoses.Num();
		if (Node.BlendMode == EUSKLayeredBoneBlendMode::BlendMask)
		{
			Node.LayerSetup.Reset();
			Node.BlendMasks.SetNum(NumPoses);
		}
		else
		{
			Node.BlendMasks.Reset();
			Node.LayerSetup.SetNum(NumPoses);
		}

		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
#endif

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

/**
 * @brief Validate the animation node during compilation
 * @param ForSkeleton The skeleton the node is being compiled for
 * @param MessageLog The message log to output any errors/warnings to
 */
void UUSKAnimGraphNode_LayeredBoneBlend::ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton,
	FCompilerResultsLog& MessageLog)
{
	UAnimGraphNode_Base::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);
	
#if ENGINE_MAJOR_VERSION >= 5
	bool bCompilationError = false;
	if (Node.BlendMode == EUSKLayeredBoneBlendMode::BlendMask)
	{
		const int NumBlendMasks = Node.BlendMasks.Num();
		for (int MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			const UBlendProfile* BlendMask = Node.BlendMasks[MaskIndex];
			if (!IsValid(BlendMask) && !GetAnimBlueprint()->bIsTemplate)
			{
				MessageLog.Error(*FString("LayeredBlendNullMask - Null BlendMask for Blend Pose"), this);
				bCompilationError = true;
			}
			
			if (IsValid(BlendMask) && BlendMask->Mode != EBlendProfileMode::BlendMask)
			{
				MessageLog.Error(*FString("LayeredBlendProfileModeError - Using BlendProfile without a BlendMask mode"), this);
				bCompilationError = true;
			}
		}
	}
	
	if (bCompilationError)
	{
		return;
	}
#endif

 	if (!Node.ArePerBoneBlendWeightsValid(ForSkeleton))
 	{
 		Node.RebuildPerBoneBlendWeights(ForSkeleton);
 	}
}

/**
 * @brief Preload required assets including those referenced on pins
 */
void UUSKAnimGraphNode_LayeredBoneBlend::PreloadRequiredAssets()
{
#if ENGINE_MAJOR_VERSION >= 5
	if (Node.BlendMode == EUSKLayeredBoneBlendMode::BlendMask)
	{
		const int NumBlendMasks = Node.BlendMasks.Num();
		for (int MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			UBlendProfile* BlendMask = Node.BlendMasks[MaskIndex];
			PreloadObject(BlendMask);
		}
	}
#endif

	Super::PreloadRequiredAssets();
}