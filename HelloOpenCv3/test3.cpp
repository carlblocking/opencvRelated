#include<iostream>
#include<string>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

void objectTrace() {

	int threshold = 25;    // ��ֵ����ֵ  
	float alpha = 0.01;     // �����ٶ� [0, 1]  

	cv::VideoCapture capture(0);
	//if (!capture.isOpened())
	//{
	//	std::cout << "cannot open video" << std::endl;
	//	return;
	//}

	cv::Mat foregroundImg;
	cv::Mat foregroundMat;

	cv::Mat backgroundImg;
	cv::Mat backgroundMat;

	cv::Mat frame;
	cv::Mat grayImg;
	cv::Mat grayMat;

	while (capture.read(frame))
	{
		cv::cvtColor(frame, grayImg, CV_BGR2GRAY);
		grayImg.convertTo(grayMat, CV_32FC1);

		if (backgroundMat.empty())
		{
			grayImg.copyTo(backgroundImg);
			grayImg.convertTo(backgroundMat, CV_32FC1);
		}

		// ��������  
		cv::absdiff(grayMat, backgroundMat, foregroundMat);

		// ����Ӧ��������  
		cv::addWeighted(backgroundMat, alpha, foregroundMat, 1 - alpha, 0, backgroundMat);

		// ��ֵ������ȡǰ�����ص�  
		cv::threshold(foregroundMat, foregroundMat, threshold, 255, CV_THRESH_BINARY);


		// Ϊ����ʾ�ã���CV_32FC1ת��ΪCV_8U  
		cv::convertScaleAbs(foregroundMat, foregroundImg);
		cv::convertScaleAbs(backgroundMat, backgroundImg);

		cv::imshow("frame", frame);
		cv::imshow("foreground", foregroundImg);
		cv::imshow("background", backgroundImg);

		if (cv::waitKey(25) > 0)
		{
			break;
		}
	}
}

void matCamera() {
	char c;
	VideoCapture inputVideo(0);
	Mat src;
	namedWindow("test", WINDOW_NORMAL);
	for (;;) {
		inputVideo >> src;
		imshow("test", src);
		c = waitKey(10);
		if (c == 27)break;
	}
}

int main3() {
	objectTrace();
	return 0;
}