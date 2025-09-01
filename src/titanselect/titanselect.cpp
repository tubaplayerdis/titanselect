#include "../../include/titanselect/titanselect.h"
#include "../../include/titanselect/titanselect.hpp"
#include <functional>
#include <cstring>
#include <utility>
#include <fstream>
#include <filesystem>
#include "../../include/liblvgl/lvgl.h"
#include "../../include/pros/misc.hpp"

namespace ts
{
    constexpr auto SELECTOR_ROWS = 4;
    constexpr auto SELECTOR_COLS = 4;
    constexpr auto SELECTOR_HEIGHT = 200;
    constexpr auto SELECTOR_WIDTH = 475;
    constexpr auto SELECTOR_X_OFFSET = 0;
    constexpr auto SELECTOR_Y_OFFSET = 0;
    constexpr auto SELECTOR_NO_AUTON_TEXT = "No Auton";
    constexpr auto SELECTOR_INVALID_AUTON_TEXT = "Invalid Auton";
    constexpr auto SELECTOR_BUTTON_X = 290;
    constexpr auto SELECTOR_BUTTON_Y = 5;
    constexpr auto SELECTOR_BUTTON_WIDTH = 180;
    constexpr auto SELECTOR_BUTTON_HEIGHT = 30;
    constexpr auto SELECTOR_BUTTON_TEXT = "Test Selected Auton";
    constexpr auto SELECTOR_LABEL_TEXT = "Selected: ";
    constexpr auto SELECTOR_LABEL_X = 10;
    constexpr auto SELECTOR_LABEL_Y = 6;
    constexpr auto SELECTOR_AUTON_FILE_PATH = "/usd/LastSelectedAuton.txt";
}

std::vector<ts::auton> registry_internal = std::vector<ts::auton>();
std::unique_ptr<ts::selector> selector_instance = nullptr;

const char* read_saved_auton()
{
    std::ifstream auton_file(ts::SELECTOR_AUTON_FILE_PATH);
    if (!auton_file || !auton_file.is_open()) return nullptr;
    
    std::string line;
    if(!std::getline(auton_file, line)) return nullptr;

    for(ts::auton auton : registry_internal)
    {
        if(line.compare(auton.name) == 0) return auton.name;
    }

    return nullptr;
}

void write_saved_auton(const char* auton)
{
    std::ofstream file(ts::SELECTOR_NO_AUTON_TEXT);
    if (!file || !file.is_open()) return;
    file << auton;
    file.close();
}

void set_lv_obj_visibility(lv_obj_t *obj, bool hidden)
{
    hidden ? lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN) : lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void ts::selector::register_auton(ts::auton a)
{
    registry_internal.push_back(a);
}

void ts::selector::handle_events(lv_event_t *e)
{
    ts::selector* selector = ts::selector::get();
    lv_obj_t * obj = lv_event_get_target_obj(e); // get the button matrix object
    if (obj == selector->l_run_selected_auton_button)
    {
        auto master = pros::Controller(pros::E_CONTROLLER_MASTER);
        master.rumble("- - -");
        //Test if rumble waits.
        selector->run_selected_auton();
    }
    else if (obj == selector->l_button_matrix)
    {
        uint32_t btn_id = lv_buttonmatrix_get_selected_button(obj); // get the ID of the pressed/released button
        const char * btn_text = lv_buttonmatrix_get_button_text(obj, btn_id);
        selector->a_selected_auton = btn_text;
        std::string format = ts::SELECTOR_LABEL_TEXT;
        format.append(get()->a_selected_auton);
        lv_label_set_text(get()->l_selected_auton_label, format.c_str());
        write_saved_auton(selector->a_selected_auton);
    }
}

ts::selector* ts::selector::get()
{
    if(!selector_instance) selector_instance = std::unique_ptr<ts::selector>( new selector() );
    return selector_instance.get();
}

