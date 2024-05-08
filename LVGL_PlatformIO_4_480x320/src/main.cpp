#define LGFX_AUTODETECT 
#include <LovyanGFX.hpp> 
#include "car_img6.h"
#include "ui.h"

LGFX tft;
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 5 ];

uint16_t calData[5]; // calibration parameters
String str;

uint16_t x = 0, y = 0;
int radius = 2; // define paintbrush radius
unsigned int color;

void lv_example_get_started_4(void);
void clear();

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow( area->x1, area->y1, w, h );
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready( disp );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
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

        Serial.print( "Data x " );
        Serial.println( touchX );

        Serial.print( "Data y " );
        Serial.println( touchY );
    }
}


void calibrate() // function to calibrate ILI9341 TFT screen
{
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

void setup()
{
  Serial.begin( 115200 ); /* prepare for possible serial debug */
  
  tft.begin();          /* TFT init */
  tft.setRotation( 1 ); /* Landscape orientation, flipped */
  tft.fillScreen(TFT_BLACK);  
  tft.setBrightness(255);
 // calibrate();
  delay(200);
  //digitalWrite(LCD_BL, HIGH);
  //touch_init();

  //  if (!ts.begin(0, SDA_FT6236, SCL_FT6236)) {
  //    Serial.println("Unable to start the capacitive touch Screen.");
  //  }
  //touch_init();

  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 5 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

#if 1
  /* Create simple label */
  lv_example_get_started_4();

#else
  /* Try an example from the lv_examples Arduino library
     make sure to include it as written above.

  */
  // uncomment one of these demos
  //lv_demo_widgets();            // OK
  ui_init();
#endif
  Serial.println( "Setup done" );
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  lv_tick_inc(1);
  delay( 5 );
  // if (tft.getTouch(&x, &y)>0) // if screen pressed
  // {
  //   if(x>40) tft.fillCircle(x, y, radius, color); // draw point
  //   if(x>0 && x<40) // select color from color palette
  //   {
  //     if(y>75 && y<95) color = TFT_RED;
  //     else if(y>100 && y<130) color = TFT_YELLOW;
  //     else if(y>140 && y<170) color = TFT_GREEN;
  //     else if(y>180 && y<210) color = TFT_BLUE;
  //     else if(y>220 && y<250) color = TFT_WHITE;
  //     // display selected color
  //     if(y>75 && y<275) tft.fillCircle(10, 50, 10, color);
  //     else if(y>300) clear(); // clear screen
  //   }
  // }
}

void clear() // function to reset screen
{
	tft.fillScreen(TFT_BLACK); // fill screen
	tft.setTextColor(TFT_GREEN); // set text color
	tft.setTextSize(2); // set text size
	tft.setCursor(110,5); // position cursor
	tft.print("Paintpot"); // screen title
	tft.fillRect(0,75,20,20, TFT_RED);
	tft.fillRect(0,100,20,20,TFT_YELLOW);
	tft.fillRect(0,125,20,20,TFT_GREEN); // build color palette
	tft.fillRect(0,150,20,20, TFT_BLUE);
	tft.fillRect(0,175,20,20, TFT_WHITE);
	tft.drawCircle(10,225,10, TFT_WHITE); // select to clear screen
	tft.setCursor(25,217);
	tft.setTextColor(TFT_WHITE);
	tft.print("clear");
	color = TFT_WHITE;
}	


static void btn_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    static uint8_t cnt = 0;
    cnt++;

    /*Get the first child of the button which is the label and change its text*/
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "Button: %d", cnt);
  }
}

/**
   Create a button with a label and react on click event.
*/
void lv_example_get_started_4(void)
{
  lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
  lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
  lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

  lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
  lv_label_set_text(label, "Button");                     /*Set the labels text*/
  lv_obj_center(label);
}
