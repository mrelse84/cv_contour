#include "opencv2\opencv.hpp"
#include <iostream>
#include <cstdlib>
using namespace cv;
using namespace std;
RNG rng(12345);

int main(int argc, char** argv)
{
	Mat srcimage = imread("d:/images/halcon_images/die/die_03.png", IMREAD_GRAYSCALE);
	if (srcimage.empty())
	{
		cout << "[INFO] No image!!" << endl;
		return -1;
	}

	Mat dstimage = Mat::zeros(srcimage.rows, srcimage.cols, CV_8UC3);

	//srcimage = srcimage > 1;
	namedWindow("Source", 1);
	imshow("Source", srcimage);
	Mat cannyimage;
	Canny(srcimage, cannyimage, 10, 100);
	imshow("Canny", cannyimage);
	waitKey();

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(cannyimage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dstimage, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	imshow("dstimage", dstimage);
	waitKey();
	return 0;
}