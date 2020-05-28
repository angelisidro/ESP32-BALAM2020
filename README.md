# Bienvenidos 
Este repositorio contiene información que puede ser utilizada en el curso de IoT (Internet Of Things) realizado por Tesla Lab de Universidad Galileo, para Proyecto Balam.

# Instalación

Para la instalación en Arduino IDE debemos seguir los siguientes pasos:

1. Abrir ARDUINO IDE
2. Debemos ir a la pestaña ***Archivo***->***Preferencias***.
	- En la pestaña ***Ajustes*** buscamos la opción: ***Gestor de URLs Adicionales de Tarjetas: ***
	- Pegamos la siguiente URL: `https://dl.espressif.com/dl/package_esp32_index.json`
	- Luego precionamos la opción ***OK*** y automaticamente se cerrara la ventana.
3. Debemos ir a la pestaña ***Herramientas***->***Placa***->***Gestor de tarjetas***.
	- Colocamos en la barra de busqueda ***ESP32***.
	- Seleccionamos la opción que nos muestre ***esp32***.
	- Instalamos y luego precionamos la opción de ***Cerrar***.

Con esto tendremos completa la instalación de nuestra tarjeta ESP32 y lista para ser programada.	 

# Instalación USB Driver ***(Si no reconoce el puerto COM)***

En algunos casos nuestra PC no es capaz de reconocer el dispositivo USB que nosotros conectamos, es por ello que dejaremos un archivo para la instalación del driver con ello nuestra PC deberá ser capaz de reconocer el dispositivo conectado, en caso de que el problema persista asegúrese de que su dispositivo no se este sobre calentando.

[Descarga este driver para Windows][DRIVER_USB]

[DRIVER_USB]: https://drive.google.com/file/d/1yuZ91mJfR12bhASqD9ffsebzsEOJz8Om/view?usp=sharing

1. Descomprimir el archivo ZIP descargado 
2. Seleccionar el archivo dependiendo de nuestra instalación de Windows
	- Para 32 Bits `CP210xVCPInstaller_x86`
	- Para 64 Bits `CP210xVCPInstaller_x64`
3. Brindar permisos de Administrador	
4. Click en la opción ***Siguiente***
5. Click en la opción ***Finalizar***

Con esto estaría lista la instalación del Driver USB para nuestra tarjeta en el Sistema Operativo Windows.
# PinOut
![](/Img/PINOUT_ESP32.png)

# DHT11

Estos son los pines que estaremos utilizando en los vídeos a lo largo del curso, pero ustedes son libres de utilizar los pines que prefieran. Muy importante es que revisen si el pin que quiere utilizar es compatible con el dispositivo que van a conectar.

En los siguiente links encontraremos códigos base para distintas implementaciones del sensor DHT11.

- [DHT11 en Web Server][CODIGO_DHT11]

[CODIGO_DHT11]: https://github.com/angelisidro/ESP32-BALAM2020/tree/master/Codigos_Base/WS-DHT11

Nombre | GPIO PIN
--- | ---
DATA | D4

![](/Img/dht11.png)

# NEOPIXEL

Estos son los pines que estaremos utilizando en los vídeos a lo largo del curso, pero ustedes son libres de utilizar los pines que prefieran. Muy importante es que revisen si el pin que quiere utilizar es compatible con el dispositivo que van a conectar.

En los siguiente links encontraremos códigos base para distintas implementaciones del dispositivo NeoPixel.

- [NeoPixel en Web Server][CODIGO_NeoPixel]

[CODIGO_NeoPixel]: https://github.com/angelisidro/ESP32-BALAM2020/tree/master/Codigos_Base/WS-Neopixels

Nombre | GPIO PIN
--- | ---
DATA | D2

![](/Img/neo_pixel.png)

# PUSH BUTTON

Estos son los pines que estaremos utilizando en los vídeos a lo largo del curso, pero ustedes son libres de utilizar los pines que prefieran. Muy importante es que revisen si el pin que quiere utilizar es compatible con el dispositivo que van a conectar.

En los siguiente links encontraremos códigos base para distintas implementaciones del dispositivo Push Button.

- [Push Button en Web Server][CODIGO_PushButton]

[CODIGO_PushButton]: https://github.com/angelisidro/ESP32-BALAM2020/tree/master/Codigos_Base/WS-pushbuttons

Nombre | GPIO PIN
--- | ---
DATA | D19
DATA | D13

![](/Img/push_button.png)

# Mapeo de Pines

### ESP32 - Touch Sensor
Touch | GPIO | *** | Touch | GPIO
--- | --- | --- | --- | ---
T0 | GPIO4 | | T5 | GPIO12 
T1 | GPIO0 | | T6 | GPIO14
T2 | GPIO2 | | T7 | GPIO27
T3 | GPIO15| | T8 | GPIO33
T4 | GPIO13| | T9 | GPIO32

# Protocolos de comunicación
## Protocolo I2C
Nombre | GPIO
--- | ---
SDA | GPIO21
SCL | GPIO22

## Protocolo SPI
Nombre | GPIO | *** | Nombre | GPIO
--- | --- | --- | --- | ---
MOSI | GPIO23 | | CLK | GPIO18
MISO | GPIO19 | | CS | GPIO5
