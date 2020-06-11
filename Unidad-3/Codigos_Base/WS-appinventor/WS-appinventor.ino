/*
   Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
   Desarrollando mi primera experiencia IoT

   Código base para utilización de un servidor web y el desarrollo de una aplicación de app inventor
   Código desarrollado por: Tesla LAB
   Rodrigo Canek - Mayo 2020
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
 
const char* ssid = "Nombre";  // Colocamos nuestro SSID (Nombre de nuestro "wifi")
const char* password = "Contraseña";  //Colocamos la contraseña de tu wifi

WiFiServer server(80);

//Definimos el pin y un 
#define PIN 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

 
void setup() {
  Serial.begin(115200); //Default Baud Rate for NodeMCU
  delay(10);


 // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  //Inicializamos la matriz de neopixels
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'

  
  // Se inicia la conexión al wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectado a la red: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  // Se inicializa el servidor
  server.begin();
  Serial.println("Servidor Web inicializado");
 
  //Desplegamos la IP
  Serial.println(WiFi.localIP());
}
 
void loop() {
  //Se revisa continuamente si se han conectado un cliente
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  //Esperamos hasta que el cliente envie información
  Serial.println("Nueva solicitud");
  while(!client.available()){
    delay(1);
  }
  
  //Revisamos la solicitud del cliente
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  //192.168.1.33/gpio/2
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else if (req.indexOf("/gpio/2") != -1)
    val = 2;
  else if (req.indexOf("/gpio/3") != -1)
    val = 3;
  else if (req.indexOf("/gpio/4") != -1)
    val = 4;
  else if (req.indexOf("/gpio/5") != -1)
    val = 5;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  //Texto a enviar
  String str = "HTTP/1.1 200 OK \nContent-Type: text/html\n \n<!DOCTYPE HTML>\r\n<html>\r\nSe ha colocado el ";
  
  //Según la solicitud, se realiza una animación en la matriz neopixel
  switch(val){
    case 0:
      theaterChase(pixels.Color(127, 127, 127), 50); // White
      str += "Color Blanco";
    break;
    case 1:
      theaterChase(pixels.Color(127, 0, 0), 50); // Red
      str += "Color Rojo";
    break;
    case 2:
      theaterChase(pixels.Color(0, 0, 127), 50); // Blue
      str += "Color Azul";
    break;
    case 3: 
      rainbowCycle(20);
      str += "Arcoiris lento";
    break;
    case 4: 
      theaterChaseRainbow(25);
      str += "Arcoiris rápido";
    break;
    case 5: 
      setColor(0, 0, 0);
      str += "Apagado";
    break;
  }
  str += "</html>";
  
  client.print(str);
}


//Tomamos efectos de los ejemplos que nos brinda la librería.

void setColor(int r, int g, int b){
  for (uint16_t i=0; i < pixels.numPixels(); i=i+1) {
        pixels.setPixelColor(i, r,g,b);    //turn ever
        }
  pixels.show();
}

// Slightly different, this makes the rainbow equally distributed throughout
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

//Theatre-style crawling lights.
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


//Theatre-style crawling lights with rainbow effect
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
