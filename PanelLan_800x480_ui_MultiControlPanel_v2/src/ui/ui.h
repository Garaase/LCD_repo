// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_splash
void ui_splash_screen_init(void);
void ui_event_splash(lv_event_t * e);
extern lv_obj_t * ui_splash;
// SCREEN: ui_ScreenWeather
void ui_ScreenWeather_screen_init(void);
void ui_event_ScreenWeather(lv_event_t * e);
extern lv_obj_t * ui_ScreenWeather;
extern lv_obj_t * ui_PanelTempereture;
extern lv_obj_t * ui_PanelHumidity;
extern lv_obj_t * ui_PanelMaxMinTemp;
extern lv_obj_t * ui_PanelPressure;
extern lv_obj_t * ui_LabelHeader;
extern lv_obj_t * ui_LabelTempereture;
extern lv_obj_t * ui_LabelHumidity;
extern lv_obj_t * ui_LabelMaxMinTemp;
extern lv_obj_t * ui_LabelPressure;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
// SCREEN: ui_ScreenSwitch
void ui_ScreenSwitch_screen_init(void);
void ui_event_ScreenSwitch(lv_event_t * e);
extern lv_obj_t * ui_ScreenSwitch;
extern lv_obj_t * ui_PanelTempereture1;
extern lv_obj_t * ui_PanelHumidity1;
extern lv_obj_t * ui_PanelMaxMinTemp1;
extern lv_obj_t * ui_PanelPressure1;
extern lv_obj_t * ui_LabelHeader1;
extern lv_obj_t * ui_LabelHumidity1;
extern lv_obj_t * ui_LabelMaxMinTemp1;
extern lv_obj_t * ui_LabelPressure1;
extern lv_obj_t * ui_Switch1;
extern lv_obj_t * ui_Switch2;
extern lv_obj_t * ui_Switch3;
extern lv_obj_t * ui_Switch4;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_logo4b_png);    // assets/logo4b.png
LV_IMG_DECLARE(ui_img_pattern1b1_png);    // assets/pattern1b1.png






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif