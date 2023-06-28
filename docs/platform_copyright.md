## Code names
Due to copyright issues, the plugin is not allowed to mention Xbox, Playstation or Switch anywhere in the code (including file names). To get around this issue, the consoles are refered to by the following code names:
<table>
    <tr>
        <th>Console</th>
        <th>Code name</th>
    </tr>
    <tr>
        <td>Xbox</td>
        <td>Console MX</td>
    </tr>
    <tr>
        <td>Playstation</td>
        <td>Console SP</td>
    </tr>
    <tr>
        <td>Switch</td>
        <td>Console NS</td>
    </tr>
</table>

## Obfuscated code
The plugin will also use the console names to determine the platform. To avoid any copyright issues, the application will instead use an obfuscated string to determine the platform. The obfuscation and deobfuscation code can be found in <code>PlatformUtils.cpp</code>
<table>
    <tr>
        <th>Console</th>
        <th>Obfuscated Text</th>
        <th>Deobfuscated Text</th>
    </tr>
    <tr>
        <td>Xbox</td>
        <td>PT1BZWk5R2U=</td>
        <td>xbox</td>
    </tr>
    <tr>
        <td>Playstation</td>
        <td>PUEzYw==<br/>PT13YzBGR2RwOW1i</td>
        <td>ps<br/>station</td>
    </tr>
    <tr>
        <td>Switch</td>
        <td>PTRXYXVSWFp1UjJi<br/>emRYYTBOR2E=</td>
        <td>nintendo</br>switch</td>
    </tr>
</table>