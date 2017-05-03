#include<iostream>
#include<string>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

void UseMatOpenImage() {
	string filePath = "E:\\照片\\创意照片\\guitar.jpg";
	Mat image = imread(filePath);
	if (image.empty()) {
		cout << "the file does not exist" << endl;
	}
	imshow("image",image);
	waitKey();
}

void UseIplImageOpendImage() {
	char filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
	/*cvLoadImage中isColor默认为1，即彩色图像（3通道）
								-1，原图像
								0，灰度图像（单通道）*/
	IplImage* image = cvLoadImage(filePath);
	cvNamedWindow("image",CV_WINDOW_NORMAL);
	cvShowImage("image", image);
	waitKey();
	cvReleaseImage(&image);
	cvDestroyWindow("image");
}

void loadVideo() {
	char filePath[] = "E:\\视频\\九九\\IMG_2107.MOV";
	//抓取每一帧用
	CvCapture* capture = cvCreateFileCapture(filePath);
	//每一帧用image来显示
	IplImage* image;
	//创建窗体存放image
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	while (1) {
		image = cvQueryFrame(capture);
		if (!image)break;
		cvShowImage("test",image);
		waitKey(20);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("test");
}

void loadCameraVideo() {
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* image;
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	while (1)
	{
		image = cvQueryFrame(capture);
		if (!image)break;
		cvShowImage("test",image);
		waitKey(30);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("test");
}

void loadMatData() {
	double data[18] = {1,2,3,4,5,6,
					   45,12,56,12,56,45,
					   45,6,5,123,12,2};
	CvMat mat;
	cvInitMatHeader(&mat,3,6,CV_32FC1,data);
	for (int i = 0; i < mat.rows;i++) {
		for (int j = 0; j < mat.cols;j++) {
			double value = cvGetReal2D(&mat,i,j);
			cout << value << "\t";
		}
		cout << endl;
	}
}

void loadMatData2() {
	double data[18] = { 1,2,3,4,5,6,
		45,12,56,12,56,45,
		45,6,5,123,12,2 };
	CvMat mat;
	cvInitMatHeader(&mat,3,3,CV_32FC2,data);
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			CvScalar value = cvGet2D(&mat,i,j);
			cout << value.val[0] << "|" << value.val[1] << "\t";
		}
		cout << endl;
	}
}

void IplImageData() {
	char filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
	IplImage* image = cvLoadImage(filePath);
	//当origin为0的时候，图像正常显示，当为1的时候，倒着显示
	//image->origin = 1;
	//IplImage* newImage = cvCreateImage(cvSize(30,30),IPL_DEPTH_32S,1);
	//cout << image->nChannels;//图片通道

	//for (int x = 0; x < image->height;x++) {
	//	uchar* data = (uchar*)(image->imageData + x*image->widthStep);
	//	for (int y = 0; y < image->width;y++) {
	//		data[3 * y + 0] = 0;//b
	//		//data[3 * y + 1] = 0;//g
	//		//data[3 * y + 2] =//r
	//	}
	//}

	//截取出感兴趣区域
	CvRect rect;
	rect.x = 10;
	rect.y = 10;
	rect.width = 200;
	rect.height = 200;
	cvSetImageROI(image,rect);
	//cvResetImageROI(image);

	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvShowImage("test",image);
	waitKey();

	cvReleaseImage(&image);
	cvDestroyWindow("test");
}


int main1() {
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		UseIplImageOpendImage();
		break;
	case 2:
		UseMatOpenImage();
		break;
	case 3:
		loadVideo();
		break;
	case 4:
		loadCameraVideo();
		break;
	case 5:
		loadMatData();
		break;
	case 6:
		loadMatData2();
		break;
	case 7:
		IplImageData();
		break;
	default:
		break;
	}
	return 0;
}