## Introduction
A widget used to display a single input indicator image 

## Dependencies
The game instance relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
There is already a <code>InputIndicatorIcon_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Type</th>
    </tr>
    <tr>
        <td>Container</td>
        <td>The size box container used to resize the image</td>
        <td>USizeBox</td>
    </tr>
    <tr>
        <td>Image</td>
        <td>The image used to display the input indicator</td>
        <td>UImage</td>
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
        <td>UpdateIcon</td>
        <td>Update the icon</td>
        <td><strong>Size (float)</strong><br/>The size of the image<br/><br/><strong>Icon (UTexture2D*)</strong><br/>The new icon</td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can update the widget using Blueprints by adding one of the following nodes (requires a reference to the <code>Input Indicator Icon</code>):
<ul>
    <li>Ultimate Starter Kit > UI > Update Icon</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The input indicator icon can now be used in any of your C++ files:
```c++
#include "USK/Widgets/InputIndicatorIcon.h"

void ATestActor::Test(UTexture2D* JumpIndicatorIcon)
{
    //InputIndicatorIcon is a reference to a UInputIndicatorIcon widget
    InputIndicatorIcon->UpdateIcon(100.0f, JumpIndicatorIcon);
}
```