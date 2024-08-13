# include <DHT_U.h>

# define pinoDHT    A0
# define modeloDHT  DHT22 

//PINOUT: 1-VCC 2-DATA 3-NC 4-GND

DHT_Unified dht(pinoDHT, modeloDHT);

uint32_t delayMS;

void setup() {
 
  dht.begin();  
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

}

void loop() {
    
  sensors_event_t evento;  

  dht.temperature().getEvent(&evento);
    
  Serial.print("TEMPERATURA: ");
  Serial.print(evento.temperature);
  
  dht.humidity().getEvent(&evento);
  Serial.print("   UMIDADE RELATIVA: ");
  Serial.println(evento.relative_humidity);
  
  delay(delayMS);

}
