// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "LogType.generated.h"

UENUM(BlueprintType)
enum class ELogType : uint8
{
	/**
	 * @brief Logs that contain the most detailed messages.
	 * These messages may contain sensitive application data. These messages are disabled by default
	 * and should never be enabled in a production environment
	 */
	Trace,

	/**
	 * @brief Logs that are used for interactive investigation during development.
	 * These logs should primarily contain information useful for debugging and have no long-term value
	 */
	Debug,

	/**
	 * @brief Logs that track the general flow of the application. These logs should have long-term value
	 */
	Information,

	/**
	 * @brief Logs that highlight an abnormal or unexpected event in the application flow,
	 * but do not otherwise cause the application execution to stop
	 */
	Warning,

	/**
	 * @brief Logs that highlight when the current flow of execution is stopped due to a failure.
	 * These should indicate a failure in the current activity, not an application-wide failure
	 */
	Error,
};