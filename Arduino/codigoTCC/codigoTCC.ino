#include "U8glib.h"
#include <DHT_U.h>

#include <SPI.h> //biblioteca SD
#include <SD.h>  //biblioteca SD

#define pinoDHT    A2
#define modeloDHT  DHT22 
#define pinoSensorSolo A6
#define pinoSensorGas A7
#define CS 10 //Chip Select SD.

int temp;
int umidRel;

int pinoGas = 5;  
int pinoBuzzer = 6; 
int estadoSensorGas;
int estadoDetGas; 
int estadoSensorSolo;

File arquivo; //faz alguma coisa no SD

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
  u8g.drawStr(6,44,"UMID. SOLO");
   u8g.drawStr(75,44,"CONC. C02");
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr(32, 25, DEGREE_SYMBOL);
  u8g.drawStr(41, 25, "C");
  u8g.drawStr(102, 25, "%");
  u8g.drawStr(45, 59, "%");
 }

void setup(void) {
  Serial.begin(9600);
    pinMode(pinoDHT, INPUT);
    pinMode(pinoSensorGas, INPUT);
    pinMode(pinoBuzzer, OUTPUT); 
    pinMode(pinoSensorSolo, INPUT);

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

  //Inicializa cartão.
  if(!SD.begin(CS))//se der errado
  {
    Serial.println("Não foi possível acessar o cartão.");
    Serial.println("Verifique se o cartão está inserido corretamente.");
    Serial.println("Verifique as conexões no módulo e o Arduino.");
  
    while(1); //Evita executar o loop quando der erro.
  }
  else
  {
    Serial.println("Cartão inicializado corretamente!!!"); //deu certo
  }

  Serial.println();
}

void loop() {

  estadoDetGas = digitalRead(pinoSensorGas);
  if (!estadoDetGas){
    digitalWrite(pinoBuzzer, HIGH);
    delay(100);
    digitalWrite(pinoBuzzer, LOW);
    delay(100);
  }

  u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_8x13B);
     char buf[9]; 
    sprintf (buf, "%d", temp);
    u8g.drawStr(14, 25, buf);
    sprintf (buf, "%d", umidRel);
    u8g.drawStr(83, 25, buf);
    sprintf (buf, "%d", estadoSensorSolo);
    u8g.drawStr(20, 57, buf);
    sprintf (buf, "%d", estadoSensorGas);
    u8g.drawStr(83, 57, buf);
   (*pag[p])();
    sensors_event_t evento;  
  } while( u8g.nextPage() );

  String dadosG = "";

  sensors_event_t evento;   

  dadosG = " Temp: " + dht.humidity().getEvent(&evento) + String(evento.temperature) + " C" + "|" + " Umid: " + dht.temperature().getEvent(&evento) + String(evento.relative_humidity) + " %" + "|" + "Gas: " + String(estadoSensorGas = analogRead(pinoSensorGas)) + " PPM" + "|" + "Solo" + String(estadoSensorSolo = analogRead(pinoSensorSolo)) + " %"; //Prepara a string com os dados a serem gravados

  //Cria o arquivo para inserir os dados, caso o arquivo já exista
  //os dados vão ser inseridos nele.
  arquivo = SD.open("dadosG.txt", FILE_WRITE);
  if(arquivo)
  { 
    dht.temperature().getEvent(&evento);
    Serial.print("T: "); 
    Serial.println(evento.temperature);

    dht.humidity().getEvent(&evento) + String(evento.temperature);
    Serial.print("U: "); 
    Serial.println(evento.relative_humidity);

     estadoSensorGas = analogRead(pinoSensorGas);
     Serial.print("PPM: ");
     Serial.println(estadoSensorGas);

     estadoSensorSolo = analogRead(pinoSensorSolo) / 10;
     Serial.print("SOLO: ");
     Serial.println(estadoSensorSolo); 

    arquivo.println(dadosG); //Grava no arquivo.
    arquivo.close();
  }
  else
  {
    Serial.println("Erro ao abrir o arquivo");
  };

  delay(2000);
}