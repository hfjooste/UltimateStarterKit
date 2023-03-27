## Introduction
A Blueprint Function Library class used for platform detection

## API Reference
### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>GetPlatform</td>
		<td>Get the current platform</td>
		<td></td>
		<td><strong>EPlatform</strong><br/>The current platform</td>
	</tr>
	<tr>
		<td>IsInEditor</td>
		<td>Is the build running inside the editor?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running inside the editor</td>
	</tr>
	<tr>
		<td>IsDesktop</td>
		<td>Is the build running on a desktop platform?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on a desktop platform</td>
	</tr>
	<tr>
		<td>IsWindows</td>
		<td>Is the build running on Windows?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Windows</td>
	</tr>
	<tr>
		<td>IsMacOS</td>
		<td>Is the build running on MacOS?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on MacOS</td>
	</tr>
	<tr>
		<td>IsMacOSx86</td>
		<td>Is the build running on MacOS (x86)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on MacOS (x86)</td>
	</tr>
	<tr>
		<td>IsMacOSArm</td>
		<td>Is the build running on MacOS (ARM)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on MacOS (ARM)</td>
	</tr>
	<tr>
		<td>IsLinux</td>
		<td>Is the build running on Linux?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Linux</td>
	</tr>
	<tr>
		<td>IsConsole</td>
		<td>Is the build running on a console platform?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on a console platform</td>
	</tr>
	<tr>
		<td>IsXbox</td>
		<td>Is the build running on Xbox?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Xbox</td>
	</tr>
	<tr>
		<td>IsPlaystation</td>
		<td>Is the build running on Playstation?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Playstation</td>
	</tr>
	<tr>
		<td>IsSwitch</td>
		<td>Is the build running on Switch?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Switch</td>
	</tr>
	<tr>
		<td>IsMobile</td>
		<td>Is the build running on a mobile platform?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on a mobile platform</td>
	</tr>
	<tr>
		<td>IsAndroid</td>
		<td>Is the build running on Android?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Android</td>
	</tr>
	<tr>
		<td>IsAndroidx86</td>
		<td>Is the build running on Android (x86)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Android (x86)</td>
	</tr>
	<tr>
		<td>IsAndroidx64</td>
		<td>Is the build running on Android (x64)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Android (x64)</td>
	</tr>
	<tr>
		<td>IsAndroidArm</td>
		<td>Is the build running on Android (ARM)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Android (ARM)</td>
	</tr>
	<tr>
		<td>IsAndroidArm64</td>
		<td>Is the build running on Android (ARM64)?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on Android (ARM64)</td>
	</tr>
	<tr>
		<td>IsIOS</td>
		<td>Is the build running on iOS?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the build is running on iOS</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>PlatformUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Utils > Platform > Get Platform</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is In Editor</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Desktop</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Windows</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is MacOS</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is MacOS (x86)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is MacOS (ARM)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Linux</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Console</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Xbox</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Playstation</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Switch</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Mobile</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Android</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Android (x86)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Android (x64)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Android (ARM)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is Android (ARM64)</li>
	<li>Ultimate Starter Kit > Utils > Platform > Is iOS</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>PlatformUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Utils/PlatformUtils.h"

void ATestActor::Test()
{
	EPlatform Platform = UPlatformUtils::GetPlatform();
	bool IsInEditorValue = UPlatformUtils::IsInEditor();
	bool IsDesktopValue = UPlatformUtils::IsDesktop();
	bool IsWindowsValue = UPlatformUtils::IsWindows();
	bool IsMacOSValue = UPlatformUtils::IsMacOS();
	bool IsMacOSx86Value = UPlatformUtils::IsMacOSx86();
	bool IsMacOSArmValue = UPlatformUtils::IsMacOSArm();
	bool IsLinuxValue = UPlatformUtils::IsLinux();
	bool IsConsoleValue = UPlatformUtils::IsConsole();
	bool IsXboxValue = UPlatformUtils::IsXbox();
	bool IsPlaystationValue = UPlatformUtils::IsPlaystation();
	bool IsSwitchValue = UPlatformUtils::IsSwitch();
	bool IsMobileValue = UPlatformUtils::IsMobile();
	bool IsAndroidValue = UPlatformUtils::IsAndroid();
	bool IsAndroidx86Value = UPlatformUtils::IsAndroidx86();
	bool IsAndroidx64Value = UPlatformUtils::IsAndroidx64();
	bool IsAndroidArmValue = UPlatformUtils::IsAndroidArm();
	bool IsAndroidArm64Value = UPlatformUtils::IsAndroidArm64();
	bool IsIOSValue = UPlatformUtils::IsIOS();
}
```
