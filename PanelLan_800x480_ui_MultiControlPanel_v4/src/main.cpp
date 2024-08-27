#include "PanelLan.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "ui/data.h" 
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <HTTPClient.h>
#include <AsyncElegantOTA.h>
#include "setupWifi.h"
#include <stdlib.h>


/******************************************************************/
const char* serverNameTemp = "http://192.168.4.2/sensorData";
const char* serverNameOnLed1 = "http://192.168.4.2/onLed1";
const char* serverNameOffLed1 = "http://192.168.4.2/offLed1";
const char* serverNameOnLed2 = "http://192.168.4.2/onLed2";
const char* serverNameOffLed2 = "http://192.168.4.2/offLed2";
const char* serverNameOnLed3 = "http://192.168.4.2/onLed3";
const char* serverNameOffLed3 = "http://192.168.4.2/offLed3";
const char* serverNameOnLed4 = "http://192.168.4.2/onLed4";
const char* serverNameOffLed4 = "http://192.168.4.2/offLed4";
const char* serverNameTemperature = "http://192.168.4.2/temperature";
const char* serverNamePressure = "http://192.168.4.2/pressure";
const char* serverNameHumidity = "http://192.168.4.2/humidity";
const char* serverNameAltitude = "http://192.168.4.2/altitude";

IPAddress _gateway1(192, 168, 4, 2);
IPAddress _gateway2(192, 168, 5, 2);
IPAddress _gateway3(192, 168, 6, 2);
const char* _ssid1 = "ESP32-NODE-1";
const char* _ssid2 = "ESP32-NODE-2";
const char* _ssid3 = "ESP32-NODE-3";
String Nonde1Name = "ESP32-NODE-1";
String Nonde2Name = "ESP32-NODE-2";
String Nonde3Name = "ESP32-NODE-3";

struct wifiActSensNode 
{
  char node; 
  const char* ssid;
  IPAddress gateway;
  char sw[4]; 
};

// Create three wifiActSensNodes
struct wifiActSensNode *wifiNode[3] = {NULL, NULL, NULL};
/******************************************************************/

String sw1 = "*";
String sw2 = "*";
String sw3 = "*";
String sw4 = "*";
char sw1num = 0;
char sw2num = 0;
char sw3num = 0;
char sw4num = 0;
char lastSW1num = 0;
char lastSW2num = 0;
char lastSW3num = 0;
char lastSW4num = 0;

String sensorData;
char previousScreenLastOnFocus;
unsigned long previousLockScreenMillis = 0;
long intervalLockScreen = 10000;
unsigned long previousNode3Millis = 0;
long intervalNode3 = 100;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char last_SWITCHSTATUS = 0;

enum SCREEN
{
  NOSCREEN = 0,
  SPLASH = 1,
  WEATHER = 2,
  SWITCHES_NODE1 = 3,
  SWITCHES_NODE2 = 4
};

void screen_update(char n);
String httpGETRequest(const char* serverName);
void buttonHandler(void);
void httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus);
void setup_WifiNode(void);
void ScreenSwitchesDebug(void);
void lockScreen(void);
void node3_Data(boolean n);

/******************************************************************/
#define W  480
#define H  800
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

String checkTemp() {
  return String("Hello from client");
}

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
  char _SWITCHSTATUS = 0;

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
  
  client.on("/check", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", checkTemp().c_str());
  });
  client.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "Message from ESP32 LCD");
  });  

  setupWifi(_ssid1, _gateway1);
  getWifi();
  
  screenLastOnFocus = 2;
  previousScreenLastOnFocus = 0;
  lockScreenTimer = millis();
}

void loop() { 
  boolean node1 = Nonde1Name.equals( WiFi.SSID());
  boolean node2 = Nonde2Name.equals( WiFi.SSID());
  boolean node3 = Nonde3Name.equals( WiFi.SSID());
  enum SCREEN scr = NOSCREEN;

  if (previousScreenLastOnFocus != screenLastOnFocus)
  {  
    Serial.print("screenLastOnFocus: ");
    Serial.println(screenLastOnFocus, DEC);
    switch (screenLastOnFocus)
    {
      case SPLASH:
        //---
        break;
      case WEATHER:
        if (!node3)
        {        
          setupWifi(_ssid3, _gateway3);
          getWifi();       
        } 
        else
        {        
        }   
        break;
      case SWITCHES_NODE1:
        if (!node1)
        {        
          setupWifi(_ssid1, _gateway1);
          getWifi();       
        }      
        break;   
      case SWITCHES_NODE2:
        if (!node2)
        { 
          setupWifi(_ssid2, _gateway2);
          getWifi();  
        } 
        break; 
      default:
        //---
        break;
    }    
    previousScreenLastOnFocus = screenLastOnFocus;
  }
  
  node3_Data(node3);
  delay(10);

  // Check clicked button and send connected event
  buttonHandler();

  if (!splashScreenOn)
  {
    lockScreen(); 
  }

  // GUI Handler
  lv_timer_handler();
  lv_tick_inc(1000);
}

