#include<iostream>
#include<opencv2\opencv.hpp>
#include<cv.h>

using namespace std;
using namespace cv;

char main7_fileName[] = "E:\\照片\\创意照片\\guitar.jpg";
char source1_image_main7[] = "E:\\照片\\创意照片\\test1.jpg";

void main7_test1() {
	IplImage* source_image = cvLoadImage(main7_fileName);
	CvSize size = cvGetSize(source_image);

	//分离通道 8位1channel
	IplImage* blue_channel = cvCreateImage(size,IPL_DEPTH_8U,1);
	IplImage* green_channel = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* red_channel = cvCreateImage(size, IPL_DEPTH_8U, 1);
	cvSplit(source_image,blue_channel,green_channel,red_channel,0);
	//创建不同通道合成的图片 8位3channel
	IplImage* blueImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* greenImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* redImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	//合并通道
	cvMerge(blue_channel,0,0,0,blueImage);
	cvMerge(0,green_channel,0,0,greenImage);
	cvMerge(0,0,red_channel,0,redImage);
	//显示图片
	cvNamedWindow("red",WINDOW_NORMAL);
	cvNamedWindow("green",WINDOW_NORMAL);
	cvNamedWindow("blue",WINDOW_NORMAL);

	cvShowImage("red",redImage);
	cvShowImage("green",greenImage);
	cvShowImage("blue",blueImage);

	cvWaitKey(0);
}

void main7_test2() {
	IplImage* source = cvLoadImage(main7_fileName);

	IplImage* hsv = cvCreateImage(cvGetSize(source),8,3);

	IplImage* h_plane = cvCreateImage(cvGetSize(source),8,1);
	IplImage* s_plane = cvCreateImage(cvGetSize(source), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(source), 8, 1);

	IplImage* planes[] = {h_plane,s_plane};

	//H分量划分为16个等级，S分量划分为8个等级
	int h_bins = 16, s_bins = 8;
	int hist_size[] = {h_bins,s_bins};

	//H风量的变化范围
	float h_ranges[] = {0,180};
	//S变量的变化范围
	float s_ranges[] = {0,255};
	float* ranges[] = {h_ranges,s_ranges};

	//输入图像转化为HSV图像并分离通道
	cvCvtColor(source,hsv,CV_BGR2HSV);
	cvCvtPixToPlane(hsv,h_plane,s_plane,v_plane,0);

	//创建直方图，二维，每个维度上均分
	CvHistogram* hist = cvCreateHist(2,hist_size,CV_HIST_ARRAY,ranges);
	//根据HS两个平面数据统计直方图
	cvCalcHist(planes,hist);

	//获取直方图统计的最大值，用于动态显示直方图
	float max_value;
	cvGetMinMaxHistValue(hist,0,&max_value);
	//设置直方图显示图像 
	int height = 240;
	int width = (h_bins*s_bins * 6);
	IplImage* hist_img = cvCreateImage(cvSize(width, height), 8, 3);
	cvZero(hist_img);

	/** 用来进行HSV到RGB颜色转换的临时单位图像 */
	IplImage * hsv_color = cvCreateImage(cvSize(1, 1), 8, 3);
	IplImage * rgb_color = cvCreateImage(cvSize(1, 1), 8, 3);
	int bin_w = width / (h_bins * s_bins);
	for (int h = 0; h < h_bins; h++)
	{
		for (int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度 */
			float bin_val = cvQueryHistValue_2D(hist, h, s);
			int intensity = cvRound(bin_val*height / max_value);

			/** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
			cvSet2D(hsv_color, 0, 0, cvScalar(h*180.f / h_bins, s*255.f / s_bins, 255, 0));
			cvCvtColor(hsv_color, rgb_color, CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color, 0, 0);

			cvRectangle(hist_img, cvPoint(i*bin_w, height),
				cvPoint((i + 1)*bin_w, height - intensity),
				color, -1, 8, 0);
		}
	}

	cvNamedWindow("Source", 1);
	cvShowImage("Source", source);

	cvNamedWindow("H-S Histogram", 1);
	cvShowImage("H-S Histogram", hist_img);

	cvWaitKey(0);

}

IplImage* test(IplImage* source) {
	IplImage* hsv = cvCreateImage(cvGetSize(source), 8, 3);
	IplImage* h_plane = cvCreateImage(cvGetSize(source), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(source), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(source), 8, 1);
	IplImage* planes[] = { h_plane,s_plane };

	//H分量划分为16个等级，S分量划分为8个等级
	int h_bins = 16, s_bins = 8;
	int hist_size[] = { h_bins,s_bins };

	//H风量的变化范围
	float h_ranges[] = { 0,180 };

	//S变量的变化范围
	float s_ranges[] = { 0,255 };
	float* ranges[] = { h_ranges,s_ranges };

	//输入图像转化为HSV图像并分离通道
	cvCvtColor(source, hsv, CV_BGR2HSV);
	cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);

	//创建直方图，二维，每个维度上均分
	CvHistogram* hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges);

	//根据HS两个平面数据统计直方图
	cvCalcHist(planes, hist);

	//获取直方图统计的最大值，用于动态显示直方图
	float max_value;
	cvGetMinMaxHistValue(hist, 0, &max_value);

	//设置直方图显示图像 
	int height = 240;
	int width = (h_bins*s_bins * 6);
	IplImage* hist_img = cvCreateImage(cvSize(width, height), 8, 3);
	cvZero(hist_img);

	/** 用来进行HSV到RGB颜色转换的临时单位图像 */
	IplImage * hsv_color = cvCreateImage(cvSize(1, 1), 8, 3);
	IplImage * rgb_color = cvCreateImage(cvSize(1, 1), 8, 3);
	int bin_w = width / (h_bins * s_bins);
	for (int h = 0; h < h_bins; h++){
		for (int s = 0; s < s_bins; s++){
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度 */
			float bin_val = cvQueryHistValue_2D(hist, h, s);
			int intensity = cvRound(bin_val*height / max_value);

			/** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
			cvSet2D(hsv_color, 0, 0, cvScalar(h*180.f / h_bins, s*255.f / s_bins, 255, 0));
			cvCvtColor(hsv_color, rgb_color, CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color, 0, 0);

			cvRectangle(hist_img, cvPoint(i*bin_w, height),
				cvPoint((i + 1)*bin_w, height - intensity),
				color, -1, 8, 0);
		}
	}
	return hist_img;
}

void main7_test3() {
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* frame;
	IplImage* hist;
	cvNamedWindow("hist",CV_WINDOW_NORMAL);
	cvNamedWindow("video",CV_WINDOW_NORMAL);
	while (1)
	{
		frame = cvQueryFrame(capture);
		//hist = test(frame);
		frame = test(frame);
		if (!frame)break;
		cvShowImage("video",frame);
		cvShowImage("hist",hist);
		if (cvWaitKey(100) == '5')break;
	}
}

int main7() {
	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* frame;
	//IplImage* hist;
	//cvNamedWindow("hist", CV_WINDOW_NORMAL);
	cvNamedWindow("video", CV_WINDOW_NORMAL);
	while (1)
	{
		frame = cvQueryFrame(capture);
		//hist = test(frame);
		frame = test(frame);
		if (!frame)break;
		cvShowImage("video", frame);
		//cvShowImage("hist", hist);
		if (cvWaitKey(33) == '5')break;
		//cvReleaseImage(&hist);
	}
	cvReleaseImage(&frame);
	//cvReleaseImage(&hist);
	cvDestroyAllWindows();
	return 0;
}