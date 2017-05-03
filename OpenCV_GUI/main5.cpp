#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main5_fileName[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
char source_image_main5[] = "E:\\��Ƭ\\������Ƭ\\test1.jpg";

//http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
void draw1() {
	Mat source, result;
	source = imread(main5_fileName);

	///�ָ��3����ͨ��ͼ��RGB
	vector<Mat> rgb_planes;
	split(source, rgb_planes);

	///�趨bin����Ŀ
	int histSize = 255;

	///�趨ȡֵ��Χ(R,G,B)
	float range[] = { 0,255 };
	const float*  histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	///����ֱ��ͼ
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	///����ֱ��ͼ����
	int hist_w = 400;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	/// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);
}

//http://blog.csdn.net/xiaowei_cqu/article/details/7600666
void draw2() {
	IplImage* source = cvLoadImage(main5_fileName);
	IplImage* gray_plane = cvCreateImage(cvGetSize(source),8,1);
	cvCvtColor(source,gray_plane,CV_RGB2GRAY);

	int hist_size = 256;//ֱ��ͼ�ߴ�
	int hist_height = 256;
	float range[] = {0,255};//�Ҷȼ��ķ�Χ
	float* ranges[] = {range};
	//����һάֱ��ͼ��ͳ��ͼ����[0,255]���صľ��ȷֲ�
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);
	//����Ҷ�ͼ��һάֱ��ͼ
	cvCalcHist(&gray_plane,gray_hist,0,0);
	//��һ��ֱ��ͼ
	cvNormalizeHist(gray_hist,1.0);

	int scale = 2;
	//����һ��һάֱ��ͼ�ġ�ͼ����������Ϊ�Ҷȼ���������Ϊ���ظ�����*scale��  
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale, hist_height), 8, 3);
	cvZero(hist_image);
	//ͳ��ֱ��ͼ�е����ֱ����  
	float max_value = 0;
	cvGetMinMaxHistValue(gray_hist, 0, &max_value, 0, 0);

	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��  
	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist, i); //����i�ĸ���  
		int intensity = cvRound(bin_val*hist_height / max_value);  //Ҫ���Ƶĸ߶�  
		cvRectangle(hist_image,
			cvPoint(i*scale, hist_height - 1),
			cvPoint((i + 1)*scale - 1, hist_height - intensity),
			CV_RGB(255, 255, 255));
	}
	cvNamedWindow("GraySource", 1);
	cvShowImage("GraySource", gray_plane);
	cvNamedWindow("H-S Histogram", 1);
	cvShowImage("H-S Histogram", hist_image);

	cvWaitKey(0);
}

int main5() {
	draw2();
	return 0;
}