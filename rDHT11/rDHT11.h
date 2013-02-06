// 
// ARCHIVO: rDHT11.h
// VERSIÓN: 0.1
// PROPÓSITO: Librería para el sensor de temperatura y humedad DHT11 con Arduino.
// LICENCIA: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
//			(http://creativecommons.org/licenses/by-nc-sa/3.0/)
//
// DATASHEET (ACCESO A): http://rduinostar.com/documentacion/datasheets/dht11-overview/
//
// URL: http://arduino.cc/playground/Main/DHT11Lib
//
// CHANGELOG:
// v.0.1.- Álvaro Cid - Original Version (04/02/2013)

#ifndef rDHT11_H__
#define rDHT11_H__

#include <include/rDHT11Definitions.h>

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class rDHT11
{
public:
	rDHT11(int pin);
    void init(int pin);
	int update();
	int getCelsius();
	float getFahrenheit();
	float getKelvin();
	float getRankine();
	float getNewton();
	float getReaumur();
	float getRomer();
	float getDewPoint();
	int getHumidity();

private:
	int pin;
	int humidity;
	int temperature;
	bool neverReaded;
};
#endif // rDHT11_H__