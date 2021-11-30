#ifndef _TRACKING_H_
#define _TRACKING_H_
/*************************************
* Library for tracking
**************************************/
#include<wiringPi.h>
#include<softPwm.h>
#include<stdio.h>
/*Here define all the pins.***********/
#define key  10       //定义按键为Raspberry的wiringPi编码10口

//循迹红外引脚定义
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      9                  21                  7                   1
#define TrackSensorLeftPin1    9  //定义左边第一个循迹红外传感器引脚为wiringPi编码9口
#define TrackSensorLeftPin2   21  //定义左边第二个循迹红外传感器引脚为wiringPi编码21口
#define TrackSensorRightPin1   7   //定义右边第一个循迹红外传感器引脚为wiringPi编码7口
#define TrackSensorRightPin2   1   //定义右边第二个循迹红外传感器引脚为wiringPi编码1口
/*************************************/
void key_scan();/*按键检测(包含软件按键去抖)*/
void loop();/*小车巡线循环*/
#endif