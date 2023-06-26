// Created by Henry Jooste

#include "DialogueManager.h"

#include "Dialogue.h"
#include "DialogueWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the DialogueManager class 
 */
ADialogueManager::ADialogueManager()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	if (PlayOnStart)
	{
		PlayDialogue();
	}
}

/**
 * @brief Tell client that the Pawn is begin restarted
 */
void ADialogueManager::PawnClientRestart()
{
	Super::PawnClientRestart();

	USK_LOG_TRACE("Adding input mapping context");
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->RemoveMappingContext(InputMappingContext);
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

/**
 * @brief Allows a Pawn to set up custom input bindings
 * @param PlayerInputComponent The component that enables an Actor to bind various forms of input events
 */
void ADialogueManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	USK_LOG_TRACE("Setting up input bindings");

	UEnhancedInputComponent* EnhancedInput = dynamic_cast<UEnhancedInputComponent*>(PlayerInputComponent);
	EnhancedInput->BindAction(SkipAction, ETriggerEvent::Started, this, &ADialogueManager::SkipEntry);
}

/**
 * @brief Play the dialogue
 */
void ADialogueManager::PlayDialogue()
{
	if (Dialogue == nullptr)
	{
		USK_LOG_ERROR("Unable to play dialogue. Dialogue is nullptr");
		return;
	}

	if (DialogueWidgetClass == nullptr)
	{
		USK_LOG_ERROR("Unable to play dialogue. Dialogue widget class is nullptr");
		return;
	}

	USK_LOG_INFO("Playing dialogue");
	if (Dialogue->RootEntries.Num() == 0)
	{
		USK_LOG_ERROR("No root entries");
		return;
	}

	DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
	if (!IsValid(DialogueWidget))
	{
		USK_LOG_ERROR("Unable to create dialogue widget");
		return;
	}

	DialogueWidget->OnChoiceSelected.AddDynamic(this, &ADialogueManager::OnChoiceSelected);

	DialogueWidget->AddToViewport();
	UpdateCurrentEntry(Dialogue->RootEntries[0]);
}

/**
 * @brief Skip the current entry in the dialogue
 */
void ADialogueManager::SkipEntry()
{
	if (!IsValid(DialogueWidget) || !IsValid(CurrentEntry))
	{
		USK_LOG_WARNING("Dialogue has not been started");
		return;
	}

	if (DialogueWidget->SkipEntry())
	{
		AudioComponent->Stop();
		UAudioUtils::PlaySound2D(GetWorld(), SkipSFX);
		return;
	}

	if (CurrentEntry->IsLeafNode())
	{
		USK_LOG_INFO("Dialogue ended");
		AudioComponent->Stop();
		OnDialogueEntryEnded.Broadcast(CurrentEntry->Id);
		OnDialogueEnded.Broadcast(CurrentEntry->Id);
		return;
	}

	if (CurrentEntry->Transition != EDialogueTransitionType::Auto)
	{
		USK_LOG_INFO("Unable to auto advance to next entry");
		return;
	}

	TArray<UDialogueEntry*> ChildEntries;
	CurrentEntry->Edges.GenerateKeyArray(ChildEntries);
	UpdateCurrentEntry(ChildEntries[0]);
	UAudioUtils::PlaySound2D(GetWorld(), AdvanceSFX);
}

/**
 * @brief Update the current dialogue entry
 * @param NewEntry The new dialogue entry
 */
void ADialogueManager::UpdateCurrentEntry(UDialogueEntry* NewEntry)
{
	if (IsValid(CurrentEntry))
	{
		OnDialogueEntryEnded.Broadcast(CurrentEntry->Id);	
	}
	
	CurrentEntry = NewEntry;	
	DialogueWidget->UpdateEntry(NewEntry);
	OnDialogueEntryStarted.Broadcast(NewEntry->Id);
	AudioComponent->Stop();

	if (IsValid(NewEntry->Audio))
	{
		AudioComponent->SetSound(NewEntry->Audio);
		AudioComponent->Play();	
	}
}

/**
 * @brief Update the dialogue after a choice has been selected
 * @param Index The index of the choice that was selected
 */
void ADialogueManager::OnChoiceSelected(int Index)
{
	if (!IsValid(CurrentEntry))
	{
		USK_LOG_ERROR("Current entry is not valid");
		return;
	}

	if (CurrentEntry->Transition != EDialogueTransitionType::Choice)
	{
		USK_LOG_WARNING("Incorrect transition type");
		return;
	}

	if (Index >= CurrentEntry->Edges.Num())
	{
		USK_LOG_ERROR("Index is out of range");
		return;
	}

	TArray<UDialogueEntry*> ChildEntries;
	CurrentEntry->Edges.GenerateKeyArray(ChildEntries);
	UpdateCurrentEntry(ChildEntries[Index]);
	UAudioUtils::PlaySound2D(GetWorld(), AdvanceSFX);
}