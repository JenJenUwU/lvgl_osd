
# On Screen Display (OSD) with LVGL

A simple OSD created with the [v8.2 of the LVGL library](https://docs.lvgl.io/8.2/).


## Installation

#### 1. Clone the lvgl_osd branch project with github

```bash
  git clone -b lvgl_osd git@gitlab.com:skywatch_pvm/pvm_osd.git [directory_name]
```
or
```bash
  git clone -b lvgl_osd https://gitlab.com/skywatch_pvm/pvm_osd.git [directory_name]
``` 
#### 2. Installing all the submodules

```bash
    cd [directory_name]
    git submodule update --init --recursive
```
#### 3. Run the build script in the main directory
```bash
    cd ..
    ./build_osd.sh
```
#### 4. Use the executable files however you like
located at `[directory_name]/build/bin/lvgl_osd`
## Documentation
### `main.c`
Initailizes lvgl, framebuffer display and input driver. As well as calling the menu gui through lvgl.
### `lv_osd_indev.c`
Distinguishes if the file descriptor is initialized correctly as well as coverting the input signals from keypad into lvgl actions (next object, select, etc).
### `lv_osd_menu_init.c`
Initializes the default group and screen. Also creates all the object with their respective name, symbol and initial value
### `lv_osd_menu_obj.c`
Functions that create differnt type of objects (dropdown list, sliders, buttons, switches, text containers). All type of object has a respective call back functions that calls the output function once the object value has been changed.
### `cb_output/*`
Output  functions that runs once an object value has changed. It checks the object label as well as the value to ensure the right output has been send. Organized by the type of object.
## Issues
#### 1. Unable to implement freetype font into lvgl
Although the library has successfuly installed, after mimicing the [demo](https://github.com/lvgl/lvgl/blob/e19410f8f8a256609da72cff549598e0df6fa4cf/examples/libs/freetype/lv_example_freetype_1.c) provided by lvgl the compiling process has not issues. However, when ran on the device, the osd does not show up and throws an error instead.
#### 2. Output of each object has not be set yet
Files located in `main_directory/lvgl_osd/src/cb_output/*`.