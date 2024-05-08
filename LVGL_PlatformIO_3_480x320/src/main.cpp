#define LGFX_AUTODETECT 
#include <LovyanGFX.hpp> 
#include "car_img6.h"
static  LGFX  lcd; 
extern  const  uint16_t  imgWidth; 
extern  const  uint16_t  imgHeight; 
extern  const  unsigned  short  img[]; 
void  setup()  { 
  lcd.init(); 
  lcd.clear(TFT_RED); 
} 
void  loop()  { 
  // int  x  =  rand()  %  lcd.width(); 
  // int  y  =  rand()  %  lcd.height(); 
  lcd.pushImage(0,  0,  imgWidth,  imgHeight,  img); 
  delay(100); 
} 