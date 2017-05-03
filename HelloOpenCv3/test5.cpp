#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>

using namespace std;
using namespace cv;

/*使用不同的方式访问图片像素*/

char file5_filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
string test5_filename1 = "E:\\我的工程\\matlab\\test1.jpg";
string test5_filename2 = "E:\\我的工程\\matlab\\test2.jpg";
char video5_filePath[] = "E:\\照片\\创意照片\\test.MOV";

void getRandom() {
	srand((int)time(0));
	for (int i = 0; i < 10;i++) {
		//cout << (rand()%255) << "\t";
		cout << (rand()/double(RAND_MAX)) << "\t";
	}
}

IplImage* createGrayImage() {
	srand((int)time(0));
	int value = rand() % 255;
	IplImage* image = cvCreateImage(cvSize(100,100),8,1);
	//cvZero(image);
	for (int i = 0; i < image->height;i++) {
		for (int j = 0; j < image->width;j++) {
			(image->imageData + i*image->widthStep)[j] = value;
		}
	}
	return image;
}

IplImage* createColorImage() {
	srand((int)time(0));
	IplImage* image = cvCreateImage(cvSize(50,50),8,3);
	int value1 = rand() % 255;
	int value2 = rand() % 255;
	int value3 = rand() % 255;
	for (int i = 0; i < image->height;i++) {
		for (int j = 0; j < image->height;j++) {
			cvSet2D(image,i,j,CvScalar(cvScalar(value1,value2,value3)));
		}
	}
	return image;
}

void playColorImage() {
	IplImage* frame;
	cvNamedWindow("test",0);
	while (1)
	{
		frame = createColorImage();
		cvShowImage("test",frame);
		cvWaitKey(50);
		cvReleaseImage(&frame);
	}
}

//灰度图像每个像素进行开方计算
void sqrtImage() {
	IplImage* sourceImage = cvLoadImage(file5_filePath,0);
	IplImage* resultImage = cvCloneImage(sourceImage);
	int value;
	for (int i = 0; i < resultImage->height;i++) {
		for (int j = 0; j < resultImage->width;j++) {
			value=(resultImage->imageData+i*resultImage->widthStep)[j];
			(resultImage->imageData + i*resultImage->widthStep)[j] = sqrt(value);
		}
	}
	cvNamedWindow("test",0);
	cvShowImage("test",resultImage);
	cvWaitKey();
}

void playVideo() {
	CvCapture* capture = cvCreateFileCapture(video5_filePath);
	IplImage* frame;
	cvNamedWindow("test",0);
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame)break;
		cvShowImage("test",frame);
		cvWaitKey(100);
	}
}

int main5() {
	return 0;
}