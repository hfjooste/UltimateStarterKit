## Introduction
The plugin includes an animation template that can be used on your 3D platformer characters

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
        <td>MovementSpeed</td>
        <td>The movement speed fo the character</td>
        <td>float</td>
        <td>0.0f</td>
    </tr>
    <tr>
        <td>IsInAir</td>
        <td>Is the character currently in the air?</td>
        <td>bool</td>
        <td>false</td>
    </tr>
    <tr>
        <td>IsDoubleJumping</td>
        <td>Is the character double jumping?</td>
        <td>bool</td>
        <td>false</td>
    </tr>
    <tr>
        <td>IdleAnimation</td>
        <td>The animation used when the character is in the idle state</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>WalkAnimation</td>
        <td>The animation used when the character is walking</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>RunAnimation</td>
        <td>The animation used when the character is running</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>JumpAnimation</td>
        <td>The animation used when the character is jumping</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>DoubleJumpAnimation</td>
        <td>The animation used when the character is double jumping</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>FallAnimation</td>
        <td>The animation used when the character is falling</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>LandAnimation</td>
        <td>The animation used when the character is landing</td>
        <td>UAnimSequence*</td>
        <td><code>nullptr</code></td>
    </tr>
</table>

## Blueprint Usage
You can use this template by creating your own animation blueprint and selecting <code>UPlatformerAnimationInstance</code> as the parent class. Set your animations and use this for your 3D platformer character