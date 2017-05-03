#include<opencv\cv.h>
#include<highgui.hpp>
#include<iostream>
#include<string>
#include<opencv2\nonfree\features2d.hpp>

using namespace std;
using namespace cv;

string file2_name = "E:\\’’∆¨\\¥¥“‚’’∆¨\\lujiazui.jpg";
string file2_name2 = "E:\\’’∆¨\\¥¥“‚’’∆¨\\lujiazui2.jpg";

void featureDetect1() {
	Ptr<DescriptorMatcher> siftMatcher = DescriptorMatcher::create("BruteForce");
	SiftFeatureDetector siftDetector;

	Mat img1 = imread(file2_name);
	Mat img2 = imread(file2_name2);

	vector<KeyPoint> keypoints1, keypoints2;
	siftDetector.detect(img1,keypoints1);
	siftDetector.detect(img2,keypoints2);
	cout << "Number of detected keypoints img1:"<<keypoints1.size() << endl;
	cout << "Number of detected keypoints img2:" << keypoints2.size() << endl;
	SiftDescriptorExtractor siftExtractor;
	Mat descriptor1, descriptor2;
	siftExtractor.compute(img1,keypoints1,descriptor1);
	siftExtractor.compute(img2, keypoints2, descriptor2);
	cout <<"Number of Description1:" <<descriptor1.rows<< endl;
	cout << "Number of Description2:" << descriptor2.rows << endl;
	cout << "Demension of sift descriptors:" << descriptor1.cols << endl;

	Mat imgkey1, imgkey2;
	drawKeypoints(img1, keypoints1, imgkey1, Scalar::all(-1));
	drawKeypoints(img2, keypoints2, imgkey2, Scalar::all(-1));
	imshow("box",imgkey1);
	imshow("box_in_scene",imgkey2);

	vector<DMatch> matches;
	siftMatcher->match(descriptor1,descriptor2,matches,Mat());

	Mat imgmatches;
	drawMatches(img1,keypoints1,img2,keypoints2,matches,imgmatches,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	namedWindow("match result",WINDOW_NORMAL);
	imshow("match result",imgmatches);

	waitKey(0);
}

void featureDetect2() {
	Mat img1 = imread(file2_name,0);
	Mat img2 = imread(file2_name2,0);

	if (!img1.data || !img2.data) { return ; }

	SurfFeatureDetector detector;
	vector<KeyPoint> keypoint1, keypoint2;
	detector.detect(img1,keypoint1);
	detector.detect(img2,keypoint2);

	SurfDescriptorExtractor extractor;
	Mat description1, description2;
	extractor.compute(img1,keypoint1,description1);
	extractor.compute(img2,keypoint2,description2);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(description1,description2,matches);

	double dist_max = 0;
	double dist_min = 100;
	for (int i = 0; i < description1.rows;i++) {
		double dist = matches[i].distance;
		if (dist < dist_min)
			dist_min = dist;
		if (dist > dist_max)
			dist_max = dist;
	}
	cout << dist_max << "\t" << dist_min;

	vector<DMatch> goodmatches;
	for (int i = 0; i < matches.size();i++) {
		if (matches[i].distance < 2*dist_min)
			goodmatches.push_back(matches[i]);
	}

	Mat imgout;
	drawMatches(img1,keypoint1,img2,keypoint2,goodmatches,imgout,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	namedWindow("matches",WINDOW_NORMAL);
	imshow("matches",imgout);

	waitKey(0);
}

int main2() {
	featureDetect2();
	return 0;
}