#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <math.h>  
//#include "stdafx.h"
//#include "funtions.h"
//#include "parameters.h"
#include<opencv2/imgproc/types_c.h> 
//#include "My_ImageProssing_base.h"
#define WINDOW_NAME1 "【程序窗口1】"			
#define WINDOW_NAME2 "【程序窗口2】"	
using namespace cv;
using namespace std;
RNG g_rng(12345);

int kMeansDemo()
{
	const int MAX_CLUSTERS = 5;
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};

	Mat img(500, 500, CV_8UC3);
	RNG rng(12345);

	for (;;)
	{
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
		int i, sampleCount = rng.uniform(1, 1001);
		Mat points(sampleCount, 1, CV_32FC2), labels;

		clusterCount = MIN(clusterCount, sampleCount);
		std::vector<Point2f> centers;

		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			Mat pointChunk = points.rowRange(k * sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1) * sampleCount / clusterCount);
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols * 0.05, img.rows * 0.05));
		}

		randShuffle(points, 1, &rng);

		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		img = Scalar::all(0);

		for (i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
		}
		for (i = 0; i < (int)centers.size(); ++i)
		{
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}
		cout << "Compactness: " << compactness << endl;

		imshow("clusters", img);

		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}

	return 0;
}

//增加了两类的限制！！！！
int createMaskByKmeans(cv::Mat src, cv::Mat& mask)
{
	if ((mask.type() != CV_8UC1)
		|| (src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	//制作kmeans用的数据
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//执行kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//制作mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
		}
	}

	if (mask.at<uchar>(0, 0) == 255)
	{//反转整个图像黑白
		mask = 255 - mask;
	}
	return 0;
}

void segColor()
{

	Mat src = imread("D:\\opencv_picture_test\\kmeans\\龙.png");

	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);

}
void seg_changed(Mat& src,Mat& mask)
{
	createMaskByKmeans(src, mask);
	imshow("src", src);
	imshow("mask", mask);
}


//int main()
//{
//	segColor();
//}
int main()
{
	VideoCapture capture1("D:\\opencv_picture_test\\videos\\绿布飞龙.avi");
	VideoCapture capture2("D:\\opencv_picture_test\\videos\\十五秒恐怖视频.avi");
	Mat frame1;
	Mat frame2;
	Mat reslut1;
	Mat reslut2;
	while (1)
	{
		capture1 >> frame1;	//读取当前帧
		capture2 >> frame2;	//读取当前帧
		Mat mask = Mat::zeros(frame1.size(), CV_8UC1);
		reslut1  = frame1.clone();
		reslut2 = frame2.clone();
		seg_changed(frame1, mask);
		//把mask大小做调整,和背景一样大小
		resize(mask, mask, frame2.size());
		resize(frame1, frame1, frame2.size());
		//在原图上显示出龙
		for (int i = 0;i < frame2.rows;i++)	//行循环
		{
			for (int j =0;j < frame2.cols;j++)	//列循环
			{
				//-------【开始处理每个像素】---------------
				if ((mask.at<uchar>(i, j) == 255))	//白色，前景
				{
					reslut2.at<Vec3b>(i, j)[0] = frame1.at<Vec3b>(i, j)[0];
					reslut2.at<Vec3b>(i, j)[1] = frame1.at<Vec3b>(i, j)[1];
					reslut2.at<Vec3b>(i, j)[2] = frame1.at<Vec3b>(i, j)[2];
				}
				//-------【处理结束】---------------
			}
		}
		imshow("reslut", reslut2);
		waitKey(10);	//延时30ms
	}
	return 0;
}






























