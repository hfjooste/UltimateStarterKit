// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**
* @brief Provides a static interface for initializing and shutting down the Slate style set used by the Dialogue Editor
 */
class FDialogueEditorStyle
{
public:
	/**
	 * @brief Initializes the Slate style set used by the Dialogue Editor.
	 */
	static void Initialize();
	
	/**
	 * @brief Shuts down the Slate style set used by the Dialogue Editor.
	 */
	static void Shutdown();	

	/**
	 * @brief Gets the name of the Slate style set used by the Dialogue Editor.
	 * @return The name of the Slate style set.
	 */
	static const FName& GetStyleSetName();

private:
	/**
	 * @brief A shared pointer to the Slate style set used by the Dialogue Editor.
	 */
	static TSharedPtr<FSlateStyleSet> StyleSet;
};