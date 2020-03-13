#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>

using namespace cv;
using namespace std;
#define byte uchar 
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏


//*--------------------------【练习1】利用不同的物体在HSV色彩空间上的不同色域，实现目标像素的提取-------------------------------------*/
//*--------------------------【主函数】-------------------------------------*/

//int main()
//{
//	VideoCapture cap(0);
//	double scale = 0.5;
//	//0-180
//	//肤色
//	double i_minH = 0;
//	double i_maxH = 20;
//	//0-255
//	double i_minS = 1;//43
//	double i_maxS = 255;
//	//0-255
//	double i_minV = 50;//55
//	double i_maxV = 255;
//	while(1)
//	{
//		Mat frame;
//		Mat hsvMat;
//		Mat detectMat;
//		cap >> frame;
//		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
//		Mat rFrame =Mat(ResImgSiz, frame.type());
//		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
//		cvtColor(rFrame, hsvMat,COLOR_BGR2HSV);
//		rFrame.copyTo(detectMat);
//		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH,i_maxS, i_maxV), detectMat);
//		imshow("whie: in the range", detectMat);
//		imshow("frame" , rFrame );
//		waitKey(30);
//	}
//	return 0;
//}


//*--------------------------【练习2】调用两种二值化函数，实现二值化 +加上自己实现的大津阈值法-------------------------------------*/

//void My_Ostu(Mat* srcImage, Mat* dstImage)
//{
//	int height = (*srcImage).rows;
//	int width = (*srcImage).cols;
//	int Ostu_Threshold = 0; //大津阈值
//	int size = height * width;
//	float variance;   //类间方差
//	float maxVariance = 0, w1 = 0, w2 = 0, avgValue = 0;
//	float u0 = 0, u1 = 0, u2 = 0;
//	//生成灰度直方图
//	int pixels[256];
//	float histgram[256];
//	for (int i = 0; i < 256; i++)
//	{
//		pixels[i] = 0;
//	}
//	for (int j = 0; j < height; j++)
//	{
//		for (int i = 0; i < width; i++)
//		{
//			pixels[(*srcImage).at<uchar>(j, i)]++;
//		}
//	}
//	for (int i = 0; i < 256; i++)
//	{
//		histgram[i] = pixels[i] * 1.0f / size;
//	}
//	//遍历找出类间方差最大（maxVariance）的阈值（Ostu_Threshold）
//	for (int i = 0;i <= 255;i++)
//	{
//		w1 = 0;
//		w2 = 0;
//		u1 = 0;
//		u2 = 0;
//		//计算背景像素占比,平均灰度
//		for (int j = 0;j <= i;j++)
//		{
//			w1 += histgram[j];
//			u1 += histgram[j] * j;
//		}
//		u1 = u1 / w1;
//		//计算前景像素占比,平均灰度
//		w2 = 1 - w1;
//		if (i == 255)
//		{
//			u2 = 0;
//		}
//		else
//		{
//			for (int j = i + 1;j <= 255;j++)
//			{
//				u2 += histgram[j] * j;
//			}
//		}
//		u2 = u2 / w2;
//		//计算类间方差
//		variance = w1 * w2 * (u1 - u2) * (u1 - u2);
//		if (variance > maxVariance)
//		{ //找到使灰度差最大的值
//			maxVariance = variance;
//			Ostu_Threshold = i;            //那个值就是阈值
//		}
//	}
//	cout << "手动大津法阈值为：" << Ostu_Threshold << endl;
//	//【3】二值化
//	for (int j = 0; j < height; j++)
//	{
//		for (int i = 0; i < width; i++)
//		{
//			if ((*srcImage).at<uchar>(j, i) >= Ostu_Threshold)
//			{
//				(*dstImage).at<uchar>(j, i) = 255;
//			}
//			else
//			{
//				(*dstImage).at<uchar>(j, i) = 0;
//			}
//
//		}
//	}
//}
//
//
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\阈值处理\\硬币.png", 0);	//读入的时候转化为灰度图
//	namedWindow("原始图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("原始图", srcImage);
//
//	Mat dstImage1,dstImage2,dstImage3,dstImage4;
//	dstImage1.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	dstImage2.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	dstImage3.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	dstImage4.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	double time0 = static_cast<double>(getTickCount());	//记录起始时间
//	//阈值处理+二值化
//	//第一种:固定阈值
//	threshold(srcImage,dstImage1,83,255,THRESH_BINARY);
//	//第二种:局部自适应阈值
//	adaptiveThreshold(srcImage,dstImage2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,10);//		原图  结果图   预设满足条件的最大值		自适应阈值算法   二进制阈值或反二进制阈值   局部区域的尺寸 3 5 7      该参数和算法有关
//	//第三种(手动实现大津阈值)
//	My_Ostu(&srcImage,&dstImage3);
//	//第四种(调用大津库函数)
//	threshold(srcImage, dstImage4, 83, 255, THRESH_OTSU);
//	//一系列处理之后
//	time0 = ((double)getTickCount() - time0) / getTickFrequency();
//	cout << "此方法运行时间为：" << time0 << "秒" << endl;	//输出运行时间
//	namedWindow("固定阈值",WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("固定阈值", dstImage1);
//	namedWindow("自适应阈值", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("自适应阈值", dstImage2);
//	namedWindow("手动实现大津阈值", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("手动实现大津阈值", dstImage3);
//	namedWindow("调用大津库函数", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("调用大津库函数", dstImage4);
//	waitKey(0);
//	return 0;
//}



