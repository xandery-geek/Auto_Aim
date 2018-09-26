#ifndef COLOR_CAPTURE_H
#define COLOR_CAPTURE_H

#include "include.h"

#define COLOR_RANGE_H		20
#define COLOR_RANGE_SV		75

using namespace cv;
using namespace std;

void HSV_value(int color);
void Capture_Color(Mat& src, Mat& dst);
//void Call_Back(int, void*);
//CONTOUR_TYPE Capture_coutour(Mat& img);

vector<vector<Point> > Capture_coutour(Mat& img);
int Find_Biggest_Contour(vector<vector<Point> > &contours);
Point Get_Image_Center(vector<vector<Point> > contours, int index);
void Draw_info(Mat& img, InputArrayOfArrays contours, int index, Point point);

#endif
