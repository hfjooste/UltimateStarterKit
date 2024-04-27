// Created by Henry Jooste

#include "AttractComponent.h"

#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "InteractTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "USK/Items/CollectableItem.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of UAttractComponent
 */
UAttractComponent::UAttractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void UAttractComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UAttractComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UAttractComponent::OnOverlapEnd);
	
	Item = dynamic_cast<ACollectableItem*>(GetOwner());
	if (!IsValid(Item))
	{
		USK_LOG_ERROR("Attract components can only be used on collectable items");
		return;
	}

	if (Item->GetComponentByClass(UInteractTrigger::StaticClass()))
	{
		USK_LOG_ERROR("Attract components cannot be used on items with an interact trigger");
		Item = nullptr;
	}
}

/**
 * @brief Function called every frame on this ActorComponent
 * @param DeltaTime The time since the last tick
 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
 * @param ThisTickFunction Internal tick function struct that caused this to run
 */
void UAttractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsValid(Player) || !IsValid(Item) || !Item->CanCollectItem(Player))
	{
		return;
	}

	const FVector CurrentLocation = Item->GetActorLocation();
	FVector TargetLocation = Player->GetActorLocation();
	TargetLocation.Z = CurrentLocation.Z;

	if (UKismetMathLibrary::Vector_Distance(CurrentLocation, TargetLocation) <= CollectDistance)
	{
		Item->CollectItem(Player);
		Player = nullptr;
		return;
	}
	
	Item->SetActorLocation(UKismetMathLibrary::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, AttractSpeed));
}

/**
 * @brief Event when this component overlaps another actor
 * @param OverlappedComponent The component that triggered the event
 * @param OtherActor The other actor that caused the overlap event
 * @param OtherComp The other component that caused the overlap event
 * @param OtherBodyIndex The index of the other body that caused the overlap event
 * @param bFromSweep A boolean value indicating if the overlap event was caused by a sweep 
 * @param SweepResult The result of the sweep that caused the overlap event
 */
void UAttractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OtherActor == PlayerPawn)
	{
		Player = PlayerPawn;
	}
}

/**
 * @brief Event when this component stops overlapping another actor
 * @param OverlappedComponent The component that triggered the event
 * @param OtherActor The other actor that caused the overlap event
 * @param OtherComp The other component that caused the overlap event
 * @param OtherBodyIndex The index of the other body that caused the overlap event
 */
void UAttractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player)
	{
		Player = nullptr;
	}
}
