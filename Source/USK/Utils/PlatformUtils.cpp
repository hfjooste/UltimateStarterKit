// Created by Henry Jooste

#include "PlatformUtils.h"

#include "Misc/Base64.h"
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
	
	if (IsConsoleMx())
	{
		return EPlatform::ConsoleMx;
	}

	if (IsConsoleSp())
	{
		return EPlatform::ConsoleSp;
	}

	if (IsConsoleNs())
	{
		return EPlatform::ConsoleNs;
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
#if PLATFORM_LINUX
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
	return IsConsoleMx() || IsConsoleSp() || IsConsoleNs();
}

/**
 * @brief Is the build running on Console MX?
 * @return A boolean value indicating if the build is running on Console MX
 */
bool UPlatformUtils::IsConsoleMx()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains(Deobfuscate("PT1BZWk5R2U="));
}

/**
 * @brief Is the build running on Console SP?
 * @return A boolean value indicating if the build is running on Console SP
 */
bool UPlatformUtils::IsConsoleSp()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains(Deobfuscate("PUEzYw==")) || Platform.Contains("PT13YzBGR2RwOW1i");
}

/**
 * @brief Is the build running on Console NS?
 * @return A boolean value indicating if the build is running on Console NS
 */
bool UPlatformUtils::IsConsoleNs()
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	return Platform.Contains("PTRXYXVSWFp1UjJi") || Platform.Contains("emRYYTBOR2E=");
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

/**
 * @brief Reverse a string
 * @param Input The string to reverse
 * @return The reversed string
 */
FString UPlatformUtils::ReverseString(const FString& Input)
{
	FString ReversedString;
	const int Length = Input.Len();
    
	for (int i = Length - 1; i >= 0; --i)
	{
		ReversedString.AppendChar(Input[i]);
	}
    
	return ReversedString;
}

/**
 * @brief Obfuscate a string
 * @param Input The string to obfuscate
 * @return The obfuscated string
 */
FString UPlatformUtils::Obfuscate(const FString& Input)
{
	return FBase64::Encode(ReverseString(FBase64::Encode(ReverseString(Input))));
}

/**
 * @brief Deobfuscate a string
 * @param Input The string to deobfuscate
 * @return The deobfuscated string
 */
FString UPlatformUtils::Deobfuscate(const FString& Input)
{
	FString DecodedFirstPass;
	FString DecodedSecondPass;
	FBase64::Decode(Input, DecodedFirstPass);
	FBase64::Decode(ReverseString(DecodedFirstPass), DecodedSecondPass);
	return ReverseString(DecodedSecondPass);
}
