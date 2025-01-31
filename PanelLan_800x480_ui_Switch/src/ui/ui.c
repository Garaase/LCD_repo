// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "data.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ScreenSwitchBoard
void ui_ScreenSwitchBoard_screen_init(void);
void ui_event_ScreenSwitchBoard(lv_event_t * e);
lv_obj_t * ui_ScreenSwitchBoard;
void ui_event_Switch1(lv_event_t * e);
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Switch2;
lv_obj_t * ui_Switch3;
lv_obj_t * ui_Switch4;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label5;


// SCREEN: ui_ScreenChart
void ui_ScreenChart_screen_init(void);
void ui_event_ScreenChart(lv_event_t * e);
lv_obj_t * ui_ScreenChart;
lv_obj_t * ui_Chart1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_Chart2;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label9;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
// #if LV_COLOR_DEPTH != 32
//     #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
// #endif
// #if LV_COLOR_16_SWAP !=0
//     #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
// #endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ScreenSwitchBoard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    // if(event_code == LV_EVENT_CLICKED) {
    //     _ui_basic_set_property(ui_ScreenChart, _UI_BASIC_PROPERTY_POSITION_X,  0);
    // }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenChart, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenChart_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenChart, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenChart_screen_init);
    }
}
void ui_event_Switch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 11;
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 10;
    }
}
void ui_event_Switch2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 22;
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 20;
    }
}
void ui_event_Switch3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 33;
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 30;
    }
}
void ui_event_Switch4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 44;
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _SWITCHSTATUS = 40;
    }
}
void ui_event_ScreenChart(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenSwitchBoard, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenSwitchBoard_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenSwitchBoard, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenSwitchBoard_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenSwitchBoard_screen_init();
    ui_ScreenChart_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_ScreenSwitchBoard);
}
