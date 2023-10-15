#define vermelho1 31
#define amarelo1 33
#define verde1 35
#define vermelho2 37
#define amarelo2 39
#define verde2 41

void setup() {
  pinMode(vermelho1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(verde1, OUTPUT);
  pinMode(vermelho2, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(verde2, OUTPUT);
}

void loop() {

  //Configuração do Tempo 1
  digitalWrite(vermelho1, HIGH);  
  digitalWrite(amarelo1, LOW);  
  digitalWrite(verde1, LOW);  
  digitalWrite(vermelho2, LOW);  
  digitalWrite(amarelo2, LOW);  
  digitalWrite(verde2, HIGH);  
  delay(2000); //ajustar o tempo correto

  //Configuração do Tempo 2
  digitalWrite(vermelho1, //definir);  
  digitalWrite(amarelo1, //definir);  
  digitalWrite(verde1, //definir);  
  digitalWrite(vermelho2, //definir);  
  digitalWrite(amarelo2, //definir);  
  digitalWrite(verde2, //definir);  
  delay(2000); //ajustar o tempo correto
    
  //Configuração do Tempo 3
  digitalWrite(vermelho1, //definir);  
  digitalWrite(amarelo1, //definir);  
  digitalWrite(verde1, //definir);  
  digitalWrite(vermelho2, //definir);  
  digitalWrite(amarelo2, //definir);  
  digitalWrite(verde2, //definir);  
  delay(2000); //ajustar o tempo correto
  
  //Configuração do Tempo 4
  digitalWrite(vermelho1, //definir);  
  digitalWrite(amarelo1, //definir);  
  digitalWrite(verde1, //definir);  
  digitalWrite(vermelho2, //definir);  
  digitalWrite(amarelo2, //definir);  
  digitalWrite(verde2, //definir);  
  delay(2000); //ajustar o tempo correto
  
}
