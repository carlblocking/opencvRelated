#include<iostream>
#include<ctime>
#include<vector>
#include<string>

#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;


//腐蚀操作
void erosionTest() {
	Mat source = imread("E:\\照片\\创意照片\\facetothecity.jpg");
	namedWindow("source", WINDOW_NORMAL);
	imshow("source", source);
	//腐蚀操作
	//getStructuringElement函数的返回值为指定形状和尺寸的结构元素
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat result;
	erode(source,result,element);
	//显示结果
	namedWindow("result",WINDOW_NORMAL);
	imshow("result",result);

	waitKey(0);
}

void blurTest() {
	Mat source = imread("E:\\照片\\创意照片\\facetothecity.jpg");
	namedWindow("source", WINDOW_NORMAL);
	imshow("source", source);

	Mat result;
	blur(source,result,Size(7,7));

	namedWindow("result", WINDOW_NORMAL);
	imshow("result", result);

	waitKey(0);
}

void canntTest() {
	Mat source = imread("E:\\照片\\创意照片\\facetothecity.jpg");
	Mat gray;
	Mat result;
	//转为灰度图像
	cvtColor(source,gray,CV_BGR2GRAY);
	//使用3*3的内核降噪
	blur(gray,result,Size(3,3));
	//使用canny函数检测边缘
	Canny(result,result,3,9,3);
	namedWindow("result",WINDOW_NORMAL);
	imshow("result",result);
	waitKey(0);
}

void readVideoFromCamTest() {
	VideoCapture capture(0);//将参数改为文件路径名即可访问文件
	while (1)
	{
		Mat frame;
		capture >> frame;
		imshow("test",frame);
		waitKey(30);
	}
}

Mat createMat() {
	Mat result(255,255,CV_8UC3);
	srand(time(0));
	int tmp1 = rand() % 255;
	int tmp2 = rand() % 255;
	int tmp3 = rand() % 255;
	for (int i = 0; i < result.rows;++i) {
		for (int j = 0; j < result.cols;++j) {
			Vec3b& v1=result.at<Vec3b>(i, j);
			v1[0] = tmp1;
			v1[1] = tmp2;
			v1[2] = tmp3;
		}
	}
	return result;
}

void createImages() {
	Mat source;
	vector<int> vInt;
	namedWindow("test",WINDOW_NORMAL);
	vInt.push_back(CV_IMWRITE_JPEG_QUALITY);
	vInt.push_back(95);
	int i = 0;
	while (1)
	{
		i += 1;
		source = createMat();
		imshow("test",source);
		string path = "C:/Users/xxw/Desktop/test/" + to_string(i) + ".jpeg";
		imwrite(path,source,vInt);
		if (waitKey(33) == 'q')
			break;
	}
}

//滑动条相关
const int maxValue = 100;//滑动条最大值
int value1;//滑动条对应变量

//回调函数
void on_TrackBar(int, void*) {
	cout << value1 << endl;
}

void createBarTest() {
	//设置滑动条初始值
	value1 = 1;
	namedWindow("test",WINDOW_NORMAL);
	createTrackbar("test","test",&value1,maxValue,on_TrackBar);
	waitKey(0);
}

int main(){
	createBarTest();
	return 0;
}