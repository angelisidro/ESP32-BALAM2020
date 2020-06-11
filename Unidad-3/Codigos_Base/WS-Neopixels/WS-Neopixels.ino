/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización de un servidor web y la matriz neopixel
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Mayo 2020
*/

//Librerias a utilizar
#include <Adafruit_NeoPixel.h>

//Servidor web
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>


WebServer server(80); //Definimos el puerto que utilizara nuestro servidor

// Credenciales de nuestra red wifi
const char* ssid = "Nombre";  // Colocamos nuestro SSID (Nombre de nuestro "wifi")
const char* password = "Contraseña";  //Colocamos la contraseña de tu wifi


// Variables y constantes a utilizar para los neopixels
#define PIN 2
#define CANTIDAD 16
int brightness = 150;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(CANTIDAD, PIN, NEO_RGB + NEO_KHZ800);



void setup ( void ) {
  Serial.begin ( 115200 );
  delay(100);

  //Inicializamos los neopixels
 
  //Se inicia la conexión a la red wifi
  

  // Se espera hasta lograr la conexión
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println ( "" );
  Serial.print ( "Se ha conectado a: " );
  Serial.println ( ssid );
  Serial.print ( "El servidor tiene la IP: " );
  Serial.println ( WiFi.localIP() );

  //Debemos inicializar el servidor web
  
}

void loop ( void ) {
  // Se esperan solicitudes de usuarios
  server.handleClient();
}

//Que hace el servidor web al momento de que alguien se conecte
void handleConnect() {
  //COLOCAR SU CÓDIGO 
  
}

//Que hace el servidor si le solicitan algo que no tiene disponible
void handle_NotFound() {
  String message = "No se encuentra la página\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  server.send ( 404, "text/plain", message );
}


//Función para colocar el color seleccionado
void colorNeopixel(String color){
  // Se convierte la cadena a un entero
  int number = (int) strtol( &color[1], NULL, 16);

  // Se obtiene el color para cada parte del RGB
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  //Se le coloca el color a cada pixel
  for(int x=0; x < CANTIDAD; x++) {
    pixels.setPixelColor(x, pixels.Color( g, r, b ) );
  }
  pixels.show();
}

//Generamos el código necesario para crear la página web.
String Generar_nuestro_HTML(){
  String str = "<!DOCTYPE html> <html>\n";
  str +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  //str +="<meta http-equiv=\"refresh\" content=\"5\">"; //importante tiempo para refrescar el servidor
  str +="<title>Control de neopixels</title>\n";
  str +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  str +="body{margin-top: 50px;} h1 {color: #57fd3a; margin: 50px auto 30px;}\n";
  str +="</style>\n";
  str +="</head>\n";
  str +="<body>\n";
  str +="<div id=\"webpage\">\n";
  str +="<h1>Control de neopixel</h1>\n";
  str +="<form action=\"\" name=\"pick\" method=\"post\">\n";
  str +="<input type=\"color\" name=\"c\" value=\"%02d\" onchange=\"document.forms['pick'].submit();\" />\n";
  str +="&nbsp;<span onclick=\"document.forms['pick'].submit();\" style=\"font-size:16pt;\"> Color a elegir </span>\n";
  str +="</form>\n";
  str +="\n</body>\n";
  str +="</html>\n";
  return str;
}
