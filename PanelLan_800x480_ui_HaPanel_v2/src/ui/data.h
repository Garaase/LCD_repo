#include "lvgl.h"
extern lv_coord_t * data_Chart1_series_array;
extern lv_coord_t * data_Chart2_series_array;
extern bool switch1Status;
extern char PRESSEDSWITCH;
extern char lastPRESSEDSWITCH;
extern char arcInit;
extern uint32_t lockScreenTimer;
extern bool splashScreenOn;
enum SWITCHSTATUS
{
	ALLOFF 		= 0,
	S1N1_ON 	= 1,
	S1N1_OFF 	= 2,
	S2N1_ON 	= 3,
	S2N1_OFF 	= 4,
	S3N1_ON 	= 5,
	S3N1_OFF 	= 6,
	S4N1_ON 	= 7,
	S4N1_OFF 	= 8,
	S1N2_ON 	= 9,
	S1N2_OFF 	= 10,
	S2N2_ON 	= 11,
	S2N2_OFF 	= 12,
	S3N2_ON 	= 13,
	S3N2_OFF 	= 14,
	S4N2_ON 	= 15,
	S4N2_OFF 	= 16,
};
extern enum SWITCHSTATUS SWSTATUS;
extern char screenOnFocus;

extern char screenLastOnFocus;
extern bool imgBtn1Sc2_status;
extern bool imgBtn2Sc2_status;
extern bool imgBtn3Sc2_status;
extern bool imgBtn4Sc2_status;

