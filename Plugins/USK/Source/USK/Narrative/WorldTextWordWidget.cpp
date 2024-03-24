// Created by Henry Jooste

#include "WorldTextWordWidget.h"

#include "WorldTextWidget.h"
#include "WorldTextLetterWidget.h"

/**
 * @brief Initialize the word
 * @param Text The parent world text widget
 * @param Word The word to display
 */
void UWorldTextWordWidget::InitializeWord(UWorldTextWidget* Text, FString Word)
{
	if (!IsValid(Text))
	{
		return;
	}
	
	ParentText = Text;
	TArray<wchar_t> Characters = Word.GetCharArray();

	for (int Index = 0; Index < Characters.Num(); Index++)
	{
		UWorldTextLetterWidget* Letter = CreateWidget<UWorldTextLetterWidget>(GetWorld(),
			ParentText->GetLetterWidgetClass());
		if (IsValid(Letter))
		{
			Letter->InitializeLetter(this, FString(1, &Characters[Index]));
			Container->AddChild(Letter);
		}
	}

	for (int Index = 0; Index < Container->GetChildrenCount() - 1; Index++)
	{
		UWorldTextLetterWidget* Letter = dynamic_cast<UWorldTextLetterWidget*>(Container->GetChildAt(Index));
		UWorldTextLetterWidget* NextLetter = dynamic_cast<UWorldTextLetterWidget*>(Container->GetChildAt(Index + 1));
		if (IsValid(Letter) && IsValid(NextLetter))
		{
			Letter->UpdateNextLetter(NextLetter);
		}
	}
}

/**
 * @brief Update the reference to the next word in the text
 * @param Word The next word in the text
 */
void UWorldTextWordWidget::UpdateNextWord(UWorldTextWordWidget* Word)
{
	NextWord = Word;
}

/**
 * @brief Show the word
 */
void UWorldTextWordWidget::Show()
{
	UWorldTextLetterWidget* Letter = dynamic_cast<UWorldTextLetterWidget*>(Container->GetChildAt(0));
	if (IsValid(Letter))
	{
		Letter->Show(0);
	}
}

/**
 * @brief Show the next word
 */
void UWorldTextWordWidget::ShowNextWord()
{
	if (IsValid(NextWord))
	{
		NextWord->Show();
		return;
	}

	if (IsValid(ParentText))
	{
		ParentText->Destroy();
	}
}

/**
 * @brief Destroy the word widget
 */
void UWorldTextWordWidget::Destroy() const
{
	TArray<UWidget*> Children = Container->GetAllChildren();
	for (int Index = 0; Index < Children.Num(); Index++)
	{
		UWorldTextLetterWidget* Letter = dynamic_cast<UWorldTextLetterWidget*>(Children[Index]);
		if (IsValid(Letter))
		{
			Letter->Destroy();
		}
	}
}
