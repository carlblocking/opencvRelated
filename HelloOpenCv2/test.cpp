#include<iostream>
#include<string>
#include<time.h>
#include<opencv2\opencv.hpp>


using namespace std;
using namespace cv;
#define max_corner_count 100
void YuZhiFengGe() {
	string filePath = "E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg";
	Mat image = imread(filePath,0);
	Mat resultImage = image.clone();
	for (int i = 0; i < resultImage.rows;i++) {
		for (int j = 0; j < resultImage.cols;j++) {
			if (resultImage.at<uchar>(i, j) < 156 && resultImage.at<uchar>(i, j) > 106)
				resultImage.at<uchar>(i, j) = 255;
			if (resultImage.at<uchar>(i, j) >= 156)
				resultImage.at<uchar>(i, j) = 0;
		}
	}
	imshow("", image);
	imshow("result", resultImage);
	waitKey();
	image.release();
	resultImage.release();
	destroyAllWindows();
}

void ZhiZhenFangWenImage() {
	string filePath = "E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg";
	Mat image = imread(filePath, 0);
	uchar* data;
	for (int i = 0; i < image.rows;i++) {
		data = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols;j++) {
			data[j] = rand() % 256;
		}
	}
	imshow("",image);
	waitKey();
	image.release();
	destroyAllWindows();
}

void LOGImage() {
	string filePath = "E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg";
	Mat image = imread(filePath, 0);

	//µÕÕ®¬À≤®
	blur(image,image,Size(3,3),Point(-1,-1));
	//laplacian±ﬂ‘µºÏ≤‚
	Laplacian(image,image,CV_16S,3);
	convertScaleAbs(image,image);

	imshow("", image);
	waitKey();
	image.release();
	destroyAllWindows();
}

void SusanTest() {
	char filePath[] = "E:\\’’∆¨\\¥¥“‚’’∆¨\\facetothecity.jpg";
	IplImage *sourceImage, *corner1, *corner2;
	int cornerCount = max_corner_count;
	CvPoint2D32f corners[max_corner_count];
	double qualityLevel = 0.05;
	double minDistanc5=5;
	CvScalar color = CV_RGB(255,0,0);
	cvNamedWindow("image",CV_WINDOW_NORMAL);
	sourceImage = cvLoadImage(filePath,0);
	corner1 = cvCreateImage(cvGetSize(sourceImage),IPL_DEPTH_32F,1);
	corner2 = cvCreateImage(cvGetSize(sourceImage), IPL_DEPTH_32F, 1);
	cvGoodFeaturesToTrack(sourceImage,corner1,corner2,corners,&cornerCount,qualityLevel,minDistanc5,0);
	cout << "the number is " << cornerCount << endl;
	if (cornerCount>0) {
		for (int i = 0; i < cornerCount;i++) {
			cvCircle(sourceImage,cvPoint((int)(corners[i].x),(int)(corners[i].y)),6,color,2,CV_AA,0);
		}
	}
	cvShowImage("image",sourceImage);
	cvWaitKey();
	cvReleaseImage(&sourceImage);
	cvReleaseImage(&corner1);
	cvReleaseImage(&corner2);
	cvDestroyWindow("image");
}

void iteratorVisitImage() {
	Mat grayImage(600,600,CV_8UC1);
	Mat colorImage(600, 600, CV_8UC3);

	MatIterator_<uchar> grayit, grayend;
	for (grayit = grayImage.begin<uchar>(), grayend = grayImage.end<uchar>(); grayit != grayend; ++grayit) {
		*grayit = rand() % 255;
	}

	MatIterator_<Vec3b> colorit, colorend;
	for (colorit = colorImage.begin<Vec3b>(), colorend = colorImage.end<Vec3b>(); colorit != colorend;++colorit) {
		(*colorit)[0] = rand() % 255;
		(*colorit)[1] = rand() % 255;
		(*colorit)[2] = rand() % 255;
	}

	imshow("gray",grayImage);
	imshow("color",colorImage);
	waitKey();
}

