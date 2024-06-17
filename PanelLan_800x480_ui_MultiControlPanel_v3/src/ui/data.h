#include "lvgl.h"
extern lv_coord_t * data_Chart1_series_array;
extern lv_coord_t * data_Chart2_series_array;
extern bool switch1Status;
extern char _SWITCHSTATUS;
extern char arcInit;
extern uint32_t lockScreenTimer;
extern bool splashScreenOn;
enum SWITCHSTATUS
{
    ALLOFF = 0,
    S1ON = 1,
    S1OFF = 2,
    S2ON = 3,
    S2OFF = 4,
    S3ON = 5,
    S3OFF = 6,
    S4ON = 7,
    S4OFF = 8,
};
extern enum SWITCHSTATUS SwStatus;
extern char screenOnFocus;
extern char screenLastOnFocus;