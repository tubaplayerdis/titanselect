#include "../../include/titanselect/titanselect.h"
#include "../../include/titanselect/titanselect.hpp"
#include <functional>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <filesystem>
#include <functional>
#include "../../include/liblvgl/lvgl.h"
#include "../../include/pros/misc.hpp"
#include "../../include/pros/rtos.hpp"

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
    constexpr auto SELECTOR_LABEL_TEXT = "Selected: ";
    constexpr auto SELECTOR_LABEL_X = 10;
    constexpr auto SELECTOR_LABEL_Y = 6;
    constexpr auto SELECTOR_AUTON_FILE_PATH = "/usd/LastSelectedAuton.txt";
    constexpr auto SELECTOR_EMPTY_STRING = "";
}

//Internal lvgl objects.
struct selector_visual
{
    lv_obj_t* l_button_matrix;
    lv_obj_t* l_selected_auton_label;
};

selector_visual objects;

std::vector<ts::auton> registry_internal = std::vector<ts::auton>();
std::unique_ptr<ts::selector> selector_instance = nullptr;
static const char* btn_map[ts::SELECTOR_ROWS * ts::SELECTOR_COLS + ts::SELECTOR_COLS + 1] = {};//static as to not be deleted

std::string read_saved_auton()
{
    std::ifstream auton_file(ts::SELECTOR_AUTON_FILE_PATH);
    if (!auton_file || !auton_file.is_open()) return ts::SELECTOR_NO_AUTON_TEXT;
    
    std::string line;
    if(!std::getline(auton_file, line)) return ts::SELECTOR_NO_AUTON_TEXT;

    for(ts::auton auton : registry_internal)
    {
        if(line == auton.name) return auton.name;
    }

    return ts::SELECTOR_NO_AUTON_TEXT;
}

void write_saved_auton(std::string auton)
{
    std::ofstream file(ts::SELECTOR_AUTON_FILE_PATH);
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
    if(selector_instance) selector_instance.get()->refresh_selector();
}

void handle_events(lv_event_t *e)
{
    ts::selector* selector = ts::selector::get();
    lv_obj_t * obj = lv_event_get_target_obj(e); // get the button matrix object
    if (obj == objects.l_button_matrix)
    {
        uint32_t btn_id = lv_buttonmatrix_get_selected_button(obj); // get the ID of the pressed/released button
        std::string btn_text = lv_buttonmatrix_get_button_text(obj, btn_id);
        if(btn_text == ts::SELECTOR_NO_AUTON_TEXT) return;
        selector->select_auton(btn_text);
    }
}

ts::selector* ts::selector::get()
{
    if(!selector_instance) selector_instance = std::unique_ptr<ts::selector>( new selector() );
    return selector_instance.get();
}

