/*
**************************************************
*********---TEST de la librería rDHT11---*********
**************************************************
*-Sensor Digital de Temperatura y Humedad DHT11-**
**************************************************
**  Uso público citando el autor o procedencia, **
**  bajo licencia: Attribution-NonCommercial-   **
**  ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)   **
**                                              **
**  Éste y más ejemplos en rDuinoStar.com, tu   **
**  comunidad Arduino en Español                **
**************************************************
*/

#include <rDHT11.h>

// Establecemos el pin digital al que conectamos la línea de datos 
// del sensor
int rDHT11pin = 52;
// Declaramos una variable que será la utilizada para 
rDHT11 DHT11(rDHT11pin);

void setup()
{
  // Establecemos la velocidad para transmitir datos en serie a
  // 115200 baudios
  Serial.begin(115200);
  Serial.println("rDHT11 TEST-EXAMPLE PROGRAM");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(rDHT11Definitions::VERSION);
  Serial.println("---------------");
}

void loop()
{
  Serial.print("\nRetrieving information from sensor: ");
  // Tomamos una muestra del sensor
  int result = DHT11.update();
  // Comprobamos si la lectura ha sido exitosa
  switch (result)
  {
    case rDHT11Definitions::OK: 
		Serial.println("OK"); 
                // Mostramos los valores recogidos
                Serial.print("Humidity (%): ");
                Serial.println((float)DHT11.getHumidity(), 2);
                Serial.print("Temperature (oC): ");
                Serial.println((float)DHT11.getCelsius(), 2);
                Serial.print("Dew Point (oC): ");
                Serial.println(DHT11.getDewPoint());
		break;
    case rDHT11Definitions::CHECKSUM_ERROR: 
		Serial.println("Checksum error"); 
		break;
    case rDHT11Definitions::TIMEOUT_ERROR: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
  }
  
  // Necesitamos esperar dos segundos entre dos peticiones de datos
  // consecutivas
  delay(2000);
}
