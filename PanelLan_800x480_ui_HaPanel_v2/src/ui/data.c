//extern lv_coord_t __chart1_series_array[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#include "lvgl.h"
lv_coord_t * data_Chart1_series_array;
lv_coord_t * data_Chart2_series_array;
bool switch1Status;
char PRESSEDSWITCH = 0;
char lastPRESSEDSWITCH = 0;
char arcInit;

enum SWITCHSTATUS;
uint32_t lockScreenTimer = 0;
bool splashScreenOn = false;
char screenOnFocus = 0;
char screenLastOnFocus = 2;
bool imgBtn1Sc2_status = false;
bool imgBtn2Sc2_status = false;
bool imgBtn3Sc2_status = false;
bool imgBtn4Sc2_status = false;

