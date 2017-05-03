#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main5_fileName[] = "E:\\照片\\创意照片\\guitar.jpg";
char source_image_main5[] = "E:\\照片\\创意照片\\test1.jpg";

//http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
void draw1() {
	Mat source, result;
	source = imread(main5_fileName);

	///分割成3个单通道图像RGB
	vector<Mat> rgb_planes;
	split(source, rgb_planes);

	///设定bin的数目
	int histSize = 255;

	///设定取值范围(R,G,B)
	float range[] = { 0,255 };
	const float*  histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	///计算直方图
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	///创建直方图画布
	int hist_w = 400;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// 将直方图归一化到范围 [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// 在直方图画布上画出直方图
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

	/// 显示直方图
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);
}

//http://blog.csdn.net/xiaowei_cqu/article/details/7600666
void draw2() {
	IplImage* source = cvLoadImage(main5_fileName);
	IplImage* gray_plane = cvCreateImage(cvGetSize(source),8,1);
	cvCvtColor(source,gray_plane,CV_RGB2GRAY);

	int hist_size = 256;//直方图尺寸
	int hist_height = 256;
	float range[] = {0,255};//灰度级的范围
	float* ranges[] = {range};
	//创建一维直方图，统计图像在[0,255]像素的均匀分布
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);
	//计算灰度图的一维直方图
	cvCalcHist(&gray_plane,gray_hist,0,0);
	//归一化直方图
	cvNormalizeHist(gray_hist,1.0);

	int scale = 2;
	//创建一张一维直方图的“图”，横坐标为灰度级，纵坐标为像素个数（*scale）  
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale, hist_height), 8, 3);
	cvZero(hist_image);
	//统计直方图中的最大直方块  
	float max_value = 0;
	cvGetMinMaxHistValue(gray_hist, 0, &max_value, 0, 0);

	//分别将每个直方块的值绘制到图中  
	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist, i); //像素i的概率  
		int intensity = cvRound(bin_val*hist_height / max_value);  //要绘制的高度  
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