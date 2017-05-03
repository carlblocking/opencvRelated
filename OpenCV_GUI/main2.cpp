#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main2_fileName[] = "E:\\照片\\创意照片\\guitar.jpg";
char source_image_main2[] = "E:\\照片\\创意照片\\test1.jpg";

void my_mouse_callback2(int event,int x, int y, int flages,void* param) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		cout << "鼠标左键按下" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONDOWN:
		cout << "鼠标右键按下" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_MBUTTONDOWN:
		cout << "鼠标中键按下" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_LBUTTONUP:
		cout << "鼠标左键放开" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONUP:
		cout << "鼠标右键放开" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_MBUTTONUP:
		cout << "鼠标中键放开" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		cout << "鼠标左键双击" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
		cout << "\n" << endl;
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		cout << "鼠标右键双击" << endl;
		cout << "当前坐标为" << x << "\t" << y << endl;
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