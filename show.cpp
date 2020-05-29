#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
//#include "My_ImageProssing_base.h"
#define WINDOW_NAME1 "【程序窗口1】"			
#define WINDOW_NAME2 "【程序窗口2】"	
using namespace cv;
using namespace std;
RNG g_rng(12345);

Mat src_image;
Mat img1;
Mat img2;

////*--------------------------练习1：手动实现HOG描述子-------------------------------------*/

float* Cal_cellHist(Mat src)
{
	//计算角度及梯度
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	float hist[8] = { 0 };
	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (angle.at<float>(j, i) >= 0 && angle.at<float>(j, i) < 45)
			{
				hist[0] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 45 && angle.at<float>(j, i) < 90)
			{
				hist[1] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 90 && angle.at<float>(j, i) < 135)
			{
				hist[2] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 135 && angle.at<float>(j, i) < 180)
			{
				hist[3] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 180 && angle.at<float>(j, i) < 225)
			{
				hist[4] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 225 && angle.at<float>(j, i) < 270)
			{
				hist[5] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 270 && angle.at<float>(j, i) < 315)
			{
				hist[6] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) >= 315 && angle.at<float>(j, i) < 360)
			{
				hist[7] += mag.at<float>(j, i);
			}
		}
	}
	return hist;
}


int main()
{
	Mat img1 = imread("D:\\opencv_picture_test\\template.png",0);
	Mat srcimg2 = imread("D:\\opencv_picture_test\\img.png", 0);
	int cellSize = 16;
	int nX = img1.cols / cellSize;
	int nY = img1.rows / cellSize;
	Mat img2 = Mat::zeros(img1.rows, img1.cols, CV_8UC1);
	int num = nX * nY * 8;

	float* srcHist = new float[num];
	memset(srcHist, 0, sizeof(float) * num);

	float* img1Hist = new float[num];
	memset(img1Hist, 0, sizeof(float) * num);

	float* img2Hist = new float[num];
	memset(img2Hist, 0, sizeof(float) * num);

	int cnt1 = 0;
	int cnt2 = 0;
	float distance = 0;
	float distance_min = 1000000;		
	int x = 0;
	int y = 0;
	//只遍历80—110见方区域
	for (int q = 80; q < 110; q++) {
		for (int p = 80; p < 110; p++) {
			//从srcimg2中扣出和img1一样大小的区域放到img2中
			for (int m = 0; m < img1.rows; m++) {
				for (int n = 0; n < img1.cols; n++) {
					img2.at<uchar>(m, n) = srcimg2.at<uchar>(q + m, p + n);
				}
			}
			//计算img1的直方图
			cnt1 = 0;
			for (int j = 0; j < nY; j++)
			{
				for (int i = 0; i < nX; i++)
				{
					Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
					Mat nowMat = img1(rectL);
					for (int k = 0; k < 8; k++)
					{
						img1Hist[k + cnt1 * 8] = Cal_cellHist(nowMat)[k];		//计算
					}
					cnt1++;
				}
			}
			//计算img2的直方图
			cnt2 = 0;
			for (int j = 0; j < nY; j++)
			{
				for (int i = 0; i < nX; i++)
				{
					Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
					Mat nowMat = img2(rectL);
					for (int k = 0; k < 8; k++)
					{
						img2Hist[k + cnt2 * 8] = Cal_cellHist(nowMat)[k];
					}
					cnt2++;
				}
			}
			distance = 0;
			//计算两个直方图的曼哈顿距离
			for (int i = 0; i < num; i++)
			{
				distance += abs(img1Hist[i] - img2Hist[i]);
				if (distance < distance_min) {
					distance_min = distance;
					x = q;
					y = p;
				}
			}
		}
	}
	cout << "最小值" << distance_min << endl;
	cout << "x" << x << endl;
	cout << "y" << y << endl;
	Rect rect(y, x, img1.cols, img1.rows);//左上坐标（x,y）和矩形的长(x)宽(y)
	cv::rectangle(srcimg2, rect, Scalar(255, 0, 0), 1, LINE_8, 0);
	imshow("dstMat", srcimg2);
	waitKey(0);
	delete[] img1Hist;
	delete[] img2Hist;
	return 0;
}





//***********************************************练习2 框出之后按回车键即可****************************************************//
//int main()
//{
//	//改变控制台字体颜色
//	system("color 02");
//	VideoCapture capture(0);
//	int cnt = 0;
//	Mat frame;	//存储每一帧的图像
//	Mat tempMat;
//	Mat refMat;
//	Mat resultMat;
//	Mat dispMat;
//	while (1)
//	{
//		capture >> frame;	//读取当前帧
//		if (cnt == 0) {
//			Rect2d r;
//			r = selectROI(frame, true);
//			tempMat = frame(r);
//			tempMat.copyTo(refMat);
//			destroyAllWindows();
//		}
//		int match_method = 0;
//		matchTemplate(frame, refMat, resultMat, match_method);
//		normalize(resultMat, resultMat, 0,1,NORM_MINMAX,-1,Mat());
//		double minVal; double maxVal; Point minLoc; Point maxLoc; Point matchLoc;
//		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc,Mat());
//		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
//			matchLoc = minLoc;
//		else
//			matchLoc = maxLoc;
//		frame.copyTo(dispMat);
//		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);
//		cnt++;
//		imshow("template",refMat) ;
//		imshow("dispMat",dispMat) ;
//		waitKey(30);
//	}
//	return 0;
//	
//}