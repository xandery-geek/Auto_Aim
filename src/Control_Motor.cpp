#include "Control_Motor.h"
#include <wiringPi.h>

/*
1.Communicate With MCU through Bluetooth.
2.MCU controls the motor to turn to a appropriate angle to cafpture image.
3.PID control
*/

inline void Value_Limit(int& value, int min, int max)
{
	if(value > max)
		value = max;
	else if(value < min)
		value = min;
}

void Motor_Init()
{
	wiringPiSetup();
    pinMode(MOTOR1,OUTPUT); // x
	pinMode(MOTOR2,OUTPUT); // y

	PWM_GPIO(1, 90);
	PWM_GPIO(2, 90);
}

Point Get_Error(const Mat& img ,Point point)
{
	Point center;

	center.x = img.rows/2;
	center.y = img.cols/2;

	center.x -= point.x;		//calculate the distance to center. 
	center.y -= point.y;

	return center;
}

void PID_Control(const Point PID_error)
{
	static Point center_point_last;
	//
	pid->delta_x = PID_error.x - center_point_last.x;
	pid->integral_x += PID_error.x;

	pid->g_x_angle = (motor_P * PID_error.x + motor_I * pid->integral_x \
					+ motor_D * pid->delta_x);
	//
	pid->delta_y = PID_error.y - center_point_last.y;
	pid->integral_y += PID_error.y;

	pid->g_y_angle = (motor_P * PID_error.y + motor_I * pid->integral_y \
					+ motor_D * pid->delta_y);

	center_point_last = PID_error;                                                                                                                                                                                                                                   
}

void Motor_Output()
{
	static int x_angle = 90;
	static int y_angle = 90;

	x_angle = static_cast<int>(x_angle + pid->g_x_angle);
	y_angle = static_cast<int>(y_angle + pid->g_y_angle);

	pid->g_x_angle = 0;
	pid->g_y_angle = 0;

	Value_Limit(x_angle, 0, 180);
	Value_Limit(y_angle, 0, 180);

	std::cout<<"g_x_angle:"<<pid->g_x_angle<<" "
			 <<"g_y_angle:"<<pid->g_y_angle<<std::endl;

	std::cout<<"x angle:"<<x_angle<<" "
			 <<"y angle:"<<y_angle<<std::endl;

	PWM_GPIO(1, x_angle);
	//PWM_GPIO(2, y_angle);
}

/*
@brief: output PWM by GPIO of raspberry
@param: 
*/
void PWM_GPIO(int index, int angle)
{	

	if(angle < 0)
	{
		std::cerr<<"the value of motor angle < 0"<<std::endl;
		angle = 0;
	}
	else if(angle > 180)
	{
		std::cerr<<"the value of motor angle > 180"<<std::endl;
		angle = 180;
	}

	int MOTOR;
	if (index == 1)
	{
		MOTOR = MOTOR1;
	}
	else
		MOTOR = MOTOR2;

	int high = 500 + int(angle * 1000/90) ;
	int low = 20000 - high;

	digitalWrite(MOTOR, HIGH);
	delayMicroseconds(high);
	//delayMicroseconds(500);

	digitalWrite(MOTOR, LOW);
	delayMicroseconds(low);
	//delayMicroseconds(19500);
}
