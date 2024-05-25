#include "PanelLan.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "ui/data.h"
// #include "WiFi.h"
// #include "ESPAsyncWebServer.h"
// #include <HTTPClient.h>
// #include <AsyncElegantOTA.h>

// const char* ssid = "void";
// const char* password = "dhulkii11#d";
// //Your IP address or domain name with URL path
// const char* serverNameTemp = "http://192.168.68.59/sensorData";
// String sensorData;
unsigned long previousMillis = 0;
const long interval = 5000; 

#define USE_UI    //if you want to use the ui export from Squareline, please do not annotate this line.
#define W   800
#define H  480

int x = 0;
int y = 0;
bool last_switch1Status = false;
char last_SWITCHSTATUS = 0;
int16_t old_value = 0;
bool arcAtMax = false;
bool arc90Max = false;

lv_coord_t init_series_array1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
lv_coord_t init_series_array2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const uint32_t color_table[20] = 
{
	// Green
	0x00b33b, 0x00cc44, 0x00e64c, 0x00ff55, 0x1aff66,
	// Yellow
	0xe5eb05, 0xf4fa0f, 0xf5fb28, 0xf6fb41, 0xf7fc5a,
	// Orange
	0xeb7e05, 0xfa8b0f, 0xfb9728, 0xfba341, 0xfcaf5a,
	// Red
	0xfc5e5a, 0xfb4641, 0xfb2d28, 0xfa150f, 0xeb0b05
};

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

char parse(String _inputString);
void screen_update(char arcValue);
// String httpGETRequest(const char* serverName);
void ledOnColor(int pos);

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
  data_Chart1_series_array = init_series_array1;
  data_Chart2_series_array = init_series_array2;
  switch1Status = false;
  char _SWITCHSTATUS = 0;  
  char arcInit = 0; 
  
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
    
  ui_init();

 // ------------- Wifi config -------------
//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) { 
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
}

void loop() {   
    unsigned long currentMillis = millis();

  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(">> ");
    Serial.println(inputString);
    _val = inputString.toInt();
    inputString = "";
    stringComplete = false;
    _val++;
  } 

  _val++;
  if(_val >= 100) {scReferesh++; _val = 0;}

  lv_timer_handler();
  lv_tick_inc(1000);

  int16_t new_value = lv_arc_get_value(ui_Arc1);

  arcAtMax = (new_value <= 100 || ((new_value >= 0) && (new_value <=20))) && old_value == 100 ? true : arcAtMax;
  arcAtMax = (new_value <= 100 && new_value >= 90) && old_value == 100 ? false : arcAtMax;

  if (new_value != old_value && !arcAtMax)
  {
    screen_update(new_value);
    lv_spinbox_set_value(ui_Spinbox1, new_value);
    ledOnColor((int)new_value);
    Serial.print("new_value: ");
    Serial.print(new_value);
    Serial.print(" ");
    Serial.print("old_value: ");
    Serial.print(old_value);
    Serial.print(" ");
    Serial.print("arcAtMax: ");
    Serial.println(arcAtMax);
    old_value = new_value;
  }
  else if (arcAtMax)
  {
    screen_update(100);
    lv_spinbox_set_value(ui_Spinbox1, 100);
  }

  if (_SWITCHSTATUS != last_SWITCHSTATUS)
  {    
    switch (_SWITCHSTATUS)
    {
      case 11:
        Serial.println("Switch1 is ON");
        break;
      case 10:
        Serial.println("Switch1 is OFF");
        break;  
      case 22:
        Serial.println("Switch2 is ON");
        break;
      case 20:
        Serial.println("Switch2 is OFF");
        break;  
      case 33:
        Serial.println("Switch3 is ON");
        break;
      case 30:
        Serial.println("Switch3 is OFF");
        break;  
      case 44:
        Serial.println("Switch4 is ON");
        break;
      case 40:
        Serial.println("Switch4 is OFF");
        break;  
      default:
        Serial.println("All Switchs are OFF");
        break;
    }
    last_SWITCHSTATUS = _SWITCHSTATUS;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
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

char parse(String _inputString){
  char _val = _inputString.toInt();
  return _val;
}

void screen_update(char arcValue)
{
  lv_arc_set_value(ui_Arc1, arcValue);
  //lv_chart_refresh(ui_Chart1);
}


// String httpGETRequest(const char* serverName) 
// {
//   WiFiClient client;
//   HTTPClient http;
    
//   // Your Domain name with URL path or IP address with path
//   http.begin(client, serverName);
  
//   // Send HTTP POST request
//   int httpResponseCode = http.GET();
  
//   String payload = "--"; 
  
//   if (httpResponseCode>0) 
//   {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     payload = http.getString();
//   }
//   else 
//   {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
//   // Free resources
//   http.end();

//   return payload;
// }

void ledOnColor(int pos)
{
  char colorPos = 0;
  switch (pos)
  {
    case 0: 
    case 1: 
    case 2: 
    case 3: 
    case 5:
          colorPos = 0;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
          colorPos = 1;
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      colorPos = 2;
      break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
      colorPos = 3;
      break;
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
      colorPos = 4;
      break;
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
      colorPos = 5;
      break;
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
      colorPos = 6;
      break;
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
      colorPos = 7;
      break;
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
      colorPos = 8;
      break;
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
      colorPos = 9;
      break;
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
      colorPos = 10;
      break;
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
      colorPos = 11;
      break;
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
      colorPos = 12;
      break;
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
      colorPos = 13;
      break;
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
      colorPos = 14;
      break;
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
      colorPos = 15;
      break;
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
      colorPos = 16;
      break;
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
      colorPos = 17;
      break;
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
      colorPos = 18;
      break;
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
      colorPos = 19;
      break;  
    default:
      break;
  }

  uint32_t color = color_table[colorPos];
  printf("pos: %d",pos);
  printf("  ");
  printf("colorPos: %d",colorPos);
  printf("  ");
  printf("color: %d\n",color);
  lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
}