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
//void ui_event_splash(lv_event_t * e);
extern lv_obj_t * ui_splash;
// SCREEN: ui_ScreenWeather
void ui_ScreenWeather_screen_init(void);
void ui_event_ScreenWeather_previous(lv_event_t * e);
void ui_event_ScreenWeather_next(lv_event_t * e);
extern lv_obj_t * ui_ScreenWeather;
extern lv_obj_t * ui_WeatherHeader;
extern lv_obj_t * ui_WeatherHeader1;
extern lv_obj_t * ui_iconWeather;
extern lv_obj_t * ui_iconTemp;
extern lv_obj_t * ui_iconAirPressure;
extern lv_obj_t * ui_iconAirHumidity;
extern lv_obj_t * ui_iconWindSpeed;
extern lv_obj_t * ui_ContainerWeatherForcast;
extern lv_obj_t * ui_LbTempText1;
extern lv_obj_t * ui_LbPressureText1;
extern lv_obj_t * ui_LbHumidityText1;
extern lv_obj_t * ui_LbWindspeedText1;
extern lv_obj_t * ui_LbTempValue1;
extern lv_obj_t * ui_LbPressureValue1;
extern lv_obj_t * ui_LbHumidityValue1;
extern lv_obj_t * ui_LbWindspeedValue1;
extern lv_obj_t * ui_LbTempUnit1;
extern lv_obj_t * ui_LbPressureUnit1;
extern lv_obj_t * ui_LbHumidityUnit1;
extern lv_obj_t * ui_LbWindspeedUnit1;
extern lv_obj_t * ui_ContainerIndoorTemp;
extern lv_obj_t * ui_LbTempText2;
extern lv_obj_t * ui_LbPressureText2;
extern lv_obj_t * ui_LbHumidityText2;
extern lv_obj_t * ui_LbWindspeedText2;
extern lv_obj_t * ui_LbTempValue2;
extern lv_obj_t * ui_LbPressureValue2;
extern lv_obj_t * ui_LbHumidityValue2;
extern lv_obj_t * ui_LbWindspeedValue2;
extern lv_obj_t * ui_LbTempUnit2;
extern lv_obj_t * ui_LbPressureUnit2;
extern lv_obj_t * ui_LbHumidityUnit2;
extern lv_obj_t * ui_LbWindspeedUnit2;
extern lv_obj_t * ui_ScreenWeather_previous;
extern lv_obj_t * ui_ScreenWeather_next;
extern lv_obj_t * ui_lbSc1LoadStatus;
// extern lv_obj_t * ui_ScreenWeather_previous;
// extern lv_obj_t * ui_ScreenWeather_next; 
extern lv_obj_t * ui_LbTimeAndDate;

// SCREEN: ui_ScreenLightControl
void ui_ScreenLightControl_screen_init(void);
extern lv_obj_t * ui_ScreenLightControl;
extern lv_obj_t * ui_PanelLightControl;
extern lv_obj_t * ui_ContainerLightStrip;
void ui_event_SwitchLightStripOnOff(lv_event_t * e);
extern lv_obj_t * ui_SwitchLightStripOnOff;
extern lv_obj_t * ui_LbSwLightStripStatusText;
void ui_event_SwLightStripBrightness(lv_event_t * e);
extern lv_obj_t * ui_LbSwLightStripBrightness;
extern lv_obj_t * ui_LbSwBriDesc;
extern lv_obj_t * ui_ContainerRGBLamp1;
void ui_event_SwitchRGBLamp1OnOff(lv_event_t * e);
extern lv_obj_t * ui_SwitchRGBLamp1OnOff;
extern lv_obj_t * ui_LbSwRGBLamp1StatusText;
void ui_event_SwRGBLamp1ColorAndBrightness(lv_event_t * e);
extern lv_obj_t * ui_LbSwRGBLamp1ColorAndBrightness;
extern lv_obj_t * ui_LbSwRGBLamp1ColAndBriDesc;
extern lv_obj_t * ui_ContainerRGBLamp2;
void ui_event_SwitchRGBLamp2OnOff(lv_event_t * e);
extern lv_obj_t * ui_SwitchRGBLamp2OnOff;
extern lv_obj_t * ui_LbSwRGBLamp2StatusText;
void ui_event_SwRGBLamp2ColorAndBrightness(lv_event_t * e);
extern lv_obj_t * ui_LbSwRGBLamp2ColorAndBrightness;
extern lv_obj_t * ui_LbSwRGBLamp2ColAndBriDesc;
extern lv_obj_t * ui_ContainerRGBLamp3;
void ui_event_SwitchRGBLamp3OnOff(lv_event_t * e);
extern lv_obj_t * ui_SwitchRGBLamp3OnOff;
extern lv_obj_t * ui_LbSwRGBLamp3StatusText;
void ui_event_SwRGBLamp3ColorAndBrightness(lv_event_t * e);
extern lv_obj_t * ui_SwRGBLamp3ColorAndBrightness;
extern lv_obj_t * ui_LbSwRGBLamp3ColAndBriDesc;
extern lv_obj_t * ui_LbSwLightStripDesc;
extern lv_obj_t * ui_LbSwRGBLamp1Desc;
extern lv_obj_t * ui_LbSwRGBLamp2Desc;
extern lv_obj_t * ui_LbSwRGBLamp3Desc;
extern lv_obj_t * ui_LbLightControlHeader;
void ui_event_ScreenLightControl_previous(lv_event_t * e);
void ui_event_ScreenLightControl_next(lv_event_t * e);
extern lv_obj_t * ui_ScreenLightControl_previous;
extern lv_obj_t * ui_ScreenLightControl_next;

