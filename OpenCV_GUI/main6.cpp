#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main6_fileName[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
char source_image_main6[] = "E:\\��Ƭ\\������Ƭ\\test1.jpg";

void test1() {
	Mat source_image, result_image;
	source_image = imread(main6_fileName);
	if (!source_image.data) { return; }

	//תΪ�Ҷ�ͼ
	cvtColor(source_image,source_image,CV_BGR2GRAY);

	//Ӧ��ֱ��ͼ���⻯(������ǿ�Աȶȵ�)
	equalizeHist(source_image,result_image);

	//��ʾ���
	namedWindow("sourceImage",WINDOW_NORMAL);
	namedWindow("resultImage",WINDOW_NORMAL);
	imshow("sourceImage",source_image);
	imshow("resultImage",result_image);
	waitKey();
}

void test2() {
	//ʹ��Mat����ֱ��ͼ
	Mat source, result;
	source = imread(main6_fileName);
	if (!source.data)return;

	//�ָ������ͨ��
	vector<Mat> rgb_planes;
	split(source, rgb_planes);

	//�趨bin����Ŀ
	int histSize = 255;

	//�趨ȡֵ��Χ(RGB)
	float range[] = { 0,255 };
	const float* ranges = range;

	Mat r_hist, g_hist, b_hist;

	//����ֱ��ͼ(�˴���rͨ��Ϊ��)
	calcHist(&rgb_planes[0],1,0,Mat(),r_hist,1,&histSize,&ranges);

	//����ֱ��ͼ����
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound((double)hist_w/histSize);

	Mat histImage(hist_w,hist_h,CV_8UC3,Scalar(0,0,0));

	//��ֱ��ͼ��һ������Χ[0,histImage,rows]
	normalize(r_hist,r_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());

	//��ֱ��ͼ�ϻ���ֱ��ͼ
	for (int i = 1; i < histSize;i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);
}

void test3() {
	IplImage * gray_plane= cvLoadImage(main6_fileName);

	IplImage* r_plane = cvCreateImage(cvGetSize(gray_plane),IPL_DEPTH_8U,1);
	IplImage* g_plane = cvCreateImage(cvGetSize(gray_plane), IPL_DEPTH_8U, 1);
	IplImage* b_plane = cvCreateImage(cvGetSize(gray_plane), IPL_DEPTH_8U, 1);
	cvSplit(gray_plane, r_plane, g_plane, b_plane,NULL);

	int hist_size = 256;    //ֱ��ͼ�ߴ�  
	int hist_height = 256;
	float range[] = { 0,255 };  //�Ҷȼ��ķ�Χ  
	float* ranges[] = { range };
	//����һάֱ��ͼ��ͳ��ͼ����[0 255]���صľ��ȷֲ�  
	CvHistogram* gray_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	//����Ҷ�ͼ���һάֱ��ͼ  
	cvCalcHist(&r_plane, gray_hist, 0, 0);
	cvCalcHist(&g_plane, gray_hist, 0, 0);
	cvCalcHist(&b_plane, gray_hist, 0, 0);
	//��һ��ֱ��ͼ  
	cvNormalizeHist(gray_hist, 1.0);

	int scale = 2;
	//����һ��һάֱ��ͼ�ġ�ͼ����������Ϊ�Ҷȼ���������Ϊ���ظ�����*scale��  
	IplImage* hist_image1 = cvCreateImage(cvSize(hist_size*scale, hist_height), 8, 3);
	cvZero(hist_image1);

	IplImage* hist_image2 = cvCreateImage(cvSize(hist_size*scale, hist_height), 8, 3);
	cvZero(hist_image2);

	IplImage* hist_image3 = cvCreateImage(cvSize(hist_size*scale, hist_height), 8, 3);
	cvZero(hist_image3);
	//ͳ��ֱ��ͼ�е����ֱ����  
	float max_value = 0;
	cvGetMinMaxHistValue(gray_hist, 0, &max_value, 0, 0);

	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��  
	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist, i); //����i�ĸ���  
		int intensity = cvRound(bin_val*hist_height / max_value);  //Ҫ���Ƶĸ߶�  
		cvRectangle(hist_image1,cvPoint(i*scale, hist_height - 1),
			cvPoint((i + 1)*scale - 1, hist_height - intensity),
			CV_RGB(255, 0, 0));
		cvRectangle(hist_image2, cvPoint(i*scale, hist_height - 1),
			cvPoint((i + 1)*scale - 1, hist_height - intensity),
			CV_RGB(0, 255, 0));
		cvRectangle(hist_image3, cvPoint(i*scale, hist_height - 1),
			cvPoint((i + 1)*scale - 1, hist_height - intensity),
			CV_RGB(0, 0, 255));
	}

	cvNamedWindow("red", 1);
	cvNamedWindow("green", 1);
	cvNamedWindow("blue", 1);


	cvShowImage("red", hist_image1);
	cvShowImage("green", hist_image2);
	cvShowImage("blue", hist_image3);

	cvWaitKey(0);
}



int main6() {
	int i;
	cout << "����������ѡ��Ҫ�����ĺ���" << endl;
	cin >> i;
	switch (i)
	{
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	}
	return 0;
}