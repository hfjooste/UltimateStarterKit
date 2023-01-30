// Created by Henry Jooste

#include "USKBaseComponent.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Overridable native event for when play begins for this component
 */
void UUSKBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);

	LoadData();
	if (GameInstance != nullptr)
	{
		GameInstance->OnDataLoadedEvent.AddDynamic(this, &UUSKBaseComponent::LoadData);
	}
}

/**
 * @brief Load the data managed by this component
 */
void UUSKBaseComponent::LoadData() { }