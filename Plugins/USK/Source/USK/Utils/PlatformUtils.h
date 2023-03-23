// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Platform.h"
#include "PlatformUtils.generated.h"

/**
 * @brief Utils class used for platform detection 
 */
UCLASS()
class USK_API UPlatformUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Get the current platform
	 * @return The current platform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static EPlatform GetPlatform();

	/**
	 * @brief Is the build running inside the editor?
	 * @return A boolean value indicating if the build is running inside the editor
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsInEditor();

	/**
	 * @brief Is the build running on a desktop platform?
	 * @return A boolean value indicating if the build is running on a desktop platform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsDesktop();

	/**
	 * @brief Is the build running on Windows?
	 * @return A boolean value indicating if the build is running on Windows
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsWindows();

	/**
	 * @brief Is the build running on MacOS?
	 * @return A boolean value indicating if the build is running on MacOS
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is MacOS")
	static bool IsMacOS();

	/**
	 * @brief Is the build running on MacOS (x86)?
	 * @return A boolean value indicating if the build is running on MacOS (x86)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is MacOS (x86)")
	static bool IsMacOSx86();

	/**
	 * @brief Is the build running on MacOS (ARM)?
	 * @return A boolean value indicating if the build is running on MacOS (ARM)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is MacOS (ARM)")
	static bool IsMacOSArm();

	/**
	 * @brief Is the build running on Linux?
	 * @return A boolean value indicating if the build is running on Linux
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsLinux();

	/**
	 * @brief Is the build running on a console platform?
	 * @return A boolean value indicating if the build is running on a console platform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsConsole();

	/**
	 * @brief Is the build running on Xbox?
	 * @return A boolean value indicating if the build is running on Xbox
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsXbox();

	/**
	 * @brief Is the build running on Playstation?
	 * @return A boolean value indicating if the build is running on Playstation
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsPlaystation();

	/**
	 * @brief Is the build running on Switch?
	 * @return A boolean value indicating if the build is running on Switch
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsSwitch();

	/**
	 * @brief Is the build running on a mobile platform?
	 * @return A boolean value indicating if the build is running on a mobile platform
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsMobile();

	/**
	 * @brief Is the build running on Android?
	 * @return A boolean value indicating if the build is running on Android
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform")
	static bool IsAndroid();

	/**
	 * @brief Is the build running on Android (x86)?
	 * @return A boolean value indicating if the build is running on Android (x86)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is Android (x86)")
	static bool IsAndroidx86();

	/**
	 * @brief Is the build running on Android (x64)?
	 * @return A boolean value indicating if the build is running on Android (x64)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is Android (x64)")
	static bool IsAndroidx64();

	/**
	 * @brief Is the build running on Android (ARM)?
	 * @return A boolean value indicating if the build is running on Android (ARM)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is Android (ARM)")
	static bool IsAndroidArm();

	/**
	 * @brief Is the build running on Android (ARM64)?
	 * @return A boolean value indicating if the build is running on Android (ARM64)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is Android (ARM64)")
	static bool IsAndroidArm64();

	/**
	 * @brief Is the build running on iOS?
	 * @return A boolean value indicating if the build is running on iOS
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Utils|Platform",
		DisplayName="Is iOS")
	static bool IsIOS();
};
