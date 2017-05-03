#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main8_fileName[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
char source_image_main8[] = "E:\\��Ƭ\\������Ƭ\\test1.jpg";

void createImage() {
	IplImage* Image = cvCreateImage(cvSize(200,200),8,1);
	cvZero(Image);
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvShowImage("test",Image);
	cvWaitKey(0);
}

void tuXiangXuanZhuan() {
	Mat sourceImage = imread("E:\\��Ƭ\\������Ƭ\\guitar.jpg");
	if (sourceImage.empty()) return;
	Point2f center = Point2f(sourceImage.cols/2,sourceImage.rows/2);
	double angle = 30;//��ת�Ƕ�
	double scale = 0.5;//���ų߶�
	Mat resultImage;
	resultImage = getRotationMatrix2D(center,angle,scale);//���б任
	Mat finalImage;
	warpAffine(sourceImage,finalImage,resultImage,sourceImage.size());//�ʾ�ǳ���Ҫ�����������ں�
	namedWindow("test1",WINDOW_NORMAL);
	namedWindow("test", WINDOW_NORMAL);
	imshow("test1", sourceImage);
	imshow("test", finalImage);
	waitKey(0);
}

void totateImage(IplImage* img, IplImage* rotateImage,double scale=1, int degree=0) {
	//��ת����Ϊͼ������
	CvPoint2D32f center;
	center.x = float(img->width/2.0+0.5);
	center.y = float(img->height/2.0+0.5);
	//�����ά��ת�ķ���任����
	float m[6];
	CvMat M = cvMat(2,3,CV_32F,m);
	cv2DRotationMatrix(center,degree,scale,&M);
	//�任ͼ�񣬲��ú�ɫ���
	cvWarpAffine(img,rotateImage,&M);
}

int main() {
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* frame;
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame)break;
		totateImage(frame, frame,0.5);
		cvShowImage("test",frame);
		cvWaitKey(60);
	}
	return 0;
}