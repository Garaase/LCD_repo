#include "PanelLan.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "ui/data.h"

#define USE_UI    //if you want to use the ui export from Squareline, please do not annotate this line.
#define W   800
#define H  480

int x = 0;
int y = 0;
bool last_switch1Status = false;
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

char parse(String _inputString);
void screen_update(void);

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
}

void loop() {   
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(">> ");
    Serial.println(inputString);
    _val = inputString.toInt();
    inputString = "";
    stringComplete = false;
    _val++;
  } 
  data_Chart2_series_array[0] = 30;
  data_Chart2_series_array[5] = 50;
  data_Chart2_series_array[6] = 60;
  data_Chart2_series_array[7] = (int16_t)_val;
  data_Chart2_series_array[8] = (int16_t)_val;
  data_Chart2_series_array[9] = (int16_t)_val;
  data_Chart2_series_array[10] = 2;
  
  data_Chart1_series_array[0] = 15;
  data_Chart1_series_array[1] = 25;
  data_Chart1_series_array[2] = (int16_t)_val;
  data_Chart1_series_array[3] = (int16_t)_val;
  data_Chart1_series_array[4] = (int16_t)_val;
  data_Chart1_series_array[5] = 25;

  // Serial.print("$ ");
  // Serial.println(_val);

  _val++;
  if(_val >= 100) {scReferesh++; _val = 0;}
  screen_update();
  lv_timer_handler();
  lv_tick_inc(1000);

  if(scReferesh >= 2) {
    scReferesh = 0;
 //   ui_Screen1_screen_init();
  }

  // if (switch1Status != last_switch1Status)
  // {
  //   if (switch1Status == true)
  //   {
  //     Serial.println("Switch1 is ON");
  //   }
  //   else
  //   {
  //     Serial.println("Switch1 is OFF");
  //   }    
  //   last_switch1Status = switch1Status;
  // }


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

void screen_update(void)
{
    // lv_chart_series_t * ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x4D1414),
    //                                                              LV_CHART_AXIS_PRIMARY_Y);
    // //static lv_coord_t ui_Chart1_series_1_array[] = { 0, 5, 10, 15, 20, 25, 30, 35, 30, 20 };
    // lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, data_Chart1_series_array);
    // lv_chart_series_t * ui_Chart1_series_2 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x697104),
    //                                                              LV_CHART_AXIS_SECONDARY_Y);
    // //static lv_coord_t ui_Chart1_series_2_array[] = { 2, 10, 20, 20, 30, 30, 20, 20, 10, 2 };
    // lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_2, data_Chart2_series_array);
    
    lv_chart_refresh(ui_Chart1);
}
