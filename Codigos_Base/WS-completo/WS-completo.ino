/*
   Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
   Desarrollando mi primera experiencia IoT

   Código base para utilización de un servidor web junto con el sensor DHT11, la matriz Neopixel y un push button
   Código desarrollado por: Tesla LAB
   Rodrigo Canek - Mayo 2020
*/



//Incluir todas las librerias

//Servidor web


//Sensor DHT11

//Neopixels



//Definir todas las variables
const char* ssid = "Nombre";  // Colocamos nuestro SSID (Nombre de nuestro "wifi")
const char* password = "contraseña";  //Colocamos la contraseña de tu wifi


WebServer server ( 80 );

uint8_t DHTPin = 4;
#define DHTTYPE DHT11


// Neopixels
#define PIN_neo 2
#define CANTIDAD 16
int brillo = 150;
int color_anterior = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(CANTIDAD, PIN_neo, NEO_RGB + NEO_KHZ800);


//Definimos las variables para el sensor
DHT dht(DHTPin, DHTTYPE);
float temperatura;
float humedad;


//D
int contador_de_pulsos = 0;   // counter for the number of button presses
int estado_boton = 0;         // current state of the button
int ultimo_estado = 0;
#define PIN_btn 19



void setup ( void ) {
  Serial.begin ( 115200 );
  delay(100);

  //Inicializamos el pin del push
  
  Serial.println("Inicializado el boton");
  
  //Inicializamos pin del sensor y al sensor

  Serial.println("Inicializado el sensor");
  
  //Inicializamos neopixels

  delay(75);
  Serial.println("Inicializados los pixels");

  //Se inicia la conexión a la red wifi
  Serial.println("Se esta intentando conectar a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password );
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

  Serial.println ( "El servidor se ha inicializado" );
}

void loop ( void ) {
  // Se esperan solicitudes de usuarios
  server.handleClient();

  //Leemos el estado actual del push
  estado_boton = digitalRead(PIN_btn);
  // Se compara si el estado actual es el mismo que el anterior, registrado
  if (estado_boton != ultimo_estado) {
    // si se dio un cambio, es posible que se sume al contador
    if (estado_boton == HIGH) {
      // Si el cambio de estado ALTO a BAJO, sumamos
      contador_de_pulsos++;
      Serial.print("Pulsos: ");
      Serial.println(contador_de_pulsos);
    }
    // Una pequeña espera para evitar duplicados
    delay(50);
  }
  // Guardamos el ultimo estado que se presento
  ultimo_estado = estado_boton;
}


void handleConnect(){

  // Se recibe el color desde el servidor
  
  // Definimos todos los leds a ese color
  colorNeopixel(color);

  //Leer valores del sensor
  
  // Generando nuestro codigo HTML
  
  //Enviar actualizar página web
  
}

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



void colorNeopixel(String color) {
  // Se convierte la cadena a un entero
  int number = (int) strtol( &color[1], NULL, 16);
  if (number != 0) {
    // Se obtiene el color para cada parte del RGB
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;

    //Se le coloca el color a cada pixel
    for (int x = 0; x < CANTIDAD; x++) {
      pixels.setPixelColor(x, pixels.Color( g, r, b ) );
    }
    pixels.show();

  }
}

//Generamos el código necesario para crear la página web.
String Generar_nuestro_HTML(int pulsos, int Temperaturaws, int Humedadws) {
  String str = "<!DOCTYPE html> <html>\n";
  str += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  str += "<meta http-equiv=\"refresh\" content=\"7\">"; //importante tiempo para refrescar el servidor
  str += "<title>Control de Servidor Web</title>\n";
  str += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  str += "body{margin-top: 50px;} h1 {color: #09209e; margin: 50px auto 30px;}\n";
  str += "</style>\n";
  str += "</head>\n";
  str += "<body>\n";
  str += "<div id=\"webpage\">\n";
  str += "<h1>Proyecto Balam</h1>\n";
  str += "<p style=\"color: #00aaff;font-size: 24px;margin-bottom: 10px;\">Temperatura: ";
  str += (int)Temperaturaws;
  str += "  &deg C</p>\n";
  str += "<p style=\"color: #27099e;font-size: 24px;margin-bottom: 10px;\">Humedad: ";
  str += (int)Humedadws;
  str += " %</p>\n\n\n";
  str += "<p style=\"color: #16d6e0;font-size: 24px;margin-bottom: 10px;\">Veces que se ha pulsado el boton: ";
  str += (int)pulsos;
  str += " </p>\n\n\n";
  str += "<form action=\"\" name=\"pick\" method=\"post\">\n";
  str += "<input type=\"color\" name=\"c\" value=\"%02d\" onchange=\"document.forms['pick'].submit();\" />\n";
  str += "&nbsp;<span onclick=\"document.forms['pick'].submit();\" style=\"font-size:16pt;\"> Color a elegir </span>\n";
  str += "</form>\n";
  str += "\n</body>\n";
  str += "</html>\n";
  return str;
}
