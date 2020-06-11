/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización de una aplicación de appinventor con bluetooth y el uso de una matriz neopixel y el sensor dht11
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Junio 2020
*/
#include "BluetoothSerial.h" //Librería a utilizar

BluetoothSerial ESP_com; //Definimos el objeto a utilizar
int mensaje_recibido;

// Neopixels
#include <Adafruit_NeoPixel.h>
#define PIN_neo 2
#define CANTIDAD 16
int brillo = 150;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(CANTIDAD, PIN_neo, NEO_RGB + NEO_KHZ800);



#include "DHT.h"

//Definimos el tipo de sensor a utilizar
#define DHTTYPE DHT11  
// Definimos el pin donde esta conectado el sensor
uint8_t DHTPin = 4; 
               
//Inicializamos el sensor y definimos variables globales.
DHT dht(DHTPin, DHTTYPE);                
float temperatura;
float humedad;

void setup() {
  Serial.begin(115200); 
  ESP_com.begin("Proyecto Balam - 2020"); //El nombre de nuestro dispositivo bluetooth

  //Inicializamos el sensor DHT
  pinMode(DHTPin, INPUT);
  dht.begin();

  //Inicializamos neopixels
  pixels.setBrightness(brillo);
  pixels.begin();
  pixels.show(); 

}


String aux, aux2;
void loop() {
  temperatura = dht.readTemperature(); // Leemos los valores de temperatura
  humedad = dht.readHumidity(); // Obtenemos los valores de humedad 
  aux = String((int)humedad);
  aux2 = String((int)temperatura);
  if (ESP_com.available()) //Check if we receive anything from Bluetooth
  {
    //Escriba aquí su código 
    mensaje_recibido = ESP_com.read();
    switch(mensaje_recibido){
      case 48: //recibir un 0 - Dar datos de temperatura y humedad
        ESP_com.println(aux2 + "," + aux);
      break;
      case 49: //recibir un 1 - Colocar color azul
        setColor(0,0,255);
      break;
      //Color rojo
      case 51: //recibir un 2 - Colocar color rojo
        setColor(255,0,0);
      break;
      //Color verde
      case 50: //recibir un 3 - Colocar color verde
        setColor(0,255,0);
      break;
      case 52: //recibir un 4 - Colocar color rainbowtheater
        theaterChaseRainbow(25);
      break;
      case 53: //recibir un 5 - Colocar color rainbowCycle
        rainbowCycle(25);
      break;
      case 54: //recibir un 6 - Colocar color blanco
        setColor(255,255,255);
      break;
      default:
        ESP_com.println(aux2 + "," + aux);
      break;
    }
  }
}





//Tomamos nuevamente ejemplos de la librería Adafruit Neopixel

void setColor(int r, int g, int b){
  for (uint16_t i=0; i < pixels.numPixels(); i=i+1) {
        pixels.setPixelColor(i, r,g,b);    //turn ever
        }
  pixels.show();
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
