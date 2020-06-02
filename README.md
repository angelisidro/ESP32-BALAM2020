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

# Unidades del curso

El Curso "Creando mi primera Aplicación IoT" esta divido en 5 Unidades las cuales están descritas a continuación:

## Unidad 1 (Electrónica)

En esta unidad se aprenderán conceptos básicos de electrónica y el funcionamiento de nuestros dispositivos, así mismo también se tocaran temas como lo son la presentación del Kit que estarán utilizado, el uso de hojas de datos para el correcto uso de los dispositivos y sus respectivas conexiones eléctricas.

![](/Img/kit.png)

## Unidad 2 (Programación)

En esta unidad se aprenderá sobre los fundamentos para programación a través del Arduino IDE. Encontrarás los códigos utilizados dentro de cada una de las subsecciones de la unidad, así como los diagramas de conexión de cada uno de los circuitos utilizados.

- [Más información en este Link][Unidad2]

[Unidad2]: https://github.com/angelisidro/ESP32-BALAM2020/tree/master/Unidad-2

## Unidad 3 (Servidor WEB y Bluetooth)


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