void ZhiZhenFangWen2() {
	Mat grayImage(600,600,CV_8UC1);
	Mat colorImage(600,600,CV_8UC3);

	for (int i = 0; i < grayImage.rows;i++) {
		uchar* data = grayImage.ptr<uchar>(i);
		for (int j = 0; j < grayImage.cols;j++) {
			data[j] = (i + j) % 255;
		}
	}

	for (int i = 0; i < colorImage.rows;i++) {
		Vec3b* data = colorImage.ptr<Vec3b>(i);
		for (int j = 0; j < colorImage.cols;j++) {
			data[j][0] = rand() % 255;
			data[j][1] = rand() % 255;
			data[j][2] = rand() % 255;
		}
	}

	imshow("gray",grayImage);
	imshow("color",colorImage);
	waitKey();
}

void HuaQiGuaiDeXianTiao() {
	string filePath = "E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg";
	Mat sourceImage, verticalImage, horizonImage;
	sourceImage = imread(filePath);
	verticalImage = sourceImage.clone();
	horizonImage = sourceImage.clone();
	for (int i = 0; i < verticalImage.rows;i++) {
		Vec3b* data = verticalImage.ptr<Vec3b>(i);
		for (int j = 0; j < verticalImage.cols;j++) {
			if (((j%100/10))%2==1) {
				data[j][0] = 0;
				data[j][1] = 0;
				data[j][2] = 255;
			}
		}
	}
	for (int i = 0; i < horizonImage.rows; i++) {
		Vec3b* data = horizonImage.ptr<Vec3b>(i);
		for (int j = 0; j < horizonImage.cols; j++) {
			if (((i % 100 / 10)) % 2 == 1) {
				data[j][0] = 0;
				data[j][1] = 0;
				data[j][2] = 255;
			}
		}
	}

	imshow("vertical",verticalImage);
	imshow("horizon",horizonImage);
	waitKey();
}

void DanWeiJuZhen() {
	Mat a = Mat::eye(10,10,CV_32S);
	for (int i = 0; i < a.rows;i++) {
		uchar* data = a.ptr<uchar>(i);
		for (int j = 0; j < a.cols;j++) {
			cout << (int)data[j] << "\t";
		}
		cout << endl;
	}
}

void RegionOfInterest() {
	Mat img(Size(320,240),CV_8UC3);
	for (int i = 0; i < img.rows;i++) {
		Vec3b* data = img.ptr<Vec3b>(i);
		for (int j = 0; j < img.cols;j++) {
			data[j][0] = rand() % 255;
			data[j][1] = rand() % 255;
			data[j][2] = rand() % 255;
		}
	}
	Mat roi1(img, Rect(10, 10, 100, 100));
	imshow("source",img);
	imshow("roi",roi1);
	waitKey();
}

void PointTest() {
	Point2d point2d(5,5);
	Point3d point3d(1,2,3);
	cout << "point2d is "<<point2d<< endl;
	cout << "point3d is "<< point3d<<endl;
}

void readCannyVedio() {
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* image;
	cvNamedWindow("canny",CV_WINDOW_NORMAL);
	while (1) {
		image = cvQueryFrame(capture);
		if (!image)break;
		cvShowImage("canny",image);
		waitKey(30);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("canny");
}

void cannyTest() {
	string filePath = "E:\\’’∆¨\\¥¥“‚’’∆¨\\facetothecity.jpg";
	char filePath2[] = "E:\\’’∆¨\\¥¥“‚’’∆¨\\facetothecity.jpg";

	IplImage* image = cvLoadImage(filePath2,0);
	cvCanny(image,image,50,150);
	cvNamedWindow("IplImage",CV_WINDOW_NORMAL);
	cvShowImage("IplImage",image);

	Mat image2 = imread(filePath,0);
	Canny(image2,image2,50,150);
	imshow("mat",image2);

	waitKey();

	image2.release();
	cvReleaseImage(&image);
	destroyAllWindows();
}


int main1() {
	int i;
	srand(time(0));
	cin >> i;
	switch (i)
	{
	case 1:
		YuZhiFengGe();
		break;
	case 2:
		ZhiZhenFangWenImage();
		break;
	case 3:
		LOGImage();
		break;
	case 4:
		SusanTest();
		break;
	case 5:
		iteratorVisitImage();
		break;
	case 6:
		ZhiZhenFangWen2();
		break;
	case 7:
		HuaQiGuaiDeXianTiao();
		break;
	case 8:
		DanWeiJuZhen();
		break;
	case 9:
		RegionOfInterest();
		break;
	case 10:
		PointTest();
		break;
	case 11:
		break;
	case 12:
		cannyTest();
		break;
	default:
		break;
	}
	return 0;
}