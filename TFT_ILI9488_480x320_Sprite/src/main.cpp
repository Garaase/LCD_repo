# define LGFX_AUTODETECT 
# include  <LovyanGFX.hpp>
 static LGFX lcd;                       // Create an instance of LGFX. 
static LGFX_Sprite sprite (&lcd) ;       // Create a sprite to draw on the LCD 
static LGFX_Sprite sprite2 (&sprite) ;   // Create a sprite to draw on a sprite 
static LGFX_Sprite sprite3;            // Create a sprite with no default drawing destination setting 
static LGFX_Sprite sprite4;            // Create a sprite with no default drawing destination setting 


void  setup ()  {
  lcd.init();
  sprite .createSprite ( 64 , 64 );
   sprite2 .createSprite ( 32 , 32 );
   sprite3 .createSprite ( 16 , 16 );
   sprite .fillScreen (TFT_RED);
   sprite2 .fillScreen (TFT_BLUE);
   sprite3 .fillScreen (TFT_GREEN);
   sprite3 . pushSprite (&sprite2, 0 , 0 );
   sprite2 .pushSprite ( 0 , 0 );
   sprite .pushSprite ( 0 , 0 );
   sprite .setPivot (sprite.width()/ 2.0 , sprite.height()/ 2.0 );
   sprite . pushRotateZoom ( 200 , 350 , 45 , 2.0 , 3.0 );
}

void  loop ()  {
}