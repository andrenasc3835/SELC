/* Um programa para calibrar os Servos de alimentação e decisão
 * para o SELC
 *  
 * Vamos usar 2 Potenciômetros de 2k Ohms (ou outros) 
 * para ler a entrada analógica e escrever nos Servos.
 */

#include <Servo.h>

// Declarando nossos Servos
Servo servoAlimentacao;
Servo servoDecisao;

// Declarando nossos Potenciômetros
byte controlePotAlimentacao = A0;
byte controlePotDecisao = A2;

void setup() {

  // Anexando os Servos
  servoAlimentacao.attach(9);
  servoDecisao.attach(11);

  // Configurando pinMode para nossos Potenciômetros
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);

  // Iniciando a comunicação Serial
  Serial.begin(9600);

}

void loop() {

  // Onde vamos salvar a leitura analógica
  int posicaoServoAlimentacao = analogRead(controlePotAlimentacao);
  int posicaoServoDecisao = analogRead(controlePotDecisao);

  // Mapeando a leitura analógica (0-1023) para converter em graus (0-180)
  int mapeadoAlimentacao = map(posicaoServoAlimentacao, 0, 1023, 0, 180);
  int mapeadoDecisao = map(posicaoServoDecisao, 0, 1023, 0, 180);

  // Escrevendo os graus lidos nos Servos
  servoAlimentacao.write(mapeadoAlimentacao);
  servoDecisao.write(mapeadoDecisao);

  // Imprimindo a posição atual para saber quais valores usar em seguida
  Serial.print("O servo de alimentação está na posição = ");
  Serial.println(mapeadoAlimentacao);

  Serial.print("O servo de decisão está na posição = ");
  Serial.println(mapeadoDecisao);
  Serial.println("");

  delay(200);

}

