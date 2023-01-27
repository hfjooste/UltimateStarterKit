// Created by Henry Jooste

#include "Log.h"
#include "LogType.h"
#include "Misc/FileHelper.h"
#include "Engine/Engine.h"

/**
 * @brief Log an error
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Error(const FString Tag, const FString Text)
{
	LogToFile(ELogType::Error, Tag, Text);
	LogToScreen(FColor::Red, Tag, Text);
}

/**
 * @brief Log a warning
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Warning(const FString Tag, const FString Text)
{
	LogToFile(ELogType::Warning, Tag, Text);
	LogToScreen(FColor::Yellow, Tag, Text);
}

/**
 * @brief Log info
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::Info(const FString Tag, const FString Text)
{
	LogToFile(ELogType::Information, Tag, Text);
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
	LogToFile(ELogType::Debug, Tag, Text);
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
	LogToFile(ELogType::Trace, Tag, Text);
	LogToScreen(FColor::White, Tag, Text);
#endif
}

/**
 * @brief Log information to a file
 * @param Type The type of information to log
 * @param Tag The category of the log entry
 * @param Text The text to log out
 */
void ULog::LogToFile(ELogType Type, const FString Tag, const FString Text)
{
#if !PLATFORM_DESKTOP
	return;
#endif

	const FString DateText = FDateTime::Now().GetDate().ToString(TEXT("%Y%m%d"));
	
#if !WITH_EDITOR
	const FString LogFile = FPaths::ProjectLogDir() + "/" + DateText + ".log";
#else
	const FString LogFile = FPaths::ProjectDir() + "/Logs/" + DateText + ".log";
#endif

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*LogFile) && PlatformFile.FileSize(*LogFile) > MaxFileSize)
	{
		int Index = 0;
		const FString OldSuffix = ".log";
		
		FString NewLogFile;
		do
		{
			Index++;
			const FString NewSuffix = "-" + FString::FromInt(Index) + OldSuffix;
			NewLogFile = LogFile.Replace(*OldSuffix, *NewSuffix);
		}
		while (PlatformFile.FileExists(*NewLogFile));
		PlatformFile.MoveFile(*NewLogFile, *LogFile);
	}
	
	const FString LogText = "[" + FDateTime::Now().ToString(TEXT("%Y/%m/%d %H:%M:%S")) + "]" +
		GetLogTypeText(Type) + "[" + Tag + "] " + Text + "\r\n";
	FFileHelper::SaveStringToFile(LogText, *LogFile, FFileHelper::EEncodingOptions::AutoDetect,
		&IFileManager::Get(), FILEWRITE_Append);
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

/**
 * @brief Convert a log type to a user friendly name
 * @param Type The log type to convert
 * @return A user friendly name for the log type
 */
FString ULog::GetLogTypeText(const ELogType Type)
{
	switch (Type)
	{
	case ELogType::Error:
		return "[Error]";
	case ELogType::Warning:
		return "[Warning]";
	case ELogType::Information:
		return "[Info]";
	case ELogType::Debug:
		return "[Debug]";
	case ELogType::Trace:
		return "[Trace]";
	default:
		return "[Unknown]";
	}
}