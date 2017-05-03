#include<opencv\cv.h>
#include<highgui.hpp>
#include<iostream>
#include<string>

#define TWO_PI 6.2831853071795864769252866  

using namespace std;
using namespace cv;

char file1_name[] = "E:\\照片\\创意照片\\guitar.jpg";

void zhiFangTuJunHengHua() {
	IplImage* sourceImage = cvLoadImage(file1_name, 0);
	IplImage* resultImage = cvCreateImage(cvGetSize(sourceImage), 8, 1);
	cvEqualizeHist(sourceImage, resultImage);//均衡化函数
	cvNamedWindow("source", CV_WINDOW_NORMAL);
	cvNamedWindow("result", CV_WINDOW_NORMAL);
	cvShowImage("source", sourceImage);
	cvShowImage("result", resultImage);
	cvWaitKey(0);
}

void differentKernel() {
	IplImage* sourceImage = cvLoadImage(file1_name);
	IplImage* resultImage1 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage2 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage3 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage4 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage5 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage6 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage7 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	IplImage* resultImage8 = cvCreateImage(cvGetSize(sourceImage), 8, 3);
	//定义一个核
	float kernel1[] = { 0,1,0,1,-4,1,0,1,0 };
	CvMat mat = cvMat(3, 3, CV_32FC1, kernel1);
	cvFilter2D(sourceImage, resultImage1, &mat);

	float kernel2[] = { 1,1,1,1,-8,1,1,1,1 };
	CvMat mat2 = cvMat(3, 3, CV_32FC1, kernel2);
	cvFilter2D(sourceImage, resultImage2, &mat2);

	float kernel3[] = { 1,-2,1,-2,4,-2,1,-2,1 };
	CvMat mat3 = cvMat(3, 3, CV_32FC1, kernel3);
	cvFilter2D(sourceImage, resultImage3, &mat3);

	float kernel4[] = { 0,-1,0,-1,4,-1,0,-1,0 };
	CvMat mat4 = cvMat(3, 3, CV_32FC1, kernel4);
	cvFilter2D(sourceImage, resultImage4, &mat4);

	float kernel5[] = { 0,-1,0,-1,5,-1,0,-1,0 };
	CvMat mat5 = cvMat(3, 3, CV_32FC1, kernel5);
	cvFilter2D(sourceImage, resultImage5, &mat5);

	float kernel6[] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
	CvMat mat6 = cvMat(3, 3, CV_32FC1, kernel6);
	cvFilter2D(sourceImage, resultImage6, &mat6);

	float kernel7[] = { 0,1,0,1,-5,1,0,1,0 };
	CvMat mat7 = cvMat(3, 3, CV_32FC1, kernel7);
	cvFilter2D(sourceImage, resultImage7, &mat7);

	float kernel8[] = { 1,1,1,1,-9,1,1,1,1 };
	CvMat mat8 = cvMat(3, 3, CV_32FC1, kernel8);
	cvFilter2D(sourceImage, resultImage8, &mat8);

	cvNamedWindow("source", CV_WINDOW_NORMAL);

	cvNamedWindow("result1", CV_WINDOW_NORMAL);
	cvNamedWindow("result2", CV_WINDOW_NORMAL);
	cvNamedWindow("result3", CV_WINDOW_NORMAL);
	cvNamedWindow("result4", CV_WINDOW_NORMAL);
	cvNamedWindow("result5", CV_WINDOW_NORMAL);
	cvNamedWindow("result6", CV_WINDOW_NORMAL);
	cvNamedWindow("result7", CV_WINDOW_NORMAL);
	cvNamedWindow("result8", CV_WINDOW_NORMAL);

	cvShowImage("source", sourceImage);

	cvShowImage("result1", resultImage1);
	cvShowImage("result2", resultImage2);
	cvShowImage("result3", resultImage3);
	cvShowImage("result4", resultImage4);
	cvShowImage("result5", resultImage5);
	cvShowImage("result6", resultImage6);
	cvShowImage("result7", resultImage7);
	cvShowImage("result8", resultImage8);
	cvWaitKey(0);
}

