// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USK/Dialogue/Dialogue.h"
#include "DialogueFactory.generated.h"

/**
 * @brief Factory class used to create new dialogue entries and transitions
 */
UCLASS()
class USKEDITOR_API UDialogueFactory : public UFactory
{
	GENERATED_BODY()

public:
	/**
	 * @brief The dialogue class to create
	 */
	UPROPERTY(EditAnywhere, Category = DataAsset)
	TSubclassOf<UDialogue> DialogueClass;
	
	/**
	 * @brief Create a new instance of the factory class
	 */
	UDialogueFactory();

	/**
	 * @brief Configure the properties of the class
	 * @return A boolean value indicating if the class was configured
	 */
	virtual bool ConfigureProperties() override;

	/**
	 * @brief Create a new dialogue
	 * @param Class The class to create
	 * @param InParent The parent of the newly created object
	 * @param Name The name of the newly created object
	 * @param Flags The object flags to apply to the new object
	 * @param Context The context used to create the new object
	 * @param Warn The context used for displaying modal warning messages
	 * @return A reference to the newly created object
	 */
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name,
	                                  EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
