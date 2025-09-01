# titanselect

titanselect is a simple visual atuon selector that works on pros. titanselect was created as a simple proprietary auton selector to be used by vex team 38535A.

**NOTE:** titanselect uses **LVGL 9**. Make sure you have to latest pros version installed that supports lvgl 9 to use titanselect

### Adding to your project

Download the latest release via the releases tab. Make sure to download the zip file.

Then, fetch the .zip file you downloaded from releases into the pros conductor

```pros conduct fetch [path to zip]```

After than run:

```pros conduct apply titanselect```

And thats it!.

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
