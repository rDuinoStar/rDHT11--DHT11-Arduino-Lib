//
// ARCHIVO: rDHT11Definitions.h
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

#ifndef RDHT11DEFINITIONS_H__
#define RDHT11DEFINITIONS_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

namespace rDHT11Definitions
{
	enum Results{OK=0, CHECKSUM_ERROR=-1001, TIMEOUT_ERROR=-1002, NOT_READY_ERROR=-1003};
	const char VERSION[4] = "0.1";
	const byte TIMEOUT = 100; //In milliseconds
};
#endif //RDHT11DEFINITIONS_H__