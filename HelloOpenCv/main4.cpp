#include<iostream>
#include<opencv2\opencv.hpp>
#include<string>
#include<time.h>

using namespace std;
using namespace cv;

string fileName1 = "E:\\照片\\创意照片\\guitar.jpg";
char fileName11[] = "E:\\照片\\创意照片\\guitar.jpg";
char videoName1[] = "E:\\视频\\九九\\IMG_2107.MOV";
char catImage[] = "E:\\我的工程\\算法\\HelloOpenCv\\cat.jpg";
char sameImage1[] = "E:\\照片\\创意照片\\test1.png";
char sameImage2[] = "E:\\照片\\创意照片\\test2.png";

float getElemet() {
	CvMat* mat = cvCreateMat(5,5,CV_32FC1);
	float elemen_3_2 = CV_MAT_ELEM(*mat,float,3,2);
	return elemen_3_2;
}

float inputElement() {
	CvMat* mat = cvCreateMat(3,2,CV_32FC1);
	float element_3_2 = 7.7;
	*((float*)CV_MAT_ELEM_PTR(*mat,3,2)) = element_3_2;
}

float sum(const CvMat* mat) {
	float s = 0.0f;
	for (int row = 0; row < mat->rows;row++) {
		const float* ptr = (const float*)(mat->data.ptr + row*mat->step);
		for (int col = 0; col < mat->cols;col++) {
			s += *ptr++;
		}
	}
	return s;
}

//最大化HSV图像“S”和“V”部分
IplImage* saturate_sv(IplImage* image) {
	for (int y = 0; y < image->height;y++) {
		uchar* ptr = (uchar*)(image->imageData+y*image->widthStep);
		for (int x = 0; x < image->width;x++) {
			ptr[3 * x + 1] = 255;
			ptr[3 * x + 2] = 255;
		}
	}
	return image;
}

void test1() {
	IplImage* source = cvLoadImage(fileName11);
	IplImage* output = saturate_sv(source);
	cvNamedWindow("test", CV_WINDOW_NORMAL);
	cvShowImage("test", output);
	waitKey(0);
	//cvReleaseImage(&output);
	//cvReleaseImage(&source);
	//cvDestroyWindow("test");
}

//画出图像中感兴趣的区域，并着色
void catFace() {
	IplImage* source = cvLoadImage(catImage);
	/**设置感兴趣区域的起点以及长宽*/
	int x = 100;
	int y = 100;
	int height = 150;
	int width = 100;

	//设置像素值
	int add = 150;

	cvSetImageROI(source,cvRect(x,y,width,height));
	cvAddS(source,cvScalar(add),source);
	cvResetImageROI(source);

	cvNamedWindow("test",1);
	cvShowImage("test",source);
	cvWaitKey();
}

void imageAdd() {
	IplImage* sourceImage1 = cvLoadImage(sameImage1);
	IplImage* sourceImage2 = cvLoadImage(sameImage2);
	IplImage* cvAddImage=cvCreateImage(cvGetSize(sourceImage1),IPL_DEPTH_8U,3);
	IplImage* cvAddWeightedImage= cvCreateImage(cvGetSize(sourceImage1), IPL_DEPTH_8U, 3);
	cvAdd(sourceImage1,sourceImage2,cvAddImage);//简单的相加
	cvAddWeighted(sourceImage1,0.2,sourceImage2,0.4,0,cvAddWeightedImage);//带权值的相加

	cvNamedWindow("simpleAdd",CV_WINDOW_NORMAL);
	cvNamedWindow("weightedAdd",CV_WINDOW_NORMAL);
	cvShowImage("simpleAdd",cvAddImage);
	cvShowImage("weightedAdd",cvAddWeightedImage);
	waitKey();
}

void imageAdd2() {
	IplImage* sourceImage1 = cvLoadImage(sameImage1);
	IplImage* sourceImage2 = cvLoadImage(sameImage2);

	int x = 100; int y = 100; int width = 100; int height = 50;
	double alpha = 0.3; double beta = 0.4; //alpha beta之和不大于1

	cvSetImageROI(sourceImage1,cvRect(0,0,width,height));
	cvSetImageROI(sourceImage2,cvRect(x,y,width,height));

	cvAddWeighted(sourceImage1,alpha,sourceImage2,beta,0.0,sourceImage1);
	cvResetImageROI(sourceImage1);
	
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvShowImage("test",sourceImage1);

	cvWaitKey();
}

void createFile() {
	CvFileStorage* fs = cvOpenFileStorage("C:\\Users\\xxw\\Desktop\\cfg.xml",0,CV_STORAGE_WRITE);
	cvWriteInt(fs,"frame_count",10);
	cvStartWriteStruct(fs,"frame_size",CV_NODE_SEQ);
	cvWriteInt(fs,0,320);
	cvWriteInt(fs,0,100);
	cvEndWriteStruct(fs);
	cvReleaseFileStorage(&fs);
}

int main() {
	int i;
	cin >> i;
	switch (i)
	{
	case 1:;
		test1();
		break;
	case 2:
		break;
	case 3:
		createFile();
		break;
	}
	return 0;
}