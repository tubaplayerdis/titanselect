# Titanselect

Titanselect is a simple visual atuon selector that works on pros. Titanselect was created as a simple proprietary auton selector used by vex team 38535A after robodash went OOS (Out Of Support)

**NOTE:** titanselect uses **LVGL 9**. Make sure you have to latest pros version installed that supports lvgl 9 to use titanselect

## Update Titanselect

```pros c update```

## Install Titanselect

> [!NOTE]
> **Titanselect ONLY SUPPORTS PROS V2.4.1+** 

### Install depot

```pros c add-depot titanselect https://raw.githubusercontent.com/tubaplayerdis/titanselect/refs/heads/main/depot.json```

### Apply latest version (0.0.9)

```pros c apply titanselect@0.0.9```

### Thats it!

### Showcase

Add pictures here.

### Features

titanselect is a relatively simple but has a few key features that make it great,

 - **Automatic auton saving/loading from file** - titanselect will automatically save/load your last used autons so you dont have to worry about an auton not running or having to reselect an auton pre-match. **(A Micro-SD has to be inserted and read/writeable for this to work)**

 - **Grid style Selector** - titanselects's grid style selector makes choosing autons simple and straightforward to maximize your time writing autons instead of trying to get your auton selector to work.

### Usage

titanselect has both a C and C++ api. to take advantage of each, include the respective titanselect.h or titanselect.hpp.

read the following documentation for each language:

[titanselect C API](https://github.com/tubaplayerdis/titanselect/blob/main/CDOCS.MD) 
[titanselect C++ API](https://github.com/tubaplayerdis/titanselect/blob/main/CPPDOCS.MD)
