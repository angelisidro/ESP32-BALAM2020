/*
 *Programa No. 3 - Push Button Configuración Pull-up
 *Descripción: En este programa se realizará la interacción con el pin 3 como entrada a través
 *de la configuración pull-up del push button.
 *
 *Programa realizado por Oscar Rodas - 20 mayo 2020 - Versión 1 
 */
#define LED 2
#define pushButton 23

boolean estadoPushButton = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(pushButton, INPUT);

  //Asegurar LED se encuentre apagado
  digitalWrite(LED,LOW);
  delay(2000);

  //Configurar y arrancar Monitor Serial
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Leer estado de push button
  estadoPushButton = digitalRead(pushButton);
  Serial.print("El estado del Push Button es: ");
  Serial.println(estadoPushButton);

  // En base al estado del push button, el LED se enciende o no
  if (estadoPushButton == true){
    Serial.println("PB no presionado");
    digitalWrite(LED,LOW);    // Al no estar presionado el push button, no se enciende el LED
  } else {
    Serial.println("PB presionado");
    digitalWrite(LED,HIGH);   // Al estar presionado el push button, se enciende el LED
  }
  delay(1000);
}
