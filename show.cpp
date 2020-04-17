#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
//#include "My_ImageProssing_base.h"
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏

using namespace cv;
using namespace std;
////*--------------------------【练习1】连通域标记-------------------------------------*/
//int main()
//{
//	cv::Mat srcMat = imread("D:\\opencv_picture_test\\rim.png", 1);
//	Mat dstMat, binMat;
//	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);
//	threshold(dstMat, binMat, 0, 255, THRESH_OTSU);
//	imshow("bin", binMat);
//	//通过findContours函数寻找连通域
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(binMat, contours, RETR_LIST,CHAIN_APPROX_NONE);
//
//	//绘制轮廓,内填充
//	for (int i = 0; i < contours.size(); i++) {
//		RotatedRect rbox = minAreaRect(contours[i]);
//		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 10)
//			drawContours(srcMat, contours, i, Scalar(0, 255, 255), -1, 8);
//	}
//	imshow("rim", srcMat);
//	waitKey(0);
//}

////*--------------------------【练习2】矩形框-------------------------------------*/
int main()
{
	cv::Mat srcMat = imread("D:\\opencv_picture_test\\die_on_chip.png", 1);
	Mat dstMat, binMat;
	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);
	threshold(dstMat, binMat, 0, 255, THRESH_OTSU);
	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 10)
		{
			drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 3, LINE_AA);
			}
		}
	}
	imshow("die_on_chip", srcMat);
	waitKey(0);
}

////*--------------------------【练习3】矩形框-------------------------------------*/
//int main()
//{
//	cv::Mat srcMat = imread("D:\\opencv_picture_test\\die_on_chip.png", 1);
//	Mat dstMat, binMat;
//	cvtColor(srcMat, dstMat, COLOR_BGR2GRAY);
//	threshold(dstMat, binMat, 0, 255, THRESH_OTSU);
//	imshow("bin", binMat);
//	//通过findContours函数寻找连通域
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(binMat, contours, RETR_LIST, CHAIN_APPROX_NONE);
//
//	//绘制轮廓
//	for (int i = 0; i < contours.size(); i++) {
//		RotatedRect rbox = minAreaRect(contours[i]);
//		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.1 && rbox.size.width > 10)
//		{
//			drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);
//			Point2f vtx[4];
//			for (int j = 0; j < 4; ++j) {
//				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 255, 255), 2, LINE_AA);
//			}
//		}
//	}
//	imshow("die_on_chip", srcMat);
//	waitKey(0);
//}