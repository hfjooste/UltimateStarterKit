// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Log.generated.h"

class ULogConfig;

/**
 * @brief Log an error
 * @param Text The text to log out
 */
#define USK_LOG_ERROR(Text) ULog::Error(__FUNCTION__, Text)

/**
 * @brief Log a warning
 * @param Text The text to log out
 */
#define USK_LOG_WARNING(Text) ULog::Warning(__FUNCTION__, Text)

/**
 * @brief Log info
 * @param Text The text to log out
 */
#define USK_LOG_INFO(Text) ULog::Info(__FUNCTION__, Text)

/**
 * @brief Log debug information
 * @param Text The text to log out
 */
#define USK_LOG_DEBUG(Text) ULog::Debug(__FUNCTION__, Text)

/**
 * @brief Log trace information
 * @param Text The text to log out
 */
#define USK_LOG_TRACE(Text) ULog::Trace(__FUNCTION__, Text)

DECLARE_LOG_CATEGORY_EXTERN(LogUSK, Log, All);

/**
 * @brief Log information to file and display on-screen messages
 */
UCLASS()
class USK_API ULog final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Configure the logger
	 * @param Config The new config file used by the logger
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Logger")
	static void Configure(ULogConfig* Config);
	
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
	 * @brief Log information to the screen
	 * @param Color The color used for the log entry
	 * @param Tag The category of the log entry
	 * @param Text The text to log out
	 */
	static void LogToScreen(const FColor Color, const FString Tag, const FString Text);

	/**
	 * @brief The current configuration used by the logger
	 */
	static ULogConfig* Configuration;
};