//添加盐噪声，白色点
void salt(Mat& sourceImage, int n) {
	for (int k = 0; k < n / 2; k++) {
		int i = rand() % sourceImage.cols;
		int j = rand() % sourceImage.rows;

		if (sourceImage.channels() == 1) {
			sourceImage.at<uchar>(j, i) = 255;
		}
		else {
			sourceImage.at<Vec3b>(j, i)[0] = 255;
			sourceImage.at<Vec3b>(j, i)[1] = 255;
			sourceImage.at<Vec3b>(j, i)[2] = 255;
		}
	}
}
//添加椒盐噪声，黑白点
void peppersalt(Mat& sourceImage,int n) {
	for (int k = 0; k < n / 2; k++) {
		int i = rand() % sourceImage.cols;
		int j = rand() % sourceImage.rows;

		if (sourceImage.channels() == 1) {
			sourceImage.at<uchar>(j, i) = 255;
		}
		else {
			sourceImage.at<Vec3b>(j, i)[0] = 255;
			sourceImage.at<Vec3b>(j, i)[1] = 255;
			sourceImage.at<Vec3b>(j, i)[2] = 255;
		}
	}

	for (int k = 0; k < n / 2; k++) {
		int i = rand() % sourceImage.cols;
		int j = rand() % sourceImage.rows;

		if (sourceImage.channels() == 1) {
			sourceImage.at<uchar>(j, i) = 0;
		}
		else {
			sourceImage.at<Vec3b>(j, i)[0] = 0;
			sourceImage.at<Vec3b>(j, i)[1] = 0;
			sourceImage.at<Vec3b>(j, i)[2] = 0;
		}
	}
}
//高斯噪声
double generateGaussianNoise() {
	static bool hasSpare = false;
	static double rand1, rand2;

	if (hasSpare) {
		hasSpare = false;
		return sqrt(rand1)*sin(rand2);
	}

	hasSpare = true;
	rand1 = rand() / ((double)RAND_MAX);
	if (rand1 < 1e-100)
		rand1 = 1e-100;
	rand2 = (rand()) / ((double)RAND_MAX)*TWO_PI;

	return sqrt(rand1)*cos(rand2);
}
void addGaussianNoise(Mat& image) {
	CV_Assert(image.depth()!=sizeof(uchar));
	int channels = image.channels();
	int nRows = image.rows;
	int nCols = image.cols*channels;
	if (image.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	for (i = 0; i < nRows;++i) {
		p = image.ptr<uchar>(i);
		for (j = 0; j < nCols;++j) {
			double val = p[j] + generateGaussianNoise() * 128;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			p[j] = (uchar)val;
		}
	}
}
//给图像添加噪声，分别为盐噪声和椒盐噪声并分别存储
//所谓盐噪声，就是白色的点，胡椒噪声就是黑色的点，椒盐噪声就是黑白的点
void addNoise() {
	Mat sourceImage = imread("E:\\照片\\创意照片\\horse.png");
	Mat image_1 = sourceImage.clone();
	Mat image_2 = sourceImage.clone();
	Mat image_3 = sourceImage.clone();
	salt(image_1,10000);
	peppersalt(image_2,10000);
	addGaussianNoise(image_3);
	imwrite("C:\\Users\\xxw\\Desktop\\image1.jpg",image_1);
	imwrite("C:\\Users\\xxw\\Desktop\\image2.jpg", image_2);
	imwrite("C:\\Users\\xxw\\Desktop\\image3.jpg", image_3);
	sourceImage.release();
	image_1.release();
	image_2.release();
	image_3.release();
}

//各种去噪

//1、谐波均值滤波适合处理“盐”噪声
//2、逆谐波均值滤波适合处理“胡椒”噪声或者“盐”噪声，但不能同时去除
//3、终点滤波适合处理高斯和均匀随机分布的噪声
//4、自适应终止滤波适合处理处理多种噪声，这里不过多赘述

int main1() {
	addNoise();
	return 0;
}