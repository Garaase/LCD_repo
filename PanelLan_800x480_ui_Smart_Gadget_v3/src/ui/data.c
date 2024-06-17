//extern lv_coord_t __chart1_series_array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#include "lvgl.h"
//lv_coord_t * data_Chart1_series_array;
//lv_coord_t * data_Chart2_series_array;
bool BtnRelay1Toggle = false;
bool BtnRelay2Toggle = false;
bool BtnRelay3Toggle = false;
bool BtnRelay4Toggle = false;
bool BtnRelaysToggled = false;
char selectWifiNode = 1;
bool switch1Status;
char _SWITCHSTATUS;
char activeScreen = 1;
int32_t sliderLevelValue = 0;
bool screen1 = false;
bool screen2 = false;
bool screen3 = false;

enum SWITCHSTATUS; 