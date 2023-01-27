// Created by Henry Jooste

#include "CurrencyManager.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the currency manager class
 */
ACurrencyManager::ACurrencyManager()
{
	CoinManager = CreateDefaultSubobject<UCurrencyManagerComponent>(TEXT("Coin Manager"));
	GemManager = CreateDefaultSubobject<UCurrencyManagerComponent>(TEXT("Gem Manager"));	
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void ACurrencyManager::BeginPlay()
{
	Super::BeginPlay();

	CoinManager->ID = "USK_CURRENCY_COINS";
	CoinManager->SaveManager = SaveManager;

	GemManager->ID = "USK_CURRENCY_GEMS";
	GemManager->SaveManager = SaveManager;

	Initialize();
	if (SaveManager != nullptr)
	{
		SaveManager->AddOnDataLoadedEventBinding(this, &ACurrencyManager::Initialize);
	}
}

/**
 * @brief Get a reference to the currency manager component responsible for managing the coins
 * @return A reference coin currency manager
 */
UCurrencyManagerComponent* ACurrencyManager::GetCoinManager() const
{
	return CoinManager;
}

/**
 * @brief Get a reference to the currency manager component responsible for managing the gems
 * @return A reference gem currency manager
 */
UCurrencyManagerComponent* ACurrencyManager::GetGemManager() const
{
	return GemManager;
}

/**
 * @brief Add a custom currency manager component
 * @param ID The unique ID associated with the currency manager component
 * @return A reference to the new currency manager component
 */
UCurrencyManagerComponent* ACurrencyManager::AddManager(FString ID)
{
	UCurrencyManagerComponent* ExistingManager = GetManager(ID);
	if (ExistingManager != nullptr)
	{
		ULog::Warning("CurrencyManager::AddManager",
			FString("Currency Manager already found with the same ID (").Append(ID).Append(")"));
		return ExistingManager;
	}

	UCurrencyManagerComponent* NewManager = NewObject<UCurrencyManagerComponent>();
	NewManager->ID = ID;
	NewManager->SaveManager = SaveManager;
	NewManager->LoadSavedCurrency();
	CustomManagers.Add(ID, NewManager);

	ULog::Info("CurrencyManager::AddManager",
		FString("Currency Manager added (").Append(ID).Append(")"));
	return NewManager;
}

/**
 * @brief Get a reference to a custom currency manager component
 * @param ID The unique ID associated with the currency manager component
 * @return A reference to the custom currency manager component
 */
UCurrencyManagerComponent* ACurrencyManager::GetManager(FString ID)
{
	if (CustomManagers.Contains(ID))
	{
		return CustomManagers[ID];
	}

	ULog::Warning("CurrencyManager::GetManager",
		FString("Currency Manager not registered (").Append(ID).Append(")"));
	return nullptr;
}

/**
 * @brief Initialize the currency manager components
 */
void ACurrencyManager::Initialize()
{
	if (SaveManager == nullptr)
	{
		ULog::Info("CurrencyManager::Initialize",
		"Not initializing currency manager components. Save manager not set");
		return;
	}
	
	ULog::Info("CurrencyManager::Initialize", "Initializing coin manager");
	CoinManager->LoadSavedCurrency();

	ULog::Info("CurrencyManager::Initialize", "Initializing gems manager");
	GemManager->LoadSavedCurrency();

	TArray<FString> ManagerKeys;
	CustomManagers.GetKeys(ManagerKeys);
	for (FString ManagerKey : ManagerKeys)
	{
		ULog::Info("CurrencyManager::Initialize", FString("Initializing ").Append(ManagerKey));
		CustomManagers[ManagerKey]->LoadSavedCurrency();
	}

	ULog::Info("CurrencyManager::Initialize", "Currency manager components initialized");
}
