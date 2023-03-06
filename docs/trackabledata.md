## Introduction
All trackable data use the `FTrackableData` struct to specify the default values and behaviours

## Properties
<table>
    <tr>
        <th>Property</th>
        <th>Description</th>
        <th>Type</th>
        <th>Default Value</th>
    </tr>
    <tr>
        <td>Initial Value</td>
        <td>The initial value of the data</td>
        <td>float</td>
        <td>0.0f</td>
    </tr>
    <tr>
        <td>Enforce Max Value</td>
        <td>Should we enforce a maximum value?</td>
        <td>bool</td>
        <td>false</td>
    </tr>
    <tr>
        <td>Max Value</td>
        <td>The maximum value of the data</td>
        <td>float</td>
        <td>100.0f</td>
    </tr>
    <tr>
        <td>Auto Save</td>
        <td>Should all value updates automatically be saved using the game instance?</td>
        <td>bool</td>
        <td>false</td>
    </tr>
    <tr>
        <td>Auto Generate</td>
        <td>Should we automatically generate value every second?</td>
        <td>bool</td>
        <td>false</td>
    </tr>
    <tr>
        <td>Generate Amount</td>
        <td>The amount of value to generate every second</td>
        <td>float</td>
        <td>0.0f</td>
    </tr>
    <tr>
        <td>Generate Delay</td>
        <td>The delay before the value starts generating after losing value</td>
        <td>float</td>
        <td>0.0f</td>
    </tr>
</table>