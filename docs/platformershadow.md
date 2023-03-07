## Introduction
A decal used as a shadow to indicate where the character will land

## API Usage
### Functions
<table>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Params</th>
        <th>Return</th>
    </tr>
    <tr>
        <td>Initialize</td>
        <td>Initialize the shadow decal</td>
        <td><strong>OwnerCharacter (ACharacter*)</strong><br/>The character owning this shadow decal</td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can initialize a shadow decal using Blueprints by adding the following node (requires a reference to the <code>Shadow Decal Instance</code>):
<ul>
    <li>Ultimate Starter Kit > Shadow Decal > Initialize</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The shadow decal can now be initialized in any of your C++ files:
```c++
#include "USK/Character/ShadowDecal.h"

void ATestCharacter::Test()
{
    // ShadowDecal is a pointer to the AShadowDecal actor
    ShadowDecal->Initialize(this);
}
```