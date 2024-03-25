// Created by Henry Jooste

#include "Log.h"

#include "LogConfig.h"
#include "Engine/Engine.h"
#include "USK/Utils/PlatformUtils.h"

DEFINE_LOG_CATEGORY(LogUSK);

ULogConfig* ULog::Configuration;

/**
 * @brief Configure the logger
 * @param Config The new config file used by the logger
 */
void ULog::Configure(ULogConfig* Config)
{
	Configuration = Config;
}

/**
 * @brief Log an error
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Error(const FString Tag, const FString Text)
{
	if (!IsValid(Configuration) || Configuration->bErrorWriteToFile)
	{
		UE_LOG(LogUSK, Error, TEXT("%s: %s"), *Tag, *Text);
	}

	if (!IsValid(Configuration) || Configuration->bErrorPrintToScreen)
	{
		LogToScreen(FColor::Red, Tag, Text);
	}
}

/**
 * @brief Log a warning
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Warning(const FString Tag, const FString Text)
{
	if (!IsValid(Configuration) || Configuration->bWarningWriteToFile)
	{
		UE_LOG(LogUSK, Warning, TEXT("%s: %s"), *Tag, *Text);
	}
	
	if (!IsValid(Configuration) || Configuration->bWarningPrintToScreen)
	{
		LogToScreen(FColor::Yellow, Tag, Text);
	}
}

/**
 * @brief Log info
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Info(const FString Tag, const FString Text)
{
	if (!IsValid(Configuration) || Configuration->bInfoWriteToFile)
	{
		UE_LOG(LogUSK, Display, TEXT("%s: %s"), *Tag, *Text);
	}

	if (!IsValid(Configuration) || Configuration->bInfoPrintToScreen)
	{
		LogToScreen(FColor::Blue, Tag, Text);
	}
}

/**
 * @brief Log debug information
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Debug(const FString Tag, const FString Text)
{
	if (!IsValid(Configuration) || Configuration->bDebugWriteToFile)
	{
		UE_LOG(LogUSK, Verbose, TEXT("%s: %s"), *Tag, *Text);
	}

	if (!IsValid(Configuration) || Configuration->bDebugPrintToScreen)
	{
		LogToScreen(FColor::Magenta, Tag, Text);
	}
}

/**
 * @brief Log trace information
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Trace(const FString Tag, const FString Text)
{
	if (!IsValid(Configuration) || Configuration->bTraceWriteToFile)
	{
		UE_LOG(LogUSK, VeryVerbose, TEXT("%s: %s"), *Tag, *Text);
	}

	if (!IsValid(Configuration) || Configuration->bTracePrintToScreen)
	{
		LogToScreen(FColor::White, Tag, Text);
	}
}

/**
 * @brief Log information to the screen
 * @param Color The color used for the log entry
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::LogToScreen(const FColor Color, const FString Tag, const FString Text)
{    	
	if (!UPlatformUtils::IsInEditor() || !GEngine)
	{
		return;
	}

	const FString LogText = "[" + Tag + "] " + Text;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, LogText);
}