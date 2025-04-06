// Definições de pinos
#define PINO_LED 3
#define PINO_FOTO A1

// Definições dos pinos do sensor e alimentação
const int PINO_SENSOR = A2;
const int PINO_ALIMENTACAO_SENSOR = 2;
const int LED_1 = 5;
const int LED_2 = 6;
const int LED_3 = 7;
int sensor;
int umido = 800;
int seco = 500;

// Definições dos pinos dos LEDs RGB
int pinoTemp = 0;
int pinoR = 8;
int pinoY = 12;  // Alterado para pino amarelo
int pinoB = 13;

// Função de configuração
void setup() {
  // Configuração dos pinos
  pinMode(pinoTemp, INPUT);  // Pino de leitura do sensor de temperatura
  pinMode(pinoR, OUTPUT);    // Pino para LED vermelho
  pinMode(pinoY, OUTPUT);    // Pino para LED amarelo
  pinMode(pinoB, OUTPUT);    // Pino para LED azul
  pinMode(PINO_LED, OUTPUT); // Pino do LED
  pinMode(PINO_FOTO, INPUT); // Pino do fotoresistor
  pinMode(LED_1, OUTPUT);    // Pino do LED 1
  pinMode(LED_2, OUTPUT);    // Pino do LED 2
  pinMode(LED_3, OUTPUT);    // Pino do LED 3
  pinMode(PINO_ALIMENTACAO_SENSOR, OUTPUT); // Pino de alimentação do sensor
  Serial.begin(9600);        // Inicia a comunicação serial
}

// Função para desligar os LEDs
void desligarLeds() {
  digitalWrite(pinoR, LOW); // Desliga o LED vermelho
  digitalWrite(pinoY, LOW); // Desliga o LED amarelo
  digitalWrite(pinoB, LOW); // Desliga o LED azul
}

// Função principal que executa repetidamente
void loop() {
  // Bloco de leitura da temperatura
  int leituraTemp = analogRead(pinoTemp);  // Lê o valor do sensor de temperatura
  int temperatura = map(leituraTemp, 20, 358, -40, 125);  // Mapeia o valor para uma faixa de temperatura

  // Controle dos LEDs baseado na temperatura
  desligarLeds();
  if (temperatura <= 10) {
    digitalWrite(pinoB, HIGH);  // Liga o LED azul se a temperatura for baixa
  }
  else if (temperatura <= 30) {
    digitalWrite(pinoY, HIGH);  // Liga o LED amarelo se a temperatura for moderada
  }
  else {
    digitalWrite(pinoR, HIGH);  // Liga o LED vermelho se a temperatura for alta
  }

  // Bloco de controle do brilho do LED
  analogWrite(PINO_LED, (analogRead(PINO_FOTO) / 4));  // Ajusta o brilho do LED com base no fotoresistor
  delay(100);  // Atraso de 100ms

  // Bloco de leitura do sensor de umidade
  digitalWrite(PINO_ALIMENTACAO_SENSOR, HIGH);  // Ativa o sensor
  delay(10);  // Atraso para garantir a leitura
  sensor = analogRead(PINO_SENSOR);  // Lê o valor do sensor de umidade
  digitalWrite(PINO_ALIMENTACAO_SENSOR, LOW);  // Desativa o sensor para evitar corrosão

  // Exibe a leitura do sensor no monitor serial
  Serial.println(sensor);

  // Bloco de controle dos LEDs com base na umidade
  if (sensor > umido) {
    digitalWrite(LED_1, LOW);  // Desliga o LED 1 (vermelho)
    digitalWrite(LED_2, LOW);  // Desliga o LED 2 (amarelo)
    digitalWrite(LED_3, HIGH); // Liga o LED 3 (azul) se o solo estiver úmido
  }
  else if (sensor < seco) {
    digitalWrite(LED_1, HIGH); // Liga o LED 1 (vermelho) se o solo estiver seco
    digitalWrite(LED_2, LOW);  // Desliga o LED 2 (amarelo)
    digitalWrite(LED_3, LOW);  // Desliga o LED 3 (azul)
  }
  else {
    digitalWrite(LED_1, LOW);  // Desliga o LED 1 (vermelho)
    digitalWrite(LED_2, HIGH); // Liga o LED 2 (amarelo) se o solo estiver moderadamente úmido
    digitalWrite(LED_3, LOW);  // Desliga o LED 3 (azul)
  }

  // Atraso antes de fazer a próxima leitura
  delay(100);
}
