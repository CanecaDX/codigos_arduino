#include "U8glib.h"
#include <DHT_U.h>

#define pinoDHT    A2
#define modeloDHT  DHT22 

int temp;
int umidRel;
uint32_t delayMS;

DHT_Unified dht(pinoDHT, modeloDHT);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	 //SCL -> A5   SDA -> A4

int p;

void pagInicial();  
void pagInfo1();

void (*pag[])() = { pagInicial , pagInfo1 };

void pagInicial(){
  ifsul_logo();
}

void pagInfo1(){
  ifsul_logo();
}

void ifsul_logo() 
{
  const char DEGREE_SYMBOL[] = { 0xB0, '\0' };
  u8g.drawRFrame(0, 0, 62, 30, 4);
  u8g.drawRFrame(66, 0, 62, 30, 4);
  u8g.drawRFrame(0, 34, 62, 30, 4);
  u8g.drawRFrame(66, 34, 62, 30, 4);
    
  u8g.setFont(u8g_font_5x8r);
  u8g.drawStr(4,10,"TEMPERATURA");
  u8g.drawStr(69,10,"UMID. RELAT.");
  u8g.drawStr(6,44,"TEMP. EXT.");
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(32, 25, DEGREE_SYMBOL);
  u8g.drawStr(41, 25, "C");
  u8g.drawStr(102, 25, "%");
  u8g.drawStr(32, 59, DEGREE_SYMBOL);
  u8g.drawStr(41, 59, "C");
 }

void setup(void) {
  Serial.begin(9600);
  pinMode(pinoDHT, INPUT);
  dht.begin(); 

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

void loop() {
  // picture loop
   u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_8x13B);
     char buf[9];
    sprintf (buf, "%d", temp);
    u8g.drawStr(14, 25, buf);
    sprintf (buf, "%d", umidRel);
    u8g.drawStr(83, 25, buf);
   (*pag[p])();
    sensors_event_t evento;  
    dht.temperature().getEvent(&evento);
    temp = evento.temperature;
    Serial.print(evento.temperature, 0);
    dht.humidity().getEvent(&evento);
    umidRel = evento.relative_humidity;
  } while( u8g.nextPage() );
  

  sensors_event_t evento;  

  dht.temperature().getEvent(&evento);
  Serial.print("TEMPERATURA: ");
  Serial.print(evento.temperature);
  Serial.print(" C");
  

  dht.humidity().getEvent(&evento);
  Serial.print("   UMIDADE RELATIVA: ");
  Serial.println(evento.relative_humidity);
  delay(1000);
}