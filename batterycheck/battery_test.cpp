#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define SPICLK 8 
#define SPIMISO 23
#define SPIMOSI 24
#define SPICS 25

int readAdc()
{
	int commandOut = 0x6;

	digitalWrite(SPICS, 1);
	digitalWrite(SPICLK, 0);
	digitalWrite(SPICS, 0);

	commandOut <<= 5;
	for (int i = 0; i < 3; ++ i)
	{
		if (commandOut & 0x80)
			digitalWrite(SPIMOSI, 1);
		else
			digitalWrite(SPIMOSI, 0);

		commandOut <<= 1;
		digitalWrite(SPICLK, 1);
		digitalWrite(SPICLK, 0);
	}

	int adcOut = 0;
	for (int i = 0; i < 12; ++ i)
	{
		digitalWrite(SPICLK, 1);
		digitalWrite(SPICLK, 0);
		adcOut <<= 1;
		if (digitalRead(SPIMISO))
			adcOut |= 0x1;
	}

	digitalWrite(SPICS, 1);

	return adcOut / 2;
}

int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return -1;

	pinMode(SPIMOSI, OUTPUT);
	pinMode(SPIMISO, INPUT);
	pinMode(SPICLK, OUTPUT);
	pinMode(SPICS, OUTPUT);

	while (1)
	{
		int adcTotal = 0;
		for (int i = 0; i < 10; ++ i)
		{
			adcTotal += readAdc();
			usleep(50000);
		}
		float adcValue = adcTotal / 10 / 1.0;
		printf("adc = %f\n", adcValue);

		float volts = adcValue * (3.33 / 1024.0) * 2.837;
		printf("volt = %f\n", volts);

		sleep(60);
	}

	return 0;
}
