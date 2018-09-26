#ifndef PARAMETER_H
#define PARAMETER_H

#include "include.h"

using namespace cv;
using namespace std;

//typedef vector<vector<Point> > CONTOUR_TYPE;

typedef enum
{
	black,
	white,
	red,
	lime,
	blue,
	yellow,
	cyan,
	magenta,
	silver,
	gray,
	maroon,
	olive,
	green,
	purple,
	teal,
	navy
}HSV_Color;


typedef struct 
{
	int low_H;
	int high_H;
	int low_S;
	int high_S;
	int low_V;
	int high_V;

}HSV_para;


typedef struct 
{
	float g_x_angle;						//the angle that motor need to turn in the horizontal direction.
	float g_y_angle;						//the angle that motor need to turn in the vertical direction.
	int integral_x;							//the integral of error.
	int integral_y;							//the integral of error.
	int delta_x;							//the differential of error.
	int delta_y;							//the differential of error.

}PTD_data;


extern const char Display_win[20];			
extern const char Image_win[20];
extern const char Control_win[20];

extern const float motor_P;					//the parameters of PID.
extern const float motor_I;
extern const float motor_D;

extern HSV_para hsv_para;						//the HSV value of each color.
extern HSV_para *hsv_p;							//the point to hsv_para
extern int HSV_table[16][3];					//the table of HSV value
extern HSV_Color hsv_color;						//the color of target

extern Mat in_video;							//the mat of source image captured by camera.
extern Mat out_image;							//the mat of processed image. 
//extern CONTOUR_TYPE img_contour;
extern vector<vector<Point> > img_contour;		//the points on the contours.
extern Point center_point;						//the center point of target contour.
extern PTD_data pid_data;
extern PTD_data *pid;


#endif
