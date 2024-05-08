#define LGFX_AUTODETECT
#include <LGFX_AUTODETECT.hpp>

//#include <lv_demo.h>
#include <lvgl.h>

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][ screenWidth * 10 ];

// If you want to use it at the same time as M5Paper and CoreInk libraries, include it before LovyanGFX.hpp.
// If you use it with M5Paper or CoreInk libraries, include it before LovyanGFX.hpp.
// #include
// #include
    

// Write the define according to the board you use.
// (Can be omitted if the corresponding board is selected in the board manager)
// #define LGFX_M5PAPER
// #define LGFX_M5STACK_COREINK
   #define LGFX_AUTODETECT // If you use automatic detection, only this description will work.

// Include LovyanGFX.hpp after the define of the board used.
    

LGFX gfx;
LGFX_Sprite sp(&gfx);

int w = 320;
int h = 480;

#ifdef min
#undef min
#endif

void setup(void)
{
// M5.begin();

  gfx.init(); // Perform initialization. Both LCD and EPD are common.

  gfx.setRotation(0); // The rotation direction setting is common for both LCD and EPD. 0 to 3 rotates clockwise in 90 degree increments. 4 to 7 will be flipped upside down.

  w = gfx.width();
  h = gfx.height();

  gfx.setBrightness(128); // Backlight brightness setting has no effect on EPD.

// You can set the EPD operation mode. Please change it each time according to your drawing purpose.
// *For M5Stack CoreInk, there is no difference except for epd_quality.
  gfx.setEpdMode(epd_mode_t::epd_fastest); // Fastest update, no black and white inversion, afterimages tend to remain
  gfx.setEpdMode(epd_mode_t::epd_fast); // Fast update, no black and white inversion, afterimages tend to remain
  gfx.setEpdMode(epd_mode_t::epd_text); // High quality update, black and white reversal occurs momentarily (for white background)
  gfx.setEpdMode(epd_mode_t::epd_quality); // High quality update, black and white reversal occurs momentarily
    lv_init();
// The characteristics of each mode in M5Paper (IT8951) are as follows.
// epd_fastest = DU4 Update time 120msec Only complete white and black can be drawn, intermediate tones are not drawn. Also, areas displayed in intermediate gradation cannot be updated.
// epd_fast = DU update time 260msec Only complete white and black can be drawn, intermediate tones are not drawn.
// epd_text = GL16 Update time 450msec Can be drawn with 16 levels of gray scale. White background/black text
// epd_quality = GC16 Update time 450msec Can be drawn with 16 grayscale levels. Image usage


// All drawing functions are available as in LCD.
// Colors can be specified in the same way as for LCD, but they are automatically converted to grayscale.
// (The ratio during grayscale conversion is R1:G2:B1. Green is expressed slightly brighter.)

//   int rectwidth = std::min(w, h) / 2;
//   gfx.fillTriangle( w / 2, 0, 0, h - 1, w - 1, h - 1, TFT_RED);
//   gfx.fillCircle(w/2, h/2, rectwidth, TFT_GREEN);
//   gfx.fillRect((w-rectwidth)/2, (h-rectwidth)/2, rectwidth, rectwidth, TFT_BLUE);

//   delay(3000);


// By surrounding the drawing process with startWrite/endWrite, it can be reflected on the screen all at once at endWrite().
// Alternatively, it can be reflected on the screen when display() is called.

//   gfx.startWrite(); // Suppress the immediate reflection of drawing contents.

//   for (int i = 0; i < 20; ++i)
//   {
//     gfx.drawLine(i * w / 20, 0, w - 1, i * h / 20, TFT_BLACK); // Not reflected on the screen at this point.
//     gfx.drawLine(0, i * h / 20, i * w / 20, h - 1, TFT_BLACK);
//   }

//   gfx.endWrite(); // It is reflected on the screen here.

//   delay(3000);

//   gfx.startWrite(); // Suppress the immediate reflection of drawing contents.

//   for (int i = 0; i < 5; i++)
//   {
//     for (int j = 0; j < 20; j++)
//     {
//       gfx.fillRect(random(w-20), random(h-20), 20, 20, random(65535)); // Not reflected on the screen at this point.
//     }
//     gfx.display(); // Reflected on the screen here.
//   }

//   gfx.endWrite(); // If it has already been reflected on the screen, nothing will happen at this point.

//   delay(3000);

// *To be exact, it is reflected on the screen only when display() is called.
// We have prepared a mechanism to call display() when the SPI bus is released, and it is enabled by default.
// With this mechanism, it is automatically reflected on the screen immediately after calling the drawing function or endWrite.
// Note that you can enable/disable this automatic display call with setAutoDisplay(bool).

//   gfx.setAutoDisplay(false); // Disable automatic display updates. (After that, it will not be reflected on the screen until display() is called.)

//   gfx.setFont(&fonts::Font4);
//   gfx.setTextColor(TFT_BLACK, TFT_WHITE); // Set text color to black and background color to white
//   gfx.setTextDatum(textdatum_t::top_center);
//   for (int i = 0; i < 10; i++)
//   {
//     gfx.drawString("Hello World !!", w / 2, i * h / 10);
//   }
//   gfx.qrcode("Hello world !", (w-rectwidth)/2, (h-rectwidth)/2, rectwidth);

//   gfx.display(); // Reflected on the screen here.

//   gfx.setAutoDisplay(true); // Enable automatic display updates.

//   delay(3000);

//   gfx.fillScreen(TFT_WHITE);

// M5Paper (IT8951) can display 16 grayscale levels using epd_quality/epd_text, but
// If you use epd_fast/epd_fastest, it will be limited to only two gradations, black and white.
// Even in this case, 17 tones can be expressed in a pseudo manner using LovyanGFX's tile pattern processing.

//   gfx.setEpdMode(epd_mode_t::epd_quality); // Set to high quality update mode (future drawings will use grayscale)
//   gfx.startWrite();
//   for (int i = 0; i < 16; i++)
//   {
//     int level = 8 + i * 16;
//     gfx.fillRect(i * w / 16, 0, w / 16 + 1, h / 2, gfx.color888(level, level, level));
//   }
//   gfx.display(); // Display update here will be in high quality mode.

//   gfx.waitDisplay(); // Wait for EPD display update to complete.
  // *If you want to check whether the display is being updated without waiting, use displayBusy().
  // Please use this when you want to draw between other processes.
  // Example: while (gfx.displayBusy()) delay(10); // Specify some other process instead of delay


  gfx.setEpdMode(epd_mode_t::epd_fast); // Set to fast update mode (subsequent drawing will use black and white binary)
  for (int i = 0; i < 17; i++)
  {
    int level = std::min(255, i * 16);
    gfx.fillRect(i * w / 17, h / 2, w / 17+1, h / 2, gfx.color888(level, level, level));
  }
  gfx.display(); // Drawing here is in high-speed mode.

  delay(3000);

  // In the high quality mode of M5Paper (IT8951), 241 tones can be expressed with 16 gray scale levels + tile pattern processing.
  gfx.setEpdMode(epd_mode_t::epd_quality);

  for (int i = 0; i < 256; ++i)
  {
    gfx.fillRect(0, (i * h) / 256, w, 4, gfx.color888(i, i, i));
  }
  gfx.display();

  gfx.endWrite();

  delay(3000);

  // It is possible to update the display of M5Paper (IT8951) in multiple locations at the same time.
  gfx.startWrite();
  for (int i = 0; i < 16; ++i)
  {
    std::int32_t y1 = (i * h) / 16, y2 = ((i + 1) * h) / 16;
    std::int32_t x1 = 0, x2 = 0;
    for (int j = 0; j < 16; ++j)
    {
      x2 = ((j + 1) * w) / 16;
      std::int_fast8_t l = 255 - (i * 16 + j);
      gfx.fillRect(x1, y1, x2 - x1, y2 - y1, gfx.color888(l, l, l));
      x1 = x2;
      if ((j & 7) == 7) gfx.display(); // Update the display once every 8 times
    }
  }
  gfx.endWrite();

  // *Please be careful not to draw in the range where the display is being updated.
  // If the content is changed while the display is being updated, it will not be drawn correctly.
    
  delay(3000);


   static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, 5);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 3));
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_img_recolor(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_img_recolor_opa(&style, LV_OPA_50);
    lv_style_set_transform_angle(&style, 300);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_img_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);

    LV_IMG_DECLARE(img_cogwheel_argb);
    lv_img_set_src(obj, &img_cogwheel_argb);

    lv_obj_center(obj);

  delay(3000);

