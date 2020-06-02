/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización de un servidor web y el sensor DHT 11
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Mayo 2020
*/

//Servidor web
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "DHT.h"
#define DHTTYPE DHT11   //Definimos el tipo de sensor a utilizar



WebServer server(80); //Definimos el puerto que utilizara nuestro servidor

uint8_t DHTPin = 4; //definimos el pin para el sensor
               
DHT dht(DHTPin, DHTTYPE);  //Inicializamos el sensor               



//Variables
float temperatura;
float humedad;

const char* ssid = "Nombre";  // Colocamos nuestro SSID (Nombre de nuestro "wifi")
const char* password = "contraseña";  //Colocamos la contraseña de tu wifi

 
void setup() {
  Serial.begin(115200);
  delay(100);

  //Debemos inicializar el sensor


  //Debemos inicializar la conexión

  
  // Se debe esperar hasta lograr la conexión
  
  
  //Debemos inicializar el servidor web
  

}


void loop() {
  server.handleClient(); //Atender a los clientes 
}

//Que hace el servidor web al momento de que alguien se conecte
void handleConnect() {
  //COLOCAR SU CÓDIGO 
}


//Que hace el servidor si le solicitan algo que no tiene disponible
void handle_NotFound(){
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


//Creamos el código para nuestro servidor web
String Enviar_nuestro_HTML(float Temperaturaws,float Humedadws){
  String str = "<!DOCTYPE html> <html>\n";
  str +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  str +="<meta http-equiv=\"refresh\" content=\"5\">";
  str +="<title>Reporte del Clima</title>\n";
  str +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  str +="body{margin-top: 50px;} h1 {color: #9d73df;margin: 50px auto 30px;}\n";
  str +="</style>\n";
  str +="</head>\n";
  str +="<body>\n";
  str +="<div id=\"webpage\">\n";
  str +="<h1>Informe del clima</h1>\n";
  
  str +="<p style=\"color: #00aaff;font-size: 24px;margin-bottom: 10px;\">Temperatura: ";
  str +=(int)Temperaturaws;
  str +="  &deg C</p>\n";
  str +="<p style=\"color: #66ff99;font-size: 24px;margin-bottom: 10px;\">Humedad: ";
  str +=(int)Humedadws;
  str +=" %</p>";
  
  str +="</div>\n";
  str +="</body>\n";
  str +="</html>\n";
  return str;
}
