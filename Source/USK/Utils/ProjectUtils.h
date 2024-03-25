// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectUtils.generated.h"

/**
 * @brief A Blueprint Function Library class used to extract project values
 */
UCLASS()
class USK_API UProjectUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Get the project ID from the game config file
	 * @return The project ID
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectId();

	/**
	 * @brief Get the project name from the game config file
	 * @return The project name
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectName();

	/**
	 * @brief Get the project description from the game config file
	 * @return The project description
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectDescription();

	/**
	 * @brief Get the project version from the game config file
	 * @return The project version
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectVersion();

	/**
	 * @brief Get the project company name from the game config file
	 * @return The project company name
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectCompanyName();

	/**
	 * @brief Get the project copyright notice from the game config file
	 * @return The project copyright notice
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectCopyrightNotice();

	/**
	 * @brief Get the project licensing terms from the game config file
	 * @return The project licensing terms
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")	
	static FString GetProjectLicensingTerms();

	/**
	 * @brief Get the project homepage from the game config file
	 * @return The project homepage
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Project")
	static FString GetProjectHomepage();
};