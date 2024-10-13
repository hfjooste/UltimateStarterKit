// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExecutionData.generated.h"

/**
 * @brief The data used to describe an execution sequence
 */
UCLASS()
class USK_API UExecutionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The animation montage to play on the player character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Execution")
	UAnimMontage* PlayerAnimation;

	/**
	 * @brief The animation montage to play on the enemy character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Execution")
	UAnimMontage* EnemyAnimation;

	/**
	 * @brief The forward offset from the enemy location that is applied to the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Execution")
	float PlayerForwardOffset;

	/**
	 * @brief The right offset from the enemy location that is applied to the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Execution")
	float PlayerRightOffset;

	/**
	 * @brief The up offset from the enemy location that is applied to the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Execution")
	float PlayerUpOffset;
};
