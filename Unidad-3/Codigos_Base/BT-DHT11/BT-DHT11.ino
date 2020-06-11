/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización de una aplicación de appinventor y el sensor DHT
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Junio 2020
*/

#include "BluetoothSerial.h" //Librería bluetooth a utilizar
#include "DHT.h"

BluetoothSerial ESP_com; //Definimos nuestro objeto bluetooth 

int recibido;

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
  ESP_com.begin("Proyecto Balam - 2020"); //El nombre de nuestro dispositivo
  pinMode(DHTPin, INPUT);
  dht.begin();
}


String s_temperatura, s_humedad;
void loop() {
  temperatura = dht.readTemperature(); // Leemos los valores de temperatura
  humedad = dht.readHumidity(); // Obtenemos los valores de humedad 

 //Casteamos nuestras variables
  s_humedad = String((int)humedad);
  s_temperatura = String((int)temperatura);

  if (ESP_com.available()) //Revisamos si existe una conexión activa
  {
    ESP_com.println(s_temperatura + ","+ s_humedad);    
  }
  delay(350);
}
