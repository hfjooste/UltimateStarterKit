// Created by Henry Jooste

#include "DialogueEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "Misc/Paths.h"

TSharedPtr<FSlateStyleSet> FDialogueEditorStyle::StyleSet = nullptr;

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

/**
 * @brief Initializes the Slate style set used by the Dialogue Editor.
 */
void FDialogueEditorStyle::Initialize()
{
if (StyleSet.IsValid())
	{
		return;
	}
	
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);

	StyleSet = MakeShareable(new FSlateStyleSet("DialogueEditorStyle"));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("Dialogue/Resources"));
	StyleSet->Set("DialogueEditor.AutoArrange", new IMAGE_BRUSH("AutoArrangeIcon", Icon40x40));
	StyleSet->Set("DialogueEditor.AutoArrange.Small", new IMAGE_BRUSH( "AutoArrangeIcon", Icon20x20 ) );
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

/**
 * @brief Shuts down the Slate style set used by the Dialogue Editor.
 */
void FDialogueEditorStyle::Shutdown()
{
	if (!StyleSet.IsValid())
	{
		return;
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	ensure(StyleSet.IsUnique());
	StyleSet.Reset();
}

/**
 * @brief Gets the name of the Slate style set used by the Dialogue Editor.
 * @return The name of the Slate style set.
 */
const FName& FDialogueEditorStyle::GetStyleSetName()
{
	return StyleSet->GetStyleSetName();
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT