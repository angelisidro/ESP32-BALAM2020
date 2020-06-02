/*
 *Programa Temp y Hum # 1 - Toma de temperatura y humedad desde DHT11 
 *Descripción: En este programa usaremos el sensor DHT11 para tomar mediciones de temperatura y humedad cada 3 segundos.
 *El resultado será mostrado en el Monitor Serial.
 *
 *Programa realizado por Oscar Rodas - 20 mayo 2020 - Versión 1 
 */
//Cargamos nuestra librerías
#include <DHT.h>

//Definimos el tipo de sensor a utilizar
//Definimos el pin
#define DHTPIN 4    //definimos el pin para el sensor
//uint8_t DHTPIN = 4; //definimos el pin para el sensor          

//Definimos el sensor
#define DHTTYPE DHT11

DHT sensorDHT11(DHTPIN, DHTTYPE);  //Inicializamos el sensor   

//Variables
float temperatura=0;
float humedad=0;
float sensacionTermica=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(DHTPIN, INPUT);

  //Configurar y arrancar Monitor Serial
  Serial.begin(115200);

  Serial.println("Inicializando el sensor DHT11.");
  sensorDHT11.begin();
  Serial.println("Programa iniciando para toma de datos del ambiente.");
  
}

void loop() {
  // Aquí nuestro código que corre de manera continua:

  Serial.println("Tomando lectura de los datos del ambiente.");
  //Tomando datos
  temperatura = sensorDHT11.readTemperature();
  humedad = sensorDHT11.readHumidity();
  sensacionTermica = sensorDHT11.computeHeatIndex(temperatura, humedad, false);
  
  //Imprimiendo datos al monitor serial
  Serial.print("La temperatura en el ambiente es: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.print("La humedad en el ambiente es: ");
  Serial.print(humedad);
  Serial.println("%");
  Serial.print("La sensación térmica es de: ");
  Serial.print(sensacionTermica);
  Serial.println("°C");
  Serial.println("------------------------");
  Serial.println();
  delay(3000);
}