void screen_update(char n)
{
  n = n-1;
  const char * relayStatus[4] ={ "OFF", "OFF", "OFF", "OFF"};
  int32_t relayLbtColor[4] = {(int)12845827, (int)12845827, (int)12845827, (int)12845827};

  relayStatus[0] = wifiNode[n]->sw[0] == 11 ? "ON" : "OFF";
  relayStatus[1] = wifiNode[n]->sw[1] == 22 ? "ON" : "OFF";
  relayStatus[2] = wifiNode[n]->sw[2] == 33 ? "ON" : "OFF";
  relayStatus[3] = wifiNode[n]->sw[3] == 44 ? "ON" : "OFF";

  relayLbtColor[0] = wifiNode[n]->sw[0] == 11 ? (int)230403 : (int)12845827;
  relayLbtColor[1] = wifiNode[n]->sw[1] == 22 ? (int)230403 : (int)12845827;
  relayLbtColor[2] = wifiNode[n]->sw[2] == 33 ? (int)230403 : (int)12845827;
  relayLbtColor[3] = wifiNode[n]->sw[3] == 44 ? (int)230403 : (int)12845827;
}

/*************************************************************
 *                     HELP FUNCTIONS                        *
 *  Your Domain name with URL path or IP address with path   *
 /************************************************************/
String httpGETRequest(const char* serverName) 
{
  WiFiClient client;
  HTTPClient http;    
  
  http.begin(client, serverName);  
  // Send HTTP POST request
  int httpResponseCode = http.GET();  
  String payload = "--";   
  if (httpResponseCode>0) 
  {
    payload = (http.getString()).c_str();
  }
  // Free resources
  http.end();
  return payload;
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

void buttonHandler(void)
{
   // Check clicked button and send connected event
  if (_SWITCHSTATUS != last_SWITCHSTATUS)
  {
    lockScreenTimer = millis();

    sw1 = ui_Switch1a->state == 3 ? "ON": sw1;
    sw1 = ui_Switch1a->state == 2 ? "OFF": sw1;
    sw2 = ui_Switch1b->state == 3 ? "ON": sw2;
    sw2 = ui_Switch1b->state == 2 ? "OFF": sw2;
    sw3 = ui_Switch1c->state == 3 ? "ON": sw3;
    sw3 = ui_Switch1c->state == 2 ? "OFF": sw3;
    sw4 = ui_Switch1d->state == 3 ? "ON": sw4;
    sw4 = ui_Switch1d->state == 2 ? "OFF": sw4;

    Serial.print("ui_ScreenSwitch1->state: ");
    Serial.print(sw1);
    Serial.print("    ui_Switch2_Node1->state: ");
    Serial.print(sw2);
    Serial.print("    ui_Switch3_Node1->state: ");
    Serial.print(sw3);
    Serial.print("    ui_Switch4_Node1->state: ");
    Serial.print(sw4);    
    Serial.print("    _SWITCHSTATUS: ");
    Serial.println(_SWITCHSTATUS, DEC);

    httpSendButtonStatus(_SWITCHSTATUS, last_SWITCHSTATUS);

    last_SWITCHSTATUS = _SWITCHSTATUS;

    lastSW1num = sw1num;
    lastSW2num = sw2num;
    lastSW3num = sw3num;
    lastSW4num = sw4num;    
  }

}

void httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus)
{ 
  if (_SWITCHSTATUS != _last_Switchstatus)
    {    
      switch (_SWITCHSTATUS)
      {
        case 11:
          //Serial.println("Switch1_Node1 is ON");
          sensorData = httpGETRequest(serverNameOnLed1);
          //Serial.println("Sensor Data (lamp 1 on): " + sensorData +".");
          break;
        case 10:
          //Serial.println("Switch1_Node1 is OFF");
          sensorData = httpGETRequest(serverNameOffLed1);
          //Serial.println("Sensor Data (lamp 1 off): " + sensorData +".");
          break;  
        case 22:
          //Serial.println("Switch2_Node1 is ON");
          sensorData = httpGETRequest(serverNameOnLed2);
          //Serial.println("Sensor Data (lamp 2 on): " + sensorData +".");
          break;
        case 20:
          //Serial.println("Switch2_Node1 is OFF");
          sensorData = httpGETRequest(serverNameOffLed2);
          //Serial.println("Sensor Data (lamp 2 off): " + sensorData +".");
          break;  
        case 33:
          //Serial.println("Switch3_Node1 is ON");
          sensorData = httpGETRequest(serverNameOnLed3);
          //Serial.println("Sensor Data (lamp 3 on): " + sensorData +".");
          break;
        case 30:
          //Serial.println("Switch3_Node1 is OFF");
          sensorData = httpGETRequest(serverNameOffLed3);
          //Serial.println("Sensor Data (lamp 3 off): " + sensorData +".");
          break;  
        case 44:
          //Serial.println("Switch4_Node1 is ON");
          sensorData = httpGETRequest(serverNameOnLed4);
          //Serial.println("Sensor Data (lamp 4 on): " + sensorData +".");
          break;
        case 40:
          //Serial.println("Switch4_Node1 is OFF");
          sensorData = httpGETRequest(serverNameOffLed4);
          //Serial.println("Sensor Data (lamp 4 off): " + sensorData +".");
          break;  
        default:
          //Serial.println("All Switchs are OFF");
          break;
      }
    }
}