//   gfx.fillScreen(TFT_WHITE);

//   // When drawing in a range that overlaps with the last display update range,
//   // LovyanGFX has a mechanism to wait for the display update to complete.
//   // Therefore, the display will not be distorted even if you are not conscious of it.
//   gfx.setEpdMode(epd_mode_t::epd_quality);
//   gfx.fillRect(0, 0, w/2, h/2, TFT_BLUE); // These drawings overlap in range, but
//   gfx.fillRect(0, 0, w/3, h/3, TFT_YELLOW);// Because the mechanism to wait for display update works
//   gfx.fillRect(0, 0, w/4, h/4, TFT_BLUE); // The drawing will not be distorted even if you are not conscious of it.
//   gfx.fillRect(0, 0, w/5, h/5, TFT_YELLOW);
//   gfx.fillRect(0, 0, w/6, h/6, TFT_BLUE);
//   gfx.fillRect(0, 0, w/7, h/7, TFT_YELLOW);

//   gfx.waitDisplay();

  // But automatic checks are not perfect. Due to the mechanism of comparing with the "previous display update range",
  // Intervening drawings to different ranges will prevent range checking from working properly.
//   gfx.fillRect(w/2, 0, w/2, h/2, TFT_BLUE); // If you alternately draw areas that do not overlap,
//   gfx.drawPixel(0, 0); // The mechanism to wait for display update does not work,
//   gfx.fillRect(w/2, 0, w/3, h/3, TFT_YELLOW);// It will no longer be drawn correctly.
//   gfx.drawPixel(0, 0);
//   gfx.fillRect(w/2, 0, w/4, h/4, TFT_BLUE); // * Even though it is drawn with the same color as the previous example
//   gfx.drawPixel(0, 0); // The displayed gradation may be different,
//   gfx.fillRect(w/2, 0, w/5, h/5, TFT_YELLOW);// Make sure the correct drawing is not done
//   gfx.drawPixel(0, 0);
//   gfx.fillRect(w/2, 0, w/6, h/6, TFT_BLUE);
//   gfx.drawPixel(0, 0);
//   gfx.fillRect(w/2, 0, w/7, h/7, TFT_YELLOW);

