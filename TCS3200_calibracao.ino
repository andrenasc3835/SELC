#include <Servo.h>

// Define os pinos do sensor de cor
#define s0 2 // Pino S0 do sensor no pino #2 do Arduino
#define s1 3 // Pino S1 do sensor no pino #3 do Arduino
#define s2 4 // Pino S2 do sensor no pino #4 do Arduino
#define s3 5 // Pino S3 do sensor no pino #5 do Arduino
#define sensorOut 6 // Pino de saída do sensor no pino #6 do Arduino

// Variável para salvar os dados provenientes do sensorOut
int frequencia = 0;

// Variável para salvar a cor identificada
byte corIdentificada = 0;

// Podemos anexar um Servo para nos ajudar a alimentar as peças, se necessário
Servo servoAlimentacao;

// Potenciômetro para usar com o Servo, se necessário
byte controlePotServo = A0;

void setup() {
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configurando a escala de frequência para 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  // Anexando o Servo
  servoAlimentacao.attach(9);
}

void loop() {

  // Onde vamos salvar a leitura analógica
  int posicaoServoAlimentacao = analogRead(controlePotServo);

  // Mapeando a leitura analógica (0-1023) para converter em graus (0-180)
  int mapeadoServo = map(posicaoServoAlimentacao, 0, 1023, 0, 180);

  // Escrevendo os graus lidos no Servo
  servoAlimentacao.write(mapeadoServo);

  /****** Início da sequência para as cores ******
   * 
   */
  
  // --- Ler valores de VERMELHO ... S2 LOW - S3 LOW ---
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequencia = pulseIn(sensorOut, LOW);

  int valorVermelho = frequencia;

  Serial.print("R=");
  Serial.print(valorVermelho);
  Serial.print("  ");

  delay(50);

  // --- Ler valores de VERDE ... S2 LOW - S3 HIGH ---
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequencia = pulseIn(sensorOut, LOW);

  int valorVerde = frequencia;

  Serial.print("G=");
  Serial.print(valorVerde);
  Serial.print("  ");

  delay(50);

  // --- Ler valores de AZUL ... S2 HIGH - S3 LOW ---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  frequencia = pulseIn(sensorOut, LOW);

  int valorAzul = frequencia;

  Serial.print("B=");
  Serial.print(valorAzul);
  Serial.println("  ");

  delay(50);

  // --- Ler valores de CLARO ... S2 HIGH - S3 HIGH ---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequencia = pulseIn(sensorOut, LOW);

  int valorClaro = frequencia;

  Serial.print("C=");
  Serial.print(valorClaro);
  Serial.println("  ");

  delay(50);

} // Fim do loop

