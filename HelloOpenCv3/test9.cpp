#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>
#include<fstream>
#include<core\core.hpp>
#include<imgproc\imgproc.hpp>


using namespace std;
using namespace cv;

char file9_filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
string test9_filename1 = "E:\\我的工程\\matlab\\test1.jpg";
string test9_filename2 = "E:\\我的工程\\matlab\\test2.jpg";
char video9_filePath[] = "E:\\照片\\创意照片\\test.MOV";

void fileDetect() {
	namedWindow("test1",CV_WINDOW_NORMAL);
	namedWindow("test2",CV_WINDOW_NORMAL);
	VideoCapture capture(video9_filePath);
	if (!capture.isOpened()) {
		return;
	}
	//获取帧的频率
	double videoFPS = capture.get(CV_CAP_PROP_FPS);
	double videoPause = 1000 / videoFPS;

	Mat framePre;//上一帧
	Mat frameNow;//当前帧
	Mat frameDet;//运动物体

	capture >> framePre;

	cvtColor(framePre,framePre,CV_RGB2GRAY);
	while (true)
	{
		capture >> frameNow;
		if (frameNow.empty()||waitKey(500)==27) {
			return;
		}
		cvtColor(frameNow,frameNow,CV_RGB2GRAY);
		absdiff(frameNow,framePre,frameDet);
		framePre = frameNow;
		imshow("test1",frameNow);
		imshow("test2",frameDet);
	}
}

int main9() {
	fileDetect();
	return 0;
}