//   gfx.waitDisplay();

//   // Also, if the display update mode is epd_fastest mode, the response is given top priority, so
//   // The process of checking the display update range will now be omitted.
//   gfx.setEpdMode(epd_mode_t::epd_fastest); // Set to fastest update mode.
//   gfx.fillRect(0, h/2, w/2, h/2, TFT_BLUE); // Even if subsequent drawing overlaps with the display update range,
//   gfx.fillRect(0, h/2, w/3, h/3, TFT_YELLOW); // Now draws without waiting at all.
//   gfx.fillRect(0, h/2, w/4, h/4, TFT_BLUE); // Therefore, if you continuously draw overlapping ranges,
//   gfx.fillRect(0, h/2, w/5, h/5, TFT_YELLOW); // Contents were rewritten while updating the display
//   gfx.fillRect(0, h/2, w/6, h/6, TFT_BLUE); // The intended drawing result is not obtained.
//   gfx.fillRect(0, h/2, w/7, h/7, TFT_YELLOW);

//   gfx.fillRect(w/2, h/2, w/2, h/2, TFT_BLUE);
//   gfx.waitDisplay(); // Wait with waitDisplay if necessary.
//   gfx.fillRect(w/2, h/2, w/3, h/3, TFT_YELLOW);// By waiting correctly,
//   gfx.waitDisplay(); // Can prevent disruption of drawing results.
//   gfx.fillRect(w/2, h/2, w/4, h/4, TFT_BLUE);
//   gfx.waitDisplay(); // Check that the displayed result is different from the previous example
//   gfx.fillRect(w/2, h/2, w/5, h/5, TFT_YELLOW);
//   gfx.waitDisplay();
//   gfx.fillRect(w/2, h/2, w/6, h/6, TFT_BLUE);
//   gfx.waitDisplay();
//   gfx.fillRect(w/2, h/2, w/7, h/7, TFT_YELLOW);

