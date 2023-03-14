## Introduction
A widget used to display input indicators based on the current input device 

## Dependencies
The game instance relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
    <li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and update the icons automatically</li>
</ul>

## Required Widgets
There is already a <code>InputIndicator_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Type</th>
    </tr>
    <tr>
        <td>Container</td>
        <td>The container used to display multiple images</td>
        <td>UHorizontalBox</td>
    </tr>
</table>

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
        <td>InputIndicatorIconClass</td>
        <td>The input indicator icon class</td>
        <td>TSubclassOf&lt;UInputIndicatorIcon&gt;</td>
        <td></td>
    </tr>
    <tr>
        <td>Action</td>
        <td>The input action displayed by widget</td>
        <td>UInputAction*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>Size</td>
        <td>The size of the image</td>
        <td>float</td>
        <td>50.0f</td>
    </tr>
    <tr>
        <td>Amount</td>
        <td>The amount of images to display for the input action</td>
        <td>int</td>
        <td>1</td>
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
        <td>UpdateAction</td>
        <td>Update the input action displayed by the widget</td>
        <td><strong>NewAction (UInputAction*)</strong><br/>The new action<br/><br/><strong>NewAmount (int)</strong><br/>The new amount of images to display</td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can update the widget using Blueprints by adding one of the following nodes (requires a reference to the <code>Input Indicator</code>):
<ul>
    <li>Ultimate Starter Kit > UI > Update Action</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The input indicator can now be used in any of your C++ files:
```c++
#include "USK/Widgets/InputIndicator.h"

void ATestActor::Test(UInputAction* JumpAction)
{
    //InputIndicator is a reference to a UInputIndicator widget
    InputIndicator->UpdateAction(JumpAction, 100.0f);
}
```