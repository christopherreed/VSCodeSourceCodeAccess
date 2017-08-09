
VSCodeSourceCodeAccess
======================
[https://github.com/christopherreed/VSCodeSourceCodeAccess](https://github.com/christopherreed/VSCodeSourceCodeAccess)

Unreal Engine 4 plugin that provides source code access for working with C++ projects using [VSCode](https://code.visualstudio.com/).

You may want to check out [ue4-cpptools](https://github.com/christopherreed/ue4-cpptools), a VSCode extension that provides tools for working with Unreal Engine 4 C++ projects in VSCode.

Features
--------

This is a very basic plugin that really only provides the ability to open C++ classes and projects in VSCode from the UE4Editor.

This plugin should work with Unreal Engine versions 4.16 and 4.17 on Linux, Windows, and Mac (not tested).

Unreal Engine   | 4.17  | 4.16  | 4.15 (or older)
----------------|-------|-------|----------------
Windows         | ok    | ok    | no
Linux           | ok    | ok    | no
Mac             | ?     | ?     | no

Install
-------

1) Download the [plugin source](https://github.com/christopherreed/VSCodeSourceCodeAccess)

2) Copy the plugin source folder into an existing Unreal Engine 4 C++ project's __Plugins__ folder (*.../MyProject/Plugins/VSCodeSourceCodeAccess*)

3) Open the project and Unreal Engine 4

4) Select __No__ if prompted to disable the __VSCodeSourceCodeAccess__ plugin because it is incompatible with your engine version
    
5) Select __Yes__ when asked if you would like to build the __VSCodeSourceCodeAccess__ plugin

> After building the plugin you can make it available to other projects by copying the __VSCodeSourceCodeAccess__ plugin folder to your Unreal Engine 4 __Engine/Plugins__ folder (*...Engine/Plugins/VSCodeSourceCodeAccess*)

4) Select __VSCode__ from __Editor Preferences/General - Source Code/Source Code Editor__

Usage
-----


Use __File/Open an IDE to edit source code__ or select a C++ Class from UE4Editor and double click or choose __Common/edit...__ from right click menu to open VSCode.

Settings
--------

__Project Settings/Plugins - VSCode/VSCode Path__ : Path to the VSCode executable

Known Issues
------------

[https://github.com/christopherreed/VSCodeSourceCodeAccess/issues](https://github.com/christopherreed/VSCodeSourceCodeAccess/issues)

* Mac not tested

LICENSE
-------
This software is licensed under the MIT License, see LICENSE for more information

<a href='https://ko-fi.com/A41034HG' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://az743702.vo.msecnd.net/cdn/kofi2.png?v=0' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>
