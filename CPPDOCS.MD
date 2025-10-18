# Titanselect C++ API Reference

## Namespace: `ts`

### Struct: `ts::auton`

Represents a single autonomous routine.  
When constructed, it automatically registers itself with the `selector`.

---

#### **Public Members**

| Member | Type | Description |
|--------|------|-------------|
| `name` | `std::string` | The name of the auton. |
| `function` | `std::function<void()>` | Function pointer to the auton’s executable routine. |

---

#### **Constructor**

##### `auton(std::string Name, std::function<void()> Function)`
Creates and registers an auton.  
**Parameters:**
- `Name` — The name of the auton.
- `Function` — Pointer to the function that implements the auton’s logic.

---

### Class: `ts::selector`

Auton selection interface for VEX robots using PROS.  
Handles registration, display, and execution of autonomous routines.

---

#### **Static Methods**

##### `static selector* get()`
Accesses (and if necessary, creates) the global selector instance.  
**Returns:** Pointer to the selector.

---

#### **Public Methods**

##### `void display()`
Displays the selector interface on the screen.

---

##### `void hide()`
Hides the selector interface from the screen.

---

##### `bool is_auton_selected()`
Checks if an auton is currently selected.  
**Returns:** `true` if an auton is selected, otherwise `false`.

---

##### `void run_selected_auton()`
Executes the currently selected auton.

---

##### `void run_auton(std::string name)`
Runs a specific auton by its name.  
**Parameters:**
- `name` — The name of the auton to run.

---

##### `std::string get_selected_auton_name()`
Retrieves the name of the currently selected auton.  
**Returns:**
- `"none"` if no auton is selected.
- Otherwise, the name of the selected auton.

---

##### `std::vector<std::string> get_auton_names()`
Retrieves the names of all registered autons, excluding “No Auton.”  
**Returns:** A vector of auton names.

---

##### `bool select_auton(std::string name)`
Attempts to select an auton by name.  
**Parameters:**
- `name` — The name of the auton to select.  
  **Returns:**  
  `true` if the auton was successfully selected, otherwise `false`.

---

##### `void cycle_autons()`
Selects the next auton. Will go back to the first registered atuon after reaching the end.

---

### Example Usage

```cpp
#include "titanselect.hpp"

void left_auton() {
    // Left-side autonomous routine
}

void right_auton() {
    // Right-side autonomous routine
}

void autonomous() {
    // Run the currently selected auton
	ts::selector::get()->run_selected_auton();
}

void initialize() {
    // Register autonomous routines
    ts::auton left("Left", left_auton);
    ts::auton right("Right", right_auton);
    
    // Display selector
    ts::selector::get()->display();
}
```
