#include "PanelLan.h"
#include "car_img9.h"
#include "icon_img.h"
#//include "ui.h"

int x = 0;
int y = 0;

// BOARD_SC01, BOARD_SC01_PLUS, BOARD_SC02, BOARD_SC05, BOARD_KC01, BOARD_BC02
PanelLan tft(BOARD_SC05);
static LGFX_Sprite sprite (&tft) ;
void setup(void) {
  tft.begin();
  tft.clear(TFT_TRANSPARENT); 
  tft.setTextDatum(textdatum_t::middle_left);
  tft.setFont(&fonts::FreeSerifBold18pt7b);
  tft.pushImage(0,  30,  imgWidth,  imgHeight,  img); 
}

void loop() {
  tft.drawString("COUNTER: ", (tft.width() / 2)-90, tft.height() / 2);
  tft.drawNumber(x, (tft.width() / 2)+100, tft.height() / 2);
  delay(10); 
  x++;
}
