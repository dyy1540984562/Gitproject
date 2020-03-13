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


//*--------------------------【练习2】调用两种二值化函数，实现二值化-------------------------------------*/

//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\阈值处理\\硬币.png", 0);	//读入的时候转化为灰度图
//	namedWindow("原始图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("原始图", srcImage);
//
//	Mat dstImage1,dstImage2;
//	dstImage1.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	dstImage2.create(srcImage.rows, srcImage.cols, CV_8UC1);
//	double time0 = static_cast<double>(getTickCount());	//记录起始时间
//	//阈值处理+二值化
//	//1
//	threshold(srcImage,dstImage1,83,255,THRESH_BINARY);
//	adaptiveThreshold(srcImage,dstImage2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,10);
//	//		原图  结果图   预设满足条件的最大值		自适应阈值算法   二进制阈值或反二进制阈值   局部区域的尺寸 3 5 7      该参数和算法有关
//	//一系列处理之后
//	time0 = ((double)getTickCount() - time0) / getTickFrequency();
//	cout << "此方法运行时间为：" << time0 << "秒" << endl;	//输出运行时间
//	namedWindow("效果图1",WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("效果图1", dstImage1);
//	namedWindow("效果图2", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("效果图2", dstImage2);
//	//dstImage = My_Rraw_histogram(&srcImage);
//	//namedWindow("一维直方图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	//imshow("一维直方图", dstImage);
//	waitKey(0);
//	return 0;
//}



//*--------------------------【练习3】利用滑动条来调整阈值-------------------------------------*/

/*--------------------------【全局变量声明】-------------------------------------*/
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

//*--------------------------【全局函数声明】-------------------------------------*/
static void ShowHelpText();		//输出帮助文字
void on_Threshold(int ,void*);	//回调函数

//*--------------------------【主函数】-------------------------------------*/
int main()
{
		//【1】读入原图片
	    g_srcImage = imread("D:\\opencv_picture_test\\阈值处理\\硬币.png", 2|4);
		if (g_srcImage.empty())
		{
			printf("Could not find the image!\n");
			return -1;
		}
		//【2】存留原图的灰度图
		cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
		namedWindow(WINDOW_NAME, WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
		//【3】创建窗口 并 显示原图
		imshow("原始图", g_srcImage);
		//【4】创建滑动条来控制阈值
		createTrackbar("模式",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
		createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue,255, on_Threshold);
		//【5】初始化自定义的阈值回调函数
		on_Threshold(0,0);
		//【6】输出一些帮助信息
		ShowHelpText();
		//【7】轮询等待用户按键，如果ESC键按下则退出程序
		while (1)
		{
			if (waitKey(10) == 27) break;		//按下Esc 退出
		}
		//imwrite("D:\\opencv_picture_test\\阈值处理\\硬币二值化.jpg", g_dstImage);
		return 0;
}

//*--------------------------【on_Threshold 函数】-------------------------------------*/
void on_Threshold(int, void*)
{
	//调用阈值函数
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	//其它参数很好理解，我们来看看第五个参数，第五参数有以下几种类型
	//	0: THRESH_BINARY  当前点值大于阈值时，取Maxval, 也就是第四个参数，下面再不说明，否则设置为0
	//	1 : THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval
	//	2 : THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变
	//	3 : THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0
	//	4 : THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变
	//更新效果图
	imshow(WINDOW_NAME,g_dstImage);
}

//-----------------------------------【ShowHelpText( )函数】-----------------------------
//          描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//输出一些帮助信息
	printf("\n\n\n\tg_nThresholdType 参数有以下几种类型\n");
	printf("\n\n\t0: THRESH_BINARY  当前点值大于阈值时，取Maxval, 也就是第四个参数，下面再不说明，否则设置为0\n");
	printf("\n\n\t1 : THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval\n");
	printf("\n\n\t2 : THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变\n");
	printf("\n\n\t3 : THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0\n");
	printf("\n\n\t4 : THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变\n");
	printf("\n\n\t按下esc 退出循环\n");
}



