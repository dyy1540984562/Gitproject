#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏

using namespace cv;
using namespace std;
//====================================练习1:canny=====================================

//int main()
//{
//	// Read image 读取图像
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//载入原图
//	Mat srcImage = imread("D:\\opencv_picture_test\\lena,jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcImage.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	Mat dstImage;
//	Mat gradx, grady;
//	Mat dstImage;
//	//求x方向的梯度
//	Sobel(srcImage, gradx, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);//	x方向1阶差分 y方向0 核大小3
//	//求y方向的梯度
//	Sobel(srcImage, grady, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);//	x方向1阶差分 y方向0 核大小3
//	Canny(gradx, grady, dstImage, 100, 33,false);
//	//Canny(srcImage, dstImage, 100, 33, 3, false);
//
//	imshow("srcImage", srcImage);
//
//	imshow("整体", dstImage);
//	waitKey(0);
//	return 0;
//}

//====================================练习2旋转和缩放=====================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//【1】参数准备
//	//定义两组点，代表两个三角形
//	Point2f srcTriangle[3];
//	Point2f dstTriangle[3];
//	//定义Mat变量（变换矩阵）
//	Mat rotMat(2, 3, CV_32FC1);	//CV_32FC1代表一个32位浮点型单通道
//	Mat srcImage, dstImage_roate;
//	//原图，仿射变换后的图，旋转变换后的图
//	srcImage = imread("D:\\opencv_picture_test\\lena.jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcImage.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//【5】获取旋转信息
//	Point center = Point(srcImage.cols / 2, srcImage.rows / 2);	//中心点
//	double angle = -30.0;			//顺时针30度
//	double scale = 0.8;
//	//【6】通过上面的旋转细节信息求得旋转矩阵
//	rotMat = getRotationMatrix2D(center, angle, scale);
//	//【7】对缩放后的图像进行旋转
//	warpAffine(srcImage, dstImage_roate, rotMat, srcImage.size());
//	//【8】显示结果
//	namedWindow("原图像", WINDOW_NORMAL);     //定义窗口显示属性
//	imshow("原图像", srcImage);
//	imshow("缩放旋转图", dstImage_roate);
//	//创建三个窗口
//	waitKey(0);
//	return 0;
//}

////====================================练习3:仿射变换=====================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//定义两组点，代表两个三角形
//	//定义Mat变量（变换矩阵）
//	Mat srcMat, dstMat;
//	//原图，仿射变换后的图，旋转变换后的图
//	srcMat = imread("D:\\opencv_picture_test\\lena.jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcMat.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//变换前的三点坐标
//	const cv::Point2f src_pt[] = {
//	cv:: Point2f(200, 200),
//	cv:: Point2f(250,200),
//	cv:: Point2f(200,100) };
//	//变换后的三点坐标
//	const cv::Point2f dst_pt[] = {
//	cv:: Point2f(300, 100),
//	cv:: Point2f(300, 50),
//	cv:: Point2f(200,100) };
//	//计算仿射矩阵
//	const cv::Mat affine_matrix = cv:: getAffineTransform(src_pt,dst_pt);
//	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());
//	imshow(" src ",srcMat);
//	imshow(" dst",dstMat);
//	waitKey(0);
//	return 0;
//}

//====================================练习4:投影变换=====================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//定义Mat变量（变换矩阵）
//	Mat srcMat, dstMat;
//	//原图，仿射变换后的图，旋转变换后的图
//	srcMat = imread("D:\\opencv_picture_test\\lena.jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcMat.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//变换前的点坐标
//	const cv::Point2f src_pt[] = {
//						cv::Point2f(150, 150),
//						cv::Point2f(150,300),
//						cv::Point2f(350,300), 
//						cv::Point2f(350,150)
//	};
//	//变换后的点坐标
//	const cv::Point2f dst_pt[] = {
//						cv::Point2f(200, 150),
//						cv::Point2f(200, 300),
//						cv::Point2f(340,270),
//						cv::Point2f(340,180)
//	};
//	//计算仿射矩阵
//	Mat perspective_matrix =getPerspectiveTransform(src_pt,dst_pt);
//	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());
//	imshow(" src ", srcMat);
//	imshow(" dst", dstMat);
//	waitKey(0);
//	return 0;
//}

