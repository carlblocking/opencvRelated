#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

char fileName[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
char source_image_main3[] = "E:\\��Ƭ\\������Ƭ\\test1.jpg";
//����ģ��
void differentImageSmooth() {
	//Դͼ��
	IplImage* source = cvLoadImage(fileName);
	cvNamedWindow("source",CV_WINDOW_NORMAL);

	IplImage* blur_image = cvLoadImage(fileName);//��ģ��
	cvNamedWindow("blur_image",CV_WINDOW_NORMAL);

	IplImage* blur_no_scale_image = cvLoadImage(fileName);//�������ű任��ģ��
	cvNamedWindow("blur_no_scale_image", CV_WINDOW_NORMAL);

	IplImage* median_image = cvLoadImage(fileName);//��ֵģ��
	cvNamedWindow("median_image", CV_WINDOW_NORMAL);

	IplImage* gaussian_image = cvLoadImage(fileName);//��˹ģ��
	cvNamedWindow("gaussian_image", CV_WINDOW_NORMAL);

	IplImage* bilateral_image = cvLoadImage(fileName);//˫��ģ��
	cvNamedWindow("bilateral_image", CV_WINDOW_NORMAL);

	//��ʾԴͼ��
	cvShowImage("source", source);

	cvSmooth(blur_image, blur_image);
	cvShowImage("blur_image", blur_image);

	cvSmooth(blur_no_scale_image, blur_no_scale_image);
	cvShowImage("blur_no_scale_image", blur_no_scale_image);

	cvSmooth(median_image, median_image);
	cvShowImage("median_image", median_image);

	cvSmooth(gaussian_image, gaussian_image);
	cvShowImage("gaussian_image", gaussian_image);

	cvSmooth(bilateral_image, bilateral_image);
	cvShowImage("bilateral_image", bilateral_image);

	cvWaitKey();

	cvReleaseImage(&source);
	cvReleaseImage(&blur_image);
	cvReleaseImage(&blur_no_scale_image);
	cvReleaseImage(&median_image);
	cvReleaseImage(&gaussian_image);
	cvReleaseImage(&bilateral_image);

	cvDestroyAllWindows();
}

//ͼ������ͺ͸�ʴ
void imageErodeAndDilate() {
	IplImage* source_image1 = cvLoadImage(fileName,0);
	IplImage* source_image2 = cvLoadImage(fileName,0);

	cvNamedWindow("erode",CV_WINDOW_NORMAL);//��ʴ
	cvNamedWindow("dilate",CV_WINDOW_NORMAL);//����

	cvErode(source_image1,source_image1);
	cvDilate(source_image2,source_image2);

	cvShowImage("erode",source_image1);
	cvShowImage("dilate",source_image2);

	waitKey();

	cvReleaseImage(&source_image1);
	cvReleaseImage(&source_image2);

	cvDestroyAllWindows();
}

//��̬�ݶ�ѧ
//�Ҷ�ֵ�仯����ҵ�����õ��Ľ����ֵ���
void gradientImage() {
	IplImage* source_image1 = cvLoadImage(fileName,0);
	IplImage* source_image2 = cvLoadImage(fileName,0);
	IplImage* result_image = cvCreateImage(cvGetSize(source_image1),IPL_DEPTH_8U,1);

	cvDilate(source_image1,source_image1);
	cvErode(source_image2,source_image2);

	cvAbsDiff(source_image1,source_image2,result_image);

	cvNamedWindow("test",CV_WINDOW_NORMAL);
	cvShowImage("test",result_image);
	waitKey();
	cvReleaseImage(&source_image1);
	cvReleaseImage(&source_image2);
	cvReleaseImage(&result_image);
	cvDestroyAllWindows();
}

//��ñ�任����ΪTop Hat & Black Hat
//TopHat(src)=src-open(src)
//BlackHat(src)=close(src)-src
//TopHat��A��ȥ��A�Ŀ�����
//BlackHat��A�ı������ȥ��A

//cvThreshold������ʹ��
void sum_rgb(IplImage* source_image,IplImage* result_image) {
	IplImage* r = cvCreateImage(cvGetSize(source_image),IPL_DEPTH_8U,1);
	IplImage* g = cvCreateImage(cvGetSize(source_image), IPL_DEPTH_8U, 1);
	IplImage* b = cvCreateImage(cvGetSize(source_image), IPL_DEPTH_8U, 1);

	//split image into the color planes
	cvSplit(source_image,r,g,b,NULL);

	//temporary storage
	IplImage* s = cvCreateImage(cvGetSize(source_image), IPL_DEPTH_8U, 1);

	//add equally weighted rgb values
	cvAddWeighted(r,1./3.,g,1./3.,0.0,s);
	cvAddWeighted(s, 2. / 3., b, 1. / 3., 0.0, s);

	//Truncate values above 100
	cvThreshold(s,result_image,100,100,CV_THRESH_TRUNC);

	cvReleaseImage(&r);
	cvReleaseImage(&g);
	cvReleaseImage(&b);
	cvReleaseImage(&s);
}

void show_sum_rgb_result() {
	cvNamedWindow("test",CV_WINDOW_NORMAL);
	IplImage* source_image = cvLoadImage(fileName);
	IplImage* result_image = cvCreateImage(cvGetSize(source_image),source_image->depth,1);
	sum_rgb(source_image,result_image);
	cvShowImage("test",result_image);
	while (1)
	{
		if ((cvWaitKey(10) & 0x7f) == 27)break;//������esc��
		//cvDestroyAllWindows();
		//cvReleaseImage(&source_image);
		//cvReleaseImage(&result_image);
	}
}

void test_cvsplit() {
	IplImage* source_image = cvLoadImage(fileName);
	IplImage* red = cvCreateImage(cvGetSize(source_image),source_image->depth,1);
	IplImage* green = cvCreateImage(cvGetSize(source_image), IPL_DEPTH_8U, 1);
	IplImage* blue = cvCreateImage(cvGetSize(source_image), IPL_DEPTH_8U, 1);

	cvSplit(source_image,red,green,blue,NULL);

	cvNamedWindow("red",CV_WINDOW_NORMAL);
	cvNamedWindow("green", CV_WINDOW_NORMAL);
	cvNamedWindow("blue", CV_WINDOW_NORMAL);

	cvShowImage("red",red);
	cvShowImage("green", green);
	cvShowImage("blue", blue);

	cout << source_image->depth << endl;
	
	cvWaitKey();
}

int main3() {
	test_cvsplit();
	return 0;
}