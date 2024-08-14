#include "U8glib.h" //display
#include <Wire.h>
#include <DHT_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define pinoDHT    A2
#define modeloDHT  DHT22 
#define pinoBuzzer 11
#define pinoSensor 2 
#define pinoSonda 3 

int contador = 0;

int estadoSensor; 
int temp;
int tempExt;
int umidRel;
uint32_t delayMS;

OneWire oneWire(pinoSonda);
DallasTemperature sonda(&oneWire);
DeviceAddress endTemp;

DHT_Unified dht(pinoDHT, modeloDHT);

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); //SCL -> A5   SDA -> A4

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
  /*u8g.drawDisc(x+3, y+19, 3, U8G_DRAW_ALL);
  u8g.drawBox( x+9, y+16, 6, 6);
  u8g.drawBox(x+18, y+16, 6, 6);
  u8g.drawBox( x+0, y+25, 6, 6);
  u8g.drawBox( x+9, y+25, 6, 6);
  u8g.drawBox( x+0, y+34, 6, 6);
  u8g.drawBox( x+9, y+34, 6, 6);
  u8g.drawBox(x+18, y+34, 6, 6);
  u8g.drawBox( x+0, y+43, 6, 6);
  u8g.drawBox( x+9, y+43, 6, 6);*/
  
  //u8g.drawRFrame(0, 0, 128, 64, 4);
  
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

void setup(){
  pinMode(pinoSensor, INPUT);
  pinMode(pinoBuzzer, OUTPUT); 
  pinMode(pinoDHT, INPUT);
  sonda.begin();
  dht.begin();  
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  //display
  p=0;
  Serial.begin(9600);
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
    u8g.setHiColorByRGB(255,255,255);
  }
}

void loop(){
  u8g.firstPage();  
  do
  {
    u8g.setFont(u8g_font_8x13B);
    char buf[9];
    sprintf (buf, "%d", temp);
    u8g.drawStr(14, 25, buf);
    sprintf (buf, "%d", umidRel);
    u8g.drawStr(83, 25, buf);
    sprintf (buf, "%d", tempExt);
    u8g.drawStr(14, 59, buf);
    (*pag[p])();
  }while( u8g.nextPage() );
  delay(500);
  p=p+1;
  if (p==2)
    p=0;
  estadoSensor = digitalRead(pinoSensor);
  if (!estadoSensor){
    for(int i=0; i<5; i++){
      digitalWrite(pinoBuzzer, HIGH);
      delay(100);
      digitalWrite(pinoBuzzer, LOW);
      delay(100);   
    } 
    /*lcd.setCursor(0,0); 
    lcd.print("      GAS       ");
    lcd.setCursor(0,1);
    lcd.print("   DETECTADO    ");
    delay(1000);*/
  }
  else{ 
    sensors_event_t evento;  
    dht.temperature().getEvent(&evento);
    /*lcd.setCursor(0,0);
    lcd.print("TEMPERATURA ");
    lcd.print(evento.temperature,0); 
    lcd.print((char)223);
    lcd.print("C");*/
    temp = evento.temperature;
  
    //Serial.print("TEMPERATURA: ");
    Serial.print(evento.temperature, 0);
   // Serial.print("°C");*/
    
    dht.humidity().getEvent(&evento);
    /*lcd.setCursor(0,1);
    lcd.print("UMIDADE REL. ");
    lcd.print(evento.relative_humidity,0);
    lcd.print("%");*/
    umidRel = evento.relative_humidity;
    /*Serial.print("     UMIDADE RELATIVA DO AR: ");
    Serial.print(evento.relative_humidity,0);
    Serial.println("%");*/
  
    delay(delayMS);
    
    sonda.requestTemperatures();
    sonda.getAddress(endTemp,0);
    tempExt = sonda.getTempC(endTemp);
    //Serial.print("Temperatura: ");
    contador++;
    Serial.print("   ");
    Serial.print(contador);
    Serial.print("  -  ");
    Serial.println(sonda.getTempC(endTemp), 1);
    //Serial.println("°C");
    delay(1000);
  }
}