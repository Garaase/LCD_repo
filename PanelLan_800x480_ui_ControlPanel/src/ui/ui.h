// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
void ui_event_ButtonRelay1(lv_event_t * e);
void ui_event_ButtonRelay2(lv_event_t * e);
void ui_event_ButtonRelay3(lv_event_t * e);
void ui_event_ButtonRelay4(lv_event_t * e);
void ui_event_SliderWifiNode(lv_event_t * e);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_PanelNodeSelect;
extern lv_obj_t * ui_SliderWifiNode;
extern lv_obj_t * ui_LabelHeader;
extern lv_obj_t * ui_LabelNode1;
extern lv_obj_t * ui_LabelNode2;
extern lv_obj_t * ui_LabelNode3;
extern lv_obj_t * ui_ButtonRelay1;
extern lv_obj_t * ui_ButtonRelay2;
extern lv_obj_t * ui_ButtonRelay3;
extern lv_obj_t * ui_ButtonRelay4;
extern lv_obj_t * ui_LabelMainHeader;
extern lv_obj_t * ui_LabelBtnRelay1;
extern lv_obj_t * ui_LabelBtnRelay2;
extern lv_obj_t * ui_LabelBtnRelay3;
extern lv_obj_t * ui_LabelBtnRelay4;
extern lv_obj_t * ui_LabelStatus;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_fire3_png);    // assets/fire3.png






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif