#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 2           // define o pino utilizado pelo sensor
#define DHTTYPE DHT11     // define o tipo de sensor utilizado

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display


DHT dht(DHTPIN, DHTTYPE); // cria um objeto do tipo DHT


int opc; 
void setup() {  
  lcd.begin(16, 2);//Define o número de colunas e linhas do display
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  delay(1000);
  lcd.print("iniciando...");
  delay(1000);
  lcd.clear();
  delay(200);

  pinMode(2, OUTPUT);



  lcd.print("M1.0");  
  delay(500);
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print(">");
  Serial.begin(9600);

  dht.begin();

}

//Função para botão select
void select() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1  
   
  if(opc == 1){
    temps();

  }
  else if(opc == 2){
    umids();

  }
  else if(opc ==3){
    luzs();
  }
  else if(opc ==4){
    reles();
  }
}

//Função para botão up
void up() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("TEMPERATURA");
  opc = 1;
}

//Função para botão down
void down() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("UMIDADE");
  opc = 2;   
}

//Função para botão right
void right() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("LUZ AMBIENTE");
  opc = 3;
}

//Função para botão left
void left() {
  lcd.clear();
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("RELE");//6 espaços para meio
  opc = 4;
}


//funçoes
void temps(){
//lcd.print(">temp: ");
while(true){

float temp = dht.readTemperature(); // lê a temperatura do sensor

lcd.setCursor(0, 0); // move o cursor para a posição (0,0) do display
lcd.print("Temp: ");
lcd.print(temp);
lcd.print(" C");

delay(1000); // espera 1 segundo antes de ler novamente
}
}
void umids(){
//lcd.print(">umid: ");
while(true){

  float humidity = dht.readHumidity();  // lê a umidade do sensor
  lcd.print("Umid: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000);         // espera 2 segundos entre as leituras
  lcd.clear();
}
}
void luzs(){
}
void reles(){

    //plotter
    int estadorele = digitalRead(2);
    Serial.println(estadorele);

}


void loop() {
  Serial.println(analogRead(0));//Exibe a leitura do pino analógico A0 no monitor serial
  delay(100);

  if ((analogRead(0)) < 80) { //Se a leitura for menor que 80 chama a função right
    right();
  }
  else if ((analogRead(0)) < 200) {//Se a leitura for menor que 200 chama a função up
    up();
  }
  else if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
    down();
  }
  else if ((analogRead(0)) < 600) {//Se a leitura for menor que 600 chama a função left
    left();
  }
  else if ((analogRead(0)) < 800) {//Se a leitura for menor que 800 chama a função left
    select();
  } 
}