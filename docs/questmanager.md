## Introduction
Actor responsible for managing quests

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
		<td>QuestWidgetClass</td>
		<td>The widget class used to display the current quest</td>
		<td>TSubclassOf&lt;UQuestWidget&gt;</td>
		<td></td>
	</tr>
</table>

### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnQuestCompleted</td>
		<td>Event used to notify other classes when a quest is completed</td>
		<td><strong>Quest (UQuest*)</strong><br/>The quest that was completed</td>
	</tr>
	<tr>
		<td>OnQuestUpdated</td>
		<td>Event used to notify other classes when a quest is updated</td>
		<td><strong>CurrentQuest (UQuest*)</strong><br/>The current active quest<br/><br/><strong>CurrentPoint (UQuest*)</strong><br/>The current point of the active quest</td>
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
		<td>StartQuest</td>
		<td>Start the specified quest</td>
		<td><strong>Quest (UQuest*)</strong><br/>The quest to start</td>
		<td></td>
	</tr>
	<tr>
		<td>OnQuestPointCompleted</td>
		<td>Complete the current quest point</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetCurrentQuest</td>
		<td>Get the current quest</td>
		<td></td>
		<td><strong>UQuest*</strong><br/>The current quest</td>
	</tr>
	<tr>
		<td>GetCurrentQuestPo</td>
		<td>Get the current quest point</td>
		<td></td>
		<td><strong>int</strong><br/>The current quest point</td>
	</tr>
	<tr>
		<td>IsQuestActive</td>
		<td>Check if the specified quest is active</td>
		<td><strong>Quest (UQuest*)</strong><br/>The quest to check</td>
		<td><strong>bool</strong><br/>A boolean value indicating if the quest is active</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>QuestManager</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Quests > Start Quest</li>
	<li>Ultimate Starter Kit > Quests > On Quest Point Completed</li>
	<li>Ultimate Starter Kit > Quests > Get Current Quest</li>
	<li>Ultimate Starter Kit > Quests > Get Current Quest Po</li>
	<li>Ultimate Starter Kit > Quests > Is Quest Active</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>QuestManager</code> can now be used in any of your C++ files:
```c++
#include "USK/Quests/QuestManager.h"

void ATestActor::Test()
{
	// QuestManager is a pointer to the AQuestManager
	QuestManager->StartQuest(Quest);
	QuestManager->OnQuestPointCompleted();
	UQuest* CurrentQuest = QuestManager->GetCurrentQuest();
	int CurrentQuestPo = QuestManager->GetCurrentQuestPo();
	bool IsQuestActiveValue = QuestManager->IsQuestActive(Quest);
}
```
