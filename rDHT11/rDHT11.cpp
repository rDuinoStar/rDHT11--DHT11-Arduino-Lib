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
// v.0.1.- Álvaro Cid - Original Version (04/02/2013) - based on Ggeorge Hadjikyriacou,
//														Simkard and Rob Tillaart works.

#include "rDHT11.h"

rDHT11::rDHT11(int pin)
{
	init(pin);
}

void rDHT11::init(int pin)
{
	this->pin = pin;
	humidity = -1;
	temperature = -1;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	neverReaded = true;
}

int rDHT11::update()
{
	byte data[5];
	byte despl = 7;
	byte data_index = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) data[i] = 0;

	// REQUEST SAMPLE
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	// ACKNOWLEDGE or TIMEOUT
	unsigned long timeStart = millis();

	while(digitalRead(pin) == LOW)
	{
		if(millis()<timeStart)
		{
			timeStart = millis();
			continue;
		}
		else
		{
			if (millis() - timeStart > rDHT11Definitions::TIMEOUT) 
				return rDHT11Definitions::TIMEOUT_ERROR;
		}
	}

	timeStart = millis();

	while(digitalRead(pin) == HIGH)
	{
		if(millis()<timeStart)
		{
			timeStart = millis();
			continue;
		}
		else
		{
			if (millis() - timeStart > rDHT11Definitions::TIMEOUT) 
				return rDHT11Definitions::TIMEOUT_ERROR;
		}
	}

	for (int i=0; i<40; i++)
	{
		timeStart = millis();

		while(digitalRead(pin) == LOW)
		{
			if(millis()<timeStart)
			{
				timeStart = millis();
				continue;
			}
			else
			{
				if (millis() - timeStart > rDHT11Definitions::TIMEOUT) 
					return rDHT11Definitions::TIMEOUT_ERROR;
			}
		}

		unsigned long timeStart2 = micros();

		while(digitalRead(pin) == HIGH)
		{
			if(millis()<timeStart)
			{
				timeStart = millis();
				continue;
			}
			else
			{
				if (millis() - timeStart > rDHT11Definitions::TIMEOUT) 
					return rDHT11Definitions::TIMEOUT_ERROR;
			}
		}

		unsigned long timeEnd = micros();

		if(micros() < timeStart2)
		{
			timeEnd = 4294967295 - timeStart2 + timeEnd;
		}
		if ((timeEnd - timeStart2) > 35) 
			data[data_index] |= (1 << despl);

		if (despl == 0)   
		{
			despl = 7;
			data_index++;
		}
		else despl--;
	}

	humidity    = data[0]; 
	temperature = data[2]; 

	byte checksum = data[0] + data[2];  

	if (data[4] != checksum) 
		return rDHT11Definitions::CHECKSUM_ERROR;

	neverReaded = false;
	return rDHT11Definitions::OK;
}

int rDHT11::getCelsius()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return temperature;
}

int rDHT11::getHumidity()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return humidity;
}

float rDHT11::getFahrenheit()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return (float)temperature * (9/5) + 32;
}

float rDHT11::getKelvin()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return (float)temperature + 273.15;
}

float rDHT11::getRankine()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return ((float)temperature + 273.15) * (9/5);
}

float rDHT11::getNewton()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return (float)temperature * 33/100;
}

float rDHT11::getReaumur()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return (float)temperature * 4/5;
}

float rDHT11::getRomer()
{
	if(neverReaded)
		return rDHT11Definitions::NOT_READY_ERROR;
	return (float)temperature * 21/400 + 7.5;
}

// Common set of values originates from the 1974 Psychrometry and Psychrometric Charts, as presented by Paroscientific.
// http://www.paroscientific.com/dewpoint.htm
// Temp: 0° C < T < 60° C  
// Rel.Hum: 1% < RH < 100 %
// DewPoint: 0° C < Td < 50° C  +- 0.4ºC
float rDHT11::getDewPoint()
{
	float a = 17.27;
	float b = 237.7;
	float alpha = (a * (float)temperature)/(b + (float)temperature) + log((float)humidity/100);
	return (b * alpha)/(a - alpha);
}
// EOF