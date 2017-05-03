#include<iostream>
#include<opencv2\opencv.hpp>
#include<string>
#include<time.h>

using namespace std;
using namespace cv;

int initValue = 0;


void createImage1() {//����һ����ͨ���ĻҶ�ͼ��
	Mat image(200,200,CV_8UC1);
	for (int i = 0; i < image.rows;i++) {
		for (int j = 0; j < image.cols;j++) {
			image.at<uchar>(i, j) = (i + j) % 255;
		}
	}
	imshow("test1",image);
	waitKey();
	//�ͷ���Դ
	image.release();
	destroyAllWindows();
}

void createImage2() {
	//����0~255֮������������
	srand(time(0));
	int b = rand() % 256;
	int g = rand() % 256;
	int r = rand() % 256;
	Mat image(200,200,CV_8SC3,Scalar(b,g,r));
	imshow("test2",image);
	waitKey();
	image.release();
	destroyAllWindows();
}

void createImage3() {
	Mat image(200,200,CV_8UC3);
	for (int i = 0; i < image.rows;i++) {
		for (int j = 0; j < image.cols;j++) {
			Vec3b pixels;
			pixels[0] = rand() % 256;
			pixels[1] = rand() % 256;
			pixels[2] = rand() % 256;
			image.at<Vec3b>(i, j) = pixels;
		}
	}
	imshow("",image);
	waitKey();
	image.release();
	destroyAllWindows;
}

void ChangeImage() {
	//�Ҷȷ�ת��Դͼ����Ϊ�Ҷ�ͼ��
	string filePath = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
	Mat image = imread(filePath,0);
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols;j++) {
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);//255��ȥÿ�����ص���Ӧ��ֵ
		}
	}
	imshow("",image);
	waitKey();
	image.release();
	destroyAllWindows();
}

void spiltChannels() {
	string filePath = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
	vector<Mat> channels;
	Mat blueChannles, greenChannels, redChannels;
	Mat sourceImage = imread(filePath);
	split(sourceImage,channels);
	blueChannles = channels.at(0);
	greenChannels = channels.at(1);
	redChannels = channels.at(2);
	imshow("blue",blueChannles);
	imshow("green",greenChannels);
	imshow("red",redChannels);
	waitKey();
	blueChannles.release();
	greenChannels.release();
	redChannels.release();
	destroyAllWindows();
}

void ImageFigure() {
	//ͼ��ļӼ�
	string filePath1 = "C:\\Users\\xxw\\Desktop\\test1.png";
	string filePath2= "C:\\Users\\xxw\\Desktop\\test2.png";
	Mat image1, image2;
	image1 = imread(filePath1);
	image2 = imread(filePath2);
	Mat imageAdd = image1 + image2;
	Mat imageMinus = image1 - image2;
	imshow("Add",imageAdd);
	imshow("minus",imageMinus);
	waitKey();
	image1.release();
	image2.release();
	imageAdd.release();
	imageMinus.release();
	destroyAllWindows();
}

void EnforcePic() {
	string filePath = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
	Mat sourceImage, resultIamge;
	sourceImage = imread(filePath,0);//��ɫͼ��ת��Ϊ�Ҷ�ͼ��
	resultIamge = sourceImage.clone();//����ͼ��
	int rows = resultIamge.rows;
	int cols = resultIamge.cols;
	//�ж�ͼ��������
	//if (resultIamge.isContinuous()) {
	//	cols = cols*rows;
	//	rows = 1;
	//}
	//ͼ��ָ�����
	uchar* pDataMat;
	int pixMax = 0, pixMin = 255;
	//����ͼ��������Сֵ
	for (int i = 0; i < rows;i++) {
		pDataMat = resultIamge.ptr<uchar>(i);
		for (int j = 0; j < cols;j++) {
			if (pDataMat[j]>pixMax) {
				pixMax = pDataMat[j];
			}
			if (pDataMat[j]<pixMin) {
				pixMin = pDataMat[j];
			}
		}
	}
	//�Աȶ�����ӳ��
	for (int j = 0; j < rows;j++) {
		pDataMat = resultIamge.ptr<uchar>(j);
		for (int i = 0; i < cols; i++)
		{
			pDataMat[i] = (pDataMat[i] - pixMin) * 255 / (pixMax - pixMin);
		}
	}
	imshow("source",sourceImage);
	imshow("resule",resultIamge);
	waitKey();
	sourceImage.release();
	resultIamge.release();
	destroyAllWindows();
}

void equalizehistTest() {
	string filePath = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
	Mat image = imread(filePath);
	Mat resultImage;
	vector<Mat> channels;
	split(image,channels);

	//�Ը���ͨ������ֱ��ͼ���⻯
	for (int i = 0; i < image.channels();i++) {
		equalizeHist(channels[i],channels[i]);
	}
	//�ϲ�����ͨ��
	merge(channels,resultImage);

	imshow("source",image);
	imshow("result",resultImage);
	waitKey();
	image.release();
	resultImage.release();
	destroyAllWindows();
}

void laplacianImage2() {
	string filePath = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
	Mat sourceImage, resultImage;
	sourceImage = imread(filePath,0);
	resultImage = sourceImage.clone();
	//laplacian����
	Laplacian(sourceImage,resultImage,CV_16S,7);//���һ������2*n+1
	convertScaleAbs(resultImage, resultImage);

	imshow("source",sourceImage);
	imshow("result",resultImage);
	waitKey();
	sourceImage.release();
	resultImage.release();
	destroyAllWindows();
}

int main2() {
	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		createImage1();
		break;
	case 2:
		createImage2();
		break;
	case 3:
		createImage3();
		break;
	case 4:
		ChangeImage();
		break;
	case 5:
		spiltChannels();
		break;
	case 6:
		ImageFigure();
		break;
	case 7:
		EnforcePic();
		break;
	case 8:
		equalizehistTest();
		break;
	case 9:
		laplacianImage2();
		break;
	case 10:
		break;
	case 11:
		break;
	default:
		break;
	}
	return 0;
}