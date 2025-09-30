//titanselect C API
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// Creates an auton.
/// @param name Name of the auton
/// @param function Function pointer to the autons function.
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
/// @returns Name of the selected auton. nullptr if none is selected.
const char* ts_get_selected_auton_name();

#ifdef __cplusplus
}
#endif