// SCREEN: ui_ScreenColorPicker
void ui_ScreenColorPicker_screen_init(void);
extern lv_obj_t * ui_ScreenColorPicker;
void ui_event_BtnColorPickerDone(lv_event_t * e);
void ui_event_BtnSc3Left(lv_event_t * e);
void ui_event_BtnSc3Right(lv_event_t * e);
void ui_event_ArcColorPicker(lv_event_t * e);
extern lv_obj_t * ui_BtnColorPickerDone;
extern lv_obj_t * ui_LbColorPickerBtnText;
extern lv_obj_t * ui_PanelColorPicker;
extern lv_obj_t * ui_ArcColorPicker;
extern lv_obj_t * ui_LbColorPicker;
extern lv_obj_t * ui_BtnSc3Left;
extern lv_obj_t * ui_BtnSc3Right;
extern lv_obj_t * ui_LbArcColorPickerText;
void ui_event_ArcBrightness(lv_event_t * e);
extern lv_obj_t * ui_ArcBrightness;
extern lv_obj_t * ui_LbArcBrightnessText;

// SCREEN: ui_ScreenColorTemp
void ui_ScreenColorTemp_screen_init(void);
extern lv_obj_t * ui_ScreenColorTemp;
void ui_event_BtnColorTempDone(lv_event_t * e);
extern lv_obj_t * ui_BtnColorTempDone;
extern lv_obj_t * ui_LbColorTempBtnText;
extern lv_obj_t * ui_PanelColorTemp;
extern lv_obj_t * ui_LbColorTemp;
extern lv_obj_t * ui_ArcColorTempsLightStrip;
extern lv_obj_t * ui_LbArcLightStripColorTempText;
void ui_event_ArcBrightnessLightStrip(lv_event_t * e);
void ui_event_ArcColorTempsLightStrip(lv_event_t * e);
extern lv_obj_t * ui_ArcBrightnessLightStrip;
extern lv_obj_t * ui_LbArcLightStripBriText;
void ui_event_BtnSc5Left(lv_event_t * e);
void ui_event_BtnSc5Right(lv_event_t * e);
extern lv_obj_t * ui_BtnSc5Left;
extern lv_obj_t * ui_BtnSc5Right;

// CUSTOM VARIABLES
extern lv_obj_t * uic_Image1;
// EVENTS
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_logo4b_png);    // assets/logo4b.pngui_event_ArcColorTempsLightStrip
LV_IMG_DECLARE(ui_img_arrow3_r_png);    // assets/pattern1b1.png
LV_IMG_DECLARE(ui_img_arrow3_l_png);    // assets/pattern1b1.png
LV_IMG_DECLARE(ui_img_arch_gradient_bg_png);    // assets/arch_gradient_bg.png
LV_IMG_DECLARE(ui_img_colortemp_cicle_2_png);  

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE(ui_img_background_png);    // assets/background.png
LV_IMG_DECLARE(ui_img_999054828);    // assets/icons8-partly-cloudy-day-50.png
LV_IMG_DECLARE(ui_img_1578496546);    // assets/icons8-thermometer-50.png
LV_IMG_DECLARE(ui_img_1668089981);    // assets/icons8-pressure-gauge-50.png
LV_IMG_DECLARE(ui_img_947629812);    // assets/icons8-hygrometer-50.png
LV_IMG_DECLARE(ui_img_233333594);    // assets/icons8-air-50.png
LV_IMG_DECLARE(ui_img_blue_background_5_png);    // assets/blue_background_5.png
LV_IMG_DECLARE(ui_img_pattern1b1_png);    // assets/pattern1b1.png
// FONTS
LV_FONT_DECLARE(ui_font_NumberDotsFont);
LV_FONT_DECLARE(ui_font_NumberDotsFont30);
LV_FONT_DECLARE(ui_font_NumbersDigital);
LV_FONT_DECLARE(ui_font_NumbersDigital60);
LV_FONT_DECLARE(ui_font_AnandaBlack);
LV_FONT_DECLARE(ui_font_AnandaBlack40);

// UI INIT
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif