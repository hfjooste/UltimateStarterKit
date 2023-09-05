## Introduction
A system used to easily log info to file and via on-screen messages

## Log Levels
This plugin supports the following log types:
<ol>
    <li>
        <strong>Trace:</strong> Logs that contain the most detailed messages. These messages may contain sensitive application data. These messages are disabled by default and should never be enabled in a production environment
    </li>
    <li>
        <strong>Debug:</strong> Logs that are used for interactive investigation during development. These logs should primarily contain information useful for debugging and have no long-term value
    </li>
    <li>
        <strong>Information:</strong> Logs that track the general flow of the application. These logs should have long-term value
    </li>
    <li>
        <strong>Warning:</strong> Logs that highlight an abnormal or unexpected event in the application flow, but do not otherwise cause the application execution to stop
    </li>
    <li>
        <strong>Error:</strong> Logs that highlight when the current flow of execution is stopped due to a failure. These should indicate a failure in the current activity, not an application-wide failure
    </li>
</ol>

The log levels corresponds to the following verbosity level in Unreal Engine:
<table>
    <tr>
        <th>Log Level</th>
        <th>Log Verbosity</th>
    </tr>
    <tr>
        <td>Trace</td>
        <td>VeryVerbose</td>
    </tr>
    <tr>
        <td>Debug</td>
        <td>Verbose</td>
    </tr>
    <tr>
        <td>Information</td>
        <td>Display</td>
    </tr>
    <tr>
        <td>Warning</td>
        <td>Warning</td>
    </tr>
    <tr>
        <td>Error</td>
        <td>Error</td>
    </tr>
</table>

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
		<td>Configure</td>
		<td>Configure the logger</td>
		<td><strong>Config (ULogConfig*)</strong><br/>The new config file used by the logger</td>
		<td></td>
	</tr>
	<tr>
		<td>Error</td>
		<td>Log an error</td>
		<td><strong>Tag (FString)</strong><br/>The category of the log entry<br/><br/><strong>Text (FString)</strong><br/>The text to log out</td>
		<td></td>
	</tr>
	<tr>
		<td>Warning</td>
		<td>Log a warning</td>
		<td><strong>Tag (FString)</strong><br/>The category of the log entry<br/><br/><strong>Text (FString)</strong><br/>The text to log out</td>
		<td></td>
	</tr>
	<tr>
		<td>Info</td>
		<td>Log info</td>
		<td><strong>Tag (FString)</strong><br/>The category of the log entry<br/><br/><strong>Text (FString)</strong><br/>The text to log out</td>
		<td></td>
	</tr>
	<tr>
		<td>Debug</td>
		<td>Log debug information</td>
		<td><strong>Tag (FString)</strong><br/>The category of the log entry<br/><br/><strong>Text (FString)</strong><br/>The text to log out</td>
		<td></td>
	</tr>
	<tr>
		<td>Trace</td>
		<td>Log trace information</td>
		<td><strong>Tag (FString)</strong><br/>The category of the log entry<br/><br/><strong>Text (FString)</strong><br/>The text to log out</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can easily log info using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Logger > Configure</li>
    <li>Ultimate Starter Kit > Logger > Log Trace</li>
    <li>Ultimate Starter Kit > Logger > Log Debug</li>
    <li>Ultimate Starter Kit > Logger > Log Info</li>
    <li>Ultimate Starter Kit > Logger > Log Warning</li>
    <li>Ultimate Starter Kit > Logger > Log Error</li>
</ul>

## C++ Usage
The logging is handled through a static class/functions. You first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The logger can now be used in any of your C++ files:
```
#include "USK/Logger/Log.h"

void ATestActor::Test()
{
    USK_LOG_TRACE("Testing trace logging");
    USK_LOG_DEBUG("Testing debug logging");
    USK_LOG_INFO("Testing info logging");
    USK_LOG_WARNING("Testing warning logging");
    USK_LOG_ERROR("Testing error logging");

	ULog::Configure(Config);
    ULog::Trace("Custom Tag", "Testing trace logging");
    ULog::Debug("Custom Tag", "Testing debug logging");
    ULog::Info("Custom Tag", "Testing info logging");
    ULog::Warning("Custom Tag", "Testing warning logging");
    ULog::Error("Custom Tag", "Testing error logging");
}
```
