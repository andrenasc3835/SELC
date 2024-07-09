#include <Servo.h>

// Define os pinos do sensor de cor
#define s0 2 // Pino S0 do sensor no pino Arduino #2
#define s1 3 // Pino S1 do sensor no pino Arduino #3
#define s2 4 // Pino S2 do sensor no pino Arduino #4
#define s3 5 // Pino S3 do sensor no pino Arduino #5
#define sensorOut 6 // Pino de saída do sensor no pino Arduino #6

// Variável para salvar os dados provenientes de sensorOut
int frequencia = 0;

// Variável para salvar a cor identificada
byte corIdentificada = 0;

// Declarando Servos
Servo servoAlimentacao;
Servo servoDecisao;

// Declarando atrasos gerais
byte pequenoAtraso_ms = 5;
byte medioAtraso_ms = 30;
byte grandeAtraso_ms = 1000;
byte muitoGrandeAtraso_ms = 2000;

// Declaração das posições do servo de alimentação
byte pos1ServoAlimentacao = 165;
byte pos2ServoAlimentacao = 92;
byte pos3ServoAlimentacao = 12;

// Declaração das posições do servo de decisão
byte servoDecisao_VERMELHO = 14;
byte servoDecisao_LARANJA = 53;
byte servoDecisao_VERDE = 85;
byte servoDecisao_AMARELO = 115;
byte servoDecisao_ROXO = 165;

void setup() {

  // Configura os pinos do sensor de cor
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT);

  /* Os pinos S0 e S1 definem a escala de frequência:
      L - L = Desligado
      L - H = 2%
      H - L = 20%
      H - H = 100%
  */
  // Usando 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  // Anexando os Servos
  servoAlimentacao.attach(9);
  servoDecisao.attach(11);

  // Inicia a comunicação serial com 9600 bits por segundo
  Serial.begin(9600);

}// Fim da função setup

void loop() {

  // Move o servo "passos" de 1 grau até pos2 (posição do sensor)
  for (int i = pos1ServoAlimentacao; i > pos2ServoAlimentacao; i--) {

    servoAlimentacao.write(i);
    delay(medioAtraso_ms);

  }// Fim do loop for

  // Atraso para estabilizar as leituras
  delay(grandeAtraso_ms);

  // Chama a função getTheColor
  corIdentificada = getTheColor();

  // Switch Case para decidir qual cor foi identificada
  switch (corIdentificada) {

    // Caso para Vermelho
    case 1:
      servoDecisao.write(servoDecisao_VERMELHO);
      break;

    // Caso para Laranja
    case 2:
      servoDecisao.write(servoDecisao_LARANJA);
      break;

    // Caso para Verde
    case 3:
      servoDecisao.write(servoDecisao_VERDE);
      break;

    // Caso para Amarelo
    case 4:
      servoDecisao.write(servoDecisao_AMARELO);
      break;

    // Caso para Roxo
    case 5:
      servoDecisao.write(servoDecisao_ROXO);
      break;

  }// Fim do switch case

  // Atraso para sair da posição
  delay(grandeAtraso_ms);

  // Move o servo de alimentação para a posição de saída
  for (int i = pos2ServoAlimentacao; i > pos3ServoAlimentacao; i--) {

    servoAlimentacao.write(i);
    delay(medioAtraso_ms);

  }// Fim do loop for - Servo para posição de saída

  // Atraso para retornar o servo
  delay(grandeAtraso_ms);

  // Retorna o servo de alimentação para a posição inicial
  for (int i = pos3ServoAlimentacao; i < pos1ServoAlimentacao; i++) {

    servoAlimentacao.write(i);
    delay(pequenoAtraso_ms);
  }// Fim do loop for - Servo posição inicial

  // Retorna o valor para 0
  corIdentificada = 0;

  // Atraso para iniciar novamente
  delay(muitoGrandeAtraso_ms);

}// Fim da função loop

/*-----Função Definida pelo Usuário-----
   Definição da Função:
   getTheColor

   Propósito:
   Aplicar os filtros nos fotodiodos para obter os valores R, G e B

   Valor de retorno:
   color      A combinação dos valores R, G, B e C para decidir a cor.

   ****Importante****
   É recomendado executar o programa sozinho
   Com um documento do Excel e o monitor serial aberto
   Verifique as leituras para encontrar os valores para cada cor e altere esses valores abaixo
*/

int getTheColor() {

  // --- Leitura dos valores VERMELHOS ... S2 LOW - S3 LOW ---
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequencia = pulseIn(sensorOut, LOW);

  int valorVermelho = frequencia;

  Serial.print("R=");
  Serial.print(valorVermelho);
  Serial.print("  ");

  delay(50);

  // --- Leitura dos valores VERDES ... S2 LOW - S3 HIGH ---
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequencia = pulseIn(sensorOut, LOW);

  int valorVerde = frequencia;

  Serial.print("G=");
  Serial.print(valorVerde);
  Serial.print("  ");

  delay(50);

  // --- Leitura dos valores AZUIS ... S2 HIGH - S3 LOW ---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  frequencia = pulseIn(sensorOut, LOW);

  int valorAzul = frequencia;

  Serial.print("B=");
  Serial.print(valorAzul);
  Serial.print("  ");

  delay(50);

  // --- Leitura dos valores CLAROS ... S2 HIGH - S3 HIGH ---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequencia = pulseIn(sensorOut, LOW);

  int valorClaro = frequencia;

  Serial.print("C=");
  Serial.print(valorClaro);
  Serial.println("  ");

  delay(50);

  ////////// Parâmetros para Vermelho //////////
  if (valorVermelho < 38 && valorVermelho > 14 && valorClaro < 58 && valorClaro >= 45) {
    corIdentificada = 1; // Vermelho
  }

  ////////// Parâmetros para Laranja //////////
  if (valorVermelho < 27 && valorVermelho > 10 && valorClaro < 45 && valorClaro >= 35) {
    corIdentificada = 2; // Laranja
  }

  ////////// Parâmetros para Verde //////////
  if (valorAzul < 15 && valorAzul > 4 && valorClaro < 35 && valorClaro > 20) {
    corIdentificada = 3; // Verde
  }

  ////////// Parâmetros para Amarelo //////////
  if (valorVermelho < 20 && valorVermelho > 8 && valorClaro < 24 && valorClaro > 10) {
    corIdentificada = 4; // Amarelo
  }

  ////////// Parâmetros para Roxo //////////
  if (valorVermelho < 49 && valorVermelho > 39 && valorClaro < 65 && valorClaro > 50) {
    corIdentificada = 5; // Roxo
  }

  // --- Retorna o valor encontrado ---
  return corIdentificada;

}// Fim da função getTheColor
