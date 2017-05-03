#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main2_fileName[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
char source_image_main2[] = "E:\\��Ƭ\\������Ƭ\\test1.jpg";

void my_mouse_callback2(int event,int x, int y, int flages,void* param) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		cout << "����������" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		cout << "����Ҽ�����" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_MBUTTONDOWN:
		cout << "����м�����" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_LBUTTONUP:
		cout << "�������ſ�" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONUP:
		cout << "����Ҽ��ſ�" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_MBUTTONUP:
		cout << "����м��ſ�" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		cout << "������˫��" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		cout << "����Ҽ�˫��" << endl;
		cout << "��ǰ����Ϊ" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	}
}

void test21() {
	IplImage* image = cvCreateImage(cvSize(200,200),8,3);
	cvZero(image);

	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvSetMouseCallback("test",my_mouse_callback2,(void*) image);
	cvShowImage("test",image);
	if(cvWaitKey(0)=='5') return;
	cvDestroyWindow("test");
}

int main2() {
	test21();
	return 0;
}