/*
 * Proyecto Balam 2020 - Universidad Galileo - Grupo Intelecto
 * Desarrollando mi primera experiencia IoT 
 * 
 * Código base para utilización la matriz neopixel por medio de bluetooth y appinventor
 * Código desarrollado por: Tesla LAB
 * Rodrigo Canek - Junio 2020
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
 
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define PIN 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);


String valor;


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define cons ","

String s_rojo, s_verde, s_azul;
int r = 0;
int g = 0;
int b = 0;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      
      int aux = 0;
      s_rojo = ""; 
      s_verde = ""; 
      s_azul = "";
      
      if (value.length() > 0) {
        valor = "";
        for (int i = 0; i < value.length(); i++){
          
          valor = valor + value[i];

          //Si es coma lo leido, cambiamos a otra variable
          if(value[i]==','){
            aux++;
            continue;
          }
            
          if(aux == 0){
            s_rojo = s_rojo+value[i]; 
          }else if(aux == 1){
            s_verde = s_verde+value[i];
          }else{
            s_azul = s_azul+value[i];  
          }
        }
        
        //Transformamos a enteros
        r = s_rojo.toInt();
        g = s_verde.toInt();
        b = s_azul.toInt();       
        
        Serial.println(s_rojo);
        Serial.println(s_verde);
        Serial.println(s_azul);
        Serial.println("--------------");
        Serial.print("Mensaje recibido: ");
        Serial.println(valor); // Presenta valor.
      }
    }
};

//Configuraciones
void setup() {
  Serial.begin(115200);
  delay(10);
  
  BLEDevice::init("ESP32 - Proyecto BALAM");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE  |
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_INDICATE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Empezamos");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  
  Serial.println("Iniciamos");
}

//loop colocando el color que se coloquen en las variables
void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  setColor(r, g, b); 
}

//Función para colocar el color
void setColor(int r1, int g1, int b1){
  for (uint16_t i=0; i < pixels.numPixels(); i=i+1) {
    pixels.setPixelColor(i, r1,g1,b1);    //turn ever
  }
  pixels.show();
}
