// define os pinos usados para alimentar o sensor de umidade e ler o sensor
#define sensorPower 7
#define sensorPin 8

#include <LiquidCrystal.h>

// define os pinos usados para a ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // configura o pino de alimentação do sensor como saída e desliga ele
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);

  // inicializa o display lcd com 16 colunas e 2 linhas
  lcd.begin(16, 2);
}

void loop() {
  // le o sensor de umidade e armazena o valor em "val"
  int val = readSensor();
  int seconds;

  if (val) {
    // se o sensor de umidade NAO detectar agua, exibe "nao banho" no display
    lcd.clear();
    lcd.print("nao banho");
    lcd.setCursor(0, 1);
    lcd.print("tempo: 0,0");
  } else {
    // inicia o contador para o tempo de banho se agua for detectada
    int seconds = 59;
    int minutes = 2;
    imprime(minutes, seconds);
    delay(500);

    for (minutes = 2; minutes > -1; minutes--) {
      for (seconds = 58; seconds > -1; seconds--) {
        imprime(minutes, seconds);
        delay(500);
        int val = readSensor();
        if (val) {
          // interrompe o banho se agua parar de ser detectada
          break;
        }
      }
    }
    
    // exibe "fim do banho" no display após o termino do banho
    lcd.clear();
    lcd.print("fim do banho");
    delay(5000);
  }
}

// função para ler o sensor de umidade
int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  int val = digitalRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}

// função para exibir o tempo no display
void imprime(int x, int y) {
  lcd.clear();
  lcd.print("banho");
  lcd.setCursor(0, 1);
  lcd.print("tempo: ");

  lcd.setCursor(6, 1);
  lcd.print(x);
  lcd.setCursor(7, 1);
  lcd.print(":");
  lcd.setCursor(8, 1);
  lcd.print(y);
  return;
}
