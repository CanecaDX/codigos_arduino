int pinoBuzzer = 2; 
int pinoSensor = 3; 
int estadoSensor; 

void setup(){
  Serial.begin(9600);
  pinMode(pinoSensor, INPUT);
  pinMode(pinoBuzzer, OUTPUT); 
}

void loop(){
  estadoSensor = digitalRead(pinoSensor);
  Serial.println(estadoSensor);
  if (!estadoSensor){
    digitalWrite(pinoBuzzer, HIGH);
    delay(100);
    digitalWrite(pinoBuzzer, LOW);
    delay(100);
  }
}
