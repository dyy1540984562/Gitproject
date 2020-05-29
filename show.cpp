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


//Mat src_image;
//Mat img1;
//Mat img2;

////*--------------------------手动实现HOG描述子-------------------------------------*/
//int main()
//{
//	//改变控制台字体颜色
//	system("color 02");
//
//	//读取图像
//	src_image = imread("D:\\opencv_picture_test\\HOG行人检测\\hogTemplate.jpg");
//	img1 = imread("D:\\opencv_picture_test\\HOG行人检测\\img1.jpg");
//	img2 = imread("D:\\opencv_picture_test\\HOG行人检测\\img2.jpg");
//	//出错判断
//	if (!(src_image.data || img1.data || img2.data))
//	{
//		cout << "image load failed!" << endl;
//		return -1;
//	}
//	//【1】计算hogTemplate
//	//所有像素计算梯度和角度方向
//	Mat gx, gy;
//	Mat mag, angle;	//幅值和角度
//	Sobel(src_image, gx, CV_32F, 1, 0, 1);
//	Sobel(src_image, gy, CV_32F, 0, 1, 1);
//	cartToPolar(gx, gy, mag, angle, false);		//false获得的是角度
//
//	int cellSize = 16;		//每个cell的大小
//	int nx = src_image.cols / cellSize;	//每行有几个
//	int ny = src_image.rows / cellSize;	//每列有几个
//	int cellnums = nx * ny;	//有几个cell
//	int bins = cellnums * 8;
//	float* ref_hist = new float[bins];
//	memset(ref_hist, 0, sizeof(float) * bins);
//	int binnum = 0;
//	//计算一张图
//	for (int j = 0;j < ny;j++)
//	{
//		for (int i = 0;i < nx;i++)
//		{
//			//计算每个cell的直方图
//			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
//			{
//				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
//				{
//					//对角度进行量化
//					int tempangle1 = 0;
//					float tempangle2 = angle.at<float>(y, x);	//当前像素的角度值
//					tempangle1 = angle_lianghua(tempangle2);	//当前cell的角度分量
//					float magnitude = mag.at<float>(y, x);		//当前像素的幅度值
//					ref_hist[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
//				}
//			}
//			binnum++;	//cell数目+1
//		}
//	}
//	//【2】计算img1
//		//所有像素计算梯度和角度方向
//	Mat gx_img1, gy_img1;
//	Mat mag_img1, angle_img1;	//幅值和角度
//	Sobel(img1, gx_img1, CV_32F, 1, 0, 1);
//	Sobel(img1, gy_img1, CV_32F, 0, 1, 1);
//	cartToPolar(gx_img1, gy_img1, mag_img1, angle_img1, false);		//false获得的是角度
//	nx = img1.cols / cellSize;	//每行有几个
//	ny = img1.rows / cellSize;	//每列有几个
//	cellnums = nx * ny;	//有几个cell
//	bins = cellnums * 8;
//	float* ref_hist_img1 = new float[bins];
//	memset(ref_hist_img1, 0, sizeof(float) * bins);
//	binnum = 0;
//	//计算一张图
//	for (int j = 0;j < ny;j++)
//	{
//		for (int i = 0;i < nx;i++)
//		{
//			//计算每个cell的直方图
//			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
//			{
//				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
//				{
//					//对角度进行量化
//					int tempangle1 = 0;
//					float tempangle2 = angle_img1.at<float>(y, x);	//当前像素的角度值
//					tempangle1 = angle_lianghua(tempangle2);	//当前cell的角度分量
//					float magnitude = mag_img1.at<float>(y, x);		//当前像素的幅度值
//					ref_hist_img1[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
//				}
//			}
//			binnum++;	//cell数目+1
//		}
//	}
//	//【3】计算img2
//	//所有像素计算梯度和角度方向
//	Mat gx_img2, gy_img2;
//	Mat mag_img2, angle_img2;	//幅值和角度
//	Sobel(img2, gx_img2, CV_32F, 1, 0, 1);
//	Sobel(img2, gy_img2, CV_32F, 0, 1, 1);
//	cartToPolar(gx_img2, gy_img2, mag_img2, angle_img2, false);		//false获得的是角度
//	nx = img2.cols / cellSize;	//每行有几个
//	ny = img2.rows / cellSize;	//每列有几个
//	cellnums = nx * ny;	//有几个cell
//	bins = cellnums * 8;
//	float* ref_hist_img2 = new float[bins];
//	memset(ref_hist_img2, 0, sizeof(float) * bins);
//	binnum = 0;
//	//计算一张图
//	for (int j = 0;j < ny;j++)
//	{
//		for (int i = 0;i < nx;i++)
//		{
//			//计算每个cell的直方图
//			for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
//			{
//				for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
//				{
//					//对角度进行量化
//					int tempangle1 = 0;
//					float tempangle2 = angle_img2.at<float>(y, x);	//当前像素的角度值
//					tempangle1 = angle_lianghua(tempangle2);	//当前像素的角度分量
//					float magnitude = mag_img2.at<float>(y, x);		//当前像素的幅度值
//					ref_hist_img2[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
//				}
//			}
//			binnum++;	//cell数目+1
//		}
//	}
//	//【4】分别计算ref_hist_img1和ref_hist\ref_hist_img2和ref_hist的矩
//	int result1 = 0;
//	int result2 = 0;
//	for (int i = 0;i < bins;i++)
//	{
//		//这里简化运算，不计算平方根,而是计算abs
//		result1 += abs(ref_hist[i] - ref_hist_img1[i]);
//		result2 += abs(ref_hist[i] - ref_hist_img2[i]);
//	}
//	cout << result1 << endl;
//	cout << result2 << endl;
//	if (result1 < result2)
//	{
//		cout << "img1更与原图相似" << endl;
//	}
//	else
//		cout << "img2更与原图相似" << endl;
//	waitKey(0);
//	delete[] ref_hist;
//	delete[] ref_hist_img1;
//	delete[] ref_hist_img2;
//	return 0;
//}

