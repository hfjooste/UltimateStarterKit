// Created by Henry Jooste

#include "WorldTextWidget.h"

#include "WorldTextWordWidget.h"
#include "Kismet/KismetStringLibrary.h"
#include "USK/Audio/AudioUtils.h"
#include "TimerManager.h"

/**
 * @brief Initialize the widget
 * @param WordClass The world word widget class
 * @param LetterClass The world letter widget class
 */
void UWorldTextWidget::InitializeWidget(const TSubclassOf<UWorldTextWordWidget> WordClass,
	const TSubclassOf<UWorldTextLetterWidget> LetterClass)
{
	WordWidgetClass = WordClass;
	LetterWidgetClass = LetterClass;
}

/**
 * @brief Show the text in the widget
 * @param Text The text to display
 * @param Sound The sound to play when displaying the text
 * @param PlaySoundAtActor The actor to play the sound at
 */
void UWorldTextWidget::Show(const FText& Text, USoundBase* Sound, AActor* PlaySoundAtActor)
{
	UpdateText(Text);
	if (IsValid(PlaySoundAtActor))
	{
		UAudioUtils::PlaySound(PlaySoundAtActor, Sound);
	}
	else
	{
		UAudioUtils::PlaySound2D(GetWorld(), Sound);
	}

	UWorldTextWordWidget* Word = dynamic_cast<UWorldTextWordWidget*>(Container->GetChildAt(0));
	if (IsValid(Word))
	{
		Word->Show();
	}
}

/**
 * @brief Destroy the text widget
 */
void UWorldTextWidget::Destroy() const
{
	if (DestroyTextDelay <= 0.0f)
	{
		DestroyAfterDelay();
		return;
	}
	
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]
	{
		DestroyAfterDelay();
	}, DestroyTextDelay, false);
}

/**
 * @brief Get the world word widget class
 * @return The world word widget class
 */
TSubclassOf<UWorldTextWordWidget> UWorldTextWidget::GetWordWidgetClass() const
{
	return WordWidgetClass;
}

/**
 * @brief Get the world letter widget class
 * @return The world letter widget class
 */
TSubclassOf<UWorldTextLetterWidget> UWorldTextWidget::GetLetterWidgetClass() const
{
	return LetterWidgetClass;
}

/**
 * @brief Update the text displayed in the widget
 * @param Text The text to display
 */
void UWorldTextWidget::UpdateText(const FText& Text)
{
	TArray<FString> Words = UKismetStringLibrary::ParseIntoArray(Text.ToString(), " ");
	for (int Index = 0; Index < Words.Num(); Index++)
	{
		UWorldTextWordWidget* Word = CreateWidget<UWorldTextWordWidget>(GetWorld(), GetWordWidgetClass());
		if (IsValid(Word))
		{
			Container->AddChild(Word);
			Word->InitializeWord(this, Words[Index].Append(" "));
		}
	}

	for (int Index = 0; Index < Container->GetChildrenCount() - 1; Index++)
	{
		UWorldTextWordWidget* Word = dynamic_cast<UWorldTextWordWidget*>(Container->GetChildAt(Index));
		UWorldTextWordWidget* NextWord = dynamic_cast<UWorldTextWordWidget*>(Container->GetChildAt(Index + 1));
		if (IsValid(Word) && IsValid(NextWord))
		{
			Word->UpdateNextWord(NextWord);
		}
	}
}

/**
 * @brief Destroy the text widget after a delay
 */
void UWorldTextWidget::DestroyAfterDelay() const
{
	TArray<UWidget*> Children = Container->GetAllChildren();
	for (UWidget* Child : Children)
	{
		const UWorldTextWordWidget* Word = dynamic_cast<UWorldTextWordWidget*>(Child);
		if (IsValid(Word))
		{
			Word->Destroy();
		}
	}

	if (DestroyActorDelay <= 0.0f)
	{
		OnDestroyed.Broadcast();
		return;
	}

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]
	{
		OnDestroyed.Broadcast();
	}, DestroyActorDelay, false);
}