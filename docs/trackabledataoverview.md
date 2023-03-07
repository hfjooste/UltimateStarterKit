## Introduction
A system that is used to easily manage different types of actor data

## Dependencies
The currency system relies on other components of this plugin to work:
<ul>
    <li><a href="../gameinstance">Game Instance</a>: Used to automatically save/load the data managed by the component(s)</li>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
    <li><a href="../savedata">Save Data</a>: Used to automatically save/load currency values (optional)</li>
</ul>

## Trackable Data Component
Before you can manage the data, you need to create a <a href="../trackabledatacomponent">Trackable Data Component</a> and add it to the actor/character containing the data

## Built-in data
The following data can automatically be managed without creating custom components:
<ol>
    <li>Currency (using the <code>Currency Component</code>)</li>
    <li>Stats (using the <code>Stats Component</code>)</li>
</ol>