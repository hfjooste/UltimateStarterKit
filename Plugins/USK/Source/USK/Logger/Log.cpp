// Created by Henry Jooste

#include "Log.h"

DEFINE_LOG_CATEGORY(LogUSK);

/**
 * @brief Log an error
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Error(const FString Tag, const FString Text)
{	
	UE_LOG(LogUSK, Error, TEXT("%s: %s"), *Tag, *Text);
	LogToScreen(FColor::Red, Tag, Text);
}

/**
 * @brief Log a warning
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Warning(const FString Tag, const FString Text)
{
	UE_LOG(LogUSK, Warning, TEXT("%s: %s"), *Tag, *Text);
	LogToScreen(FColor::Yellow, Tag, Text);
}

/**
 * @brief Log info
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Info(const FString Tag, const FString Text)
{
	UE_LOG(LogUSK, Display, TEXT("%s: %s"), *Tag, *Text);
	LogToScreen(FColor::Blue, Tag, Text);
}

/**
 * @brief Log debug information
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Debug(const FString Tag, const FString Text)
{
#if WITH_EDITOR || UE_EDITOR || UE_BUILD_TEST || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	UE_LOG(LogUSK, Verbose, TEXT("%s: %s"), *Tag, *Text);
	LogToScreen(FColor::Magenta, Tag, Text);
#endif
}

/**
 * @brief Log trace information
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Trace(const FString Tag, const FString Text)
{
#if WITH_EDITOR || UE_EDITOR || UE_BUILD_TEST || UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	UE_LOG(LogUSK, VeryVerbose, TEXT("%s: %s"), *Tag, *Text);
	LogToScreen(FColor::White, Tag, Text);
#endif
}

/**
 * @brief Log information to the screen
 * @param Color The color used for the log entry
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::LogToScreen(const FColor Color, const FString Tag, const FString Text)
{
#if !UE_EDITOR && !WITH_EDITOR
	return;
#endif
    	
	if (!GEngine)
	{
		return;
	}

	const FString LogText = "[" + Tag + "] " + Text;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, LogText);
}