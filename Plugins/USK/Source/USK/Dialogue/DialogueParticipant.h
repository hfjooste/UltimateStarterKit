// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueParticipant.generated.h"

/**
 * @brief A participant in the dialogue
 */
UCLASS()
class USK_API UDialogueParticipant : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief The name of the dialogue participant
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant")
	FText Name;

	/**
	 * @brief The color used to represent the dialogue participant
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant")
	FLinearColor Color = FLinearColor::Black;
};