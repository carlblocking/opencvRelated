#include<iostream>
#include<ctime>
#include<vector>
#include<string>

#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;


//��ʴ����
void erosionTest() {
	Mat source = imread("E:\\��Ƭ\\������Ƭ\\facetothecity.jpg");
	namedWindow("source", WINDOW_NORMAL);
	imshow("source", source);
	//��ʴ����
	//getStructuringElement�����ķ���ֵΪָ����״�ͳߴ�ĽṹԪ��
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat result;
	erode(source,result,element);
	//��ʾ���
	namedWindow("result",WINDOW_NORMAL);
	imshow("result",result);

	waitKey(0);
}

void blurTest() {
	Mat source = imread("E:\\��Ƭ\\������Ƭ\\facetothecity.jpg");
	namedWindow("source", WINDOW_NORMAL);
	imshow("source", source);

	Mat result;
	blur(source,result,Size(7,7));

	namedWindow("result", WINDOW_NORMAL);
	imshow("result", result);

	waitKey(0);
}

void canntTest() {
	Mat source = imread("E:\\��Ƭ\\������Ƭ\\facetothecity.jpg");
	Mat gray;
	Mat result;
	//תΪ�Ҷ�ͼ��
	cvtColor(source,gray,CV_BGR2GRAY);
	//ʹ��3*3���ں˽���
	blur(gray,result,Size(3,3));
	//ʹ��canny��������Ե
	Canny(result,result,3,9,3);
	namedWindow("result",WINDOW_NORMAL);
	imshow("result",result);
	waitKey(0);
}

void readVideoFromCamTest() {
	VideoCapture capture(0);//��������Ϊ�ļ�·�������ɷ����ļ�
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

//���������
const int maxValue = 100;//���������ֵ
int value1;//��������Ӧ����

//�ص�����
void on_TrackBar(int, void*) {
	cout << value1 << endl;
}

void createBarTest() {
	//���û�������ʼֵ
	value1 = 1;
	namedWindow("test",WINDOW_NORMAL);
	createTrackbar("test","test",&value1,maxValue,on_TrackBar);
	waitKey(0);
}

int main(){
	createBarTest();
	return 0;
}