//   delay(3000);


//   gfx.setEpdMode(epd_mode_t::epd_quality);

//   gfx.fillScreen(TFT_WHITE);

//   if (gfx.touch()) // You can determine whether a touch controller is present by checking whether the return value of the touch function is null.
//   {
//     gfx.startWrite();
//     for (int i = 0; i < 1024; i++)
//     {
//       if ((i & 255) == 0)
//       {
//         gfx.setEpdMode(epd_mode_t::epd_fast);
//         gfx.fillScreen(TFT_WHITE);
//         gfx.setTextColor(TFT_BLACK, TFT_WHITE);
//         gfx.setTextSize(3, 3);
//         gfx.drawString("Touch Test", w/2, h/2);
//         gfx.display();
//         delay(100);
//         gfx.waitDisplay();
//         gfx.setEpdMode(epd_mode_t::epd_fastest);
//       }
//       delay(15);

//       std::int32_t x, y, number = 0;
//       while (gfx.getTouch(&x, &y, number)) // You can get the coordinates during touch with the getTouch function.
//       {
//         gfx.fillCircle(x, y, 5, (std::uint32_t)(number * 0x333333u));
//         gfx.display();
//         ++number;
//       }
//     }
//     gfx.endWrite();
//   }

//   gfx.setEpdMode(epd_mode_t::epd_fast);
//   gfx.fillScreen(TFT_WHITE);

//   sp.setColorDepth(4);
//   if (!sp.createSprite(w / 2, h / 2)) sp.createSprite(w / 4, h / 4);
//   sp.setFont(&fonts::Font8);
}

void loop(void)
{
//   static int count = 0;

//   if (0 == (count & 15))
//   {
//     switch ((count >> 4) & 3)
//     {
//     case 0: gfx.setEpdMode(epd_mode_t::epd_quality); break;
//     case 1: gfx.setEpdMode(epd_mode_t::epd_text ); break;
//     case 2: gfx.setEpdMode(epd_mode_t::epd_fast ); break;
//     case 3: gfx.setEpdMode(epd_mode_t::epd_fastest); break;
//     }
//   }

//   for (int y = 0; y < sp.height(); y += 4) {
//     for (int x = 0; x < sp.width(); x += 4) {
//       std::uint32_t val = ((x+count*4)|(y+count*4)) >> 4;
//       sp.fillRect(x, y, 4, 4, val);
//     }
//   }

//   int x = 2;
//   int y = 2;
//   sp.setTextColor(TFT_BLACK);
//   sp.drawNumber(count, x-2, y-2);
//   sp.drawNumber(count, x+2, y-2);
//   sp.drawNumber(count, x+2, y+2);
//   sp.drawNumber(count, x-2, y+2);
//   sp.setTextColor(TFT_WHITE);
//   sp.drawNumber(count, x, y);

//   gfx.waitDisplay();
//   sp.pushSprite(count & 1 ? w / 2 : 0, count & 2 ? h / 2 : 0);
//   ++count;
}

