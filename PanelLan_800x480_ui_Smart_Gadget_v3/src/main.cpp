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

const char* serverNameTemp = "http://192.168.4.2/sensorData";
const char* serverNameOnLed1 = "http://192.168.4.2/onLed1";
const char* serverNameOffLed1 = "http://192.168.4.2/offLed1";
const char* serverNameOnLed2 = "http://192.168.4.2/onLed2";
const char* serverNameOffLed2 = "http://192.168.4.2/offLed2";
const char* serverNameOnLed3 = "http://192.168.4.2/onLed3";
const char* serverNameOffLed3 = "http://192.168.4.2/offLed3";
const char* serverNameOnLed4 = "http://192.168.4.2/onLed4";
const char* serverNameOffLed4 = "http://192.168.4.2/offLed4";
bool toggleOnOff = false;

IPAddress _gateway1(192, 168, 4, 2);
IPAddress _gateway2(192, 168, 5, 2);
IPAddress _gateway3(192, 168, 6, 2);
const char* _ssid1 = "ESP32-NODE-1";
const char* _ssid2 = "ESP32-NODE-2";
const char* _ssid3 = "ESP32-NODE-3";

String sensorData;
unsigned long previousMillis = 0;
const long interval = 5000; 

#define W  800
#define H  480

int x = 0;
int y = 0;
// bool last_switch1Status = false;
char last_SWITCHSTATUS = 0;

lv_coord_t init_series_array1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
lv_coord_t init_series_array2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[W * H / 10]; 
static lv_disp_drv_t disp_drv;

// BOARD_SC01, BOARD_SC01_PLUS, BOARD_SC02, BOARD_SC05, BOARD_KC01, BOARD_BC02
PanelLan tft(BOARD_SC05);
static LGFX_Sprite sprite (&tft) ;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char val = 10;
int _val = 0;
int scReferesh = 0;
char selectNode = '0';
char changeNode = '0';

char parse(String _inputString);
void screen_update(char n);
String httpGETRequest(const char* serverName);
void changeWifiNode(char _selectWifiNode, char _changeNode);
void httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus);
void  setup_WifiNode(void);
void ScreenSwitchesDebug(void);
void connectionStatusSwitchBoard(void);

AsyncWebServer client(80);

struct wifiActSensNode 
{
  char node; 
  const char* ssid;
  IPAddress gateway;
  char sw[4]; 
};

// Create three wifiActSensNodes
struct wifiActSensNode *wifiNode[3] = {NULL, NULL, NULL};

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
  // switch1Status = false;
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

  // setupWifi(_ssid1, _gateway1);
  // getWifi();
  
  // setup_WifiNode();
}

void loop() { 
  Serial.print("Active screen: ");
  Serial.print(sliderLevelValue, DEC);
  Serial.print(" screen1: ");
  Serial.print(screen1);
  Serial.print(" screen2: ");
  Serial.print(screen2);
  Serial.print(" screen3: ");
  Serial.println(screen3);

  delay(10);

  lv_timer_handler();
  lv_tick_inc(1000);

  // if (stringComplete) 
  // {
  //   selectNode = inputString[0];
  //   inputString = "";
  //   stringComplete = false;
  // }
  // // Change Wifi Node
  // if (selectWifiNode != changeNode)
  // {    
  //   changeWifiNode(selectWifiNode, changeNode);
  //   screen_update(selectWifiNode);
  //   changeNode = selectWifiNode;
  // }  
  // // Check clicked button and send connected event
  // if (_SWITCHSTATUS != last_SWITCHSTATUS)
  // { 
  //   httpSendButtonStatus(_SWITCHSTATUS, last_SWITCHSTATUS); 
  //   last_SWITCHSTATUS = _SWITCHSTATUS;
  //   wifiNode[selectWifiNode-1]->sw[((_SWITCHSTATUS/10))-1] = _SWITCHSTATUS;    
  //   void ScreenSwitchesDebug();
  // }

  // connectionStatusSwitchBoard();
}

void connectionStatusSwitchBoard(void)
{  
  // if (WiFi.isConnected())
  // {
  //   lv_label_set_text(ui_LabelStatus, "Wifi is connected!");
  //   lv_obj_set_style_text_color(ui_LabelStatus, lv_color_hex(0x38403),  0);
  // }
  // else
  // {
  //   lv_label_set_text(ui_LabelStatus, "Wifi is disconnected!");  
  //   lv_obj_set_style_text_color(ui_LabelStatus, lv_color_hex(0xC40303), 0);  
  // }
}