////*--------------------------练习1：手动实现HOG描述子-------------------------------------*/
int angle_lianghua(float angle)
{
	int result = angle / 45;
	return result;
}

int main()
{
	Mat img1 = imread("D:\\opencv_picture_test\\template.png",0);
	Mat srcimg2 = imread("D:\\opencv_picture_test\\img.png", 0);
	Mat img2 = Mat::zeros(img1.rows, img1.cols, CV_8UC1);

	int cnt1 = 0;
	int cnt2 = 0;
	float distance = 0;
	float distance_min = 1000000;		
	int x = 0;
	int y = 0;
	//先计算模板的直方图
	//所有像素计算梯度和角度方向
	Mat gx, gy;
	Mat mag, angle;	//幅值和角度
	Sobel(img1, gx, CV_32F, 1, 0, 1);
	Sobel(img1, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, false);		//false获得的是角度

	int cellSize = 16;		//每个cell的大小
	int nx = img1.cols / cellSize;	//每行有几个
	int ny = img1.rows / cellSize;	//每列有几个
	int cellnums = nx * ny;	//有几个cell
	int bins = cellnums * 8;
	float* ref_hist = new float[bins];
	float* ref_hist_img2 = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	int binnum = 0;
	//计算模板的直方图
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
	//只遍历80—110见方区域
	for (int q = 80; q < 110; q++) {
		for (int p = 80; p < 110; p++) {
			//从srcimg2中扣出和img1一样大小的区域放到img2中
			for (int m = 0; m < img1.rows; m++) {
				for (int n = 0; n < img1.cols; n++) {
					img2.at<uchar>(m, n) = srcimg2.at<uchar>(q + m, p + n);
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
							tempangle1 = angle_lianghua(tempangle2);	//当前像素的角度分量
							float magnitude = mag_img2.at<float>(y, x);		//当前像素的幅度值
							ref_hist_img2[tempangle1 + binnum * 8] += magnitude;				//在数组中加上当前的
						}
					}
					binnum++;	//cell数目+1
				}
			}
			distance = 0;
			//计算两个直方图的曼哈顿距离
			for (int i = 0; i < bins; i++)
			{
				distance += abs(ref_hist[i] - ref_hist_img2[i]);
				if (distance < distance_min) {
					distance_min = distance;
					x = q;
					y = p;
				}
			}
		}
	}
	cout << "最小值" << distance_min << endl;
	cout << "x" << x << endl;
	cout << "y" << y << endl;
	Rect rect(y, x, img1.cols, img1.rows);//左上坐标（x,y）和矩形的长(x)宽(y)
	cv::rectangle(srcimg2, rect, Scalar(255, 0, 0), 1, LINE_8, 0);
	imshow("dstMat", srcimg2);
	waitKey(0);
	delete[] ref_hist;
	delete[] ref_hist_img2;
	return 0;
}





//***********************************************练习2 框出之后按回车键即可****************************************************//
//int main()
//{
//	//改变控制台字体颜色
//	system("color 02");
//	VideoCapture capture(0);
//	int cnt = 0;
//	Mat frame;	//存储每一帧的图像
//	Mat tempMat;
//	Mat refMat;
//	Mat resultMat;
//	Mat dispMat;
//	while (1)
//	{
//		capture >> frame;	//读取当前帧
//		if (cnt == 0) {
//			Rect2d r;
//			r = selectROI(frame, true);
//			tempMat = frame(r);
//			tempMat.copyTo(refMat);
//			destroyAllWindows();
//		}
//		int match_method = 0;
//		matchTemplate(frame, refMat, resultMat, match_method);
//		normalize(resultMat, resultMat, 0,1,NORM_MINMAX,-1,Mat());
//		double minVal; double maxVal; Point minLoc; Point maxLoc; Point matchLoc;
//		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc,Mat());
//		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
//			matchLoc = minLoc;
//		else
//			matchLoc = maxLoc;
//		frame.copyTo(dispMat);
//		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);
//		cnt++;
//		imshow("template",refMat) ;
//		imshow("dispMat",dispMat) ;
//		waitKey(30);
//	}
//	return 0;
//	
//}