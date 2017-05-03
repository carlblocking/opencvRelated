#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>

using namespace std;
using namespace cv;

/*ʹ�ò�ͬ�ķ�ʽ����ͼƬ����*/

char file7_filePath[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
string test7_filename1 = "E:\\�ҵĹ���\\matlab\\test1.jpg";
string test7_filename2 = "E:\\�ҵĹ���\\matlab\\test2.jpg";
char video7_filePath[] = "E:\\��Ƭ\\������Ƭ\\test.MOV";

class VideoProcessor {
private:
	VideoCapture capture;
	//the callback function to be called for the processing of each frame
	void(*process)(Mat&,Mat&);
	bool callIt;
	string WindowNameInput;
	string WindowNameOutput;
	int delay;
	//number of processed frame
	long fnumber;
	//stop at this frame number
	long frameToStop;
	bool stop;
public:
	VideoProcessor() :callIt(true), delay(0), fnumber(0),
		stop(false), frameToStop(-1) {}

	void setFrameProcess(void(*process)(Mat&,Mat&)) {
		this->process = process;
	}

	bool setInput(string fileName) {
		fnumber = 0;
		capture.release();
		return capture.open(fileName);
	}

	void diplayInput(string wn) {
		WindowNameInput = wn;
		namedWindow(WindowNameInput,0);
	}

	void displayOutput(string wn) {
		WindowNameOutput = wn;
		namedWindow(WindowNameOutput,0);
	}

	void dontDisplay() {
		destroyWindow(WindowNameInput);
		destroyWindow(WindowNameOutput);
		WindowNameInput.clear();
		WindowNameOutput.clear();
	}

	void stopIt() {
		stop = true;
	}

	bool isStopped() {
		return stop;
	}

	bool isOpened() {
		return capture.isOpened();
	}

	void setDelay(int d) {
		delay = d;
	}

	bool readNextFrame(Mat &frame) {
		return capture.read(frame);
	}

	void CallProcess() {
		callIt = true;
	}

	void dontCallProcess() {
		callIt = false;
	}

	void stopAtFrameNo(long frame) {
		frameToStop = frame;
	}

	long getFrameNumber() {
		long fnumber = static_cast<long>(capture.get((CV_CAP_PROP_POS_FRAMES)));
		return fnumber;
	}

	double getFrameRate() {
		return capture.get(CV_CAP_PROP_FPS);
	}

	void run() {
		Mat frame;
		Mat output;
		if (!isOpened())return;
		stop = false;
		while (!isStopped())
		{
			if (!readNextFrame(frame))break;
			if (WindowNameInput.length() != 0)
				imshow(WindowNameInput,frame);
			if (callIt)process(frame,output);
			else output = frame;
			if (WindowNameOutput.length() != 0)
				imshow(WindowNameOutput,output);
			if (delay >= 0 && waitKey(delay) >= 0) waitKey(0);
			if (frameToStop >= 0 && getFrameNumber() == frameToStop)
				stopIt();
		}
	}
};

void canny(Mat& image,Mat& out) {
	if (image.channels() == 3)
		cvtColor(image,out,CV_BGR2GRAY);
	Canny(out,out,100,200);
	//�����ؽ��з�ת
	threshold(out,out,128,255,THRESH_BINARY_INV);
}

///main������ʹ��videoProcess�Ĵ���
//VideoProcessor processor;
//processor.setInput("E:\\��Ƭ\\������Ƭ\\test.MOV");
//processor.diplayInput("input");
//processor.displayOutput("output");
//processor.setDelay(2000./processor.getFrameRate());
//processor.setFrameProcess(canny);
//processor.run();

void openVideo() {
	VideoCapture capture("E:\\��Ƭ\\������Ƭ\\test.MOV");
	if (!capture.isOpened()) {
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return;
	}
	//��ȡ����֡��
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "�ܹ�" << totalFrameNumber<<"֡"<<endl;
	//���ÿ�ʼ֡
	long frameToStart = 300;
	capture.set(CV_CAP_PROP_POS_FRAMES,frameToStart);
	cout << "�ӵ�" << frameToStart << "֡��ʼ����" << endl;
	//���ý���֡
	int frameToStop = 400;
	if (frameToStop<frameToStart) {
		cout << "error" << endl;
		return;
	}
	else {
		cout << "����֡Ϊ��" << frameToStop << "֡" << endl;
	}
	//��ȡ֡��
	double rate = capture.get(CV_CAP_PROP_FPS);
	cout << "֡��Ϊ" << rate << endl;
	//����һ���������ƶ�ȡ��Ƶѭ�������ı���
	bool stop = false;
	//����ÿһ֡��ͼ��
	Mat frame;
	//��ʾÿһ֡�Ĵ���
	namedWindow("show",0);
	//��֡�ļ��ʱ��
	int delay = 1000 / rate;
	//����whileѭ����ȡ֡
	long currentFrame = frameToStart;
	while (!stop)
	{
		//��ȡ��һ֡
		if (!capture.read(frame))
			return;
		imshow("show",frame);
		int c = waitKey(delay);
		if ((char)c==27||currentFrame>frameToStop) {
			stop = true;
			return;
		}
		if (c >= 0)
			waitKey(0);
		currentFrame++;
	}
	//�ر���Ƶ�ļ�
	capture.release();
	waitKey(0);
}

int main7() {
	openVideo();
	return 0;
}
