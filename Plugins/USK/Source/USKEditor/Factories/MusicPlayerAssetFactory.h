// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Audio/MusicPlayer.h"
#include "MusicPlayerAssetFactory.generated.h"

/**
 * @brief Factory class used to create a music player
 */
UCLASS()
class USKEDITOR_API UMusicPlayerAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UMusicPlayerAssetFactory() { SupportedClass = AMusicPlayer::StaticClass(); }
};
