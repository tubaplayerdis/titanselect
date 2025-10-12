# TitanSelect C API Reference

C interface for the TitanSelect auton selector system used in VEX robots running PROS.  
This API provides procedural access to the auton registration, selection, and execution system.

---

### Function: `void ts_create_auton(const char* name, void(*function)())`
Creates and registers a new autonomous routine.  

**Parameters:**
- `name` — The name of the auton.
- `function` — Pointer to the function that defines the auton’s behavior.

---

### Function: `void ts_display_selector()`
Initializes and displays the auton selector on screen.

---

### Function: `void ts_hide_selector()`
Hides the auton selector interface.

---

### Function: `char ts_is_auton_selected()`
Checks whether an auton is currently selected.

**Returns:**
- `1` if an auton is selected.
- `0` otherwise.

---

### Function: `void ts_run_selected_auton()`
Runs the currently selected auton.

---

### Function: `void ts_run_auton(const char* name)`
Runs a specific auton by name.

**Parameters:**
- `name` — The name of the auton to execute.

---

### Function: `const char* ts_get_selected_auton_name()`
Retrieves the name of the currently selected auton.

**Returns:**
- Pointer to the selected auton’s name.
- `"No Auton"` if none is selected.

⚠️ **Warning:**  
The returned pointer references internal data — **modifying it is strongly discouraged.**

---

### Function: `void ts_get_auton_names(const char** buffer)`
Retrieves the names of all registered autons.

**Parameters:**
- `buffer` — Array of `const char*` with a **fixed length of 16**.  
  It will be populated with auton name pointers.

**Notes:**
- The function modifies the contents of the array passed in.
- If the buffer size is not exactly 16, **behavior is undefined**.
- The strings in the buffer point to internal auton names and **must not be modified**.

---

### Function: `bool ts_select_auton(const char* name)`
Attempts to select an auton by name.

**Parameters:**
- `name` — The name of the auton to select.

**Returns:**
- `true` if the auton was successfully selected.
- `false` otherwise.

---

### Function: `void ts_cycle_autons()`
Selects the next auton. Will go back to the first registered atuon after reaching the end.

---

### Example Usage

```c
#include "titanselect.h"

void left_auton() {
    // Code for left autonomous routine
}

void right_auton() {
    // Code for right autonomous routine
}

void initialize() {
    // Register autons
    ts_create_auton("Left", left_auton);
    ts_create_auton("Right", right_auton);

    // Display selector
    ts_display_selector();

    // Example: manually select and run an auton
    if (ts_select_auton("Left")) {
        ts_run_selected_auton();
    }
}
```
