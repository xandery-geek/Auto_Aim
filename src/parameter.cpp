#include "parameter.h"


const char Display_win[20] = "Camera Window";		//the name of all windows.
const char Image_win[20] = "Image Window";
const char Control_win[20] = "Control Window";

const float motor_P = 0.03;					//the parameters of PID.
const float motor_I = 0;
const float motor_D = 0.001;

HSV_para hsv_para;						//the HSV value of each color.
HSV_para *hsv_p = &hsv_para;			//the point to hsv_para
HSV_Color hsv_color = blue;				//the color of target.

Mat in_video;							//the mat of source image captured by camera.
Mat out_image;							//the mat of processed image. 
//CONTOUR_TYPE img_contour;
vector<vector<Point> > img_contour;		//the points on the contours.
Point center_point;						//the center point of target contour.
PTD_data pid_data;
PTD_data *pid = &pid_data;


int HSV_table[16][3] =					//the table of HSV value
{							
	//HSV value				//color				//tested
	{ 0,0,0 },				//black
	{ 0,0,255 },			//white
	{ 0,255,255 },			//red
	{ 60,255,255 },			//lime
	{ 120,175,175 },		//blue				1			
	{ 30,255,255 },			//yellow
	{ 90,255,255 },			//cyan
	{ 150,255,255 },		//magenta
	{ 0,0,191 },			//silver
	{ 0,0,127 },			//gray
	{ 0,255,127 },			//maroon
	{ 30,255,127 },			//olive
	{ 60,255,127 },			//green
	{ 150,255,127 },		//purple
	{ 90,255,127 },			//teal
	{ 120,255,127 },		//navy
};
