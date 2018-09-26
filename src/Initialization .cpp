#include "Initialization.h"



void Init_Information()
{
	cout
		<< "\n--------------------------------------------------------------------------" << endl
		<< "The funcation of  this program is to find the objects which have the specific color" << endl
		<< "Here are three Windows to display image or information" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}


void Init_Windows()
{
	namedWindow(Display_win, WINDOW_NORMAL);	//Can change the size of Windows
	namedWindow(Image_win, WINDOW_NORMAL);
	namedWindow(Control_win, WINDOW_NORMAL);
	Motor_Init();

}


/*
*brief�����ü����������ͷ�豸��ʾͼ��
*parament��
*/

/*
*brief: open the camera of computer
*param: the id of camera
*/
int Load_From_Camera(int index)
{
	VideoCapture capture(index);//����VideoCapture����
	if (!capture.isOpened())	//�ж��Ƿ������ͷ����isOpened����ture
	{
		cout << "Open the camera fail!\n" << endl;
		abort();
	}

	bool stop(false);			//����һ������ֹͣѭ���ı���
	Mat frame;					//������Ŷ�ȡ����Ƶ���У�����ÿһ֡��ͼ�� ��Mat�������ڱ���ͼ���Լ������������ݵ����ݽṹ

	namedWindow("Camera");		//����һ�����ڣ���ʾÿһ֡�Ĵ���
	while (!stop)
	{
		if (!capture.read(frame))//���û�ж�ȡ�����ж�
		{
			break;
		}
		imshow("Camera", frame);//������ʾ���ѻ�ȡ����Ƶ��䵽������

		char c = cvWaitKey(33);	//�ȴ�33ms
		if (c == 27)break;		//ʹ��ESC����ֹͣASCII Ϊ27
	}
	capture.release();			//�ͷ�
	return 0;
}

void Init_Control_Bar()
{
	createTrackbar("H_low", Control_win, &hsv_p->low_H,180 );
	createTrackbar("H_high", Control_win, &hsv_p->high_H, 180);
	createTrackbar("S_low", Control_win, &hsv_p->low_S,255 );
	createTrackbar("S_high", Control_win,&hsv_p->high_S, 255 );
	createTrackbar("V_low", Control_win, &hsv_p->low_V, 255 );
	createTrackbar("V_hig", Control_win, &hsv_p->high_V, 255 );
}
