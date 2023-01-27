// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "LogType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Log.generated.h"

/**
 * @brief Log information to file and display on-screen messages
 */
UCLASS()
class USK_API ULog final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The maximum size of a log file in bytes before a new file is created
	 */
	inline static int MaxFileSize = 10 * 1024 * 1024;
	
	/**
	 * @brief Log an error
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger", DisplayName = "Log Error")
	static void Error(const FString Tag, const FString Text);

	/**
	 * @brief Log a warning
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger", DisplayName = "Log Warning")
	static void Warning(const FString Tag, const FString Text);

	/**
	 * @brief Log info
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger", DisplayName = "Log Info")
	static void Info(const FString Tag, const FString Text);

	/**
	 * @brief Log debug information
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger", DisplayName = "Log Debug")
	static void Debug(const FString Tag, const FString Text);

	/**
	 * @brief Log trace information
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger", DisplayName = "Log Trace")
	static void Trace(const FString Tag, const FString Text);

private:
	/**
	 * @brief Log information to a file
	 * @param Type The type of information to log
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	static void LogToFile(ELogType Type, const FString Tag, const FString Text);
	
	/**
	 * @brief Log information to the screen
	 * @param Color The color used for the log entry
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	static void LogToScreen(const FColor Color, const FString Tag, const FString Text);
	
	/**
	 * @brief Convert a log type to a user friendly name
	 * @param Type The log type to convert
	 * @return A user friendly name for the log type
	 */
	static FString GetLogTypeText(ELogType Type);
};