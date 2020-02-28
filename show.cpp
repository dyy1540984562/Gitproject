#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
#define byte uchar 

/************练习1**********************/
//imread 功能是加载图像文件成为一个 Mat 对象，其中第一个参数表示 图像文件名称 。第二个参数表示 读取图像的颜色类型（默认参数是1） ，返回3通道图像，支持常见的三个参数值：
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku2.jpg", 2 | 4);		//无损原图像
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	imshow("无损原图", img1);
//	int height = img1.rows;	//行数/高
//	int width = img1.cols;	//列数/宽
//	
//	for (int j = 0;j < height;j++)
//	{
//		for (int i = 0;i < width;i++)
//		{
//			//描述：使用动态地址运算配合at访问,可读性强
//			//--------------------开始像素处理-------------------
//			byte ave = (img1.at<Vec3b>(j,i)[0]+ img1.at<Vec3b>(j, i)[1] + img1.at<Vec3b>(j, i)[2])/3;		//计算平均值
//			img1.at<Vec3b>(j, i)[0] = ave;
//			img1.at<Vec3b>(j, i)[1] = ave;
//			img1.at<Vec3b>(j, i)[2] = ave;
//			//-------------------像素处理结束--------------------
//		}
//	}
//	imshow("处理后的图像", img1);
//    //imwrite("D:\\opencv_picture_test\\test1.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/************练习2**********************/
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku2.jpg", 0);			//灰度图
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//
//	imshow("灰度图", img1);
//  //imwrite("D:\\opencv_picture_test\\miku2.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/************练习3**********************/
/*
3.在练习1的基础上，在处理每个像素的时候加个一个条件。声明一个
uchar变量
uchar threshold = 100;
如果average> threshold则average=255,否则为0。
然后再把average值赋值给像素的3个通道，并通过imshow函数观察结果，
然后修改threshold值，观察输出结果。
*/
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku2.jpg", 2 | 4);		//无损原图像
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	imshow("无损原图", img1);
//	int height = img1.rows;	//行数/高
//	int width = img1.cols;	//列数/宽
//	byte threshold = 100;
//	for (int j = 0;j < height;j++)
//	{
//		for (int i = 0;i < width;i++)
//		{
//			//描述：使用动态地址运算配合at访问,可读性强
//			//--------------------开始像素处理-------------------
//			byte ave = (img1.at<Vec3b>(j,i)[0]+ img1.at<Vec3b>(j, i)[1] + img1.at<Vec3b>(j, i)[2])/3;		//计算平均值
//			//二值化
//			if (ave > threshold)
//			{
//				img1.at<Vec3b>(j, i)[0] = 255;
//				img1.at<Vec3b>(j, i)[1] = 255;
//				img1.at<Vec3b>(j, i)[2] = 255;
//			}
//			else
//			{
//				img1.at<Vec3b>(j, i)[0] = 0;
//				img1.at<Vec3b>(j, i)[1] = 0;
//				img1.at<Vec3b>(j, i)[2] = 0;
//			}
//			//-------------------像素处理结束--------------------
//		}
//	}
//	imshow("处理后的图像", img1);
//    //imwrite("D:\\opencv_picture_test\\test1.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/************练习4**********************/
/****mat的基本操作示例**********/
/*
赋值和构造函数只复制信息头
Mat A,C;	//仅创建信息头部分
A =imread();	//为矩阵开辟内容
Mat B(A);		//使用拷贝构造函数
C=A;		//赋值语句


所有Mat指向同一个数据矩阵
Mat D(A,Rect(0,0,100,100) );//使用矩形界定
Mat E(Range:all(),Range(1,3) );//使用行和列界定

使用copyto或者clone可以复制整个矩阵
Mat F =A.clone();
Mat G;
A.copyTo(G);

*/
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku2.jpg", 2 | 4);		//无损原图像
//	Mat deepMat, shallowMat;
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	imshow("无损原图", img1);
//	shallowMat = img1;	//浅复制
//	deepMat = img1.clone();	//深复制
//	int height = img1.rows;	//行数/高
//	int width = img1.cols;	//列数/宽
//	byte threshold = 100;
//	for (int j = 0;j < height;j++)
//	{
//		for (int i = 0;i < width;i++)
//		{
//			//描述：使用动态地址运算配合at访问,可读性强
//			//--------------------开始像素处理-------------------
//			byte ave = (img1.at<Vec3b>(j,i)[0]+ img1.at<Vec3b>(j, i)[1] + img1.at<Vec3b>(j, i)[2])/3;		//计算平均值
//			//二值化
//			if (ave > threshold)
//			{
//				img1.at<Vec3b>(j, i)[0] = 255;
//				img1.at<Vec3b>(j, i)[1] = 255;
//				img1.at<Vec3b>(j, i)[2] = 255;
//			}
//			else
//			{
//				img1.at<Vec3b>(j, i)[0] = 0;
//				img1.at<Vec3b>(j, i)[1] = 0;
//				img1.at<Vec3b>(j, i)[2] = 0;
//			}
//			//-------------------像素处理结束--------------------
//		}
//	}
//	imshow("浅复制的图像", shallowMat);
//	imshow("深复制的图像", deepMat);
//	//观察结果： 深复制的没有改变     浅复制的改变了
//    //imwrite("D:\\opencv_picture_test\\test1.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}
