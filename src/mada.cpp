#include <Arduino.h>
#include "mada.h"

#define pwmL 22
#define LIN 23
#define pwmR 25
#define RIN 26
#define diverL 13
#define diverR 14
#define lightL 18
#define lightR 19

#define pwmFreq 50 		 //PWM波形频率50HZ
#define pwmChannel1  3 //使用PWM的通道3
#define pwmChannel2  4 //使用通道4
#define pwmResolution  10		//使用PWM占空比的分辨率，占空比最大可写2^10-1=1023

#define speed(x)  (700+100*x)
#define maxSpeed 1024
#define halfSpeed 512


void madaReady()
{
    pinMode(LIN,OUTPUT);
    
    pinMode(RIN,OUTPUT);
    
    pinMode(diverL,OUTPUT);
    digitalWrite(diverL,HIGH);                                                                                                                                                                       
    pinMode(diverR,OUTPUT);
    digitalWrite(diverR,HIGH);
    ledcSetup(pwmChannel1,pwmFreq,pwmResolution);
    ledcSetup(pwmChannel2,pwmFreq,pwmResolution);
    ledcAttachPin(pwmL,pwmChannel1);
    ledcAttachPin(pwmR,pwmChannel2);

    pinMode(lightL,OUTPUT);
    pinMode(lightR,OUTPUT);
}


void run(int x)
{
    ledcWrite(pwmChannel1,x);
    ledcWrite(pwmChannel2,x);
    digitalWrite(LIN,HIGH);
    digitalWrite(RIN,LOW);
}

void back(int x)
{
    ledcWrite(pwmChannel1,x);
    ledcWrite(pwmChannel2,x);
    digitalWrite(LIN,LOW);
    digitalWrite(RIN,HIGH);
}

void turnLeft()
{
    ledcWrite(pwmChannel1,maxSpeed);
    ledcWrite(pwmChannel2,0);
    digitalWrite(LIN,HIGH);
    digitalWrite(RIN,LOW);
    digitalWrite(lightL,HIGH);
}

void turnRight()
{
    ledcWrite(pwmChannel2,maxSpeed);
    ledcWrite(pwmChannel1,0);
    digitalWrite(LIN,HIGH);
    digitalWrite(RIN,LOW);
    digitalWrite(lightR,HIGH);
}
void stop()
{
    digitalWrite(LIN,HIGH);
    digitalWrite(RIN,LOW);
    ledcWrite(pwmChannel2,0);
    ledcWrite(pwmChannel1,0);
    digitalWrite(lightL,HIGH);
    digitalWrite(lightR,HIGH);

}