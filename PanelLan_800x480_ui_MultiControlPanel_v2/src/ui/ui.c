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
void ui_event_ScreenWeather(lv_event_t * e);
lv_obj_t * ui_ScreenWeather;
lv_obj_t * ui_PanelTempereture;
lv_obj_t * ui_PanelHumidity;
lv_obj_t * ui_PanelMaxMinTemp;
lv_obj_t * ui_PanelPressure;
lv_obj_t * ui_LabelHeader;
lv_obj_t * ui_LabelTempereture;
lv_obj_t * ui_LabelHumidity;
lv_obj_t * ui_LabelMaxMinTemp;
lv_obj_t * ui_LabelPressure;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;


// SCREEN: ui_ScreenSwitch
void ui_ScreenSwitch_screen_init(void);
void ui_event_ScreenSwitch(lv_event_t * e);
lv_obj_t * ui_ScreenSwitch;
lv_obj_t * ui_PanelTempereture1;
lv_obj_t * ui_PanelHumidity1;
lv_obj_t * ui_PanelMaxMinTemp1;
lv_obj_t * ui_PanelPressure1;
lv_obj_t * ui_LabelHeader1;
lv_obj_t * ui_LabelHumidity1;
lv_obj_t * ui_LabelMaxMinTemp1;
lv_obj_t * ui_LabelPressure1;
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Switch2;
lv_obj_t * ui_Switch3;
lv_obj_t * ui_Switch4;
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
            _ui_screen_change(&ui_ScreenSwitch, LV_SCR_LOAD_ANIM_FADE_ON, 1, 1500, &ui_ScreenSwitch_screen_init);
        }
        
        lockScreenTimer = millis();
    }
    if (event_code == LV_EVENT_ALL)
    {
        lockScreenTimer = millis();
    }    
}
void ui_event_ScreenWeather(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        //screenOnFocus = 3;
        screenLastOnFocus = 3;
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenSwitch, LV_SCR_LOAD_ANIM_FADE_ON, 0, 400, &ui_ScreenSwitch_screen_init);
        lockScreenTimer = millis();
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        //screenOnFocus = 3;
        screenLastOnFocus = 3;
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenSwitch, LV_SCR_LOAD_ANIM_FADE_ON, 0, 400, &ui_ScreenSwitch_screen_init);
        lockScreenTimer = millis();
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        //screenOnFocus = 1;
        _ui_screen_change(&ui_splash, LV_SCR_LOAD_ANIM_FADE_ON, 0, 1500, &ui_splash_screen_init);
        lockScreenTimer = millis();
    }
    if (event_code == LV_EVENT_ALL)
    {
        lockScreenTimer = millis();
    } 
    
}
void ui_event_ScreenSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        //screenOnFocus = 2;
        screenLastOnFocus = 2;
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 0, 400, &ui_ScreenWeather_screen_init);
        lockScreenTimer = millis();
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        //screenOnFocus = 2;
        screenLastOnFocus = 2;
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 0, 400, &ui_ScreenWeather_screen_init);
        lockScreenTimer = millis();
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        //screenOnFocus = 1;
        _ui_screen_change(&ui_splash, LV_SCR_LOAD_ANIM_FADE_ON, 0, 1500, &ui_splash_screen_init);
        lockScreenTimer = millis();
    }
    if (event_code == LV_EVENT_ALL)
    {
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
    ui_ScreenSwitch_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_splash);
}
