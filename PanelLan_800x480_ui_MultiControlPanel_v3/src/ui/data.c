//extern lv_coord_t __chart1_series_array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#include "lvgl.h"
lv_coord_t * data_Chart1_series_array;
lv_coord_t * data_Chart2_series_array;
bool switch1Status;
char _SWITCHSTATUS;
char arcInit;

enum SWITCHSTATUS; 
uint32_t lockScreenTimer = 0;
bool splashScreenOn = false;
char screenOnFocus = 0;
char screenLastOnFocus = 2;