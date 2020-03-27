#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include "My_ImageProssing_base.h"

using namespace cv;
using namespace std;




//练习1中值滤波

//int main()
//{
//	VideoCapture capture(0);
//	//VideoCapture capture("D:\\opencv_picture_test\\videos\\脸.avi");		
//	while (1)
//	{
//		Mat img, dst;
//		capture >> img;	//读取当前帧
//		//imshow("原视频", img);	//显示当前帧
//		medianBlur(img, dst, 5);
//		imshow("中值滤波", dst);//显示当前帧
//		if (waitKey(10) >= 0) break;	//延时10ms
//	}
//	return 0;
//}
//练习2均值滤波

//int main()
//{
//	VideoCapture capture(0);
//	//VideoCapture capture("D:\\opencv_picture_test\\videos\\脸.avi");		
//	while (1)
//	{
//		Mat img,dst;
//		capture >> img;	//读取当前帧
//		//imshow("原视频", img);	//显示当前帧
//		blur(img,dst, Size(5,5));
//		imshow("均值滤波",dst);//显示当前帧
//		if (waitKey(10) >= 0) break;	//延时10ms
//	}
//	return 0;
//}

//练习3高斯滤波

//int main()
//{
//	VideoCapture capture(0);
//	//VideoCapture capture("D:\\opencv_picture_test\\videos\\脸.avi");		
//	while (1)
//	{
//		Mat img, dst;
//		capture >> img;	//读取当前帧
//		//imshow("原视频", img);	//显示当前帧
//		GaussianBlur(img, dst, Size(5, 5), 0, 0);
//		imshow("高斯滤波", dst);//显示当前帧
//		if (waitKey(10) >= 0) break;	//延时10ms
//	}
//	return 0;
//}

//练习4 sobel边缘提取

//int main()
//{
//	VideoCapture capture(0);
//	//VideoCapture capture("D:\\opencv_picture_test\\videos\\脸.avi");		
//	while (1)
//	{
//		Mat srcImage;
//		capture >> srcImage;	//读取当前帧
//		//imshow("原视频", img);	//显示当前帧
//		Mat gradx, grady;
//		Mat abs_gradx, abs_grady;
//		Mat dstImage;
//		//求x方向的梯度
//		Sobel(srcImage, gradx, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);//	x方向1阶差分 y方向0 核大小3
//		convertScaleAbs(gradx, abs_gradx);		//绝对值
//		//求y方向的梯度
//		Sobel(srcImage, grady, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);//	x方向1阶差分 y方向0 核大小3
//		convertScaleAbs(grady, abs_grady);		//绝对值
//		addWeighted(abs_gradx, 0.5, abs_grady, 0.5, 0, dstImage);
//
//		imshow("srcImage", srcImage);
//		imshow("x方向", abs_gradx);
//		imshow("y方向", abs_grady);
//		imshow("整体", dstImage);
//		if (waitKey(10) >= 0) break;	//延时10ms
//	}
//	return 0;
//}

//练习5 利用Opencv自带的分类器检测人脸并对ROI区域进行部分处理

//训练文件路径
string xmlPath = "D:\\opencv\\opencv4.0\\opencv4.0.0\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";
//打马赛克函数
void mosaic(Mat& srcImage, Mat& dstImage, int times)
{
	blur(srcImage, dstImage, Size(times * 2 + 1, times * 2 + 1));
}
void clearFreckle(Mat& srcImage, Mat& dstImage, int times)
{
	bilateralFilter(srcImage, dstImage, times, times * 2, times / 2);
}
void paste(Mat& srcImage, Mat& dstImage)
{
	resize(srcImage, dstImage, dstImage.size());
}
int main()
{
	//Mat img = imread("D:\\opencv_picture_test\\beauty\\裴佳欣.png",0);
	//Mat img2 = imread("D:\\opencv_picture_test\\趣图景图\\小猪.jpg", 0);
	//imshow("input image", img);
	//【1】加载分类器
	CascadeClassifier detector;
	detector.load(xmlPath);
	if (!detector.load(xmlPath))   //加载训练文件  
	{
		cout << "不能加载指定的xml文件" << endl;
		return -1;
	}
	//调用摄像头
	VideoCapture capture(0);		//类似于 int a=1;
	//VideoCapture capture("D:\\opencv_picture_test\\videos\\脸.avi");		//类似于 int a=1;
	while (1)
	{
		Mat img;
		capture >> img;	//读取当前帧
		//imshow("原视频", img);	//显示当前帧
		cvtColor(img, img, COLOR_BGR2GRAY);		//转化为灰度图
		Mat dstImage = img.clone();
		//【2】检测人脸，将信息存储到矩形类faces中
		vector<Rect> faces;
		detector.detectMultiScale(img, faces, 1.1, 3, 0);//分类器对象调用
		//【3】修改区域信息
		for (size_t t = 0; t < faces.size(); t++)
		{
			int rows = faces[t].height;
			int cols = faces[t].width;
			int start_y = faces[t].y;
			int start_x = faces[t].x;
			Mat ROI(rows, cols, CV_8UC1, Scalar(0));
			Mat dstROI(rows, cols, CV_8UC1, Scalar(0));
			for (int j = 0;j < rows;j++)	//行循环
			{
				for (int i = 0;i < cols;i++)	//列循环
				{
					//-------【开始处理每个像素】---------------
					ROI.at<uchar>(j, i) = img.at<uchar>(j + start_y, i + start_x);
					//-------【处理结束】---------------
				}
			}
			//马赛克化
			//mosaic(ROI,dstROI,10);
			//贴图
			//paste(img2, dstROI);
			//去雀斑(磨皮)
			clearFreckle(ROI, dstROI, 10);
			for (int j = 0;j < rows;j++)	//行循环
			{
				for (int i = 0;i < cols;i++)	//列循环
				{
					//-------【开始处理每个像素】---------------
					dstImage.at<uchar>(j + start_y, i + start_x) = dstROI.at<uchar>(j, i);
					//-------【处理结束】---------------
				}
			}
		}
		imshow("处理后的视频", dstImage);	//显示当前帧
		if (waitKey(10) >= 0) break;	//延时10ms
	}
	return 0;
}





















//
//int main()
//{
//	// Read image 读取图像
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//载入原图
//	Mat srcImage = imread("D:\\opencv_picture_test\\形态学操作\\coin_inv.png", 0);	//读取灰度图
//	//判断图像是否加载成功
//	if (srcImage.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	Mat dstImage,abs_dst;
//	GaussianBlur(srcImage,srcImage,Size(3,3),0);	//高斯模糊
//	Laplacian(srcImage,dstImage,CV_16S,3,1,0);
//	convertScaleAbs(dstImage, abs_dst);
//	imshow("srcImage", srcImage);
//
//	imshow("整体", dstImage);
//	waitKey(0);
//	return 0;
//}

