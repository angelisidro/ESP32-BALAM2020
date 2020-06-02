/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización neopixel con ciclos.
 * Código desarrollado por: Tesla LAB
 * Oscar Rodas - Mayo 2020
*/

//Librerias a utilizar
#include <Adafruit_NeoPixel.h>

// Variables y constantes a utilizar para los neopixels
#define PIN 22
#define CANTIDAD 16
int intensidad = 50;

Adafruit_NeoPixel anilloLED = Adafruit_NeoPixel(CANTIDAD, PIN, NEO_GRB + NEO_KHZ800);

//Inicializo mis variables de colores de LEDs RGB
int r = 0;
int g = 0;
int b = 0;

void setup ( void ) {
  Serial.begin (115200);
  delay(100);

  //Inicializamos los neopixels
  anilloLED.begin();  // Inicializar el anillo de LEDs
  anilloLED.setBrightness(intensidad);  //Definir la intensidad con la que brillarán
  anilloLED.clear();  // Asegurarse que todos los LEDs estén 'Apagados'
  Serial.println("Iniciando....");
  
}

void loop ( void ) {
  //Definimos el color
  int r = random(20,100);
  int g = random(10,75);
  int b = random(30,150);
  
  //Corremos ejemplo
   for( int i = 0; i < CANTIDAD; i++ ){
       anilloLED.setPixelColor(i, r, g, b);
       Serial.println("Mostrando color");
       anilloLED.show();
       delay(250);
   }
   //Resetear mi anillo de LEDs
   anilloLED.clear();
   anilloLED.show();
   delay(50);
}
