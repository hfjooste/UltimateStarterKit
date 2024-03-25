// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigUtils.generated.h"

/**
 * @brief A Blueprint Function Library class used to extract config values
 */
UCLASS()
class USK_API UConfigUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Extract a config value from a given config file
	 * @param Filename The name of the config file
	 * @param Section The section in the config file
	 * @param Key The key in the config file
	 * @param DefaultValue The default value to return if the config file can't be read
	 * @return The value extracted from the config file
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Config")
	static FString GetConfigValue(FString Filename, FString Section, FString Key, FString DefaultValue);

	/**
	 * @brief Extract a config value from the default game config file
	 * @param Section The section in the config file
	 * @param Key The key in the config file
	 * @param DefaultValue The default value to return if the config file can't be read
	 * @return The value extracted from the config file
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Config")
	static FString GetGameConfigValue(FString Section, FString Key, FString DefaultValue);
};