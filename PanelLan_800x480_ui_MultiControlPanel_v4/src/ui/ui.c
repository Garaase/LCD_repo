// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "data.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_splash
void ui_splash_screen_init(void);
void ui_event_splash(lv_event_t * e);
lv_obj_t * ui_splash;

// SCREEN: ui_ScreenWeather
void ui_ScreenWeather_screen_init(void);
void ui_event_BtnSc1Left(lv_event_t * e);
void ui_event_BtnSc1Right(lv_event_t * e);
void ui_event_BtnSc1Left(lv_event_t * e);
void ui_event_BtnSc1Right(lv_event_t * e);
lv_obj_t * ui_ScreenWeather;
lv_obj_t * ui_BarTemp;
lv_obj_t * ui_lbTempMain;
lv_obj_t * ui_Label15;
lv_obj_t * ui_Label16;
lv_obj_t * ui_Label17;
lv_obj_t * ui_Label18;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Bar3;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_LbPressure;
lv_obj_t * ui_Label5;
lv_obj_t * ui_LbAltitude;
lv_obj_t * ui_Label7;
lv_obj_t * ui_LbHumidity;
lv_obj_t * ui_Label9;
lv_obj_t * ui_LbTemp;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Label14;
lv_obj_t * ui_Bar4;
lv_obj_t * ui_BtnSc1Left;
lv_obj_t * ui_BtnSc1Right;
lv_obj_t * ui_lbSc1LoadStatus;
void ui_ScreenSwitchNode1_screen_init(void);
void ui_event_ScreenSwitch(lv_event_t * e);
void ui_event_BtnSc2Left(lv_event_t * e);
void ui_event_BtnSc2Right(lv_event_t * e);
lv_obj_t * ui_LabelHeaderNode1;
lv_obj_t * ui_ScreenSwitchNode1;
lv_obj_t * ui_PanelSwitch1Node1;
lv_obj_t * ui_PanelSwitch2Node1;
lv_obj_t * ui_PanelSwitch3Node1;
lv_obj_t * ui_PanelSwitch4Node1;
lv_obj_t * ui_Switch1Node1;
lv_obj_t * ui_Switch2Node1;
lv_obj_t * ui_Switch3Node1;
lv_obj_t * ui_Switch4Node1;
lv_obj_t * ui_Bar2;
lv_obj_t * ui_BtnSc2Left;
lv_obj_t * ui_BtnSc2Right; 
lv_obj_t * ui_lbSc2LoadStatus;
lv_obj_t * ui_LbSwitch1Node1;
lv_obj_t * ui_LbSwitch2Node1;
lv_obj_t * ui_LbSwitch3Node1;
lv_obj_t * ui_LbSwitch4Node1;

void ui_ScreenSwitchNode2_screen_init(void);
void ui_event_ScreenSwitch(lv_event_t * e);
void ui_event_BtnSc3Left(lv_event_t * e);
void ui_event_BtnSc3Right(lv_event_t * e);
lv_obj_t * ui_LabelHeaderNode2;
lv_obj_t * ui_ScreenSwitchNode2;
lv_obj_t * ui_PanelSwitch1Node2;
lv_obj_t * ui_PanelSwitch2Node2;
lv_obj_t * ui_PanelSwitch3Node2;
lv_obj_t * ui_PanelSwitch4Node2;
lv_obj_t * ui_Switch1Node2;
lv_obj_t * ui_Switch2Node2;
lv_obj_t * ui_Switch3Node2;
lv_obj_t * ui_Switch4Node2;
lv_obj_t * ui_Bar1;
lv_obj_t * ui_BtnSc3Left;
lv_obj_t * ui_BtnSc3Right;
lv_obj_t * ui_lbSc3LoadStatus;
lv_obj_t * ui_LbSwitch1Node2;
lv_obj_t * ui_LbSwitch2Node2;
lv_obj_t * ui_LbSwitch3Node2;
lv_obj_t * ui_LbSwitch4Node2;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_patternb[1] = {&ui_img_pattern1b1_png};

///////////////////// TEST LVGL SETTINGS ////////////////////

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_splash(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_LONG_PRESSED_REPEAT) {        
        if (screenLastOnFocus == 2)
        {
            _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 1, 1500, &ui_ScreenWeather_screen_init);
        }
        else if (screenLastOnFocus == 3)
        {
            _ui_screen_change(&ui_ScreenSwitchNode1, LV_SCR_LOAD_ANIM_FADE_ON, 1, 1500, &ui_ScreenSwitchNode1_screen_init);
        }
        else if (screenLastOnFocus == 4)
        {
            _ui_screen_change(&ui_ScreenSwitchNode2, LV_SCR_LOAD_ANIM_FADE_ON, 1, 1500, &ui_ScreenSwitchNode2_screen_init);
        }        
        
        lockScreenTimer = millis();
    }
    if (event_code == LV_EVENT_ALL)
    {
        lockScreenTimer = millis();
    }    
}

void ui_event_Switch1Node1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 11 : 10;
    }
}
void ui_event_Switch2Node1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 22 : 20;
    }
}
void ui_event_Switch3Node1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 33 : 30;
    }
}
void ui_event_Switch4Node1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 44 : 40;
    }
}

void ui_event_Switch1Node2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        //LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 11 : 10;
    }
}
void ui_event_Switch2Node2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 22 : 20;
    }
}
void ui_event_Switch3Node2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 33 : 30;
    }
}
void ui_event_Switch4Node2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_UNUSED(obj);
        _SWITCHSTATUS = lv_obj_has_state(obj, LV_STATE_CHECKED) ? 44 : 40;
    }
}

void ui_event_BtnSc1Left(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSwitchNode2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSwitchNode2_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        screenLastOnFocus = 4;
        lockScreenTimer = millis();
    }
}
void ui_event_BtnSc1Right(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSwitchNode1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSwitchNode1_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        screenLastOnFocus = 3;
        lockScreenTimer = millis();
    }
}
void ui_event_BtnSc2Left(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenWeather_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        screenLastOnFocus = 2;
        lockScreenTimer = millis();
    }
}
void ui_event_BtnSc2Right(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSwitchNode2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSwitchNode2_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        screenLastOnFocus = 4;
        lockScreenTimer = millis();
    }
}
void ui_event_BtnSc3Left(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSwitchNode1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSwitchNode1_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        screenLastOnFocus = 3;
        lockScreenTimer = millis();
    }
}
void ui_event_BtnSc3Right(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenWeather_screen_init);
        _ui_flag_modify(ui_lbSc1LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc2LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_lbSc3LoadStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        screenLastOnFocus = 2;
        lockScreenTimer = millis();
    }
}
///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_splash_screen_init();
    ui_ScreenWeather_screen_init();
    ui_ScreenSwitchNode1_screen_init();
    ui_ScreenSwitchNode2_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_splash);
}
