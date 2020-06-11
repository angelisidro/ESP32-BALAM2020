/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización de un servidor web y los push buttons
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Mayo 2020
*/


//Servidor Web
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server(80);//Definimos el puerto que utilizara nuestro servidor


// Credenciales de nuestra red wifi
const char* ssid = "CLARO_f3292e";  // Colocamos nuestro SSID (Nombre de nuestro "wifi")
const char* password = "B9BaBa0C6B";  //Colocamos la contraseña de tu wifi


//Variables para el push 1 
int contador_de_pulsos1 = 0;   //Estado anterior del boton
int estado_boton1 = 0;         //Estado actual del boton
int ultimo_estado1 = 0;
#define PIN_btn1 19

//Variables para el push 2 
int contador_de_pulsos2 = 0;   //Estado anterior del boton
int estado_boton2 = 0;         //Estado actual del boton
int ultimo_estado2 = 0;
#define PIN_btn2 13


void setup ( void ) {
  Serial.begin ( 115200 );
  delay(100);

  //Inicializamos los pines de los botones
  pinMode(PIN_btn1, INPUT);
  pinMode(PIN_btn2, INPUT);

  //Se inicia la conexión a la red wifi
  Serial.println("Se esta intentando conectar a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.println();

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
  server.on("/", handleConnect);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop ( void ) {
  // Se esperan solicitudes de usuarios
  server.handleClient();

  //Leemos el estado actual del push
  estado_boton1 = digitalRead(PIN_btn1);
  estado_boton2 = digitalRead(PIN_btn2);
  
  // Se compara si el estado actual es el mismo que el anterior, registrado
  if(estado_boton1 != ultimo_estado1){
  // Si se dio un cambio, es posible que se sume al contador
    if(estado_boton1 == HIGH){  
  // Si el cambio de estado ALTO a BAJO, sumamos
     contador_de_pulsos1++;
     Serial.print("Se ha sumado al contador, el total es");
     Serial.println(contador_de_pulsos1); 
  // Una pequeña espera para evitar duplicados

  // Guardamos el ultimo estado que se presento
    }
    delay(50);
  }

  //BOTON 2
  // Se compara si el estado actual es el mismo que el anterior, registrado
  if(estado_boton2 != ultimo_estado2){
  // Si se dio un cambio, es posible que se sume al contador
    if(estado_boton2 == HIGH){  
  // Si el cambio de estado ALTO a BAJO, sumamos
     contador_de_pulsos2++;
     Serial.print("Se ha sumado al contador, el total es");
     Serial.println(contador_de_pulsos2); 
  // Una pequeña espera para evitar duplicados

  // Guardamos el ultimo estado que se presento
    }
    delay(50);
  }

  ultimo_estado1 = estado_boton1;
  ultimo_estado2 = estado_boton2;
  
}

//Que hace el servidor web al momento de que alguien se conecte
void handleConnect() {
  String str;
  str = Generar_nuestro_HTML(contador_de_pulsos1, contador_de_pulsos2);
  server.send(200, "text/html", str);
}

void handleNotFound() {
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

//Generamos el código necesario para crear la página web.
String Generar_nuestro_HTML(int pulsos1, int pulsos2){
  String str = "<!DOCTYPE html> <html>\n";
  str +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  str +="<meta http-equiv=\"refresh\" content=\"5\">"; //importante tiempo para refrescar el servidor
  str +="<title>Control de Servidor Web</title>\n";
  str +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  str +="body{margin-top: 50px;} h1 {color: #09209e; margin: 50px auto 30px;}\n";
  str +="</style>\n";
  str +="</head>\n";
  str +="<body>\n";
  str +="<div id=\"webpage\">\n";
  str +="<h1>Proyecto Balam</h1>\n";
  str +="<p style=\"color: #16d6e0;font-size: 24px;margin-bottom: 10px;\">Veces que se ha pulsado el boton 1: ";
  str +=(int)pulsos1;
  str +=" </p>\n\n\n";
  str +="<p style=\"color: #16d6e0;font-size: 24px;margin-bottom: 10px;\">Veces que se ha pulsado el boton 2: ";
  str +=(int)pulsos2;
  str +=" </p>\n\n\n";
  str +="\n</body>\n";
  str +="</html>\n";
  return str;
}
