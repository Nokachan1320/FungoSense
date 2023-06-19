#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 2           // define o pino utilizado pelo sensor
#define DHTTYPE DHT11     // define o tipo de sensor utilizado
#define ldr A5
#define led 04 

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display

DHT dht(DHTPIN, DHTTYPE); // cria um objeto do tipo DHT

int valnav1 = 0;
int vldr=0;

int opc; 
void setup() {  
  lcd.begin(16, 2);//Define o número de colunas e linhas do display
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.clear();

  pinMode(2, OUTPUT);

  lcd.print("FSense");  
  delay(500);
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print(">");
  Serial.begin(9600);

 pinMode(ldr,INPUT);
 pinMode(led,OUTPUT);

  pinMode(ldr,INPUT);
  dht.begin();
  pinMode(3, OUTPUT);
  valnav1 = 0;
  while(valnav1 == 0){
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
    refr();
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
  lcd.print("          _");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("REFRIGERACAO");//6 espaços para meio
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
  //sair
if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
  lcd.clear();
  lcd.print("sair");
  delay(500);
  exit();
}

}
}
void umids(){
//lcd.print(">umid: ");
while(true){

  float humidity = dht.readHumidity();  // lê a umidade do sensor
  lcd.setCursor(0, 0); // move o cursor para a posição (0,0) do display
  lcd.print("Umid: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000);         // espera 2 segundos entre as leituras
  lcd.clear();
  //sair
  if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
  lcd.clear();
  lcd.print("sair");
  delay(500);
  exit();
  }

  valnav1 = 1;
}
}
void luzs(){
while(true){

  if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
  lcd.clear();
  lcd.print("sair");
  delay(500);
    exit();
}

  vldr=analogRead(ldr);
  if(vldr>400){
      Serial.println("luz alta");
      lcd.clear();
      lcd.print("luz alta");
    digitalWrite(led,LOW);
  }
  
  else{
      Serial.println("luz baixa");
      lcd.clear();
      lcd.print("luz baixa");
    digitalWrite(led,HIGH);
  }
  
  Serial.println( vldr);
  delay(100);
}
    //sair

  
}
void refr(){
  valnav1 = 1;
  lcd.setCursor(0, 0);
  lcd.print("refrigerar");
  lcd.setCursor(0, 1);
  Serial.println(analogRead(0));//Exibe a leitura do pino analógico A0 no monitor serial
  lcd.print("up - ligar");

while(true){
  delay(500);
  if((analogRead(0)) < 200){
    digitalWrite(3, HIGH);
    lcd.clear();
    lcd.print("ligado");
    delay(600);
    setup();
  }
    //sair
  if ((analogRead(0)) < 400) {//Se a leitura for menor que 400 chama a função down
  lcd.clear();
  lcd.print("sair");
  delay(500);
    exit();
  }
} 
}
void exit(){
  setup();

}

void loop() {
  Serial.print(valnav1);
}
