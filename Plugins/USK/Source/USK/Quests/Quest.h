// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"

/**
 * @brief The information about a specific quest
 */
UCLASS(BlueprintType)
class USK_API UQuest : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief The name of the quest
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	FText Name;

	/**
	 * @brief The ID of the quest
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	FGuid Id = FGuid::NewGuid();

	/**
	 * @brief The points of the quest
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	TArray<FText> Points;
};
