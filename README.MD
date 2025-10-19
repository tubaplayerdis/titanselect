# Titanselect

Titanselect is a simple visual atuon selector that works on pros. Titanselect was created as a simple proprietary auton selector used by vex team 38535A after robodash went OOS (Out Of Support)

**NOTE:** Titanselect uses **LVGL 9**. Make sure you have to latest pros version installed that supports lvgl 9 to use Titanselect

## Update Titanselect

```pros c update```

## Install Titanselect

> [!NOTE]
> **Titanselect ONLY SUPPORTS PROS V2.4.1+** 

### Install depot

```pros c add-depot titanselect https://raw.githubusercontent.com/tubaplayerdis/titanselect/refs/heads/main/depot.json```

### Apply latest version (1.0.0)

```pros c apply titanselect@1.0.0```

### Thats it!

### Showcase

![Titanselect before selecting an auton](images/ts1.png "Titanselect before selecting an auton")
![Titanselect after selecting an auton](images/ts2.png "Titanselect after selecting an auton")

### Features

Titanselect is a relatively simple but has a few key features that make it great,

 - **Automatic auton saving/loading from file** - Titanselect will automatically save/load your last used autons so you dont have to worry about an auton not running or having to reselect an auton pre-match. **(A Micro-SD has to be inserted and read/writeable for this to work)**

 - **Grid style Selector** - Titanselects's grid style selector makes choosing autons simple and straightforward to maximize your time writing autons instead of trying to get your auton selector to work.

### Usage

Titanselect has both a C and C++ api. to take advantage of each, include the respective titanselect.h or titanselect.hpp.

read the following documentation for each language:

[Titanselect C API](CDOCS.MD) 
[Titanselect C++ API](CPPDOCS.MD)
