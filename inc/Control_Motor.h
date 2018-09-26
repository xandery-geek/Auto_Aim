#ifndef CONTROL_MOTOR_H
#define CONTROL_MOTOR_H

#include "include.h"

#define MOTOR1 24
#define MOTOR2 25

void Motor_Init();
void PWM_GPIO(int index, int angle);
Point Get_Error(const Mat& img ,Point point);
void PID_Control(const Point PID_error);
void Motor_Output();

#endif

 

