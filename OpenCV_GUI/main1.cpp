#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

char videoName[] = "E:\\视频\\九九\\IMG_2107.MOV";

//实现鼠标在窗口中画方形的程序

/*1:define our callback which we will install for mouse events*/
void my_mouse_callback(int event,int x,int y,int flag, void* param);

CvRect box;
bool drawing_box = false;

/* A little subroutine to draw a box onto an image*/
void draw_box(IplImage* image,CvRect rect) {
	cvRectangle(image,cvPoint(box.x,box.y),cvPoint(box.x+box.width,box.y+box.height),cvScalar(0xff,0x00,0x00));
}

int main1() {
	box = cvRect(-1,-1,0,0);
	IplImage* image = cvCreateImage(cvSize(200,200),IPL_DEPTH_8U,3);
	cvZero(image);//将图片中的像素元素设置为0
	IplImage* temp = cvCloneImage(image);
	cvNamedWindow("test",CV_WINDOW_NORMAL);

	//Here is the crucial moment that we will actually install 
	//the callback. Note that we set the value 'param' to 
	//be the image we are working with so that the callback 
	//will have the image to edit.
	cvSetMouseCallback("test",my_mouse_callback,(void*)image);

	//The main program loop. Here we copy the working image
	//to the 'temp' image, and if the user us drawing, then 
	//put the currently contemplated box onto that temp image.
	//display the temp image, and wait 15ms for a keystroke,
	//then repeat...
	while (1) {
		cvCopy(image,temp);
		if (drawing_box)draw_box(temp,box);
		cvShowImage("test",temp);
		if (cvWaitKey(15) == 'q')break;
	}
	cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvDestroyWindow("test");
	return 0;
}

void my_mouse_callback(int event, int x ,int y, int flag, void* param) {
	IplImage* image = (IplImage*)param;
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE: {
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
	}
		break;
	case CV_EVENT_LBUTTONDOWN: {
		drawing_box = true;
		box = cvRect(x,y,0,0);
	}
		break;
	case CV_EVENT_LBUTTONUP: {
		drawing_box = false;
		if (box.width < 0) {
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0) {
			box.y += box.height;
			box.height *= -1;
		}
	}
		 break;
	}
}