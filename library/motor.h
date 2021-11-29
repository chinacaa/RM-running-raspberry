#ifndef _MORTOR_H_
#define _MORTOR_H_
/*************************************
* Library for motor
* Creat time : 2021_11_28_19_58
* @CREATOR All Rights Reserved.
**************************************/
#include<wiringPi.h>
#include<softPwm.h>
#include<stdio.h>
/*Here define all the pins.***********/
#define lfIN1 4
#define lfIN2 5
#define lfENA 6
#define riIN1 7
#define riIN2 8
#define riENA 9
/*************************************/
int motorSetup();
void motorStop();//Stop move with no return.
int movFor(int lfSpd, int riSpd, unsigned int t);//(Speed of left machinery (0-255), Speed of right machinery (0-255), Time(int) ),return 0 if success.
int movBac(int lfSpd, int riSpd, unsigned int t);//(Speed of left machinery (0-255), Speed of right machinery (0-255), Time(int) ),return 0 if success.
int movTur(int direction, int Spd, unsigned int t);//(Turning direction (lf or ri), Speeed of turning (0-255), Time(int) ), return 0 if success or 1 if fail.
#endif