#include "PanelLan.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "ui/data.h" 
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <HTTPClient.h>
#include "setupWifi.h"
#include <stdlib.h>
#include "configurations.h"
#include "homeassistantapi.h"
#include "driver/rtc_io.h"

/******************************************************************/
const char* haLED1 = "http://homeassistant.local:8123/api/webhook/test-led1";
const char* haLED2 = "http://homeassistant.local:8123/api/webhook/test-led2";
const char* haLED3 = "http://homeassistant.local:8123/api/webhook/test-led3";
const char* haLED4 = "http://homeassistant.local:8123/api/webhook/test-led4";
const char* haLEDAll = "http://homeassistant.local:8123/api/webhook/test";
const char* rbgLamp1OnOff = "http://homeassistant.local:8123/api/webhook/rbglamp1onoff";
const char* lightstripOnOff = "http://homeassistant.local:8123/api/webhook/lightstriponoff";

String HASensorTemperature;
String HASensorHumidity;
String HASensorPressure;

// Create three wifiActSensNodes
struct wifiActSensNode *wifiNode[3] = {NULL, NULL, NULL};
/******************************************************************/
char previousScreenLastOnFocus;
int milisec = 1000;
int delay5min =60*5;                          //60s * 5 = 300s => 5min
long intervalLockScreen = delay5min*milisec;  // 5min
unsigned long previousNode3Millis = 0;
long intervalNode3 = 4000;

unsigned long currentstopSplashScreenMillis = millis();
unsigned long stopSplashScreenTimer = 0;
long intervalstopSplashScreen = 3000; // 5s splash time

long intervalDeepSleep = delay5min*milisec; // 5min
long timeToSleepTimer = 0;
RTC_DATA_ATTR unsigned long runMillis = 0;
RTC_DATA_ATTR unsigned long sleepMillis = 0;
#define USE_EXT0_WAKEUP          1              // 1 = EXT0 wakeup, 0 = EXT1 wakeup
#define WAKEUP_GPIO GPIO_NUM_1     // Only RTC IO are allowed - ESP32 Pin example
int MOTION_GPIO  = GPIO_NUM_2;     // Only RTC IO are allowed - ESP32 Pin example

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool last_SwitchRGBLamp1OnOff = false;
bool last_SwitchLightStripOnOff = false;

bool startScreen = true;
bool wifiIsConnected = false;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR String timebetweenSleeps = "";
void print_wakeup_reason();
void prepToGoToSleep(void);
char httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus);
void lockScreen(void);
void weather_Data();
void switchBetweenScreens();
void stopSplashScreen(void);
void rgbLampControl(void);
void changeScreenControlButtonStatusText(bool init, int sw);

/******************************************************************/
#define W  800
#define H  480
int x = 0;
int y = 0;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[W * H / 10]; 
static lv_disp_drv_t disp_drv;

// BOARD_SC01, BOARD_SC01_PLUS, BOARD_SC02, BOARD_SC05, BOARD_KC01, BOARD_BC02
PanelLan tft(BOARD_SC05);
static LGFX_Sprite sprite (&tft) ;

AsyncWebServer client(80);
/******************************************************************/

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
static void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;
    data->state = LV_INDEV_STATE_REL;
    bool touched = tft.getTouch( &touchX, &touchY);
    if( touched )
    {
        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

void calibrate() // function to calibrate ILI9341 TFT screen
{
    uint16_t calData[5]; // calibration parameters
    String str;

    tft.fillScreen(TFT_BLACK); // fill screen in black
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // set text color, white on black
    tft.setCursor(30, 0); // move cursor to position (0, 30)
    tft.println("Touch corners as indicated");
    tft.calibrateTouch(calData, TFT_RED, TFT_BLACK, 15);
    // calibrate screen
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 50);
    tft.setTextSize(2);
    tft.print("Calibration parameters");
    str = ""; // display calibration parameters
    for (int i=0; i<4; i++) str = str + String(calData[i])+",";
    str = str + String(calData[4]);
    tft.setCursor(0, 90);
    tft.print(str);
}

