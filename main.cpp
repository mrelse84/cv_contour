#include "opencv2\opencv.hpp"
#include <iostream>
#include <cstdlib>

using namespace cv;
using namespace std;
RNG rng(12345);

int main(int argc, char** argv)
{
	//Mat srcimage = imread("d:/sglee/images/halcon_images/die/die_03.png", IMREAD_GRAYSCALE);
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

	//----- Blur
	Mat blur_image;
	//blur(srcimage, blur_image, cv::Size(5, 5));
	//GaussianBlur(srcimage, blur_image, cv::Size(5, 5), 1.5);
	medianBlur(srcimage, blur_image, 5);
	imshow("Blur", blur_image);

	//----- Morphology Filtering
	//Mat result_image;
	// ħ�� : �ּ�, ȸ�� ������(Bridge ����) ���� (ȸ��->����) // Bridge ����, �׷��� ������ Ŀ��
	// ��â : �ִ�, ���� ���� �޿�� (����->ȸ��) // ���� ����, �׷��� Bridge �β�����
	// ���� : ħ��->��â (�� ������ ����, �� ���� �޿��) // Bridge ����, ������ �������
	// ���� : ��â->ħ�� (�� ���� �޿��, �� ������ ����) // ���� ����, Bridge�� �������
	//erode(srcimage, result_image, cv::Mat());
	//Mat element(7, 7, CV_8U, cv::Scalar(1));
	//erode(srcimage, result_image, element);
	//erode(srcimage, result_image, cv::Mat(), cv::Point(-1,-1), 3); // 3�� ħ��
	//morphologyEx(srcimage, result_image, cv::MORPH_CLOSE, element);

	Mat cannyimage;
	Canny(srcimage, cannyimage, 10, 100);
	imshow("Canny", cannyimage);

	waitKey();

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(cannyimage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	int cont_size = contours.size();

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dstimage, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	imshow("dstimage", dstimage);
	waitKey();
	return 0;
}