ts::selector::selector()
{
    a_selected_auton = read_saved_auton();
    objects.l_button_matrix = nullptr;
    objects.l_selected_auton_label = nullptr;

    lv_obj_t * btnm = lv_buttonmatrix_create(lv_screen_active());

    //Normally this would go rows->cols, but button matrix likes to be difficult
    short aIndex = 0; //Index for taking stuff out of the autons
    short rIndex = 0; //Index for the one dimensional array of button map
    for (int i = 0; i < SELECTOR_COLS; i++)
    {
        for (int j = 0; j < SELECTOR_ROWS; j++)
        {
            //Item will not be valid
            if (registry_internal.size() > aIndex)
            {
                if (registry_internal[aIndex].function == nullptr)
                {
                    btn_map[rIndex] = SELECTOR_INVALID_AUTON_TEXT;
                } else
                {
                    btn_map[rIndex] = registry_internal[aIndex].name.c_str();
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

    lv_obj_add_event_cb(btnm, handle_events, LV_EVENT_VALUE_CHANGED, nullptr);

    objects.l_button_matrix = btnm;

    std::string labelText = SELECTOR_LABEL_TEXT;
    labelText.append(a_selected_auton);
    lv_obj_t* label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, labelText.c_str());
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, 0);
    lv_obj_set_pos(label, SELECTOR_LABEL_X, SELECTOR_LABEL_Y);
    objects.l_selected_auton_label = label;

    hide();
}

void ts::selector::refresh_selector()
{
    //Normally this would go rows->cols, but button matrix likes to be difficult
    short aIndex = 0; //Index for taking stuff out of the autons
    short rIndex = 0; //Index for the one dimensional array of button map
    for (int i = 0; i < SELECTOR_COLS; i++)
    {
        for (int j = 0; j < SELECTOR_ROWS; j++)
        {
            //Item will not be valid
            if (registry_internal.size() > aIndex)
            {
                if (registry_internal[aIndex].function == nullptr)
                {
                    btn_map[rIndex] = SELECTOR_INVALID_AUTON_TEXT;
                } else
                {
                    btn_map[rIndex] = registry_internal[aIndex].name.c_str();
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

    lv_buttonmatrix_set_map(objects.l_button_matrix, btn_map);
}

ts::selector::~selector()
{
    lv_obj_delete(objects.l_button_matrix);
    lv_obj_delete(objects.l_selected_auton_label);
}

void ts::selector::display()
{
    set_lv_obj_visibility(objects.l_button_matrix, false);
    set_lv_obj_visibility(objects.l_selected_auton_label, false);
}

void ts::selector::hide()
{
    set_lv_obj_visibility(objects.l_button_matrix, true);
    set_lv_obj_visibility(objects.l_selected_auton_label, true);
}

bool ts::selector::is_auton_selected()
{
    if(a_selected_auton == SELECTOR_EMPTY_STRING) return false;
    if(a_selected_auton == SELECTOR_NO_AUTON_TEXT) return false;
    if(a_selected_auton == SELECTOR_INVALID_AUTON_TEXT) return false;
    return true;
}

void ts::selector::run_selected_auton()
{
    if(!is_auton_selected()) return;

    for(ts::auton auton : registry_internal)
    {
        if(auton.name == a_selected_auton) return auton.function();
    }
}

void ts::selector::run_auton(std::string name)
{
    for(ts::auton auton : registry_internal)
    {
        if(name == auton.name) return auton.function();
    }
}

std::string ts::selector::get_selected_auton_name()
{
    return a_selected_auton;
}

std::vector<std::string> ts::selector::get_auton_names()
{
    std::vector<std::string> ret_autons = std::vector<std::string>();
    for(auton aut : registry_internal)
    {
        ret_autons.push_back(aut.name);
    }
    return ret_autons;
}

bool ts::selector::select_auton(std::string name)
{
    for(auton obj : registry_internal)
    {
        if(obj.name == name)
        {
            write_saved_auton(name);
            a_selected_auton = name;
            std::string format = SELECTOR_LABEL_TEXT + name;
            lv_label_set_text(objects.l_selected_auton_label, format.c_str());
            return true;
        }
    }
    return false;
}

void ts::selector::cycle_autons()
{
    if(!is_auton_selected() && registry_internal.size() != 0) {
        select_auton(registry_internal[0].name);
    } 
    if(!is_auton_selected()) {
        return;
    }
    for(int i = 0; i < registry_internal.size(); i++)
    {
        if(a_selected_auton == registry_internal[i].name)
        {
            if(i == registry_internal.size()-1)
            {
                select_auton(registry_internal[0].name);
                return;
            }
            select_auton(registry_internal[i+1].name);
            return;
        }
    }

}

ts::auton::auton(std::string Name, std::function<void()> Function)
{
    name = Name;
    function = Function;
    ts::selector::register_auton(*this);
}

//C-impl functions

extern "C" void ts_create_auton(const char* name, void(*function)())
{
    std::function<void()> wrapper;
    wrapper = function;
    ts::auton(std::string(name), wrapper);
}

extern "C" void ts_display_selector()
{
    ts::selector::get()->display();
}

extern "C" void ts_hide_selector()
{
    ts::selector::get()->hide();
}

extern "C" char ts_is_auton_selected()
{
    if(ts::selector::get()->is_auton_selected()) return 1;
    return 0;
}

extern "C" void ts_run_selected_auton()
{
    ts::selector::get()->run_selected_auton();
}

extern "C" void ts_run_auton(const char* name)
{
    ts::selector::get()->run_auton(std::string(name));
}

std::string selected_auton_name = "No Auton";

extern "C" const char* ts_get_selected_auton_name()
{
    selected_auton_name = ts::selector::get()->get_selected_auton_name();
    return selected_auton_name.c_str();
}

extern "C" void ts_get_auton_names(const char** buffer)
{
    for(int i = 0; i < ts::SELECTOR_COLS * ts::SELECTOR_ROWS; i++)
    {
        buffer[i] = registry_internal[i].name.c_str();
    }
}

extern "C" bool ts_select_auton(const char* name)
{
    return ts::selector::get()->select_auton(name);
}

extern "C" void ts_cycle_autons()
{
    ts::selector::get()->cycle_autons();
}