void setup(void) {
  PRESSEDSWITCH = 0;

  pinMode(MOTION_GPIO, INPUT);  // Define BUTTON pin as Input.

  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(1);
  Serial.println("Started! ...");

  tft.begin();
  tft.clear(TFT_BLACK); 
  //calibrate();
  delay(100);
  lv_init();
  delay(100);
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, W * H / 10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = W;
  disp_drv.ver_res = H;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
    
  // Start the ui (LCD)  
  ui_init();
  
  // Connecting to Wifi
  wifiIsConnected = initWiFi(true);

  screenLastOnFocus = 2;
  previousScreenLastOnFocus = 0;

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  if (bootCount > 0)
  {
    intervalNode3 = 3000;
  }  
  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  #if USE_EXT0_WAKEUP
  esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 1);  //1 = High, 0 = Low
  // Configure pullup/downs via RTCIO to tie wakeup pins to inactive level during deepsleep.
  // EXT0 resides in the same power domain (RTC_PERIPH) as the RTC IO pullup/downs.
  // No need to keep that power domain explicitly, unlike EXT1.
  rtc_gpio_pullup_dis(WAKEUP_GPIO);
  rtc_gpio_pulldown_en(WAKEUP_GPIO);
  #else  // TIME WAKEUP
  /* wake up every 10 seconds  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  #endif

  //Start the awake timer
  runMillis = millis();

  //Print sleep timer    
  sleepMillis = millis()-sleepMillis;
  int sleepSeconds = sleepMillis/1000;
  int secsRemaining=sleepSeconds%3600;
  int _sleepMinutes=secsRemaining/60;
  int _sleepSeconds=secsRemaining%60;

  char buf[21];
  sprintf(buf,"Sleepntime %02d:%02d",_sleepMinutes,_sleepSeconds);
  Serial.println(buf);

  startScreen = true;
  stopSplashScreenTimer = millis();
  timeToSleepTimer = millis();
  previousNode3Millis = millis(); 
  
  startColorPickerScreen = true;
}

void loop() { 

  if (!startScreen)
  { 
    int MOTION_GPIOState = digitalRead(MOTION_GPIO); // Reading input from Button Pin.

    if (MOTION_GPIOState == HIGH) // Checking if Input from button is HIGH (1/+5V)
    { 
      screenLastOnFocus = 2; // Weather screen 
      timeToSleepTimer = millis();
    } 
  }
  
  stopSplashScreen();

  // Prepare to put the unit in deep sleep mode  
  prepToGoToSleep();  

  // Switch between the different screens
  switchBetweenScreens();
  
  // Update the weather screen
  weather_Data();

  // Change RBG spotlight brightness and color
  rgbLampControl();

  // Check clicked button and send connected event
  lastPRESSEDSWITCH = httpSendButtonStatus(PRESSEDSWITCH, lastPRESSEDSWITCH);
  
  // Connect or reconnect to Wifi
  initWiFi(false);
  // GUI Handler
  lv_timer_handler();
  lv_tick_inc(100);
}

/*************************************************************
 *                     HELP FUNCTIONS                        *
 *  Your Domain name with URL path or IP address with path   *
 /************************************************************/
void switchBetweenScreens()
{
  if (previousScreenLastOnFocus != screenLastOnFocus)
  {  
    Serial.print("screenLastOnFocus: ");
    Serial.println(screenLastOnFocus, DEC);
    switch (screenLastOnFocus)
    {
      case SPLASH:
        Serial.println("SPLASH screen");
        break;
      case WEATHER:
        Serial.println("WEATHER screen"); 
        break;
      case SCREENLIGHTCONTROL:
        changeScreenControlButtonStatusText(1,SWLIGHTSTRIP);
        changeScreenControlButtonStatusText(1,SWRGBLAMP1);
        changeScreenControlButtonStatusText(1,SWRGBLAMP2);
        changeScreenControlButtonStatusText(1,SWRGBLAMP3);
        Serial.println("SCREENLIGHTCONTROL screen");     
        break;   
      case SCREENCOLORPICKER:
        Serial.println("SCREENCOLORPICKER screen");
        break; 
      case SCREENCOLORTEMP:
        Serial.println("SCREENCOLORTEMP screen");
        break; 
      default:
        //---
        break;
    }    
    previousScreenLastOnFocus = screenLastOnFocus;
  }
}

void stopSplashScreen(void)
{  
  if (startScreen)
  {  
    unsigned long currentstopSplashScreenMillis = millis();
    if (currentstopSplashScreenMillis - stopSplashScreenTimer >= intervalstopSplashScreen) {
        screenOnFocus = 2;
        stopSplashScreenTimer = currentstopSplashScreenMillis;
        intervalstopSplashScreen = delay5min*milisec;
        Serial.println("stopSplashScreen");
        _ui_screen_change(&ui_ScreenWeather, LV_SCR_LOAD_ANIM_FADE_ON, 0, 1500, &ui_ScreenWeather_screen_init);  
        startScreen = false;
    } 
  }
}

