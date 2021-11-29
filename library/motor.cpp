#include"motor.h"
/*************************************
* Library for motor
* Creat time : 2021_11_28_19_58
* @CREATOR All Rights Reserved.
**************************************/
#include<wiringPi.h>
#include<softPwm.h>
#include<stdio.h>
/*************************************/
int motorSetup()
{
	wiringPiSetup();
	pinMode(lfIN1, OUTPUT);
	pinMode(lfIN2, OUTPUT);
	pinMode(riIN1, OUTPUT);
	pinMode(riIN2, OUTPUT);
	return 0;
}
/*Stop********************************/
void Stop()
{
	digitalWrite(lfENA, HIGH);
	digitalWrite(riENA, HIGH);
	digitalWrite(lfIN1, LOW);
	digitalWrite(lfIN2, LOW);
	digitalWrite(riIN1, LOW);
	digitalWrite(riIN2, LOW);
}
/*Forward*****************************/
int movFor(int lfSpd, int riSpd, unsigned int t)
{
	Setup();
	if (t == 0)
	{
		digitalWrite(lfIN1, LOW);
		digitalWrite(lfIN2, HIGH);
		digitalWrite(riIN1, LOW);
		digitalWrite(riIN2, HIGH);
		softPwmWrite(lfENA, lfSpd);
		softPwmWrite(riENA, riSpd);
		return 0;
	}
	else
	{
		digitalWrite(lfIN1, LOW);
		digitalWrite(lfIN2, HIGH);
		digitalWrite(riIN1, LOW);
		digitalWrite(riIN2, HIGH);
		softPwmWrite(lfENA, lfSpd);
		softPwmWrite(riENA, riSpd);
		delay(t);
		Stop();
		return 0;
	}
}
/*Backward*******************************/
int movBac(int lfSpd, int riSpd, unsigned int t)
{
	Setup();
	if (t == 0)
	{
		digitalWrite(lfIN1, HIGH);
		digitalWrite(lfIN2, LOW);
		digitalWrite(riIN1, HIGH);
		digitalWrite(riIN2, LOW);
		softPwmWrite(lfENA, lfSpd);
		softPwmWrite(riENA, riSpd);
		return 0;
	}
	else
	{
		digitalWrite(lfIN1, HIGH);
		digitalWrite(lfIN2, LOW);
		digitalWrite(riIN1, HIGH);
		digitalWrite(riIN2, LOW);
		softPwmWrite(lfENA, lfSpd);
		softPwmWrite(riENA, riSpd);
		delay(t);
		Stop();
		return 0;
	}
}
/*Turn************************************/

int movTur(int direction, int Spd, unsigned int t)
{
	int lf = 0;
	int ri = 1;
	Setup();
	if (t == 0)
	{
		if (direction == lf)
		{
			digitalWrite(lfIN1, HIGH);
			digitalWrite(lfIN2, LOW);
			digitalWrite(riIN1, LOW);
			digitalWrite(riIN2, HIGH);
			softPwmWrite(lfENA, Spd);
			softPwmWrite(riENA, Spd);
			return 0;
		}
		else if (direction == ri)
		{
			digitalWrite(lfIN1, LOW);
			digitalWrite(lfIN2, HIGH);
			digitalWrite(riIN1, HIGH);
			digitalWrite(riIN2, LOW);
			softPwmWrite(lfENA, Spd);
			softPwmWrite(riENA, Spd);
			return 0;
		}
		else
		{
			printf("Please check turning direction.\n");
			return 1;
		}
		
	}
	else
	{
		if (direction == lf)
		{
			digitalWrite(lfIN1, HIGH);
			digitalWrite(lfIN2, LOW);
			digitalWrite(riIN1, LOW);
			digitalWrite(riIN2, HIGH);
			softPwmWrite(lfENA, Spd);
			softPwmWrite(riENA, Spd);
			delay(t);
			Stop();
			return 0;
		}
		else if (direction == ri)
		{
			digitalWrite(lfIN1, LOW);
			digitalWrite(lfIN2, HIGH);
			digitalWrite(riIN1, HIGH);
			digitalWrite(riIN2, LOW);
			softPwmWrite(lfENA, Spd);
			softPwmWrite(riENA, Spd);
			delay(t);
			Stop();
			return 0;
		}
		else
		{
			printf("Please check turning direction.\n");
			return 1;
		}
	}
}