void  setup_WifiNode(void)
{    
  wifiNode[0] = (struct wifiActSensNode*)malloc(sizeof(struct wifiActSensNode));
  wifiNode[1] = (struct wifiActSensNode*)malloc(sizeof(struct wifiActSensNode));
  wifiNode[2] = (struct wifiActSensNode*)malloc(sizeof(struct wifiActSensNode));
  wifiNode[3] = (struct wifiActSensNode*)malloc(sizeof(struct wifiActSensNode));

  char i = (wifiNode[0]->node= 1)-1;
  wifiNode[0]->ssid = _ssid1;
  wifiNode[0]->gateway[i] = _gateway1;
  wifiNode[0]->sw[0]= 10;
  wifiNode[0]->sw[1]= 20;
  wifiNode[0]->sw[2]= 30;
  wifiNode[0]->sw[3]= 40;
  
  i = (wifiNode[1]->node = 2)-1;
  wifiNode[1]->ssid = _ssid2;
  wifiNode[1]->gateway[i] = _gateway2;
  wifiNode[1]->sw[0]= 10;
  wifiNode[1]->sw[1]= 20;
  wifiNode[1]->sw[2]= 30;
  wifiNode[1]->sw[3]= 40;
  
  i = (wifiNode[2]->node = 3)-1;
  wifiNode[2]->ssid = _ssid3;
  wifiNode[2]->gateway[i] = _gateway3;
  wifiNode[2]->sw[0]= 10;
  wifiNode[2]->sw[1]= 20;
  wifiNode[2]->sw[2]= 30;
  wifiNode[2]->sw[3]= 40;
}

void ScreenSwitchesDebug()
{
    //Serial.print("NODE1 SWITCHSTATUS: ");
    Serial.print(wifiNode[0]->sw[0], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[0]->sw[1], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[0]->sw[2], DEC);
    Serial.print(" ");
    Serial.println(wifiNode[0]->sw[3], DEC);
    Serial.print("NODE2 SWITCHSTATUS: ");
    Serial.print(wifiNode[1]->sw[0], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[1]->sw[1], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[1]->sw[2], DEC);
    Serial.print(" ");
    Serial.println(wifiNode[1]->sw[3], DEC);
    Serial.print("NODE3 SWITCHSTATUS: ");
    Serial.print(wifiNode[2]->sw[0], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[2]->sw[1], DEC);
    Serial.print(" ");
    Serial.print(wifiNode[2]->sw[2], DEC);
    Serial.print(" ");
    Serial.println(wifiNode[2]->sw[3], DEC);
}

void lockScreen(void)
{  
  unsigned long currentLockScreenMillis = millis();
  if (currentLockScreenMillis - lockScreenTimer >= intervalLockScreen) {
      screenOnFocus = 1;
//      _ui_screen_change(&ui_splash, LV_SCR_LOAD_ANIM_FADE_ON, 0, 1500, &ui_splash_screen_init);
      lockScreenTimer = currentLockScreenMillis;
      intervalLockScreen = 60000;
  } 
}

void node3_Data(boolean n)
{  
  
  unsigned long currentNode3Millis = millis();
  if (currentNode3Millis - previousNode3Millis >= intervalNode3) 
  {   
    if(n)
    {
      String temperature = "";
      String pressure = "";
      String MaxMinTemp = "";
      String humidity = "";
      String altitude = "";

      temperature = httpGETRequest(serverNameTemperature);
      pressure = httpGETRequest(serverNamePressure);
      humidity = httpGETRequest(serverNameHumidity);
      altitude = httpGETRequest(serverNameAltitude);

      Serial.print("Temperature: ");
      Serial.print(temperature);  
      Serial.print("  ");
      Serial.print("Pressure: ");
      Serial.print(pressure);  
      Serial.print("  ");
      Serial.print("Humidity: ");
      Serial.println(humidity); 
      Serial.print("  ");
      Serial.print("Altitude: ");
      Serial.println(altitude); 
      
      lv_label_set_text(ui_LabelValue1, temperature.c_str());      
      lv_arc_set_value(ui_ArcGauge1, temperature.toInt());

      lv_label_set_text(ui_LabelValue4, humidity.c_str());   
      lv_arc_set_value(ui_ArcGauge4, humidity.toInt());

      lv_label_set_text(ui_LabelValue3, altitude.c_str());   
      lv_arc_set_value(ui_ArcGauge3, altitude.toInt());

      lv_label_set_text(ui_LabelValue2, pressure.c_str());   
      lv_arc_set_value(ui_ArcGauge2, pressure.toInt());
    }  
    previousNode3Millis = currentNode3Millis;
    intervalNode3 = 10000;
  } 
}