void weather_Data()
{  
  String temperature = "";
  String pressure = "";
  String MaxMinTemp = "";
  String humidity = "";
  String altitude = "";
  
  String weathet_temperature = "";
  String weathet_humidity = "";
  String weathet_pressure = "";
  String weathet_wind_speed = "";

  String time_and_date = "";  
  unsigned long currentNode3Millis = millis();
  
  if (screenLastOnFocus == WEATHER)
  {     
    if(currentNode3Millis - previousNode3Millis >= intervalNode3) 
    {
      if (wifiIsConnected)
      {        
        temperature	= getSensorValue("sensor.temppressuresensor_bme280_temperature");
        pressure 		= getSensorValue("sensor.temppressuresensor_bme280_pressure");
        humidity 		= getSensorValue("sensor.temppressuresensor_bme280_humidity");
        altitude 		= getSensorValue("sensor.temppressuresensor_bme280_pressure");

        weathet_temperature = String(getSensorAttributeValue("weather.forecast_hem", "temperature").toFloat(), 1);
        weathet_humidity= String(getSensorAttributeValue("weather.forecast_hem", "humidity").toFloat(), 1);
        weathet_pressure = String(getSensorAttributeValue("weather.forecast_hem", "pressure").toFloat(), 1);
        weathet_wind_speed = String(getSensorAttributeValue("weather.forecast_hem", "wind_speed").toFloat(), 1);         
        time_and_date	= getSensorValue("sensor.time_date");
        timebetweenSleeps = time_and_date.c_str(); 
      }
        
      if (weathet_temperature != "" ||
          weathet_humidity 	  != "" ||	
          weathet_pressure 	  != "" || 	
          weathet_wind_speed )
      {
        lv_label_set_text(ui_LbTempValue1, weathet_temperature.c_str());   
        lv_label_set_text(ui_LbHumidityValue1, weathet_humidity.c_str()); 
        lv_label_set_text(ui_LbPressureValue1, weathet_pressure.c_str()); 
        lv_label_set_text(ui_LbWindspeedValue1, weathet_wind_speed.c_str()); 
        lv_label_set_text(ui_LbTempValue2, temperature.c_str());   
        lv_label_set_text(ui_LbHumidityValue2, humidity.c_str()); 
        lv_label_set_text(ui_LbPressureValue2, pressure.c_str());  
        lv_label_set_text(ui_LbTimeAndDate, time_and_date.c_str());   
        intervalNode3 = 10000;		
      }
      else
      {
        intervalNode3 = 1000;
        Serial.println("intervalNode3 = 10");
        WiFi.reconnect();
      } 
      
      previousNode3Millis = currentNode3Millis;	 
    }     
  } 
}

void rgbLampControl(void)
{ 

  // if (cPickRBGBrightnessChanged || cPickRBGColorChanged)
  // {
  //   Serial.print("cPickRBGBrightnessChanged; ");
  //   Serial.print(cPickRBGBrightnessChanged);
  //   Serial.print(", cPickRBGColorChanged: ");
  //   Serial.print(cPickRBGColorChanged);
  //   Serial.print(", PRESSEDSWITCH: ");
  //   Serial.println(PRESSEDSWITCH, DEC);
  // }

  if (cPickRBGBrightnessChanged)
  {
    // Change rgblamp1 brightness
    cPickRBGBrightnessChanged = false;
    setWebhookrgbLampValues(1, PRESSEDSWITCH, rgbLampBrightness, cPickerRGBValue);
  }
  if (cPickRBGColorChanged)
  {
    // Change rgblamp1 color
    cPickRBGColorChanged = false;
    setWebhookrgbLampValues(2, PRESSEDSWITCH, rgbLampBrightness, cPickerRGBValue);
  }
  if (lightstripBrightnessChanged)
  {  
    // Change ligh strip brightness
    lightstripBrightnessChanged = false;
    setWebhookLightstripValues(1, lightstripBrightness, lightstripColorTemp);
  }
  if (lightstripColorTempChanged)
  {  
    // Change ligh strip color temp 
    lightstripColorTempChanged = false;
    setWebhookLightstripValues(2, lightstripBrightness, lightstripColorTemp);
  }
}

