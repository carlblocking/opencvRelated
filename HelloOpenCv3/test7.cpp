#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>

using namespace std;
using namespace cv;

/*使用不同的方式访问图片像素*/

char file7_filePath[] = "E:\\照片\\创意照片\\guitar.jpg";
string test7_filename1 = "E:\\我的工程\\matlab\\test1.jpg";
string test7_filename2 = "E:\\我的工程\\matlab\\test2.jpg";
char video7_filePath[] = "E:\\照片\\创意照片\\test.MOV";

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
	//对像素进行翻转
	threshold(out,out,128,255,THRESH_BINARY_INV);
}

///main函数中使用videoProcess的代码
//VideoProcessor processor;
//processor.setInput("E:\\照片\\创意照片\\test.MOV");
//processor.diplayInput("input");
//processor.displayOutput("output");
//processor.setDelay(2000./processor.getFrameRate());
//processor.setFrameProcess(canny);
//processor.run();

void openVideo() {
	VideoCapture capture("E:\\照片\\创意照片\\test.MOV");
	if (!capture.isOpened()) {
		cout << "不能打开视频文件" << endl;
		return;
	}
	//获取整个帧数
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "总共" << totalFrameNumber<<"帧"<<endl;
	//设置开始帧
	long frameToStart = 300;
	capture.set(CV_CAP_PROP_POS_FRAMES,frameToStart);
	cout << "从第" << frameToStart << "帧开始播放" << endl;
	//设置结束帧
	int frameToStop = 400;
	if (frameToStop<frameToStart) {
		cout << "error" << endl;
		return;
	}
	else {
		cout << "结束帧为第" << frameToStop << "帧" << endl;
	}
	//获取帧率
	double rate = capture.get(CV_CAP_PROP_FPS);
	cout << "帧率为" << rate << endl;
	//定义一个用来控制读取视频循环结束的变量
	bool stop = false;
	//承载每一帧的图像
	Mat frame;
	//显示每一帧的窗口
	namedWindow("show",0);
	//两帧的间隔时间
	int delay = 1000 / rate;
	//利用while循环读取帧
	long currentFrame = frameToStart;
	while (!stop)
	{
		//读取下一帧
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
	//关闭视频文件
	capture.release();
	waitKey(0);
}

int main7() {
	openVideo();
	return 0;
}
