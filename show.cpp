#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
#include<opencv2/imgproc/types_c.h> 
//#include "My_ImageProssing_base.h"
#define WINDOW_NAME1 "【程序窗口1】"			
#define WINDOW_NAME2 "【程序窗口2】"	
using namespace cv;
using namespace std;
RNG g_rng(12345);

//识别并标出火焰
//输入 原图像 输出：原图像上框出框框（火）
void find_fire(Mat& srcMat, Mat& outputMat)
{
	Mat gray_srcMat;
	Mat dstMat, binMat;
	cvtColor(srcMat, gray_srcMat, COLOR_BGR2GRAY);
	Mat fire_Mat = Mat::zeros(gray_srcMat.size(), gray_srcMat.type());
	cvtColor(srcMat, dstMat, COLOR_BGR2HSV);
	vector<Mat> channels;
	split(dstMat, channels);
	//将S通道的图像复制，然后处理
	Mat S_Mat;
	channels.at(1).copyTo(S_Mat);
	int row_num = srcMat.rows;			//行数
	int col_num = srcMat.cols;			//列数
	//双重循环，遍历右下角像素值
	for (int i = row_num * 0.75;i < row_num;i++)	//行循环
	{
		for (int j = col_num * 0.75;j < col_num;j++)	//列循环
		{
			//-------【开始处理每个像素】---------------
			if ((gray_srcMat.at<uchar>(i, j) >= 150 && S_Mat.at<uchar>(i, j) >= 120))
			{
				fire_Mat.at<uchar>(i, j) = 255;
			}
			//-------【处理结束】---------------
		}
	}
	//膨胀
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//返回的是内核矩阵
	Mat firedstImage;
	dilate(fire_Mat, fire_Mat, element);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(fire_Mat, contours, RETR_LIST, CHAIN_APPROX_NONE);
	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		drawContours(srcMat, contours, i, Scalar(0, 255, 255), 1, 8);
		Point2f vtx[4];
		rbox.points(vtx);
		for (int j = 0; j < 4; ++j) {
			cv::line(outputMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(255, 255, 255), 2, LINE_AA);
		}
	}
}
//--------------------------------------------工程大作业---------------------------------------------------

//输入：二值化图片  输出：点集 （每列最多只有一个点，符合函数一一映射的关系）
void find_point(Mat& binMat, std::vector<cv::Point>& key_point)
{
	//第一个点肯定是水枪位置

	//遍历：170列到430列
	//		30行到230行
	//遍历方式：遍历每列，从上往下遍历（小到大），找到的第一个为白的点记录下来，如果遍历完这一列并没有发现白色点，则不作记录
	//注意这里的循环方式与其他地方的相反
	for (int i = 170;i < 430;i++)	//列循环
	{
		for (int j =30;j < 230;j++)	//行循环
		{
			if (binMat.at<uchar>(j, i) == 255)
			{
				//行列与坐标系对应关系
				//行rows: Y(height)
				//列cols : X(width)
				//注意!注意!注意!
				//在Mat类型变量访问时下标是反着写的
				key_point.push_back(cv::Point(i,j));
				break;
			}
		}
	}
	//打印出来让我看看
	int N= key_point.size();
	for (int n = 0;n < N;n++)
	{
		cout << "point"<< key_point[n].x<<" "<< key_point[n].y << endl;
	}
	//画出来
	Mat image = cv::Mat::zeros(binMat.rows, binMat.cols, CV_8UC3);
	for (int i = 0; i < key_point.size(); i++)
	{
		cv::circle(image, key_point[i], 5, cv::Scalar(0, 0, 255), 2, 8, 0);
	}
	//imshow("tu", image);
}

//输入：待拟合的点集，拟合出来的曲线的点
bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A)
{
	//Number of key points
	int N = key_point.size();

	//构造矩阵X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<double>(i, j) = X.at<double>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}

	//构造矩阵Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<double>(i, 0) = Y.at<double>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}

	A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//求解矩阵A
	cv::solve(X, Y, A, cv::DECOMP_LU);
	return true;
}

//输入：图片 输出：去除干扰后的图
void clear_other_disturb(Mat& srcMa)
{
	//通过观察、发现0-180列为干扰，320-480列且0-90行为干扰
	for (int i = 0;i < 90;i++)	//行循环
	{
		for (int j = 320;j < srcMa.cols;j++)	//列循环
		{
			//-------【开始处理每个像素】---------------

			srcMa.at<uchar>(i, j) = 0;
			//-------【处理结束】---------------
		}
	}
	for (int i = 0;i < srcMa.rows;i++)	//行循环
	{
		for (int j = 0;j < 180;j++)	//列循环
		{
			//-------【开始处理每个像素】---------------

			srcMa.at<uchar>(i, j) = 0;
			//-------【处理结束】---------------
		}
	}
}
int main()
{
	//实例化的同时初始化
	VideoCapture capture("D:\\opencv_picture_test\\videos\\大作业.avi");		//类似于 int a=1;
		//如果视频打开失败
	//计数器
	int cnt = 0;
	Mat frame;
	Mat rgb_mat;		
	Mat rgb_mat1;
	Mat bgMat1;		//第0帧图像
	Mat bgMat2;		//之后每帧图像
	while (1)
	{
		capture >> frame;
		//图像保护
		if (!frame.data)
		{
			cout << "src image load failed!" << endl;
			break;
		}
		//将彩色图保存下来，用于最后画图的底布
		rgb_mat = frame.clone();
		rgb_mat1= frame.clone();
		//转灰度图，用于之后的找水柱
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0)
		{
			//第一帧，获得背景图像
			frame.copyTo(bgMat1);
			//找火
			find_fire(rgb_mat, rgb_mat);
			imshow("output", rgb_mat);
			waitKey(20);
		}
		else if (cnt<=100)	//水柱还没有出现，我们不找水柱，防止误判（其实是有误判的），此时我们只绘制火焰
		{
			//找火
			find_fire(rgb_mat, rgb_mat);
			imshow("output", rgb_mat);
			waitKey(20);
		}
		else
		{
			//获取本次场景的图像
			frame.copyTo(bgMat2);
			//====================================进行处理================================================
			Mat result = bgMat1.clone();
			//【1】背景图像和当前图像相减
			absdiff(bgMat1, bgMat2, result);
			//【2】接下来是去除干扰
			clear_other_disturb(result);
			//【3】二值化一下
			threshold(result, result, 100, 255, THRESH_BINARY);
			//imshow("result", result);
			//【4】找点
			std::vector<cv::Point> points;
			find_point(result, points);
			//【5】找到点之后就是拟合曲线，这里采用【https://blog.csdn.net/guduruyu/article/details/72866144】的思路
			cv::Mat A;
			//这里使用3次函数，效果很好
			polynomial_curve_fit(points, 3, A);
			std::cout << "A = " << A << std::endl;
			std::vector<cv::Point> points_fitted;
			for (int x = 170; x < 430; x++)
			{
				double y = A.at<double>(0, 0) + A.at<double>(1, 0) * x +
					A.at<double>(2, 0) * std::pow(x, 2) + A.at<double>(3, 0) * std::pow(x, 3);

				points_fitted.push_back(cv::Point(x, y));
			}
			//【6】在彩色图上绘制水柱
			cv::polylines(rgb_mat, points_fitted, false, cv::Scalar(0, 255, 255), 1, 8, 0);
			find_fire(rgb_mat1, rgb_mat);
			imshow("output", rgb_mat);
			//====================================处理结束================================================
			waitKey(20);
		}
		cnt++;
	}
	waitKey(0);
	return 0;
}


