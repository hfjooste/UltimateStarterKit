// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateColor.h"
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
	 * @brief The portrait image for the dialogue participant
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant")
	UTexture2D* PortraitImage;

	/**
	 * @brief The color used to represent the dialogue participant
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant")
	FLinearColor Color = FLinearColor::Black;

	/**
	 * @brief Should a custom border color be used for the portrait image instead of the participant color?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant")
	bool bCustomPortraitImageBorderColor;

	/**
	 * @brief The custom portrait image border color
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Participant",
		meta=(EditCondition="bCustomPortraitImageBorderColor", EditConditionHides))
	FSlateColor PortraitImageBorderColor = FSlateColor(FLinearColor::Black);
};