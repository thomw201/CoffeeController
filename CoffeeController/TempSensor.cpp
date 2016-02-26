#include "TempSensor.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int dht11_dat[5] = { 0, 0, 0, 0, 0 };
#define MAXTIMINGS	85

TempSensor::TempSensor(int tempsensorPin)
{
	tsPin = tempsensorPin;
}


TempSensor::~TempSensor()
{
}

int TempSensor::getTemp()
{
	return currentTemperature;
}

void TempSensor::read_dht11_dat()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	/* pull pin down for 18 milliseconds */
	pinMode(tsPin, OUTPUT);
	digitalWrite(tsPin, LOW);
	delay(18);
	/* then pull it up for 40 microseconds */
	digitalWrite(tsPin, HIGH);
	delayMicroseconds(40);
	/* prepare to read the pin */
	pinMode(tsPin, INPUT);

	/* detect change and read data */
	for (i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(tsPin) == laststate)
		{
			counter++;
			delayMicroseconds(1);
			if (counter == 255)
			{
				break;
			}
		}
		laststate = digitalRead(tsPin);

		if (counter == 255)
			break;

		/* ignore first 3 transitions */
		if ((i >= 4) && (i % 2 == 0))
		{
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if (counter > 16)
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}

	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ((j >= 40) &&
	     (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
	{
		//printf( "Humidity = %d.%d %% Temperature = %d.%d *C \n",
			//dht11_dat[0],
			//dht11_dat[1],
			//dht11_dat[2],
			//dht11_dat[3]);
		currentTemperature = dht11_dat[2];
	}
	else {
		//printf("Data not good, skip\n");
	}
}