char parse(String _inputString){
  char _val = _inputString.toInt();
  return _val;
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
  
  // _ui_label_set_property(ui_LabelBtnRelay1, _UI_LABEL_PROPERTY_TEXT, relayStatus[0]);
  // lv_obj_set_style_text_color(ui_LabelBtnRelay1, lv_color_hex(relayLbtColor[0]), LV_PART_MAIN | LV_STATE_DEFAULT);
  // _ui_label_set_property(ui_LabelBtnRelay2, _UI_LABEL_PROPERTY_TEXT, relayStatus[1]);
  // lv_obj_set_style_text_color(ui_LabelBtnRelay2, lv_color_hex(relayLbtColor[1]), LV_PART_MAIN | LV_STATE_DEFAULT);
  // _ui_label_set_property(ui_LabelBtnRelay3, _UI_LABEL_PROPERTY_TEXT, relayStatus[2]);
  // lv_obj_set_style_text_color(ui_LabelBtnRelay3, lv_color_hex(relayLbtColor[2]), LV_PART_MAIN | LV_STATE_DEFAULT);
  // _ui_label_set_property(ui_LabelBtnRelay4, _UI_LABEL_PROPERTY_TEXT, relayStatus[3]);
  // lv_obj_set_style_text_color(ui_LabelBtnRelay4, lv_color_hex(relayLbtColor[3]), LV_PART_MAIN | LV_STATE_DEFAULT);
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
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
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

void changeWifiNode(char _selectWifiNode, char _changeNode)
{
  if (_selectWifiNode == 1 && _changeNode != _selectWifiNode)
  {      
    setupWifi(_ssid1, _gateway1);
    getWifi();
    _changeNode = _selectWifiNode;
  }
  else if (_selectWifiNode == 2 && _changeNode != _selectWifiNode)
  {      
    setupWifi(_ssid2, _gateway2);
    getWifi();
    _changeNode = _selectWifiNode;
  } 
  else if (_selectWifiNode == 3 && _changeNode != _selectWifiNode)
  {      
    setupWifi(_ssid3, _gateway3);
    getWifi();
    _changeNode = _selectWifiNode;
  } 
  
  if (_selectWifiNode == 1 || _selectWifiNode == 2 || _selectWifiNode == 3)
  {
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= interval) 
    {
      // Check WiFi connection status
      if(WiFi.status() == WL_CONNECTED )
      { 
        Serial.print("Gateway IP: ");
        Serial.print(WiFi.gatewayIP());
        Serial.print(" & local IP: ");
        Serial.println(WiFi.localIP());
        sensorData = httpGETRequest(serverNameTemp);
        Serial.println("Sensor Data: " + sensorData +".");
        // save the last HTTP GET Request
        previousMillis = currentMillis;
      }
      else 
      {
        Serial.println("WiFi Disconnected");
      }
    }
  }
}

void httpSendButtonStatus(char __Switchstatus, char _last_Switchstatus)
{ 
  if (_SWITCHSTATUS != _last_Switchstatus)
    {    
      switch (_SWITCHSTATUS)
      {
        case 11:
          Serial.println("Switch1 is ON");
          sensorData = httpGETRequest(serverNameOnLed1);
          Serial.println("Sensor Data (lamp 1 on): " + sensorData +".");
          break;
        case 10:
          Serial.println("Switch1 is OFF");
          sensorData = httpGETRequest(serverNameOffLed1);
          Serial.println("Sensor Data (lamp 1 off): " + sensorData +".");
          break;  
        case 22:
          Serial.println("Switch2 is ON");
          sensorData = httpGETRequest(serverNameOnLed2);
          Serial.println("Sensor Data (lamp 2 on): " + sensorData +".");
          break;
        case 20:
          Serial.println("Switch2 is OFF");
          sensorData = httpGETRequest(serverNameOffLed2);
          Serial.println("Sensor Data (lamp 2 off): " + sensorData +".");
          break;  
        case 33:
          Serial.println("Switch3 is ON");
          sensorData = httpGETRequest(serverNameOnLed3);
          Serial.println("Sensor Data (lamp 3 on): " + sensorData +".");
          break;
        case 30:
          Serial.println("Switch3 is OFF");
          sensorData = httpGETRequest(serverNameOffLed3);
          Serial.println("Sensor Data (lamp 3 off): " + sensorData +".");
          break;  
        case 44:
          Serial.println("Switch4 is ON");
          sensorData = httpGETRequest(serverNameOnLed4);
          Serial.println("Sensor Data (lamp 4 on): " + sensorData +".");
          break;
        case 40:
          Serial.println("Switch4 is OFF");
          sensorData = httpGETRequest(serverNameOffLed4);
          Serial.println("Sensor Data (lamp 4 off): " + sensorData +".");
          break;  
        default:
          Serial.println("All Switchs are OFF");
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
    Serial.print("NODE1 SWITCHSTATUS: ");
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