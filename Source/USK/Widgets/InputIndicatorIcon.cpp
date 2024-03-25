// Created by Henry Jooste

#include "InputIndicatorIcon.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "USK/Logger/Log.h"

/**
 * @brief Update the icon
 * @param Size The size of the image
 * @param Icon The new icon
 */
void UInputIndicatorIcon::UpdateIcon(const float Size, UTexture2D* Icon) const
{
	USK_LOG_TRACE("Updating icon");
	Container->SetWidthOverride(Size);
	Container->SetHeightOverride(Size);
	Image->SetBrushFromTexture(Icon);
}