//====================================练习5:图像矫正=====================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//定义Mat变量（变换矩阵）
//	Mat srcMat, dstMat;
//	//原图，仿射变换后的图，旋转变换后的图
//	srcMat = imread("D:\\opencv_picture_test\\lena_rot.jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcMat.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//遍历找四个点
//	Point2f one;
//	Point2f two;
//	Point2f three;
//	Point2f four;
//	//第一行
//	for (int i = 0;i < srcMat.cols;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(0, i)[0] + srcMat.at<Vec3b>(0, i)[1] + srcMat.at<Vec3b>(0, i)[2]) / 3;
//		if (temp <= 250)
//		{
//			one.x = 0;
//			one.y = i;
//			break;
//		}
//	}
//	//最后一行
//	for (int i = 0;i < srcMat.cols;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(srcMat.rows - 1, i)[0] + srcMat.at<Vec3b>(srcMat.rows - 1, i)[1] + srcMat.at<Vec3b>(srcMat.rows - 1, i)[2]) / 3;
//		if (temp <= 250)
//		{
//			four.x = srcMat.rows - 1;
//			four.y = i;
//			break;
//		}
//	}
//	//第一列
//	for (int i = 0;i < srcMat.rows;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(i,0)[0] + srcMat.at<Vec3b>(i, 0)[1] + srcMat.at<Vec3b>(i, 0)[2]) / 3;
//		if (temp <= 250)
//		{
//			three.x = i;
//			three.y = 0;
//			break;
//		}
//	}
//	//最后一列
//	for (int i = 0;i < srcMat.rows;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(i, srcMat.cols-1)[0] + srcMat.at<Vec3b>(i, srcMat.cols - 1)[1] + srcMat.at<Vec3b>(i, srcMat.cols - 1)[2]) / 3;
//		if (temp <= 250)
//		{
//			two.x = i;
//			two.y = srcMat.cols-1;
//			break;
//		}
//	}
//	//变换前的点坐标
//	const cv::Point2f src_pt[] = {
//						//one,
//						//two,
//						//three,
//						//four
//						Point2f(one.y,one.x),
//						Point2f(two.y,two.x),
//						Point2f(three.y,three.x),
//						Point2f(four.y,four.x)
//	};
//	//计算变换后的MAT长度
//	int chandu = sqrt((srcMat.cols - 1 - one.y)* (srcMat.cols - 1 - one.y) + (two.x)* (two.x));
//
//	//变换后的点坐标
//	const cv::Point2f dst_pt[] = {
//						cv::Point2f(0,0),
//						/*cv::Point2f(0,srcMat.cols - 1),
//						cv::Point2f(srcMat.rows - 1,0),
//						cv::Point2f(srcMat.rows - 1,srcMat.cols - 1)*/
//						cv::Point2f(srcMat.cols - 1,0),
//						cv::Point2f(0,srcMat.rows - 1),
//						cv::Point2f(srcMat.cols - 1,srcMat.rows - 1)
//	};
//
//	//计算仿射矩阵
//	Mat perspective_matrix = getPerspectiveTransform(src_pt, dst_pt);
//	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());
//	imshow(" src ", srcMat);
//	imshow(" dst", dstMat);
//	waitKey(0);
//	return 0;
//}

//====================================练习6:图像矫正加剪切（待完成）=====================================

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//定义Mat变量（变换矩阵）
//	Mat srcMat, dstMat;
//	//原图，仿射变换后的图，旋转变换后的图
//	srcMat = imread("D:\\opencv_picture_test\\lena_rot.jpg");	//读取灰度图
//	//判断图像是否加载成功
//	if (srcMat.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//遍历找四个点
//	Point2f one;
//	Point2f two;
//	Point2f three;
//	Point2f four;
//	//第一行
//	for (int i = 0;i < srcMat.cols;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(0, i)[0] + srcMat.at<Vec3b>(0, i)[1] + srcMat.at<Vec3b>(0, i)[2]) / 3;
//		if (temp <= 250)
//		{
//			one.x = 0;
//			one.y = i;
//			break;
//		}
//	}
//	//最后一行
//	for (int i = 0;i < srcMat.cols;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(srcMat.rows - 1, i)[0] + srcMat.at<Vec3b>(srcMat.rows - 1, i)[1] + srcMat.at<Vec3b>(srcMat.rows - 1, i)[2]) / 3;
//		if (temp <= 250)
//		{
//			four.x = srcMat.rows - 1;
//			four.y = i;
//			break;
//		}
//	}
//	//第一列
//	for (int i = 0;i < srcMat.rows;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(i,0)[0] + srcMat.at<Vec3b>(i, 0)[1] + srcMat.at<Vec3b>(i, 0)[2]) / 3;
//		if (temp <= 250)
//		{
//			three.x = i;
//			three.y = 0;
//			break;
//		}
//	}
//	//最后一列
//	for (int i = 0;i < srcMat.rows;i++)
//	{
//		int temp = (srcMat.at<Vec3b>(i, srcMat.cols-1)[0] + srcMat.at<Vec3b>(i, srcMat.cols - 1)[1] + srcMat.at<Vec3b>(i, srcMat.cols - 1)[2]) / 3;
//		if (temp <= 250)
//		{
//			two.x = i;
//			two.y = srcMat.cols-1;
//			break;
//		}
//	}
//	//变换前的点坐标
//	const cv::Point2f src_pt[] = {
//						//one,
//						//two,
//						//three,
//						//four
//						Point2f(one.y,one.x),
//						Point2f(two.y,two.x),
//						Point2f(three.y,three.x),
//						Point2f(four.y,four.x)
//	};
//	//计算变换后的MAT长度
//	int chandu = sqrt((srcMat.cols - 1 - one.y)* (srcMat.cols - 1 - one.y) + (two.x)* (two.x));
//
//	//变换后的点坐标
//	const cv::Point2f dst_pt[] = {
//						cv::Point2f(0,0),
//						/*cv::Point2f(0,srcMat.cols - 1),
//						cv::Point2f(srcMat.rows - 1,0),
//						cv::Point2f(srcMat.rows - 1,srcMat.cols - 1)*/
//						cv::Point2f(srcMat.cols - 1,0),
//						cv::Point2f(0,srcMat.rows - 1),
//						cv::Point2f(srcMat.cols - 1,srcMat.rows - 1)
//	};
//
//	//计算仿射矩阵
//	Mat perspective_matrix = getPerspectiveTransform(src_pt, dst_pt);
//	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());
//	imshow(" src ", srcMat);
//	imshow(" dst", dstMat);
//	waitKey(0);
//	return 0;
//}