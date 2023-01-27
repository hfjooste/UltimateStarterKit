// Created by Henry Jooste

#pragma once

#include "CurrencyManagerComponent.h"
#include "GameFramework/Actor.h"
#include "USK/Data/SaveManager.h"
#include "CurrencyManager.generated.h"

/**
 * @brief An actor responsible for managing all the currency manager components
 */
UCLASS()
class USK_API ACurrencyManager : public AActor
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A reference to the save manager used to automatically save currency values
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
	ASaveManager* SaveManager;
	
	/**
	 * @brief Create a new instance of the currency manager class
	 */
	ACurrencyManager();
	
	/**
	 * @brief Get a reference to the currency manager component responsible for managing the coins
	 * @return A reference coin currency manager
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	UCurrencyManagerComponent* GetCoinManager() const;

	/**
	 * @brief Get a reference to the currency manager component responsible for managing the gems
	 * @return A reference gem currency manager
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	UCurrencyManagerComponent* GetGemManager() const;
	
	/**
	 * @brief Add a custom currency manager component
	 * @param ID The unique ID associated with the currency manager component
	 * @return A reference to the new currency manager component
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	UCurrencyManagerComponent* AddManager(FString ID);
	
	/**
	 * @brief Get a reference to a custom currency manager component
	 * @param ID The unique ID associated with the currency manager component
	 * @return A reference to the custom currency manager component
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	UCurrencyManagerComponent* GetManager(FString ID);

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:	
	/**
	 * @brief A reference to the currency manager component responsible for managing the coins 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCurrencyManagerComponent* CoinManager;

	/**
	 * @brief A reference to the currency manager component responsible for managing the gems 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCurrencyManagerComponent* GemManager;
	
	/**
	 * @brief A map of all the custom currency manager components
	 */
	UPROPERTY() TMap<FString, UCurrencyManagerComponent*> CustomManagers;

	/**
	 * @brief Initialize the currency manager components
	 */
	void Initialize();
};