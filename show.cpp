#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
//#include "My_ImageProssing_base.h"
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏

using namespace cv;
using namespace std;


//====================================练习1:图像矫正加剪切=====================================
//int main()
//{
//	cv::Mat srcMat = imread("D:\\opencv_picture_test\\lena.jpg", 1);
//	cv::Mat dstMat, dstMat1;
//
//	int height = srcMat.rows;
//	int width = srcMat.cols;
//
//	//顺时针旋转10°
//	float angle = -10.0, scale = 1;
//	//旋转中心为图像中心
//	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
//	//获得变换矩阵
//	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
//	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());
//
//	//改进后(sin、cos是弧度制并非角度制)
//	float scale1 = width / (sin(abs(angle) / 360 * 2 * 3.14) * height + cos(abs(angle) / 360 * 2 * 3.14) * width);
//	cout << scale1 << endl;
//	//获得变换矩阵
//	const cv::Mat affine_matrix1 = cv::getRotationMatrix2D(center, angle, scale1);
//	cv::warpAffine(srcMat, dstMat1, affine_matrix1, srcMat.size());
//
//	cv::imshow("srcMat", srcMat);
//	cv::imshow("dstMat", dstMat);
//	cv::imshow("dstMat1", dstMat1);
//	waitKey(0);
//}

//==================================2、标准霍夫变换============================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//
//	Mat srcImage = imread("D:\\opencv_picture_test\\霍夫变换\\金属.png");
//	//判断图像是否加载成功
//	if (srcImage.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	Mat midImage, dstImage;
//	dstImage = srcImage.clone();
//	Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测  
//	//【3】进行霍夫线变换  
//	vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
//	HoughLines(midImage, lines, 1, CV_PI / 180, 100, 0, 0);
//	//【4】依次在图中绘制出每条线段  
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		float rho = lines[i][0], theta = lines[i][1];
//		Point pt1, pt2;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a * rho, y0 = b * rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//		line(dstImage, pt1, pt2, Scalar(255, 255, 255), 1, LINE_AA);
//	}
//
//	//【5】显示原始图    
//	imshow("【原始图】", srcImage);
//
//	//【6】边缘检测后的图   
//	imshow("【边缘检测后的图】", midImage);
//
//	//【7】显示效果图   
//	imshow("【效果图】", dstImage);
//	waitKey(0);
//	return 0;
//}
//==================================3、累计概率霍夫变换============================================
int main()
{
	//读取原图片
	Mat Image = imread("D:\\opencv_picture_test\\霍夫变换\\金属.png");
	//显示原图片
	namedWindow("【原图】");
	imshow("【原图】", Image);

	Mat srcImage = Image.clone();
	Mat midImage, dstImage;
	//进行边缘检测和转化为将灰度图转为RGB图
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//定义矢量结构lines用于存放得到的线段矢量集合
	vector<Vec4i> lines;
	//进行霍夫变换
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 50, 30, 10);
	//依次在图中绘制每条线段
	for (size_t i = 0;i < lines.size();i++) {
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
	}

	imshow("【边缘检测后的图】", midImage);
	imshow("【效果图】", dstImage);

	waitKey(0);
	return 0;
}