/*
* Sketch generated by duck2spark from Marcus Mengs aka MaMe82
*
*/
#include "DigiKeyboard.h"

#define DUCK_LEN 22
const PROGMEM uint8_t duckraw [DUCK_LEN] = {
	0xb, 0x0, 0x8, 0x0, 0xf, 0x0, 0xf, 0x0, 0x12, 0x0, 0x2c, 0x0, 0x1a, 0x0, 0x12, 0x0, 0x15, 0x0, 0xf, 0x0, 0x7, 0x0
};
int i = 1; //how many times the payload should run (-1 for endless loop)
bool blink=false;

void setup()
{
	// initialize the digital pin as an output.
	pinMode(0, OUTPUT); //LED on Model B
	pinMode(1, OUTPUT); //LED on Model A
	DigiKeyboard.delay(1000); //wait 1000 milliseconds before first run, to give target time to initialize
}

void loop()
{

	//should code be runned in this loop?
	if (i != 0) {
		DigiKeyboard.sendKeyStroke(0);

		//parse raw duckencoder script
		for (int i=0; i<DUCK_LEN; i+=2)
		{
			uint8_t key = pgm_read_word_near(duckraw + i);
			uint8_t mod = pgm_read_word_near(duckraw + i+1);
			if (key == 0) //delay (a delay>255 is split into a sequence of delays)
			{
				DigiKeyboard.delay(mod);
			}
			else DigiKeyboard.sendKeyStroke(key,mod);
		}
		i--;
		DigiKeyboard.delay(5000); //wait 5000 milliseconds before next loop iteration

	}
	else if (blink)
	{
		digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
		digitalWrite(1, HIGH);
		delay(100);               // wait for a second
		digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
		digitalWrite(1, LOW);
		delay(100);               // wait for a second
	}
}
