#include <Arduino.h>

int pinoTrig = 13;
int pinoEcho = 12;
int pinoBuzzer = 11; //ADICIONAR
float tempo, distancia;

void setup()
{
  Serial.begin(9600);
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  pinMode(pinoBuzzer, OUTPUT); //ADICIONAR
}

void loop()
{
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);

  tempo = pulseIn(pinoEcho, HIGH);
  distancia = (tempo*0.0343)/2;
  
    Serial.println(distancia);

    //ADICIONAR
    
    if (distancia < 100 && distancia > 25) 
    {
        tone(pinoBuzzer, 330, 110);
        delay(40);
 
        delay(200   );
         tone(pinoBuzzer, 297, 110);
        delay(40);
 
        delay(200   );
         tone(pinoBuzzer, 352, 110);
        delay(40);
 
        delay(200  );
         tone(pinoBuzzer, 396, 110);
        delay(40);

        delay(200   );
         tone(pinoBuzzer, 528, 110);
        delay(40);
      
        delay(200   );
         tone(pinoBuzzer, 495, 110);
        delay(40);
    
        delay(100   );
         tone(pinoBuzzer, 297, 110);
        delay(40);
   
        delay(100  );
         tone(pinoBuzzer, 330, 110);
        delay(40);
    
        delay(100   );
         tone(pinoBuzzer, 495, 110);
        delay(40);

        delay(100   );
         tone(pinoBuzzer, 440, 110);
        delay(40);

        delay(100   );
         tone(pinoBuzzer, 528, 110);
        delay(40);
  
        delay(100   );
         tone(pinoBuzzer, 330, 440);
        delay(40);

        delay(100);
         tone(pinoBuzzer, 440, 650);
        delay(1600);


    }
  
    /*if (distancia < 50 && distancia > 25) 
    {
        tone(pinoBuzzer, 440, 25);
        delay(50);
        noTone(pinoBuzzer);
        delay(50);
    }
  
    if (distancia < 25) 
    {
        tone(pinoBuzzer, 440, 12);
        delay(25);
        noTone(pinoBuzzer);
        delay(25);
    }*/
  
}
