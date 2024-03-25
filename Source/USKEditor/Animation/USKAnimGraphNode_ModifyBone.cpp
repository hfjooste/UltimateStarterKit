// Created by Henry Jooste

#include "USKAnimGraphNode_ModifyBone.h"
#include "AnimNodeEditModes.h"
#include "Kismet2/CompilerResultsLog.h"

/**
 * @brief Create a new instance of the animation node
 * @param ObjectInitializer The initializer used during the UObject creation
 */
UUSKAnimGraphNode_ModifyBone::UUSKAnimGraphNode_ModifyBone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) { }

/**
 * @brief Get the node title
 * @param TitleType The type of title displayed by the node
 * @return The node title
 */
FText UUSKAnimGraphNode_ModifyBone::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const FString Title = *FString::Format(TEXT("{0}\nBone: {1}"),
		{ GetControllerDescription().ToString(), Node.Bone.ToString() });
	CachedNodeTitles.SetCachedTitle(TitleType, FText::FromString(Title), this);	
	return CachedNodeTitles[TitleType];
}

/**
 * @brief Get the category used by the node
 * @return The category used by the node
 */
FString UUSKAnimGraphNode_ModifyBone::GetNodeCategory() const
{
	return "Ultimate Starter Kit";
}

/**
 * @brief Get the tooltip text displayed by the node
 * @return The tooltip text displayed by the node
 */
FText UUSKAnimGraphNode_ModifyBone::GetTooltipText() const
{
	return FText::FromString(
		"The Transform Bone node alters the transform - i.e. Translation, Rotation, or Scale - of the bone");
}

/**
 * @brief Validate the animation node during compilation
 * @param ForSkeleton The skeleton the node is being compiled for
 * @param MessageLog The message log to output any errors/warnings to
 */
void UUSKAnimGraphNode_ModifyBone::ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog)
{ 
	if (ForSkeleton && !ForSkeleton->HasAnyFlags(RF_NeedPostLoad))
	{
		if (ForSkeleton->GetReferenceSkeleton().FindBoneIndex(Node.BoneToModify.BoneName) == INDEX_NONE)
		{
			if (Node.BoneToModify.BoneName == NAME_None)
			{
				MessageLog.Warning(*FString("NoBoneSelectedToModify - You must pick a bone to modify"), this);
			}
			else
			{
				FFormatNamedArguments Args;
				Args.Add(TEXT("BoneName"), FText::FromName(Node.BoneToModify.BoneName));
				MessageLog.Warning(*FString("NoBoneSelectedToModify - Bone not found in Skeleton"), this);
			}
		}
	}

	if ((Node.TranslationMode == BMM_Ignore) && (Node.RotationMode == BMM_Ignore) && (Node.ScaleMode == BMM_Ignore))
	{
		MessageLog.Warning(*FString("NothingToModify - No components to modify selected"), this);
	}

	Super::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);
}

/**
 * @brief Get the editor mode used by the node
 * @return The editor mode used by the node
 */
FEditorModeID UUSKAnimGraphNode_ModifyBone::GetEditorMode() const
{
	return AnimNodeEditModes::ModifyBone;
}

/**
 * @brief Copy the node data to the preview node
 * @param InPreviewNode The preview node to copy the data to
 */
void UUSKAnimGraphNode_ModifyBone::CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode)
{
	FAnimNode_ModifyBone* ModifyBone = static_cast<FAnimNode_ModifyBone*>(InPreviewNode);
	
	ModifyBone->Translation = Node.Translation;
	ModifyBone->Rotation = Node.Rotation;
	ModifyBone->Scale = Node.Scale;

	ModifyBone->TranslationMode = Node.TranslationMode;
	ModifyBone->RotationMode = Node.RotationMode;
	ModifyBone->ScaleMode = Node.ScaleMode;

	ModifyBone->TranslationSpace = Node.TranslationSpace;
	ModifyBone->RotationSpace = Node.RotationSpace;
	ModifyBone->ScaleSpace = Node.ScaleSpace;
}

/**
 * @brief Copy the pin defaults to the node data
 * @param InPin The pin to copy the defaults from
 */
void UUSKAnimGraphNode_ModifyBone::CopyPinDefaultsToNodeData(UEdGraphPin* InPin)
{
	if (InPin->GetName() == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Translation))
	{
		GetDefaultValue(GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Translation), Node.Translation);
	}
	else if (InPin->GetName() == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Rotation))
	{
		GetDefaultValue(GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Rotation), Node.Rotation);
	}
	else if (InPin->GetName() == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Scale))
	{
		GetDefaultValue(GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_ModifyBone, Scale), Node.Scale);
	}
}

/**
 * @brief Get the controller description
 * @return The controller description
 */
FText UUSKAnimGraphNode_ModifyBone::GetControllerDescription() const
{
	return FText::FromString("[USK] Transform Bone");
}

/**
 * @brief Get the animation node
 * @return A reference to the animation node
 */
const FAnimNode_SkeletalControlBase* UUSKAnimGraphNode_ModifyBone::GetNode() const
{
	return &Node;
}