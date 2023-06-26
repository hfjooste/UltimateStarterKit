## Introduction
A Blueprint Function Library class used to extract project values

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
		<td>GetProjectId</td>
		<td>Get the project ID from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project ID</td>
	</tr>
	<tr>
		<td>GetProjectName</td>
		<td>Get the project name from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project name</td>
	</tr>
	<tr>
		<td>GetProjectDescription</td>
		<td>Get the project description from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project description</td>
	</tr>
	<tr>
		<td>GetProjectVersion</td>
		<td>Get the project version from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project version</td>
	</tr>
	<tr>
		<td>GetProjectCompanyName</td>
		<td>Get the project company name from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project company name</td>
	</tr>
	<tr>
		<td>GetProjectCopyrightNotice</td>
		<td>Get the project copyright notice from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project copyright notice</td>
	</tr>
	<tr>
		<td>GetProjectLicensingTerms</td>
		<td>Get the project licensing terms from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project licensing terms</td>
	</tr>
	<tr>
		<td>GetProjectHomepage</td>
		<td>Get the project homepage from the game config file</td>
		<td></td>
		<td><strong>FString</strong><br/>The project homepage</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>ProjectUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Id</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Name</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Description</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Version</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Company Name</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Copyright Notice</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Licensing Terms</li>
	<li>Ultimate Starter Kit > Utils > Project > Get Project Homepage</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>ProjectUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Utils/ProjectUtils.h"

void ATestActor::Test()
{
	FString ProjectId = UProjectUtils::GetProjectId();
	FString ProjectName = UProjectUtils::GetProjectName();
	FString ProjectDescription = UProjectUtils::GetProjectDescription();
	FString ProjectVersion = UProjectUtils::GetProjectVersion();
	FString ProjectCompanyName = UProjectUtils::GetProjectCompanyName();
	FString ProjectCopyrightNotice = UProjectUtils::GetProjectCopyrightNotice();
	FString ProjectLicensingTerms = UProjectUtils::GetProjectLicensingTerms();
	FString ProjectHomepage = UProjectUtils::GetProjectHomepage();
}
```
