#define vermelho1 31
#define amarelo1 33

void setup() {
  pinMode(vermelho1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
}

void loop() {

  //Configuração do Tempo 1
  digitalWrite(vermelho1, HIGH);  
  digitalWrite(amarelo1, LOW); 
  delay(2000); //ajustar o tempo correto

  //Configuração do Tempo 2
  digitalWrite(vermelho1, HIGH);  
  digitalWrite(amarelo1,  LOW);  
  delay(2000); //ajustar o tempo correto
  
}
