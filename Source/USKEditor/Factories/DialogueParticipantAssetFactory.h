// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USKDataAssetFactory.h"
#include "USK/Dialogue/DialogueParticipant.h"
#include "DialogueParticipantAssetFactory.generated.h"

/**
 * @brief Factory class used to create a dialogue participant
 */
UCLASS()
class USKEDITOR_API UDialogueParticipantAssetFactory : public UUSKDataAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UDialogueParticipantAssetFactory()
	{
		DataAssetClass = UDialogueParticipant::StaticClass();
		SupportedClass = UDialogueParticipant::StaticClass();
	}
};
