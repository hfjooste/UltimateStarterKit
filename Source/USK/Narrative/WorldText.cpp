// Created by Henry Jooste

#include "WorldText.h"

#include "WorldTextWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "USK/Character/USKCharacter.h"

/**
 * @brief Constructor for the world text actor
 */
AWorldText::AWorldText()
{
	Container = CreateDefaultSubobject<USceneComponent>(TEXT("Container"));
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TextWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text Widget"));

	TriggerComponent->SetupAttachment(Container);
	TextWidgetComponent->SetupAttachment(Container);
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AWorldText::BeginPlay()
{
	Super::BeginPlay();
	
	UWorldTextWidget* Widget = dynamic_cast<UWorldTextWidget*>(TextWidgetComponent->GetWidget());
	if (IsValid(Widget))
	{
		Widget->OnDestroyed.AddDynamic(this, &AWorldText::OnDestroyed);
	}
}

/**
 * @brief Event when this actor overlaps another actor
 * @param OtherActor The other actor that caused the overlap event
 */
void AWorldText::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (CanActorTriggerText(OtherActor))
	{
		Activate();
	}
}

/**
 * @brief Activate the text
 */
void AWorldText::Activate()
{
	if (bIsDisabled)
	{
		return;
	}

	UWorldTextWidget* Widget = dynamic_cast<UWorldTextWidget*>(TextWidgetComponent->GetWidget());
	if (!IsValid(Widget))
	{
		return;
	}

	bIsDisabled = true;
	Widget->InitializeWidget(WordWidgetClass, LetterWidgetClass);
	Widget->Show(Text, Sound, bPlaySoundAtActor ? this : nullptr);
}

/**
 * @brief Can the actor trigger the text?
 * @param Actor The actor to check
 * @return A boolean value indicating if the actor can trigger the text
 */
bool AWorldText::CanActorTriggerText_Implementation(const AActor* Actor) const
{
	return IsValid(Actor) && Actor->IsA(AUSKCharacter::StaticClass());
}

/**
 * @brief Called after the world text widget is destroyed
 */
void AWorldText::OnDestroyed()
{
	for (AWorldText* WorldText : ActivateOnDestroy)
	{
		if (IsValid(WorldText))
		{
			WorldText->Activate();
		}
	}

	for (AWorldText* WorldText : EnableOnDestroy)
	{
		if (IsValid(WorldText))
		{
			WorldText->bIsDisabled = false;
		}
	}

	Destroy();
}
