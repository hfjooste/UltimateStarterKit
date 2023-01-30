// Created by Henry Jooste

#pragma once

#include "USKGameInstance.h"
#include "USKBaseComponent.generated.h"

/**
 * @brief Base component that can save/load data using the game instance
 */
UCLASS()
class UUSKBaseComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	/**
	 * @brief A reference to the current UUSKGameInstance
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;

	/**
	 * @brief Overridable native event for when play begins for this component
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Load the data managed by this component
	 */
	virtual void LoadData();
};
