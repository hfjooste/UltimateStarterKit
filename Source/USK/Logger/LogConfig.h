// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LogConfig.generated.h"

/**
 * @brief Config file for the logger
 */
UCLASS()
class USK_API ULogConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Should error logs be written to file?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Error",
		DisplayName = "Write to File")
	bool bErrorWriteToFile = true;

	/**
	 * @brief Should error logs be printed to screen?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Error",
		DisplayName = "Print to Screen")
	bool bErrorPrintToScreen = true;

	/**
	 * @brief Should warning logs be written to file?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Warning",
		DisplayName = "Write to File")
	bool bWarningWriteToFile = true;

	/**
	 * @brief Should warning logs be printed to screen?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Warning",
		DisplayName = "Print to Screen")
	bool bWarningPrintToScreen = true;

	/**
	 * @brief Should info logs be written to file?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Info",
		DisplayName = "Write to File")
	bool bInfoWriteToFile = true;

	/**
	 * @brief Should info logs be printed to screen?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Info",
		DisplayName = "Print to Screen")
	bool bInfoPrintToScreen = true;

	/**
	 * @brief Should debug logs be written to file?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Debug",
		DisplayName = "Write to File")
	bool bDebugWriteToFile = true;

	/**
	 * @brief Should debug logs be printed to screen?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Debug",
		DisplayName = "Print to Screen")
	bool bDebugPrintToScreen = true;

	/**
	 * @brief Should debug logs be written to file?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Trace",
		DisplayName = "Write to File")
	bool bTraceWriteToFile = true;

	/**
	 * @brief Should debug logs be printed to screen?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger|Trace",
		DisplayName = "Print to Screen")
	bool bTracePrintToScreen = true;
};
