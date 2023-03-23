// Created by Henry Jooste

#include "PlatformUtils.h"

#include "Kismet/GameplayStatics.h"

/**
 * @brief Get the current platform
 * @return The current platform
 */
EPlatform UPlatformUtils::GetPlatform()
{
	if (IsWindows())
	{
		return EPlatform::Windows;
	}

	if (IsMacOS())
	{
		return EPlatform::MacOS;
	}

	if (IsLinux())
	{
		return EPlatform::Linux;
	}
	
	if (IsXbox())
	{
		return EPlatform::Xbox;
	}

	if (IsPlaystation())
	{
		return EPlatform::Playstation;
	}

	if (IsSwitch())
	{
		return EPlatform::Switch;
	}

	if (IsAndroid())
	{
		return EPlatform::Android;
	}
	
	if (IsIOS())
	{
		return EPlatform::IOS;
	}

	return EPlatform::Unknown;
}

/**
 * @brief Is the build running inside the editor?
 * @return A boolean value indicating if the build is running inside the editor
 */
bool UPlatformUtils::IsInEditor()
{
#if WITH_EDITOR || UE_EDITOR
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on a desktop platform?
 * @return A boolean value indicating if the build is running on a desktop platform
 */
bool UPlatformUtils::IsDesktop()
{
	return IsWindows() || IsMacOS() || IsLinux();
}

/**
 * @brief Is the build running on Windows?
 * @return A boolean value indicating if the build is running on Windows
 */
bool UPlatformUtils::IsWindows()
{
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on MacOS?
 * @return A boolean value indicating if the build is running on MacOS
 */
bool UPlatformUtils::IsMacOS()
{
#if PLATFORM_MAC || PLATFORM_MAC_X86 || PLATFORM_MAC_ARM64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on MacOS (x86)?
 * @return A boolean value indicating if the build is running on MacOS (x86)
 */
bool UPlatformUtils::IsMacOSx86()
{
#if PLATFORM_MAC && PLATFORM_MAC_X86
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on MacOS (ARM)?
 * @return A boolean value indicating if the build is running on MacOS (ARM)
 */
bool UPlatformUtils::IsMacOSArm()
{
#if PLATFORM_MAC && PLATFORM_MAC_ARM64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on Linux?
 * @return A boolean value indicating if the build is running on Linux
 */
bool UPlatformUtils::IsLinux()
{
#if PLATFORM_LINUX || PLATFORM_LINUXARM64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on a console platform?
 * @return A boolean value indicating if the build is running on a console platform
 */
bool UPlatformUtils::IsConsole()
{
	return IsXbox() || IsPlaystation() || IsSwitch();
}

/**
 * @brief Is the build running on Xbox?
 * @return A boolean value indicating if the build is running on Xbox
 */
bool UPlatformUtils::IsXbox()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains("xbox");
}

/**
 * @brief Is the build running on Playstation?
 * @return A boolean value indicating if the build is running on Playstation
 */
bool UPlatformUtils::IsPlaystation()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains("ps") || Platform.Contains("station");
}

/**
 * @brief Is the build running on Switch?
 * @return A boolean value indicating if the build is running on Switch
 */
bool UPlatformUtils::IsSwitch()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains("nintendo") || Platform.Contains("switch");
}

/**
 * @brief Is the build running on a mobile platform?
 * @return A boolean value indicating if the build is running on a mobile platform
 */
bool UPlatformUtils::IsMobile()
{
	return IsAndroid() || IsIOS();
}

/**
 * @brief Is the build running on Android?
 * @return A boolean value indicating if the build is running on Android
 */
bool UPlatformUtils::IsAndroid()
{
#if PLATFORM_ANDROID || PLATFORM_ANDROID_X86 || PLATFORM_ANDROID_X64 || PLATFORM_ANDROID_ARM || PLATFORM_ANDROID_ARM64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on Android (x86)?
 * @return A boolean value indicating if the build is running on Android (x86)
 */
bool UPlatformUtils::IsAndroidx86()
{
#if PLATFORM_ANDROID && PLATFORM_ANDROID_X86
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on Android (x64)?
 * @return A boolean value indicating if the build is running on Android (x64)
 */
bool UPlatformUtils::IsAndroidx64()
{
#if PLATFORM_ANDROID && PLATFORM_ANDROID_X64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on Android (ARM)?
 * @return A boolean value indicating if the build is running on Android (ARM)
 */
bool UPlatformUtils::IsAndroidArm()
{
#if PLATFORM_ANDROID && PLATFORM_ANDROID_ARM
    return true;
#else
    return false;
#endif
}

/**
 * @brief Is the build running on Android (ARM64)?
 * @return A boolean value indicating if the build is running on Android (ARM64)
 */
bool UPlatformUtils::IsAndroidArm64()
{
#if PLATFORM_ANDROID && PLATFORM_ANDROID_ARM64
	return true;
#else
	return false;
#endif
}

/**
 * @brief Is the build running on iOS?
 * @return A boolean value indicating if the build is running on iOS
 */
bool UPlatformUtils::IsIOS()
{
#if PLATFORM_IOS
	return true;
#else
	return false;
#endif
}