int buzzer2 =  9;
int buzzer = 10;

void setup() {
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {

  //S
  tone(buzzer, 264, 100);  
  delay(20);  
  tone(buzzer, 297, 100);  
  delay(20);
  tone(buzzer, 396, 100);  
  delay(20);  
  tone(buzzer, 264, 100);  
  delay(1000);  
 
}
