// Created by Henry Jooste

#include "InteractTrigger.h"

#include "USK/Character/USKCharacter.h"
#include "USK/Items/CollectableItem.h"
#include "USK/Widgets/InteractWidget.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void UInteractTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UInteractTrigger::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractTrigger::OnOverlapEnd);
}

/**
 * @brief Check if the actor can interact with the object
 * @param Actor The actor trying to interact with the object
 * @return A boolean value indicating if the actor can interact with the object
 */
bool UInteractTrigger::CanInteract_Implementation(AActor* Actor)
{
	return true;
}

/**
 * @brief Called when the actor interacts with the object
 * @param Actor The actor that interacted with the object
 */
void UInteractTrigger::OnInteracted(AActor* Actor)
{
	if (!IsValid(Actor) || !CanInteract(Actor))
	{
		return;
	}
	
	ACollectableItem* CollectableItem = dynamic_cast<ACollectableItem*>(GetOwner());
	if (IsValid(CollectableItem) && CollectableItem->CanCollectItem(Actor))
	{
		CollectableItem->CollectItem(Actor);
		return;
	}

	ReceiveOnInteracted(Actor);
}

/**
 * @brief Show the interact widget
 */
void UInteractTrigger::ShowWidget()
{
	if (IsValid(InteractWidgetClass))
	{
		InteractWidget = CreateWidget<UInteractWidget>(GetWorld(), InteractWidgetClass);
		InteractWidget->Show(BeforeText, AfterText);	
	}
}

/**
 * @brief Hide the interact widget
 */
void UInteractTrigger::HideWidget()
{
	if (IsValid(InteractWidget))
	{
		InteractWidget->Hide();
		InteractWidget = nullptr;
	}
}

/**
 * @brief Called when the actor interacts with the object
 * @param Actor The actor that interacted with the object
 */
void UInteractTrigger::ReceiveOnInteracted_Implementation(AActor* Actor) { }

/**
 * @brief Event when this component overlaps another actor
 * @param OverlappedComponent The component that triggered the event
 * @param OtherActor The other actor that caused the overlap event
 * @param OtherComp The other component that caused the overlap event
 * @param OtherBodyIndex The index of the other body that caused the overlap event
 * @param bFromSweep A boolean value indicating if the overlap event was caused by a sweep 
 * @param SweepResult The result of the sweep that caused the overlap event
 */
void UInteractTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(OtherActor);
	if (IsValid(Character))
	{
		Character->UpdateInteractTrigger(this);
	}
}

/**
 * @brief Event when this component stops overlapping another actor
 * @param OverlappedComponent The component that triggered the event
 * @param OtherActor The other actor that caused the overlap event
 * @param OtherComp The other component that caused the overlap event
 * @param OtherBodyIndex The index of the other body that caused the overlap event
 */
void UInteractTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(OtherActor);
	if (IsValid(Character) && Character->GetInteractTrigger() == this)
	{
		Character->UpdateInteractTrigger(nullptr);
	}
}