## Introduction
The Logger Plugin for Unreal Engine allows you to easily log info to file and via on-screen messages

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

The plugin will automatically ignore certain log levels based on the type of build:
<table>
    <tr>
        <th>Log Level</th>
        <th>Development</th>
        <th>Shipping</th>
    </tr>
    <tr>
        <td>Trace</td>
        <td>Enabled</td>
        <td>Disabled</td>
    </tr>
    <tr>
        <td>Debug</td>
        <td>Enabled</td>
        <td>Disabled</td>
    </tr>
    <tr>
        <td>Information</td>
        <td>Enabled</td>
        <td>Enabled</td>
    </tr>
    <tr>
        <td>Warning</td>
        <td>Enabled</td>
        <td>Enabled</td>
    </tr>
    <tr>
        <td>Error</td>
        <td>Enabled</td>
        <td>Enabled</td>
    </tr>
</table>

## Logging Methods
There are 2 different logging methods. Both of these are used each time you log something:
<ul>
    <li><strong>On-screen messages:</strong> These messages will appear on-screen for 5 seconds (only used when running the game through the editor)</li>
    <li><strong>Log File:</strong> Everything you log is also written to a file. The file name is the current date and a new file is created each day the game is played. All log files are stored in the root of the project under the <code>Logs</code> directory</li>
</ul>

## API Reference
### Properties
<table>
    <tr>
        <th>Property</th>
        <th>Description</th>
        <th>Type</th>
        <th>Default Value</th>
    </tr>
    <tr>
        <td>MaxFileSize</td>
        <td>The maximum size of a log file in bytes before a new file is created</td>
        <td>int</td>
        <td>10485760 (10MB)</td>
    </tr>
</table>

### Functions
<table>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Params</th>
        <th>Return</th>
    </tr>
    <tr>
        <td>Trace</td>
        <td>Log trace information</td>
        <td>
            <strong>Tag (FString)</strong><br/>The category of the log entry. This is usually the function or class name. It allows you to find out exactly where this is being logged<br/><br/>
            <strong>Text (FString)</strong><br/>The actual text that should be logged out
        </td>
        <td></td>
    </tr>
    <tr>
        <td>Debug</td>
        <td>Log debug information</td>
        <td>
            <strong>Tag (FString)</strong><br/>The category of the log entry. This is usually the function or class name. It allows you to find out exactly where this is being logged<br/><br/>
            <strong>Text (FString)</strong><br/>The actual text that should be logged out
        </td>
        <td></td>
    </tr>
    <tr>
        <td>Info</td>
        <td>Log information</td>
        <td>
            <strong>Tag (FString)</strong><br/>The category of the log entry. This is usually the function or class name. It allows you to find out exactly where this is being logged<br/><br/>
            <strong>Text (FString)</strong><br/>The actual text that should be logged out
        </td>
        <td></td>
    </tr>
    <tr>
        <td>Warning</td>
        <td>Log a warning</td>
        <td>
            <strong>Tag (FString)</strong><br/>The category of the log entry. This is usually the function or class name. It allows you to find out exactly where this is being logged<br/><br/>
            <strong>Text (FString)</strong><br/>The actual text that should be logged out
        </td>
        <td></td>
    </tr>
    <tr>
        <td>Error</td>
        <td>Log an error</td>
        <td>
            <strong>Tag (FString)</strong><br/>The category of the log entry. This is usually the function or class name. It allows you to find out exactly where this is being logged<br/><br/>
            <strong>Text (FString)</strong><br/>The actual text that should be logged out
        </td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can easily log info using Blueprints by adding one of the following nodes:
<ul>
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
    ULog::Trace("TestActor::Test", "Testing trace logging");
    ULog::Debug("TestActor::Test", "Testing debug logging");
    ULog::Info("TestActor::Test", "Testing info logging");
    ULog::Warning("TestActor::Test", "Testing warning logging");
    ULog::Error("TestActor::Test", "Testing error logging");
}
```