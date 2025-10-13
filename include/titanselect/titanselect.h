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
/// @warning The pointer returned is to the actual selected auton pointer. MODIFICATION IS STRONGLY DISCOURAGED.
/// @returns Name of the selected auton. "No Auton" if none is selected.
const char* ts_get_selected_auton_name();

/// All the names of the registered autons. Pass an array of length 16.
/// @warning The names populated in the buffer are pointers to the actual auton names at runtime. MODIFICATION IS STRONGLY DISCOURAGED.
/// @note If the size of the buffer is not 16 there will be undefined behavior.
/// @param buffer Array of const char* that is 16 in length.
/// @returns A populated buffer
void ts_get_auton_names(const char** buffer);

/// Attempts to select an auton on the selector.
/// @param name Name of the Auton.
/// @return Whether the inputted auton was selected.
bool ts_select_auton(const char* name);

/// Selects the next auton. Will go back to the first registered auton after reaching the end.
void ts_cycle_autons();

#ifdef __cplusplus
}
#endif