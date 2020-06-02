/*Programa No. 1 - Hola Mundo - Proyecto Balam 2020
 * 
 * En este programa haremos que el LED del ESP32 se encienda por 1 seg y se apague por 1 seg
 * de manera indefinida.
 * 
 * Autor: Oscar Rodas - Tesla Lab - UGAL
 * Mayo 2020
 */

//Variables
#define LED 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);   //Configurand el pin 2 como salida.
}

void loop() {
  // put your main code here, to run repeatedly:
  // Colocaré mi código para encender el LED por 1 seg
  digitalWrite(LED, HIGH);
  delay(1000);
  // Colocaré mi código para apagar el LED por 1 seg
  digitalWrite(LED, LOW);
  delay(1000);
}
