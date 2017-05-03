#include<iostream>
#include<opencv2\opencv.hpp>
#include<string>
#include<time.h>

using namespace std;
using namespace cv;

string fileName = "E:\\照片\\创意照片\\guitar.jpg";
char fileName1[] = "E:\\照片\\创意照片\\guitar.jpg";
char videoName[] = "E:\\视频\\九九\\IMG_2107.MOV";

void createRandomColorImageVideo() {
	srand(time(0));
	namedWindow("test",WINDOW_NORMAL);
	while (1)
	{
		int color1 = rand() % 256;
		int color2 = rand() % 256;
		int color3 = rand() % 256;
		cout << color1<<"\t"<<color2<<"\t"<< color3<<endl;
		Mat image(200, 200, CV_8UC3,Scalar(color1, color2, color3));
		imshow("test",image);
		waitKey(1000);
	}
}

void showRandGrayImage() {
	srand(time(0));
	namedWindow("test",WINDOW_NORMAL);
	while (1)
	{
		int grayValue = rand() % 256;
		Mat newImage(200, 200, CV_8UC1);
		for (int i = 0; i < newImage.rows; i++){
			for (int j = 0; j < newImage.cols; j++){
				newImage.at<uchar>(i,j) = grayValue;
			}
		}
		imshow("test",newImage);
		waitKey(1000);
	}
}

//play video from file
void playVedio() {
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	CvCapture* capture = cvCreateFileCapture(videoName);
	IplImage* frame;
	while(1) {
		frame = cvQueryFrame(capture);
		if (!frame)break;
		cvShowImage("test",frame);
		char c = cvWaitKey(33);
		if (c == '1')break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("test");
}

//play from camera
void playVideo2() {
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame)break;
		cvShowImage("test",frame);
		char c = cvWaitKey(33);
		if (c == '1')break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("test");
}

//加载图像并进行平滑处理
void smoothChange(IplImage* image) {
	//create window to show the input image and output image
	cvNamedWindow("out",CV_WINDOW_NORMAL);
	cvNamedWindow("in",CV_WINDOW_NORMAL);

	//show input image
	cvShowImage("in",image);

	/**create smoothed image
	参数1：尺寸
	参数2：每个像素的位数
	参数3：通道数**/
	IplImage* out = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);

	/**do the smooth
	参数1：输入图像
	参数2：输出图像
	参数3：平滑的类型
	参数4、5：平滑块的尺寸**/
	cvSmooth(image,out,CV_GAUSSIAN,3,3);

	//显示平滑后的图像
	cvShowImage("out",out);

	//释放图像资源
	cvReleaseImage(&out);
	cvWaitKey(0);
	cvDestroyWindow("in");
	cvDestroyWindow("out");
}

//缩小一半的图像
IplImage* doPyrDown(IplImage* in, int filter=CV_GAUSSIAN_5x5){
	//make sure input image can be divided by 2
	assert(in->width%2==0&&in->height%2==0);

	IplImage* out = cvCreateImage(cvSize(in->width/2,in->height/2),in->depth,in->nChannels);
	cvPyrDown(in,out);
	return out;
}

//Canny边缘检测输出写入的灰度图像
IplImage* doCanny(IplImage* in , double lowThresh,double highThresh,double aperture) {
	//首先看是不是灰度图像，如果不是的话直接退出
	if (in->nChannels != 1)return 0;
	IplImage* out = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,1);
	cvCanny(in,out,lowThresh,highThresh,aperture);
	return out;
}

//将彩色图片转为灰度图片
IplImage* turnToGray(IplImage* input) {
	IplImage* output = cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);
	cvCvtColor(input,output,CV_BGR2GRAY);
	return output;
}

int main3() {
	int i;
	cin >> i;
	switch (i)
	{
	//case 1:
	//	IplImage* image = cvLoadImage(fileName1,0);
	//	IplImage* newImage = doCanny(image,10,100,3);
	//	cvNamedWindow("in",CV_WINDOW_NORMAL);
	//	cvNamedWindow("out",CV_WINDOW_NORMAL);
	//	cvShowImage("in",image);
	//	cvShowImage("out",newImage);
	//	waitKey(0);
	//	cvReleaseImage(&image);
	//	cvReleaseImage(&newImage);
	//	cvDestroyWindow("in");
	//	cvDestroyWindow("out");
	//	break;
	case 2:
		cvNamedWindow("test",CV_WINDOW_NORMAL);
		CvCapture* capture = cvCreateCameraCapture(0);
		IplImage* frame;
		IplImage* frame1;
		IplImage* frame2;
		while (1)
		{
			frame = cvQueryFrame(capture);
			if (!frame)break;
			frame1 = turnToGray(frame);
			frame2 = doCanny(frame1,30,100,3);
			cvShowImage("test",frame2);
			char c = waitKey(33);
			if (c == '5')break;
		}
		cvReleaseCapture(&capture);
		cvDestroyWindow("test");
		break;
	}
	return 0;
}