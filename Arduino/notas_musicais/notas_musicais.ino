int buzzer2 =  9;
int buzzer = 10;

void setup() {
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  

  //mi, fa, sol
    tone(buzzer, 297, 600);  
  delay(1000);  
  tone(buzzer, 528, 700);  
  delay(1000);
  tone(buzzer, 297, 100);  
  delay(1000);
    tone(buzzer, 440, 100);  
  delay(1000);  

      tone(buzzer, 297, 600);  
  delay(1000);  
  tone(buzzer, 528, 700);  
  delay(1000);
  tone(buzzer, 297, 100);  
  delay(1000);
    tone(buzzer, 440, 100);  
  delay(1000);  

      tone(buzzer, 396, 600);  
  delay(1000);  
  tone(buzzer, 440, 700);  
  delay(1000);
  tone(buzzer, 264, 100);  
  delay(1000);
    tone(buzzer, 330, 100);  
  delay(1000);  
 
}
