//extern lv_coord_t __chart1_series_array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#include "lvgl.h"
lv_coord_t * data_Chart1_series_array;
lv_coord_t * data_Chart2_series_array;
bool switch1Status;
char PRESSEDSWITCH = 0;
char lastPRESSEDSWITCH = 0;
char arcInit;

enum SWITCHSTATUS;
enum SCREEN;
uint32_t lockScreenTimer = 0;
bool splashScreenOn = false;
char screenOnFocus = 0;
char screenLastOnFocus = 2;
bool imgBtn1Sc2_status = false;
bool imgBtn2Sc2_status = false;
bool imgBtn3Sc2_status = false;
bool imgBtn4Sc2_status = false;

lv_color32_t cPickerRGBValue; 
bool cPickRBGBrightnessChanged = false;
bool cPickRBGColorChanged = false;
bool lightstripBrightnessChanged = false;
bool lightstripColorTempChanged = false;
int16_t lightstripColorTemp = 0;
int16_t rgbLampBrightness;
int16_t lightstripBrightness;
const char* objectName;

bool SwitchLightStripOnOff = false;
bool SwitchRGBLamp1OnOff = false;
bool SwitchRGBLamp2OnOff = false;
bool SwitchRGBLamp3OnOff = false;

bool startColorTempScreen = false;
bool startColorPickerScreen = false;

char swLightstripPressed;
char swRgbLamp1Pressed;
char swRgbLamp2Pressed;
char swRgbLamp3Pressed;