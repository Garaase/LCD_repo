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
	ALLOFF 			= 0,
	SWLIGHTSTRIPOFF = 1,
	SWRGBLAMP1OFF 	= 2,
	SWRGBLAMP2OFF 	= 3,
	SWRGBLAMP3OFF 	= 4,
	SWLIGHTSTRIPON 	= 5,
	SWRGBLAMP1ON 	= 6,
	SWRGBLAMP2ON 	= 7,
	SWRGBLAMP3ON 	= 8
};
extern enum SWITCHSTATUS SWSTATUS;

enum SWITCHNUMBER
{
	NOSW 		= 0,
	SWLIGHTSTRIP= 1,
	SWRGBLAMP1 	= 2,
	SWRGBLAMP2 	= 3,
	SWRGBLAMP3 	= 4
};
extern enum SWITCHNUMBER SWITCHNR;

enum SCREEN
{
  NOSCREEN = 0,
  SPLASH = 1,
  WEATHER = 2,
  SCREENLIGHTCONTROL = 3,
  SCREENCOLORPICKER = 4,
  SCREENCOLORTEMP = 5
};
extern enum SCREEN scr;

extern char screenOnFocus;

extern char screenLastOnFocus;
extern bool imgBtn1Sc2_status;
extern bool imgBtn2Sc2_status;
extern bool imgBtn3Sc2_status;
extern bool imgBtn4Sc2_status;

//extern uint16_t cPickerRGBValue[3];

extern lv_color32_t cPickerRGBValue;
extern bool cPickRBGBrightnessChanged;
extern bool cPickRBGColorChanged;
extern bool lightstripBrightnessChanged;
extern bool lightstripColorTempChanged;
extern int16_t lightstripColorTemp;

extern int16_t rgbLampBrightness;
extern int16_t lightstripBrightness;

extern const char* objectName;

extern bool cPickRBGValueChanged;

extern bool SwitchLightStripOnOff;
extern bool SwitchRGBLamp1OnOff;
extern bool SwitchRGBLamp2OnOff;
extern bool SwitchRGBLamp3OnOff;

extern bool startColorTempScreen;
extern bool startColorPickerScreen;

extern char swLightstripPressed;
extern char swRgbLamp1Pressed;
extern char swRgbLamp2Pressed;
extern char swRgbLamp3Pressed;
 

