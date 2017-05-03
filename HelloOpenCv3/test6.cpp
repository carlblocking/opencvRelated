#include <iostream>  
#include<opencv2\opencv.hpp>
#include<opencv2\ml\ml.hpp>
#include<stdlib.h>

using namespace std;
using namespace cv;

char video6_filePath[] = "E:\\照片\\创意照片\\test.MOV";
char file6_filePath[] = "E:\\照片\\创意照片\\facetothecity.jpg";

void detect(Mat source) {
	Mat src = source;
	vector<Rect> personCasc, personListCacs; 
	CascadeClassifier *cascade = new CascadeClassifier;
	cascade->load("D:\\opencv\\sources\\data\\hogcascades\\hogcascade_pedestrians.xml");
	cascade->detectMultiScale(src, personCasc);

	for (int i = 0; i < personCasc.size(); i++)
	{
		Rect r = personCasc[i];
		int j = 0;
		for (; j < personCasc.size(); j++)
			if (j != i && (r & personCasc[j]) == r)
				break;
		if (j == personCasc.size())
			personListCacs.push_back(r);
	}

	for (int i = 0; i<personListCacs.size(); i++)
	{
		Rect r = personListCacs[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(src, r.tl(), r.br(), Scalar(0, 255, 0), 2);
	}
}

void changeMat(Mat source) {
	int nr = source.rows;
	int nc = source.cols*source.channels();
	for (int j = 0; j < nr;j++) {
		uchar* data = source.ptr<uchar>(j);
		for (int i = 0; i < nc;i++) {
			if (data[i] >= 125)
				data[i] = 125;
			else
				data[i] = 1;
		}
	}
}

void testSVM() {
	//用来显示结果的图片
	int width = 512, height = 512;
	Mat image = Mat::zeros(height,width,CV_8UC3);

	//设置训练数据
	float labels[] = {1.0,-1.0,-1.0,-1.0};
	Mat labelMat(3,1,CV_32FC1,labels);

	float trainingData[4][2] = { {501,10},{25,10},{501,255},{10,501} };
	Mat trainingMat(3,2,CV_32FC1,trainingData);

	//设置SVM的参数
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER,100,1e-6);

	//训练SVM
	CvSVM svm;
	svm.train(trainingMat,labelMat,Mat(),Mat(),params);

	Vec3b green(0, 255, 0), blue(255,0,0);

	//显示决策边界
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1, 2) << i, j);
			float response = svm.predict(sampleMat);

			if (response == 1)
				image.at<Vec3b>(j, i) = green;
			else if (response == -1)
				image.at<Vec3b>(j, i) = blue;
		}

	// Show the training data
	int thickness = -1;
	int lineType = 8;
	circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);
	circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

	// Show support vectors
	thickness = 2;
	lineType = 8;
	int c = svm.get_support_vector_count();

	for (int i = 0; i < c; ++i)
	{
		const float* v = svm.get_support_vector(i);
		circle(image, Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thickness, lineType);
	}
	imshow("SVM Simple Example", image); // show it to the user
	waitKey(0);
}

//标准化gamma空间和颜色空间
//首先灰度化图像
//然后对图像中的每个像素做开方计算
IplImage* step1(IplImage* source) {
	uchar* tmp;
	for (int i = 0; i < source->height;i++) {
		for (int j = 0; j < source->width;j++) {
			//*tmp = ((uchar*)(source->imageData+i*source->widthStep))[j];
			((uchar*)(source->imageData + i*source->widthStep))[j]=sqrt(
				((uchar*)(source->imageData + i*source->widthStep))[j]);
		}
	}
	return source;
}

///将图片转化为LBP特征图
int getHopCount(uchar i)
{
	int a[8] = { 0 };
	int k = 7;
	int cnt = 0;
	while (i)
	{
		a[k] = i & 1;
		i >>= 1;
		--k;
	}
	for (int k = 0; k<8; ++k)
	{
		if (a[k] != a[k + 1 == 8 ? 0 : k + 1])
		{
			++cnt;
		}
	}
	return cnt;
}

void lbp59table(uchar* table)
{
	memset(table, 0, 256);
	uchar temp = 1;
	for (int i = 0; i<256; ++i)
	{
		if (getHopCount(i) <= 2)
		{
			table[i] = temp;
			temp++;
		}
		// printf("%d\n",table[i]);  
	}
}

void LBP(IplImage* src, IplImage* dst)
{
	int width = src->width;
	int height = src->height;
	uchar table[256];
	lbp59table(table);
	for (int j = 1; j<width - 1; j++)
	{
		for (int i = 1; i<height - 1; i++)
		{
			uchar neighborhood[8] = { 0 };
			neighborhood[7] = CV_IMAGE_ELEM(src, uchar, i - 1, j - 1);
			neighborhood[6] = CV_IMAGE_ELEM(src, uchar, i - 1, j);
			neighborhood[5] = CV_IMAGE_ELEM(src, uchar, i - 1, j + 1);
			neighborhood[4] = CV_IMAGE_ELEM(src, uchar, i, j + 1);
			neighborhood[3] = CV_IMAGE_ELEM(src, uchar, i + 1, j + 1);
			neighborhood[2] = CV_IMAGE_ELEM(src, uchar, i + 1, j);
			neighborhood[1] = CV_IMAGE_ELEM(src, uchar, i + 1, j - 1);
			neighborhood[0] = CV_IMAGE_ELEM(src, uchar, i, j - 1);
			uchar center = CV_IMAGE_ELEM(src, uchar, i, j);
			uchar temp = 0;

			for (int k = 0; k<8; k++)
			{
				temp += (neighborhood[k] >= center) << k;
			}
			//CV_IMAGE_ELEM( dst, uchar, i, j)=temp;  
			CV_IMAGE_ELEM(dst, uchar, i, j) = table[temp];
		}
	}
}
///end

int main6() {
	return 0;
}