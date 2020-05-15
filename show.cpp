#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include<opencv2/highgui.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
#include "My_ImageProssing_base.h"
#include<opencv2/imgproc/types_c.h> 
#define WINDOW_NAME "【程序窗口】"			
using namespace cv;
using namespace std;

//RNG g_rng(12345);



/*********************************************练习1：gama矫正*****************************************************/
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\直方图均衡与矫正\\face.jpg",1);			//原图
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//【转化为灰度图】
//	cvtColor(srcImage, srcImage,COLOR_BGR2GRAY);
//	int row_num = srcImage.rows;
//	int col_num = srcImage.cols;
//	//进行表的建立
//	float gama = 0.3;
//	float LUT[256] = { 0 };
//	for (int i = 0; i < 256; i++) 
//	{
//		LUT[i] = pow(i * 1.0 / 255, gama);
//	}
//	for (int i = 0;i < row_num;i++)	//行循环
//	{
//		for (int j = 0;j < col_num;j++)	//列循环
//		{
//			srcImage.at<uchar>(i, j) = LUT[srcImage.at<uchar>(i, j)] * 255;
//		}
//	}
//
//	//【显示结果】
//	namedWindow("gama", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("gama", srcImage);
//	waitKey(0);
//	return 0;
//}


/*********************************************练习2：直方图均衡*****************************************************/
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\直方图均衡与矫正\\etest.jpg",1),dstImage;			//原图
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	首先分到三个通道里面去
//	Mat channels[3];
//	Mat dst_channels[3];
//	src为要分离的Mat对象  
//	split(srcImage, channels);               //利用vector对象分离  
//
//	imshow("B", channels[0]);
//	imshow("G", channels[1]);
//	imshow("R", channels[2]);
//	对每个通道的图像进行均衡化
//	for (int i = 0;i <= 2;i++)
//	{
//		equalizeHist(channels[i], dst_channels[i]);
//	}
//	合并
//	 merge(dst_channels,3, dstImage);
//	【显示结果】
//	namedWindow("经过直方图均衡化后的图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("经过直方图均衡化后的图", dstImage);
//	waitKey(0);
//	return 0;
//}


/*********************************************练习3：gama矫正*****************************************************/
int main()
{
	Mat srcImage = imread("D:\\opencv_picture_test\\直方图均衡与矫正\\gtest.jpg",1);			//原图
	if (srcImage.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}
	//【转化为灰度图】
	cvtColor(srcImage, srcImage,COLOR_BGR2GRAY);
	int row_num = srcImage.rows;
	int col_num = srcImage.cols;
	//进行表的建立
	float gama = 0.3;
	float LUT[256] = { 0 };
	for (int i = 0; i < 256; i++) 
	{
		LUT[i] = pow(i * 1.0 / 255, gama);
	}
	for (int i = 0;i < row_num;i++)	//行循环
	{
		for (int j = 0;j < col_num;j++)	//列循环
		{
			srcImage.at<uchar>(i, j) = LUT[srcImage.at<uchar>(i, j)] * 255;
		}
	}

	//【显示结果】
	namedWindow("gama", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("gama", srcImage);
	waitKey(0);
	return 0;
}

