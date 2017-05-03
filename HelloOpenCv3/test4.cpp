#include<iostream>
#include<opencv2\opencv.hpp>
#include<nonfree\features2d.hpp>
using namespace std;
using namespace cv;

char file4_filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
string test4_filename1 = "E:\\我的工程\\matlab\\test1.jpg";
string test4_filename2 = "E:\\我的工程\\matlab\\test2.jpg";

IplImage* useLBP() {
	IplImage* source = cvLoadImage(file4_filePath,0);
	IplImage* result = cvCreateImage(cvGetSize(source),8,1);
	int tmp[8] = { 0 };
	CvScalar s;
	IplImage * temp = cvCreateImage(cvGetSize(source), IPL_DEPTH_8U, 1);
	uchar *data = (uchar*)source->imageData;
	int step = source->widthStep;
	cout << "step" << step << endl;
	for (int i = 1; i<source->height - 1; i++)
		for (int j = 1; j<source->width - 1; j++)
		{
			int sum = 0;
			if (data[(i - 1)*step + j - 1]>data[i*step + j])
				tmp[0] = 1;
			else
				tmp[0] = 0;
			if (data[i*step + (j - 1)]>data[i*step + j])
				tmp[1] = 1;
			else
				tmp[1] = 0;
			if (data[(i + 1)*step + (j - 1)]>data[i*step + j])
				tmp[2] = 1;
			else
				tmp[2] = 0;
			if (data[(i + 1)*step + j]>data[i*step + j])
				tmp[3] = 1;
			else
				tmp[3] = 0;
			if (data[(i + 1)*step + (j + 1)]>data[i*step + j])
				tmp[4] = 1;
			else
				tmp[4] = 0;
			if (data[i*step + (j + 1)]>data[i*step + j])
				tmp[5] = 1;
			else
				tmp[5] = 0;
			if (data[(i - 1)*step + (j + 1)]>data[i*step + j])
				tmp[6] = 1;
			else
				tmp[6] = 0;
			if (data[(i - 1)*step + j]>data[i*step + j])
				tmp[7] = 1;
			else
				tmp[7] = 0;
			//计算LBP编码  
			s.val[0] = (tmp[0] * 1 + tmp[1] * 2 + tmp[2] * 4 + tmp[3] * 8 + tmp[4] * 16 + tmp[5] * 32 + tmp[6] * 64 + tmp[7] * 128);

			cvSet2D(result, i, j, s); //写入LBP图像
		}
	return result;
}

void SIFT1() {
	//Load Image   
	Mat c_src1 = imread(test4_filename1);
	Mat c_src2 = imread(test4_filename2);
	Mat src1 = imread(test4_filename1, CV_LOAD_IMAGE_GRAYSCALE);
	Mat src2 = imread(test4_filename2, CV_LOAD_IMAGE_GRAYSCALE);
	if (!src1.data || !src2.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return;
	}

	//sift feature detect  
	SiftFeatureDetector detector;
	std::vector<KeyPoint> kp1, kp2;

	detector.detect(src1, kp1);
	detector.detect(src2, kp2);
	SiftDescriptorExtractor extractor;
	Mat des1, des2;//descriptor  
	extractor.compute(src1, kp1, des1);
	extractor.compute(src2, kp2, des2);
	Mat res1, res2;
	int drawmode = DrawMatchesFlags::DRAW_RICH_KEYPOINTS;
	drawKeypoints(c_src1, kp1, res1, Scalar::all(-1), drawmode);//在内存中画出特征点  
	drawKeypoints(c_src2, kp2, res2, Scalar::all(-1), drawmode);
	cout << "size of description of Img1: " << kp1.size() << endl;
	cout << "size of description of Img2: " << kp2.size() << endl;

	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(des1, des2, matches);
	Mat img_match;
	drawMatches(src1, kp1, src2, kp2, matches, img_match);//,Scalar::all(-1),Scalar::all(-1),vector<char>(),drawmode);  
	cout << "number of matched points: " << matches.size() << endl;
//	namedWindow("matches",WINDOW_NORMAL);
	imshow("matches", img_match);
	cvWaitKey();
}

int main4() {
	SIFT1();
	return 0;
}