ts::selector::selector()
{
    a_selected_auton = SELECTOR_NO_AUTON_TEXT;
    l_button_matrix = nullptr;
    l_selected_auton_label = nullptr;
    l_run_selected_auton_button = nullptr;
    l_run_selected_auton_button_label = nullptr;

    const char* saved = read_saved_auton();
    if(saved) a_selected_auton = saved;

    lv_obj_t * btnm = lv_buttonmatrix_create(lv_screen_active());
    static const char* btn_map[SELECTOR_ROWS * SELECTOR_COLS + SELECTOR_COLS + 1] = {};


    //Normally this would go rows->cols, but button matrix likes to be difficult
    short aIndex = 0; //Index for taking stuff out of the autons
    short rIndex = 0; //Index for the one dimensional array of button map
    std::vector<auton> autons = registry_internal;
    for (int i = 0; i < SELECTOR_COLS; i++)
    {
        for (int j = 0; j < SELECTOR_ROWS; j++)
        {
            //Item will not be valid
            if (autons.size() > aIndex)
            {
                if (autons[aIndex].function == nullptr)
                {
                    btn_map[rIndex] = SELECTOR_INVALID_AUTON_TEXT;
                } else
                {
                    btn_map[rIndex] = autons[aIndex].name;
                }
            } else
            {
                btn_map[rIndex] = SELECTOR_NO_AUTON_TEXT;
            }
            aIndex++;
            rIndex++;
        }
        btn_map[rIndex] = "\n";
        rIndex++;
    }
    btn_map[rIndex] = "";


    lv_buttonmatrix_set_map(btnm, btn_map);

    lv_obj_set_size(btnm, SELECTOR_WIDTH, SELECTOR_HEIGHT);
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, SELECTOR_X_OFFSET, SELECTOR_Y_OFFSET);

    lv_obj_add_event_cb(btnm, selector::handle_events, LV_EVENT_VALUE_CHANGED, nullptr);

    l_button_matrix = btnm;


    lv_obj_t* btnau = lv_button_create(lv_screen_active());
    lv_obj_set_size(btnau, SELECTOR_BUTTON_WIDTH, SELECTOR_BUTTON_HEIGHT);
    lv_obj_set_pos(btnau, SELECTOR_BUTTON_X, SELECTOR_BUTTON_Y);
    lv_obj_t* btnlabel = lv_label_create(btnau);
    lv_label_set_text(btnlabel, SELECTOR_BUTTON_TEXT);
    lv_obj_align(btnlabel, LV_ALIGN_CENTER, 0, 0);

    l_run_selected_auton_button = btnau;
    l_run_selected_auton_button_label = btnlabel;

    std::string labelText = SELECTOR_LABEL_TEXT;
    labelText.append(a_selected_auton);
    lv_obj_t* label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, labelText.c_str());
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);
    lv_obj_set_pos(label, SELECTOR_LABEL_X, SELECTOR_LABEL_Y);
    l_selected_auton_label = label;

    hide();
}

ts::selector::~selector()
{
    lv_obj_delete(l_button_matrix);
    lv_obj_delete(l_selected_auton_label);
    lv_obj_delete(l_run_selected_auton_button);
    lv_obj_delete(l_run_selected_auton_button_label);
}

void ts::selector::display()
{
    set_lv_obj_visibility(l_button_matrix, true);
    set_lv_obj_visibility(l_selected_auton_label, true);
    set_lv_obj_visibility(l_run_selected_auton_button, true);
    set_lv_obj_visibility(l_run_selected_auton_button_label, true);
}

void ts::selector::hide()
{
    set_lv_obj_visibility(l_button_matrix, false);
    set_lv_obj_visibility(l_selected_auton_label, false);
    set_lv_obj_visibility(l_run_selected_auton_button, false);
    set_lv_obj_visibility(l_run_selected_auton_button_label, false);
}

bool ts::selector::is_auton_selected()
{
    if(!a_selected_auton) return false;
    if(strcmp(a_selected_auton, SELECTOR_NO_AUTON_TEXT) == 0) return false;
    if(strcmp(a_selected_auton, SELECTOR_INVALID_AUTON_TEXT) == 0) return false;
    return true;
}

void ts::selector::run_selected_auton()
{
    if(!is_auton_selected()) return;

    for(ts::auton auton : registry_internal)
    {
        if(strcmp(a_selected_auton, auton.name) == 0) return auton.function();
    }
}

void ts::selector::run_auton(const char* name)
{
    for(ts::auton auton : registry_internal)
    {
        if(strcmp(name, auton.name) == 0) return auton.function();
    }
}

const char* ts::selector::get_selected_auton_name()
{
    return a_selected_auton;
}

//C-impl functions

extern "C" void create_auton(const char* name, void(*function)())
{
    ts::auton(name, function);
}

extern "C" void selector_display_selector()
{
    ts::selector::get()->display();
}

extern "C" void selector_hide_selector()
{
    ts::selector::get()->hide();
}

extern "C" char selector_is_auton_selected()
{
    if(ts::selector::get()->is_auton_selected()) return 1;
    return 0;
}

extern "C" void selector_run_selected_atuon()
{
    ts::selector::get()->run_selected_auton();
}

extern "C" void selector_run_atuon(const char* name)
{
    ts::selector::get()->run_auton(name);
}

extern "C" const char* selector_get_selected_auton_name()
{
    return ts::selector::get()->get_selected_auton_name();
}