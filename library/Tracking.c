/*tracking.c*/
#include <wiringPi.h>
#include <softPwm.h>
#include"motor.h"
int key = 10;                 //定义按键为Raspberry的wiringPi编码10口
//循迹红外引脚定义
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      9                 21                  7                   1
const int TrackSensorLeftPin1  =  9;   //定义左边第一个循迹红外传感器引脚为wiringPi编码9口
const int TrackSensorLeftPin2  =  21;  //定义左边第二个循迹红外传感器引脚为wiringPi编码21口
const int TrackSensorRightPin1 =  7;   //定义右边第一个循迹红外传感器引脚为wiringPi编码7口
const int TrackSensorRightPin2 =  1;   //定义右边第二个循迹红外传感器引脚为wiringPi编码1口

//定义各个循迹红外引脚采集的数据的变量
int TrackSensorLeftValue1;
int TrackSensorLeftValue2;
int TrackSensorRightValue1;
int TrackSensorRightValue2;

/*按键检测(包含软件按键去抖)*/
void key_scan()
{
  while (digitalRead(key));       //当按键没有被按下一直循环
  while (!digitalRead(key))       //当按键被按下时
  {
    delay(10);	                  //延时10ms
    if (digitalRead(key)  ==  LOW)//第二次判断按键是否被按下
    {
      delay(100);
      while (!digitalRead(key));  //判断按键是否被松开
    }
  }
}

/* 先调用setup初始化配置里面的按键扫描函数，循迹模式开启 */
void main()
{
  //wiringPi初始化
  setup();
  //定义按键接口为输入接口
  pinMode(key, INPUT);

  //定义四路循迹红外传感器为输入接口
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);

  //调用按键扫描函数
  key_scan();
  
  while(1)
  {
   //检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
   //未检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
   TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
   TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
   TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
   TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);

   //四路循迹引脚电平状态
   // 0 0 X 0
   // 1 0 X 0
   // 0 1 X 0
   //以上6种电平状态时小车原地右转，速度为250,延时80ms
   //处理右锐角和右直角的转动
   if ( (TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) &&  TrackSensorRightValue2 == LOW)
   {
        movTur(1, 250, 0);
        delay(80);
   }
   //四路循迹引脚电平状态
   // 0 X 0 0       
   // 0 X 0 1 
   // 0 X 1 0       
   //处理左锐角和左直角的转动
   else if ( TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW ||  TrackSensorRightValue2 == LOW))
   {
        movTur(0, 250, 0);//小车原地左转(左轮后退，右轮前进)
        delay(80);
   }
   // 0 X X X
   //最左边检测到
   else if ( TrackSensorLeftValue1 == LOW)
   {
        movTur(0, 150, 0);//小车原地右转(右轮后退，左轮前进)
        //delay(10);
   }
   // X X X 0
   //最右边检测到
   else if ( TrackSensorRightValue2 == LOW )
   {
        movTur(1, 150, 0);
        //delay(10);
   }
   //四路循迹引脚电平状态
   // X 0 1 X
   //处理左小弯
   else if ( TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
   {
        movTur(0,220, 0);//小车左转(左轮不动，右轮前进)
   }
   //四路循迹引脚电平状态
   // X 1 0 X  
   //处理右小弯
   else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
   {
        movTur(1, 220, 0);//小车右转(右轮不动，左轮前进)
   }
   //四路循迹引脚电平状态
   // X 0 0 X
   //处理直线
   else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
   {
        movFor(250, 250, 0);
   }
   //当为1 1 1 1时小车保持上一个小车运行状态
 }
 return;
}
