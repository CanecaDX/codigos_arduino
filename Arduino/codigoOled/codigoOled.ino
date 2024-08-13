#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	 //SCL -> A5   SDA -> A4

void draw1(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setHiColorByRGB(255, 0, 34);
  u8g.drawStr( 15, 40, "Carregando...");
}

void draw2(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setHiColorByRGB(255, 0, 34);
  u8g.drawStr( 15, 40, "Sofia Linda <3");
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 0, 34);
  }
  
  pinMode(8, OUTPUT);
}

void loop(void) {
  // picture loop
   u8g.firstPage();  
  do {
    draw1();
  } while( u8g.nextPage() );
  delay(5000);
  u8g.firstPage();   
  do {
   draw2();
  } 
  while( u8g.nextPage() );
  delay(5000);
}
