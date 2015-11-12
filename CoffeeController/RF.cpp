#include "RF.h"
#include <wiringPi.h>


int rfPin;

RF::RF(int GpioPin)
{
	rfPin = GpioPin;
	pinMode(rfPin, OUTPUT);
	digitalWrite(rfPin, LOW);
}

RF::~RF()
{
}

void RF::switchOn(){
	unsigned long onSignal = -1146093542;
	sendSignal(onSignal, rfPin);
	delay(250);
}

void RF::switchOff(){
	unsigned long offSignal = -1146093544;
	sendSignal(offSignal, rfPin);
	delay(250);
}

/**
* Format data:
* pppppppp|prrrdddd|dddddddd|dddddddd (32 bit)
* p = perioud (9 bit unsigned int
* r = repeats as 2log. Thus, if r = 3, then signal is sent 2^3=8 times
* d = data
*/
void RF::sendSignal(unsigned long signal, unsigned short rfPin) {
	unsigned int periodusec = (unsigned long)signal >> 23;
	unsigned short repeats = 5 << (((unsigned long)signal >> 20) & 7); // 7 = B111
	signal = signal & 0xfffff; //truncate to 20 bit

	//Convert the base3-code to base4, to avoid lengthy calculations when transmitting.. Messes op timings.
	unsigned long dataBase4 = 0;

	for (unsigned short i = 0; i<12; i++) {
		dataBase4 <<= 2;
		dataBase4 |= (signal % 3);
		signal /= 3;
	}

	for (unsigned short int j = 0; j<repeats; j++) {
		//Sent one telegram		

		//Use data-var as working var
		signal = dataBase4;

		for (unsigned short i = 0; i<12; i++) {
			switch (signal & 3) { // 3 = B11
			case 0:
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec * 3);
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec * 3);
				break;
			case 1:
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec * 3);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec);
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec * 3);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec);
				break;
			case 2: //AKA: X or float
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec * 3);
				digitalWrite(rfPin, HIGH);
				delayMicroseconds(periodusec * 3);
				digitalWrite(rfPin, LOW);
				delayMicroseconds(periodusec);
				break;
			}
			//Next trit
			signal >>= 2;
		}

		//Send termination/synchronisation-signal. Total length: 32 periods
		digitalWrite(rfPin, HIGH);
		delayMicroseconds(periodusec);
		digitalWrite(rfPin, LOW);
		delayMicroseconds(periodusec * 31);
	}
}

