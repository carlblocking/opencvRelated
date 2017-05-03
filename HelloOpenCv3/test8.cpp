#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>
#include<fstream>
#include<core\core.hpp>
#include<imgproc\imgproc.hpp>


using namespace std;
using namespace cv;

class VideoProcessor8 {
private:
	VideoCapture capture;
	//the callback function to be called for the processing of each frame
	void(*process)(Mat&, Mat&);
	void(*process2)(Mat&);
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
	VideoProcessor8() :callIt(true), delay(0), fnumber(0),
		stop(false), frameToStop(-1) {}

	void setFrameProcess(void(*process)(Mat&, Mat&)) {
		this->process = process;
	}

	void setFrameProcess2(void(*process2)(Mat&)) {
		this->process2 = process2;
	}

	bool setInput(string fileName) {
		fnumber = 0;
		capture.release();
		return capture.open(fileName);
	}

	void diplayInput(string wn) {
		WindowNameInput = wn;
		namedWindow(WindowNameInput, 0);
	}

	void displayOutput(string wn) {
		WindowNameOutput = wn;
		namedWindow(WindowNameOutput, 0);
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
				imshow(WindowNameInput, frame);
			if (callIt)process(frame, output);
			else output = frame;
			if (WindowNameOutput.length() != 0)
				imshow(WindowNameOutput, output);
			if (delay >= 0 && waitKey(delay) >= 0) waitKey(0);
			if (frameToStop >= 0 && getFrameNumber() == frameToStop)
				stopIt();
		}
	}

	void run2() {
		Mat frame;
		if (!isOpened())return;
		stop = false;
		while (!isStopped())
		{
			if (!readNextFrame(frame))break;
			if (WindowNameInput.length() != 0)
				imshow(WindowNameInput, frame);
			if (callIt)process2(frame);
			if (delay >= 0 && waitKey(delay) >= 0) waitKey(0);
			if (frameToStop >= 0 && getFrameNumber() == frameToStop)
				stopIt();
		}
	}
};

/*ʹ�ò�ͬ�ķ�ʽ����ͼƬ����*/

char file8_filePath[] = "E:\\��Ƭ\\������Ƭ\\guitar.jpg";
string test8_filename1 = "E:\\�ҵĹ���\\matlab\\test1.jpg";
string test8_filename2 = "E:\\�ҵĹ���\\matlab\\test2.jpg";
char video8_filePath[] = "E:\\��Ƭ\\������Ƭ\\test.MOV";

void  writeCameraVideoInDifferentWays() {
	VideoCapture capture(0);
	namedWindow("test",0);
	if (!capture.isOpened()) {
		return;
	}
	//����֡��
	float fpsInput = 24;
	//����֡�ļ��
	float pauseInput = 1000 / fpsInput;
	Mat frame;
	Size videoSize = Size(capture.get(CV_CAP_PROP_FRAME_WIDTH),capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	string videoPath1 = "D://test2.avi";
	VideoWriter writer(videoPath1,-1,fpsInput,videoSize,true);
	if (!writer.isOpened()) {
		return;
	}
	while (1)
	{
		capture >> frame;
		if (frame.empty()||waitKey(pauseInput)=='q') {
			return;
		}
		writer << frame;
		imshow("test",frame);
		//waitKey(24);
	}
	waitKey();
}

double ImageEntropy(Mat img) {
	double temp[256] = { 0.0 };
	if (img.channels() == 3)
		cvtColor(img, img, CV_RGB2GRAY);
	//��˹ģ��
	GaussianBlur(img,img,Size(91,91),1.5,1.5);
	// ����ÿ�����ص��ۻ�ֵ
	for (int m = 0; m<img.rows; m++)
	{// ��Ч�������еķ�ʽ
		const uchar* t = img.ptr<uchar>(m);
		for (int n = 0; n<img.cols; n++)
		{
			int i = t[n];
			temp[i] = temp[i] + 1;
		}
	}
	// ����ÿ�����صĸ���
	for (int i = 0; i<256; i++)
	{
		temp[i] = temp[i] / (img.rows*img.cols);
	}
	double result = 0;
	// ����ͼ����Ϣ��
	for (int i = 0; i<256; i++)
	{
		if (temp[i] == 0.0)
			result = result;
		else
			result = result - temp[i] * (log(temp[i]) / log(2.0));
	}
	return result;
}

void writeEntropyIntoFile(double data) {
	ofstream outfile("D://data3.txt",ios::app);
	if (!outfile) {
		cout << "could not open the file" << endl;
		return;
	}
	outfile << data << "\n";
	outfile.close();
}

void writeEntropy(Mat &input) {
	double entropy ;
	entropy=ImageEntropy(input);
	//cout << "��Ϣ��Ϊ"<<entropy << endl;
	writeEntropyIntoFile(entropy);
}

void inforForVideo4(Mat &input) {
	double entropy;
	entropy = ImageEntropy(input);
	//cout << "��Ϣ��Ϊ"<<entropy << endl;
	if (entropy >= 7.19&&entropy <= 7.21) {
		cout << "û�м�⵽�ƶ�����" << endl;
	}
	else
		cout << "��⵽�ƶ�����" << endl;
}

int main8() {
	VideoProcessor8 processor;
	processor.setInput("E:\\��Ƭ\\������Ƭ\\test4.MOV");
	processor.diplayInput("input");
	processor.setDelay(1000/processor.getFrameRate());
	processor.setFrameProcess2(writeEntropy);
	processor.run2();
	return 0;
}

