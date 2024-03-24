// Created by Henry Jooste

#include "WorldTextLetterWidget.h"

#include "WorldTextWordWidget.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"

/**
 * @brief Initialize the letter
 * @param Word The parent world text word widget
 * @param Letter The letter to display
 */
void UWorldTextLetterWidget::InitializeLetter(UWorldTextWordWidget* Word, const FString& Letter)
{
	ParentWord = Word;
	TextBlock->SetText(FText::FromString(Letter));
}

/**
 * @brief Update the reference to the next letter in the word
 * @param Letter The next letter in the word
 */
void UWorldTextLetterWidget::UpdateNextLetter(UWorldTextLetterWidget* Letter)
{
	NextLetter = Letter;
}

/**
 * @brief Show the letter
 * @param Index The index of the letter in the word
 */
void UWorldTextLetterWidget::Show(const int Index)
{
	if (IsValid(NextLetter))
	{
		NextLetter->Show(Index + 1);
	}

	FTimerHandle TypeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TypeTimerHandle, [this]
	{
		if (IsValid(ShowAnimation))
		{
			PlayAnimation(ShowAnimation);
		}

		if (!IsValid(NextLetter) && IsValid(ParentWord))
		{
			ParentWord->ShowNextWord();
		}
	}, (Index + 1) * TypeDuration, false);	
}

/**
 * @brief Destroy the letter
 */
void UWorldTextLetterWidget::Destroy()
{
	if (IsValid(DestroyAnimation))
	{
		PlayAnimation(DestroyAnimation);
	}
}