void changeScreenControlButtonStatusText(bool init, int sw)
{
  const char* swstatus = "";
  if (sw == SWRGBLAMP1)
  {
    String rgblamp1Status = getSensorValue("light.rbglamp1");
    Serial.print(">> rgblamp1Status: ");
    Serial.println(rgblamp1Status);
    if (init == 1)
    {
      swstatus = rgblamp1Status == "on"? "ON" : "OFF";
    }
    else
    {
      swstatus = rgblamp1Status == "on"? "OFF" : "ON";
    }
    
    lv_label_set_text(ui_LbSwRGBLamp1StatusText, swstatus);
  }
  else if (sw == SWRGBLAMP2)
  {
    String rgblamp2Status = getSensorValue("light.rgblamp2");
    Serial.print(">> rgblamp2Status: ");
    Serial.println(rgblamp2Status);
    if (init == 1)
    {
      swstatus = rgblamp2Status == "on"? "ON" : "OFF";
    }
    else
    {
      swstatus = rgblamp2Status == "on"? "OFF" : "ON";
    }
    
    lv_label_set_text(ui_LbSwRGBLamp2StatusText, swstatus);
  }
  else if (sw == SWRGBLAMP3)
  {
    String rgblamp3Status = getSensorValue("light.rgblamp3");
    Serial.print(">> rgblamp3Status: ");
    Serial.println(rgblamp3Status);
    if (init == 1)
    {
      swstatus = rgblamp3Status == "on"? "ON" : "OFF";
    }
    else
    {
      swstatus = rgblamp3Status == "on"? "OFF" : "ON";
    }
    
    lv_label_set_text(ui_LbSwRGBLamp3StatusText, swstatus);
  }
  else if (sw == SWLIGHTSTRIP)
  {
    String lightstripStatus = getSensorValue("light.co_smart_lightstrip");
    Serial.print(">> lightstripStatus");
    Serial.println(lightstripStatus);
    if (init == 1)
    {
      swstatus = lightstripStatus == "on"? "ON" : "OFF";
    }
    else
    {
      swstatus = lightstripStatus == "on"? "OFF" : "ON";
    }
    
    lv_label_set_text(ui_LbSwLightStripStatusText, swstatus);
  }
}

char httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus)
{ 
  if (__Switchstatus != _last_Switchstatus)
    {    
      switch (__Switchstatus)
      {
        case SWLIGHTSTRIPON:
        case SWLIGHTSTRIPOFF:
          setWebhookSwitches("lightstriponoff");
          changeScreenControlButtonStatusText(0,SWLIGHTSTRIP);
          setWebhookSwitches("lightstriponoff");
          changeScreenControlButtonStatusText(0,SWLIGHTSTRIP);
          break;  
        case SWRGBLAMP1ON:
        case SWRGBLAMP1OFF:
          setWebhookSwitches("rgblamp1onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP1);
          setWebhookSwitches("rgblamp1onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP1);
          break;  
        case SWRGBLAMP2ON:
        case SWRGBLAMP2OFF:
          setWebhookSwitches("rgblamp2onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP2);
          setWebhookSwitches("rgblamp2onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP2);
          break;  
        case SWRGBLAMP3ON:
        case SWRGBLAMP3OFF:
          setWebhookSwitches("rgblamp3onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP3);
          setWebhookSwitches("rgblamp3onoff");
          changeScreenControlButtonStatusText(0,SWRGBLAMP3);
          break;  
        default:
          break;
      }
    }
    return __Switchstatus;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void prepToGoToSleep(void)
{  
  unsigned long currentAwakeMillis = millis();
  if (currentAwakeMillis - timeToSleepTimer >= intervalDeepSleep) {
      timeToSleepTimer = currentAwakeMillis;

      //Print the awake timer
      runMillis = millis()-runMillis;
      int runSeconds = runMillis/1000;
      int secsRemaining=runSeconds%3600;
      int _runMinutes=secsRemaining/60;
      int _runSeconds=secsRemaining%60;
      char buf[21];
      sprintf(buf,"Runtime %02d:%02d",_runMinutes, _runSeconds);
      Serial.println(buf);
      
      // Start sleep timer
      sleepMillis = millis();

      Serial.println("Going to sleep now: "+timebetweenSleeps);
      Serial.flush(); 
      esp_deep_sleep_start();
  } 
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}