//*--------------------------【练习3】利用滑动条来调整阈值-------------------------------------*/

/*--------------------------【全局变量声明】-------------------------------------*/
//int g_nThresholdValue = 100;
//int g_nThresholdType = 3;
//Mat g_srcImage, g_grayImage, g_dstImage;
//
////*--------------------------【全局函数声明】-------------------------------------*/
//static void ShowHelpText();		//输出帮助文字
//void on_Threshold(int ,void*);	//回调函数
//
////*--------------------------【主函数】-------------------------------------*/
//int main()
//{
//		//【1】读入原图片
//	    g_srcImage = imread("D:\\opencv_picture_test\\阈值处理\\硬币.png", 2|4);
//		if (g_srcImage.empty())
//		{
//			printf("Could not find the image!\n");
//			return -1;
//		}
//		//【2】存留原图的灰度图
//		cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
//		namedWindow(WINDOW_NAME, WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//		//【3】创建窗口 并 显示原图
//		imshow("原始图", g_srcImage);
//		//【4】创建滑动条来控制阈值
//		createTrackbar("模式",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
//		createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue,255, on_Threshold);
//		//【5】初始化自定义的阈值回调函数
//		on_Threshold(0,0);
//		//【6】输出一些帮助信息
//		ShowHelpText();
//		//【7】轮询等待用户按键，如果ESC键按下则退出程序
//		while (1)
//		{
//			if (waitKey(10) == 27) break;		//按下Esc 退出
//		}
//		//imwrite("D:\\opencv_picture_test\\阈值处理\\硬币二值化.jpg", g_dstImage);
//		return 0;
//}
//
////*--------------------------【on_Threshold 函数】-------------------------------------*/
//void on_Threshold(int, void*)
//{
//	//调用阈值函数
//	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
//	//其它参数很好理解，我们来看看第五个参数，第五参数有以下几种类型
//	//	0: THRESH_BINARY  当前点值大于阈值时，取Maxval, 也就是第四个参数，下面再不说明，否则设置为0
//	//	1 : THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval
//	//	2 : THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变
//	//	3 : THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0
//	//	4 : THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变
//	//更新效果图
//	imshow(WINDOW_NAME,g_dstImage);
//}
//
////-----------------------------------【ShowHelpText( )函数】-----------------------------
////          描述：输出一些帮助信息
////----------------------------------------------------------------------------------------------
//void ShowHelpText()
//{
//	//输出一些帮助信息
//	printf("\n\n\n\tg_nThresholdType 参数有以下几种类型\n");
//	printf("\n\n\t0: THRESH_BINARY  当前点值大于阈值时，取Maxval, 也就是第四个参数，下面再不说明，否则设置为0\n");
//	printf("\n\n\t1 : THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval\n");
//	printf("\n\n\t2 : THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变\n");
//	printf("\n\n\t3 : THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0\n");
//	printf("\n\n\t4 : THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变\n");
//	printf("\n\n\t按下esc 退出循环\n");
//}



