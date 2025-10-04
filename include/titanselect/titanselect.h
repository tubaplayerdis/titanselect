//titanselect C API
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an auton.
/// @param name Name of the auton
/// @param function Function pointer to the auton's function.
void ts_create_auton(const char* name, void(*function)());

/// Initializes and displays the selector.
void ts_display_selector();

/// Hides the selector.
void ts_hide_selector();

/// Whether an auton is selected
/// @returns 0 or 1 on whether an auton is selected.
char ts_is_auton_selected();

/// Runs the selected auton.
void ts_run_selected_auton();

/// Runs the specified auton by name
/// @param name Name of the auton to run.
void ts_run_auton(const char* name);

/// Selected auton name.
/// @returns Name of the selected auton. "none" if none is selected.
const char* ts_get_selected_auton_name();

/// All the names of the registered autons. Pass an array of length 16.
/// @note autons not present are filled in as nullptr in the array.
/// @param buffer Array of const char* that is 16 in length.
/// @returns out
void ts_get_auton_names(const char** buffer);

/// Attempts to select an auton on the selector.
/// @param name Name of the Auton.
/// @return Whether the inputted auton was selected.
bool ts_select_auton(const char* name);

#ifdef __cplusplus
}
#endif