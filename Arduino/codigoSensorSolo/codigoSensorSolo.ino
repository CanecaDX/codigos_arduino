#include <DHT_U.h>

#define pinoSensor A0
#define pinoDHT A15
#define modeloDHT DHT11


DHT_Unified dht(pinoDHT, modeloDHT);

uint32_t delayMS;
void setup() {
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay/1000;

  pinMode(pinoSensor, INPUT);
}

void loop() {  
  
  sensors_event_t evento;  

  dht.temperature().getEvent(&evento);  
  Serial.println("TEMPERATURA ");
  Serial.println(evento.temperature, 1);
  Serial.println("C");

  dht.humidity().getEvent(&evento);
  Serial.println("UMIDADE REL.");
  Serial.println(evento.relative_humidity, 1);
  Serial.println("%");

  delay(delayMS); 


  Serial.println("\nUMIDADE RELATIVA DO SOLO");
  Serial.println(analogRead(pinoSensor));
  delay(5000);
}
