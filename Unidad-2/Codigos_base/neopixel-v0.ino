/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización neopixel ring.
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

int r = 0;
int g = 0;
int b = 0;
int numeroLED = 7;

void setup ( void ) {
  Serial.begin (115200);
  delay(100);

  //Inicializamos los neopixels
  anilloLED.begin();  // Inicializar el anillo de LEDs
  anilloLED.setBrightness(intensidad);  //Definir la intensidad con la que brillarán
  anilloLED.clear();  // Asegurarse que limpiemos los colores en los LEDs estén
  anilloLED.show();   // Asegurarse que todos los LEDs estén 'Apagados'
  Serial.println("Iniciando....");
  
}

void loop ( void ) {
  //Corremos ejemplo
   Serial.println("Configurando un color para un pixel");
   //Primer color
   r=255;
   g=0;
   b=0;
   anilloLED.setPixelColor(numeroLED, r, g, b);
   anilloLED.show();
   delay(1000);

   //Segundo color
   r=0;
   g=255;
   b=0;
   anilloLED.setPixelColor(numeroLED, r, g, b);
   anilloLED.show();
   delay(1000);

   //Tercer color
   r=0;
   g=0;
   b=255;
   anilloLED.setPixelColor(numeroLED, r, g, b);
   anilloLED.show();
   delay(1000);

   anilloLED.clear(); //Borra el arreglo de LEDs
}
