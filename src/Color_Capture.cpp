#include "Color_Capture.h"
#include "parameter.h"

/*
Be carefur!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		   The range of HSV in opencv are as follows;
		   H:0-180
		   S:0-255
		   V:0-255
*/


/*
1.Capture image from the camera.
2.RGB to HSV.
3.devide the three channels.
4.Histogram equalization.
5.Merge the three channels
6.Capture the color
7.Display the control bar.
8.Display the treated image.
*/

void HSV_value(int color)
{
	hsv_p->low_H = HSV_table[color][0] - COLOR_RANGE_H;
	hsv_p->high_H = HSV_table[color][0] + COLOR_RANGE_H;
	hsv_p->low_S = HSV_table[color][1] - COLOR_RANGE_SV;
	hsv_p->high_S = HSV_table[color][1] + COLOR_RANGE_SV;
	hsv_p->low_V = HSV_table[color][2] - COLOR_RANGE_SV;
	hsv_p->high_V = HSV_table[color][2] + COLOR_RANGE_SV;

	if (hsv_p->low_H < 0)
		hsv_p->low_H = 0;
	if (hsv_p->high_H > 180)
		hsv_p->high_H = 180;
	if (hsv_p->low_S < 0)
		hsv_p->low_S = 0;
	if (hsv_p->high_S > 255)
		hsv_p->high_S = 255;
	if (hsv_p->low_V < 0)
		hsv_p->low_V = 0;
	if (hsv_p->high_V > 255)
		hsv_p->high_V = 255;

}


void Capture_Color(Mat& src, Mat& dst)
{
	Mat imgHSV;
	vector<Mat> hsvSplit;
	cvtColor(src, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	split(imgHSV, hsvSplit);
	equalizeHist(hsvSplit[2], hsvSplit[2]);
	merge(hsvSplit, imgHSV);

	inRange(imgHSV, Scalar(hsv_p->low_H, hsv_p->low_S, hsv_p->low_V), 
		Scalar(hsv_p->high_H, hsv_p->high_S, hsv_p->high_V), dst); //Threshold the image

	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));//5*5

	//������
	morphologyEx(dst, dst, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(dst, dst, MORPH_CLOSE, element);
}


vector<vector<Point> > Capture_coutour(Mat& img)
{
	vector<vector<Point> > contours;
	//The image should be a gray image!
	if (img.channels() != 1)
	{
		cout << "The source image is not a gray image" << endl;
		abort();
	}
	
	//find the extern contours of the image.
	findContours(img, contours, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

	return contours;
}

int Find_Biggest_Contour(vector<vector<Point> > &contours)
{
	int index = -1;
	if (contours.size())
	{
		for (int i = 0; i < contours.size() - 1; i++)
		{
			if (contours[i].size() < contours[i + 1].size())
			{
				index = i + 1;
			}
		}

		if(contours[index].size() < 50)
			index = -1;
	}
	return index;
}
/*
@brief: Find the center of the biggest contour.
@param: 
*/

Point Get_Image_Center(vector<vector<Point> > contours ,int index)
{
	Point center;
	int point_num = 0;
	point_num = contours[index].size();
		
	vector<Point>::iterator p;
	for (p = contours[index].begin(); p < contours[index].end(); p++)
	{
		center.x += p->x;
		center.y += p->y;
	}

	if (point_num)
	{
		center.x /= point_num;
		center.y /= point_num;
	}
	else
	{
		cout << "The contour is empty!" << endl;
		abort();
	}

	return center;
}

void Draw_info(Mat& img, InputArrayOfArrays contours,int index,Point point)
{
	static Scalar color = Scalar(0, 0, 255);	//red
	drawContours(img, contours, index, color,3);	//draw contou
	circle(img, point, 3,color ,-1);			  	//target point
}

void Call_Back(int ,void*)
{
	Capture_Color(in_video, out_image);
}


