#include<iostream>
#include<string>
#include<time.h>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat image = imread("E:\\’’∆¨\\¥¥“‚’’∆¨\\guitar.jpg");
	imshow("",image);
	waitKey();
	image.release();
	destroyAllWindows();
	return 0;
}