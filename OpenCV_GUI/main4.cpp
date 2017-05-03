#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main4_fileName[] = "E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg";
char source_image_main4[] = "E:\\’’∆¨\\¥¥“‚’’∆¨\\test1.jpg";

IplImage* g_image = NULL;
IplImage* g_gray = NULL;
int g_thresh = 100;
CvMemStorage* g_storage = NULL;
void on_trackbar(int) {
	if (g_storage == NULL) {
		g_gray = cvCreateImage(cvGetSize(g_image),8,1);
		g_storage = cvCreateMemStorage(0);
	}
	else
	{
		cvClearMemStorage(g_storage);
	}
	CvSeq* counters = 0;
	cvCvtColor(g_image,g_gray,CV_BGR2GRAY);
	cvThreshold(g_gray,g_gray,g_thresh,255,CV_THRESH_BINARY);
	cvFindContours(g_gray,g_storage,&counters);
	cvZero(g_gray);
	if (counters)
		cvDrawContours(g_gray,counters,cvScalarAll(255),cvScalarAll(255),100);
	cvShowImage("test",g_gray);
}

void on_trackbar_test() {
	g_image = cvLoadImage(main4_fileName);
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvCreateTrackbar("test_bar","test",&g_thresh, 10,on_trackbar);
	on_trackbar(0);
	cvWaitKey();
}
int main4() {
	on_trackbar_test();
	return 0;
}