#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
#define byte uchar 
#define TYEPE_GRAY 0
#define TYEPE_RGB 1
#define TYEPE_HS2D 1
#define CAL_AND_DRAW 0
#define CAL_AND_NOMALIZE 1

/************练习1**********************/
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku2.jpg",2|4);			//灰度图
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	std::vector<cv::Mat> channels;
//	cv::split(img1,channels);
//	Mat B = channels.at(0);
//	Mat G = channels.at(1);
//	Mat R = channels.at(2);
//	imshow("blue", B);
//	imshow("green", G);
//	imshow("red", R);
//	waitKey(0);
//	return 0;
//}
///************练习2**********************/
//int main()
//{
//	//实例化的同时初始化
//	//调用摄像头
//	VideoCapture capture(0);		//类似于 int a=1;
//	/*
//		先实例化
//		VideoCapture capture;
//		再初始化
//		capture.open("D:\\opencv_picture_test\\video1.avi");
//	*/
//	while (1)
//	{
//		Mat frame;	//存储每一帧的图像
//		capture >> frame;	//读取当前帧
//		imshow("原视频", frame);	//显示当前帧
//		//进行腐蚀操作
//		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//返回的是内核矩阵
//		Mat dstImage;
//		erode(frame, dstImage, element);					//腐蚀操作
//		imshow("处理后的视频", dstImage);	//显示当前帧
//		if(waitKey(10) >= 0) break;	//延时10ms
//	}
//	return 0;
//}
/************练习3**********************/
//int main()
//{
//	Mat displayMat = imread("D:\\opencv_picture_test\\RGB纯色图\\blue.jpg", 0);			//灰度图
//	if (displayMat.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//画圆
//	Point pt;
//	pt.x = 90;
//	pt.y = 90;
//	circle(displayMat, pt, 20, CV_RGB(0, 255, 0), 1, 8, 0);
//	//画线段
//	Point pt1;
//	pt1.x = 100;
//	pt1.y = 100;
//	Point pt2;
//	pt2.x = 300;
//	pt2.y = 300;
//	line(displayMat, pt1, pt2, CV_RGB(0, 255, 0), 10, 8, 0);
//	//画矩形框
//	Rect rect;
//	rect.x = 20;
//	rect.y = 20;
//	rect.width = 20;
//	rect.height = 20;
//	rectangle(displayMat, rect, CV_RGB(0, 255, 0), 1, 8, 0);
//	imshow("图片", displayMat);
//	waitKey(0);
//	return 0;
//
//}
///*--------------------------【练习5】绘制一维灰度直方图-------------------------------------*/
Mat	My_Rraw_histogram(Mat* srcImage)		//输入:要处理的灰度图   输出：该图像的直方图
{
	//【2】定义变量
	MatND dstHist;
	int dims = 1;		//需要计算的直方图的维数
	float grayranges[] = { 0,255 };
	const float* ranges[] = { grayranges };	//这里需要为const类型
	int size = 256;			//表示的是将统计的灰度值分成的等份
	int channels = 0;	//灰度图只有一个0通道

	//【3】计算图像直方图
	calcHist(srcImage,	//输入数组
		1,	//数组个数
		&channels,	//通道索引
		Mat(),//不使用掩膜
		dstHist,	//输出的目标直方图
		dims,	//需要计算的直方图的维数
		&size,	//存放每个维度的直方图尺寸的数组
		ranges);	//每一维数值的取值范围	
	int scale = 1;		//scale 每一个像素占的格数

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));		//长 ：size*scale ，宽：size ,值为0

	//【4】获取最大值和最小值
	double minVal = 0;
	double maxVal = 0;
	minMaxLoc(dstHist, &minVal, &maxVal, 0, 0);		//获得直方图中最大值和最小值

	//【5】绘制出直方图
	int hpt = saturate_cast<int>(0.9 * size);			//saturate_cast 是溢出保护    大概意思 ：if(data<0)  data = 0; else if (data > 255) data = 255;
	for (int i = 0;i < 256;i++)
	{
		float binVal = dstHist.at<float>(i);
		int realVal = saturate_cast<int>(binVal * hpt / maxVal);		//在图像上的高度 = 像素值/最大像素值 * 0.9*256   这里0.9是为了削减图像像素高度，因为最大的时候会触及顶端不美观
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realVal), Scalar(255));
		//要进行绘制的目标图像 矩形的左下顶点 矩阵对角线上的右上顶点 线条的颜色（RGB）或亮度（灰度图）  一共要绘制256个矩形
	}
	return dstImage;
}
//主函数
int main()
{
	//【1】载入原图
	Mat srcImage = imread("D:\\opencv_picture_test\\新垣结衣\\test2.jpg", 0);			//原图的灰度图
	namedWindow("灰度图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("灰度图", srcImage);
	if (srcImage.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}
	Mat dstImage = My_Rraw_histogram(&srcImage);
	namedWindow("一维直方图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("一维直方图", dstImage);
	waitKey(0);
	return 0;
}
