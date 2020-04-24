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

//*--------------------------手动实现HOG描述子-------------------------------------*/
int angle_lianghua(float angle)
{
	int result = angle/45;
	return result;
}
int main()
{
	//改变控制台字体颜色
	system("color 02");
	
	//读取图像
    src_image = imread("D:\\opencv_picture_test\\HOG行人检测\\hogTemplate.jpg");
	img1 = imread("D:\\opencv_picture_test\\HOG行人检测\\img1.jpg");
	img2 = imread("D:\\opencv_picture_test\\HOG行人检测\\img2.jpg");
	//出错判断
	if (!(src_image.data || img1.data || img2.data))
	{
		cout << "image load failed!" << endl;
		return -1;
	}
	//【1】计算hogTemplate
	//所有像素计算梯度和角度方向
	Mat gx, gy;
	Mat mag, angle;	//幅值和角度
	Sobel(src_image, gx, CV_32F, 1, 0, 1);
	Sobel(src_image, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, false);		//false获得的是角度

	int cellSize = 16;		//每个cell的大小
	int nx = src_image.cols / cellSize;	//每行有几个
	int ny = src_image.rows / cellSize;	//每列有几个
	int cellnums = nx * ny;	//有几个cell
	int bins = cellnums * 8;
	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	int binnum = 0;
	//计算一张图
	for (int j = 0;j < ny;j++)
	{
		for (int i = 0;i < nx;i++)
		{
			//计算每个cell的直方图
			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
			{
				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
				{
					//对角度进行量化
					int tempangle1 = 0;
					float tempangle2 = angle.at<float>(y, x);	//当前像素的角度值
					tempangle1 = angle_lianghua(tempangle2);	//当前cell的角度分量
					float magnitude = mag.at<float>(y, x);		//当前像素的幅度值
					ref_hist[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
				}
			}
			binnum++;	//cell数目+1
		}
	}
	//【2】计算img1
		//所有像素计算梯度和角度方向
	Mat gx_img1, gy_img1;
	Mat mag_img1, angle_img1;	//幅值和角度
	Sobel(img1, gx_img1, CV_32F, 1, 0, 1);
	Sobel(img1, gy_img1, CV_32F, 0, 1, 1);
	cartToPolar(gx_img1, gy_img1, mag_img1, angle_img1, false);		//false获得的是角度
	nx = img1.cols / cellSize;	//每行有几个
	ny = img1.rows / cellSize;	//每列有几个
	cellnums = nx * ny;	//有几个cell
	bins = cellnums * 8;
	float* ref_hist_img1 = new float[bins];
	memset(ref_hist_img1, 0, sizeof(float) * bins);
	binnum = 0;
	//计算一张图
	for (int j = 0;j < ny;j++)
	{
		for (int i = 0;i < nx;i++)
		{
			//计算每个cell的直方图
			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
			{
				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
				{
					//对角度进行量化
					int tempangle1 = 0;
					float tempangle2 = angle_img1.at<float>(y, x);	//当前像素的角度值
					tempangle1 = angle_lianghua(tempangle2);	//当前cell的角度分量
					float magnitude = mag_img1.at<float>(y, x);		//当前像素的幅度值
					ref_hist_img1[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
				}
			}
			binnum++;	//cell数目+1
		}
	}
	//【3】计算img2
	//所有像素计算梯度和角度方向
	Mat gx_img2, gy_img2;
	Mat mag_img2, angle_img2;	//幅值和角度
	Sobel(img2, gx_img2, CV_32F, 1, 0, 1);
	Sobel(img2, gy_img2, CV_32F, 0, 1, 1);
	cartToPolar(gx_img2, gy_img2, mag_img2, angle_img2, false);		//false获得的是角度
	nx = img2.cols / cellSize;	//每行有几个
	ny = img2.rows / cellSize;	//每列有几个
	cellnums = nx * ny;	//有几个cell
	bins = cellnums * 8;
	float* ref_hist_img2 = new float[bins];
	memset(ref_hist_img2, 0, sizeof(float) * bins);
	binnum = 0;
	//计算一张图
	for (int j = 0;j < ny;j++)
	{
		for (int i = 0;i < nx;i++)
		{
			//计算每个cell的直方图
			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
			{
				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
				{
					//对角度进行量化
					int tempangle1 = 0;
					float tempangle2 = angle_img2.at<float>(y, x);	//当前像素的角度值
					tempangle1 = angle_lianghua(tempangle2);	//当前cell的角度分量
					float magnitude = mag_img2.at<float>(y, x);		//当前像素的幅度值
					ref_hist_img2[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
				}
			}
			binnum++;	//cell数目+1
		}
	}
	//【4】分别计算ref_hist_img1和ref_hist\ref_hist_img2和ref_hist的矩
	int result1 = 0;
	int result2 = 0;
	for (int i = 0;i < bins;i++)
	{
		//这里简化运算，不计算平方根,而是计算abs
		result1 += abs(ref_hist[i]- ref_hist_img1[i]);
		result2 += abs(ref_hist[i] - ref_hist_img2[i]);
	}
	cout << result1 << endl;
	cout << result2 << endl;
	if (result1 < result2)
	{
		cout << "img1更与原图相似" << endl;
	}
	else
		cout << "img2更与原图相似" << endl;
	waitKey(0);
	delete[] ref_hist;
	delete[] ref_hist_img1;
	delete[] ref_hist_img2;
	return 0;
}


