//titanselect CPP API

#pragma once

#include "../liblvgl/lvgl.h"
#include <memory>
#include <vector>
#include <string>
#include <functional>

namespace ts
{   
    struct auton;

    class selector
    {
        friend struct auton;
        friend class std::unique_ptr<selector>;
        friend struct std::default_delete<selector>;
        static void register_auton(auton a);
        static void handle_events(lv_event_t *e);

        void refresh_selector();

        std::string a_selected_auton;

        lv_obj_t* l_button_matrix;
        lv_obj_t* l_selected_auton_label;
        lv_obj_t* l_run_selected_auton_button;
        lv_obj_t* l_run_selected_auton_button_label;

        selector();
        ~selector();

        public:

        /// Displays the selector on screen.
        void display();

        /// Hides the selector.
        void hide();

        /// Whether an auton is selected.
        /// @returns bool representing whether an auton is selected.
        bool is_auton_selected();

        /// Runs the selected auton.
        void run_selected_auton();

        /// Runs an auton by name.
        /// @param name Name of the auton to run.
        void run_auton(std::string name);

        /// The selected autons name.
        /// @return "No Auton" if none is selected, otherwise the selected autons name.
        std::string get_selected_auton_name();

        /// The names of all the autons registered with titanselect.
        /// @return vector of strings with the No Auton autons omited.
        std::vector<std::string> get_auton_names();

        /// Attempts to select an auton on the selector.
        /// @param name Name of the Auton.
        /// @return Whether the inputted auton was selected.
        bool select_auton(std::string name);

        /// Selects the next auton. Will go back to the first registered atuon after reaching the end.
        void cycle_autons();

        public:

        /// Access and or create the selector.
        /// @returns The selector.
        static selector* get();
    };

    struct auton
    {
        /// Name of the auton
        std::string name;

        /// Function pointer to the auton function
        std::function<void()> function;

        /// Creates and registers an auton.
        /// @param Name Name of the auton
        /// @param Function Function pointer of the function the auton should run.
        auton(std::string Name, std::function<void()> Function);
    };
}