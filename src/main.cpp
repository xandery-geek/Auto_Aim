#include "include.h"


using namespace std;
using namespace cv;

int main()
{
	Init_Information();			//��ʼ��������Ϣ
	Init_Windows();				//��ʼ������
	HSV_value(hsv_color);		//��ʼ��HSVֵ
	
	int index;					//�������

	VideoCapture capture(0);	//����VideoCapture����
	if (!capture.isOpened())	//�ж��Ƿ������ͷ����isOpened����ture
	{
		cout << "Open the camera fail!\n" << endl;
		return -1;
	}

	while (true)
	{
		if (!capture.read(in_video))	//���û�ж�ȡ�����ж�
		{
			break;
		}
		
		Init_Control_Bar();
		Capture_Color(in_video,out_image);
		img_contour = Capture_coutour(out_image);
		index = Find_Biggest_Contour(img_contour);
		if(index != -1)
		{
			center_point = Get_Image_Center(img_contour, index);
			Point point_error =  Get_Error(out_image, center_point);
			PID_Control(point_error);
			Motor_Output();
		}

		Draw_info(in_video, img_contour, index, center_point);//����������Ϣ
		imshow(Image_win, out_image);	//������ʾ���Ѵ�����ͼ����䵽������
		imshow(Display_win, in_video);//������ʾ���ѻ�ȡ����Ƶ��䵽������		

		char c = cvWaitKey(33);	//33ms
		if (c == 27)break;		//ESC: ֹASCII 127
	}
	

	capture.release();			
	destroyAllWindows();
	return 0;
}

