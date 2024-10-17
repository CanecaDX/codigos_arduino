/*
Exemplo que obtém os dados de dois potenciômetros e armazena estes dados 
em um arquivo no cartão micro SD.

www.bitabittecnologia.com.br
*/

#include <SPI.h>
#include <SD.h>
#include <DHT_U.h>


#define pinoDHT A0 //DHT11
#define modeloDHT  DHT11
#define pinoGas A3 //MQ-2
DHT_Unified dht(pinoDHT, modeloDHT);

#define CS 53 //Chip Select.

int estadoSensorGas;

File arquivo;

void setup() 
{
  Serial.begin(9600);

  dht.begin();  
  sensor_t sensor;
  pinMode(pinoGas, INPUT);
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  //Inicializa cartão.
  if(!SD.begin(CS))
  {
    Serial.println("Não foi possível acessar o cartão.");
    Serial.println("Verifique se o cartão está inserido corretamente.");
    Serial.println("Verifique as conexões no módulo e o Arduino.");
    
    while(1); //Evita executar o loop quando der erro.
  }
  else
  {
    Serial.println("Cartão inicializado corretamente!!!");
  }

  Serial.println();
}

void loop() 
{

  String dadosT8= "";

  sensors_event_t evento;                 

  dadosT8 = " Temp: " + dht.humidity().getEvent(&evento) + String(evento.temperature) + " C" + "|" + " Umid: " + dht.temperature().getEvent(&evento) + String(evento.relative_humidity) + " %"; //+ "|" + "Gas: " + String(estadoSensorGas = analogRead(pinoGas)) + " PPM"; Prepara a string com os dados a serem gravados 


  //Cria o arquivo para inserir os dados, caso o arquivo já exista
  //os dados vão ser inseridos nele.
  arquivo = SD.open("dadosT8.txt", FILE_WRITE);
  if(arquivo)
  { 
    dht.temperature().getEvent(&evento);
    Serial.print("T: "); 
    Serial.println(evento.temperature);

    dht.humidity().getEvent(&evento) + String(evento.temperature);
    Serial.print("U: "); 
    Serial.println(evento.relative_humidity);

     estadoSensorGas = analogRead(pinoGas);
     Serial.print("PPM: ");
     Serial.println(estadoSensorGas);

    arquivo.println(dadosT8); //Grava no arquivo.
    arquivo.close();
  }
  else
  {
    Serial.println("Erro ao abrir o arquivo");
  }

  delay(2000);
}
