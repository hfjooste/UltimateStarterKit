## Using the Game Instance
You need to create a blueprint using the `USKGameInstance_Implementation` as a parent before using the game instance. The input indicators feature is already configured if you use this base class. If you prefer to set this up manually, you can use `USKGameInstance` instead. After creating your own game instance blueprint, set this as the default game instance:
<ol>
    <li>Open the Project Settings</li>
    <li>Go to Project > Maps & Modes</li>
    <li>Change the <code>Game Instance Class</code> value to your own blueprint</li>
</ol>

## Save Data
You need to create a <code>USK Save Game</code> object before you can save/load data. This object contains all the data that you want to save. Just add the data you want to save as variables to the blueprint. The <code>Game Instance</code> will handle the rest. You also need to set the following properties before you can save/load data:
<ul>
    <li><strong>Save Game Class:</strong> A reference to the <code>USK Save Game</code> class that contains the data you want to save</li>
</ul>

<i><strong>NB:</strong> You are required to set the save slot before you can save/load data. If not, you will get a <code>nullptr</code> and might cause your game to crash</i>

## Input Indicators
The Game Instance will automatically detect input events and update the current input device if needed. If the input device is changed, other classes will be notified through the <code>OnInputDeviceUpdated</code> event