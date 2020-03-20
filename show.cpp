#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <stdio.h>

using namespace cv;
using namespace std;
#define byte uchar 
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏
/**************************无关精要的函数**************************************/
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

////*--------------------------【练习】阈值分割的若干种方法-------------------------------------*/
void My_P_tile(Mat* srcImage, Mat* dstImage, int P)
{
	//【1】计算一维灰度直方图
	int height = (*srcImage).rows;
	int width = (*srcImage).cols;
	int pixels[256];
	float histgram[256];
	for (int i = 0; i < 256; i++)
	{
		pixels[i] = 0;
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++) {
			pixels[(*srcImage).at<uchar>(j, i)]++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = pixels[i] * 1.0 / (height * width);
	}
	//【2】计算直方图积分,并且找出阈值
	float p_of_hist = P * 1.0 / 100;
	float sum = 0;
	int threshold = 0;
	for (int i = 0; i < 256; i++)
	{
		sum += histgram[i];
		if (sum >= p_of_hist)
		{
			threshold = i;
			break;
		}
	}
	cout << "P_tile方法阈值为：" << threshold << endl;
	//【3】二值化
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if ((*srcImage).at<uchar>(j, i) >= threshold)
			{
				(*dstImage).at<uchar>(j, i) = 255;
			}
			else
			{
				(*dstImage).at<uchar>(j, i) = 0;
			}

		}
	}
}
void My_Iteration(Mat* srcImage, Mat* dstImage, float delta_T)
{
	//【1】求最大灰度和最小灰度
	byte max_his = 0;
	byte min_his = 255;
	int height = (*srcImage).rows;
	int width = (*srcImage).cols;
	for (int j = 0;j < height;j++)
	{
		for (int i = 0;i < width;i++)
		{
			if ((*srcImage).at<uchar>(j, i) > max_his)
			{
				max_his = (*srcImage).at<uchar>(j, i);
			}
			if ((*srcImage).at<uchar>(j, i) < min_his)
			{
				min_his = (*srcImage).at<uchar>(j, i);
			}
		}
	}
	float T = 0.5 * (max_his + min_his);
	float m1 = 255;
	float m2 = 0;
	float old_T = T;
	float new_T = 0.5 * (m1 + m2);
	int times = 10;
	//while (times--)
	while (abs(new_T - old_T) > delta_T)
	{
		int G1 = 0;
		int G2 = 0;
		int timer_G1 = 0;
		int timer_G2 = 0;
		for (int j = 0;j < height;j++)
		{
			for (int i = 0;i < width;i++)
			{
				if ((*srcImage).at<uchar>(j, i) > old_T)
				{
					G1 += (*srcImage).at<uchar>(j, i);
					timer_G1++;
				}
				else
				{
					G2 += (*srcImage).at<uchar>(j, i);
					timer_G2++;
				}
			}
		}
		m1 = G1 * 1.0f / timer_G1;
		m2 = G2 * 1.0f / timer_G2;
		old_T = new_T;
		new_T = 0.5 * (m1 + m2);
	}
	cout << "迭代方法阈值为：" << new_T << endl;
	//根据得出的阈值二值化图像
	for (int j = 0;j < height;j++)
	{
		for (int i = 0;i < width;i++)
		{
			if ((*srcImage).at<uchar>(j, i) > new_T)
			{
				(*dstImage).at<uchar>(j, i) = 255;

			}
			else
			{
				(*dstImage).at<uchar>(j, i) = 0;

			}
		}
	}
}
void My_Ostu(Mat* srcImage, Mat* dstImage)
{
	int height = (*srcImage).rows;
	int width = (*srcImage).cols;
	int Ostu_Threshold = 0; //大津阈值
	int size = height * width;
	float variance;   //类间方差
	float maxVariance = 0, w1 = 0, w2 = 0, avgValue = 0;
	float u0 = 0, u1 = 0, u2 = 0;
	//生成灰度直方图
	int pixels[256];
	float histgram[256];
	for (int i = 0; i < 256; i++)
	{
		pixels[i] = 0;
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			pixels[(*srcImage).at<uchar>(j, i)]++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = pixels[i] * 1.0f / size;
	}
	//遍历找出类间方差最大（maxVariance）的阈值（Ostu_Threshold）
	for (int i = 0;i <= 255;i++)
	{
		w1 = 0;
		w2 = 0;
		u1 = 0;
		u2 = 0;
		//计算背景像素占比,平均灰度
		for (int j = 0;j <= i;j++)
		{
			w1 += histgram[j];
			u1 += histgram[j] * j;
		}
		u1 = u1 / w1;
		//计算前景像素占比,平均灰度
		w2 = 1 - w1;
		if (i == 255)
		{
			u2 = 0;
		}
		else
		{
			for (int j = i + 1;j <= 255;j++)
			{
				u2 += histgram[j] * j;
			}
		}
		u2 = u2 / w2;
		//计算类间方差
		variance = w1 * w2 * (u1 - u2) * (u1 - u2);
		if (variance > maxVariance)
		{ //找到使灰度差最大的值
			maxVariance = variance;
			Ostu_Threshold = i;            //那个值就是阈值
		}
	}
	cout << "大津法阈值为：" << Ostu_Threshold << endl;
	//【3】二值化
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if ((*srcImage).at<uchar>(j, i) >= Ostu_Threshold)
			{
				(*dstImage).at<uchar>(j, i) = 255;
			}
			else
			{
				(*dstImage).at<uchar>(j, i) = 0;
			}

		}
	}
}
//局部自适应法   基于大津阈值  areas_of_H：竖直方向分割的个数  areas_of_W：横坐标方向分割的个数
void My_local_adaptive(Mat* srcImage, Mat* dstImage, int areas_of_H, int areas_of_W)		//基于大津阈值法
{
	int height = (*srcImage).rows / areas_of_H;			//每一小块的height
	int width = (*srcImage).cols / areas_of_W;			//每一小块的width
	int Ostu_Threshold = 0; //大津阈值
	int size = height * width / areas_of_H / areas_of_W;		//每一小块的size
	//一行一行地来
	for (int y = 0; y < areas_of_H; y++)
	{
		for (int x = 0; x < areas_of_W; x++)
		{
			float variance = 0;   //类间方差
			float maxVariance = 0, w1 = 0, w2 = 0, avgValue = 0;
			float u0 = 0, u1 = 0, u2 = 0;
			//生成areas_of_W*areas_of_H个局部灰度直方图
			int pixels[256];
			float histgram[256];
			for (int i = 0; i < 256; i++)
			{
				pixels[i] = 0;
			}
			//【处理每个小区域并且二值化】
			//【计算直方图】
			for (int j = y * height; j < ((y + 1 == areas_of_H) ? (*srcImage).rows : (y + 1) * height); j++) //? : 是一个三目运算符，也是唯一的一个三目运算符。？前面表逻辑条件，：前面也就是？后面表示条件成立时的值，：后面表条件不成立时的值。例如，当a > b时，x = 1否则x = 0，可以写成x = a > b ? 1 : 0。
			{
				for (int i = x * width; i < ((x + 1 == areas_of_W) ? (*srcImage).cols : (x + 1) * width); i++)
				{
					pixels[(*srcImage).at<uchar>(j, i)]++;
				}
			}
			//【直方图归一化】
			for (int i = 0; i < 256; i++)
			{
				histgram[i] = pixels[i] * 1.0f / size;
			}
			//遍历找出类间方差最大（maxVariance）的阈值（Ostu_Threshold）
			for (int i = 0;i <= 255;i++)
			{
				w1 = 0;
				w2 = 0;
				u1 = 0;
				u2 = 0;
				//计算背景像素占比,平均灰度
				for (int j = 0;j <= i;j++)
				{
					w1 += histgram[j];
					u1 += histgram[j] * j;
				}
				u1 = u1 / w1;
				//计算前景像素占比,平均灰度
				w2 = 1 - w1;
				if (i == 255)
				{
					u2 = 0;
				}
				else
				{
					for (int j = i + 1;j <= 255;j++)
					{
						u2 += histgram[j] * j;
					}
				}
				u2 = u2 / w2;
				//计算类间方差
				variance = w1 * w2 * (u1 - u2) * (u1 - u2);
				if (variance > maxVariance)
				{ //找到使灰度差最大的值
					maxVariance = variance;
					Ostu_Threshold = i;            //那个值就是阈值
				}
			}
			cout << "大津法阈值为：" << Ostu_Threshold << endl;
			//【3】二值化
			for (int j = y * height; j < ((y + 1 == areas_of_H) ? (*srcImage).rows : (y + 1) * height); j++) //? : 是一个三目运算符，也是唯一的一个三目运算符。？前面表逻辑条件，：前面也就是？后面表示条件成立时的值，：后面表条件不成立时的值。例如，当a > b时，x = 1否则x = 0，可以写成x = a > b ? 1 : 0。
			{
				for (int i = x * width; i < ((x + 1 == areas_of_W) ? (*srcImage).cols : (x + 1) * width); i++)
				{
					if ((*srcImage).at<uchar>(j, i) >= Ostu_Threshold)
					{
						(*dstImage).at<uchar>(j, i) = 255;
					}
					else
					{
						(*dstImage).at<uchar>(j, i) = 0;
					}
				}
			}
		}
	}
}
void My_artificial(Mat* srcImage, Mat* dstImage, int Threshold)
{
	int height = (*srcImage).rows;
	int width = (*srcImage).cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if ((*srcImage).at<uchar>(j, i) >= Threshold)
			{
				(*dstImage).at<uchar>(j, i) = 255;
			}
			else
			{
				(*dstImage).at<uchar>(j, i) = 0;
			}

		}
	}
}
void main_of_diferent_Threshold_types()
{
	//Mat srcImage = imread("D:\\opencv_picture_test\\新垣结衣\\test2.jpg", 0);	//读入的时候转化为灰度图
	//Mat srcImage = imread("D:\\opencv_picture_test\\miku\\miku2.jpg", 0);	//读入的时候转化为灰度图
	Mat srcImage = imread("D:\\opencv_picture_test\\阈值处理\\硬币.png", 0);	//读入的时候转化为灰度图
	//Mat srcImage = imread("D:\\opencv_picture_test\\JQ\\JQ32.jpg", 0);	//读入的时候转化为灰度图
	namedWindow("原始图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("原始图", srcImage);

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);
	double time0 = static_cast<double>(getTickCount());	//记录起始时间
	//阈值处理+二值化
	//My_P_tile(&srcImage,&dstImage,20);			//设P为20
	//My_Iteration(&srcImage, &dstImage,0.1);
	//My_Ostu(&srcImage, &dstImage);
	//My_local_adaptive(&srcImage, &dstImage, 5, 5);
	My_artificial(&srcImage, &dstImage, 83);
	//一系列处理之后
	//time0 = ((double)getTickCount() - time0) / getTickFrequency();
	//cout << "此方法运行时间为：" << time0 << "秒" << endl;	//输出运行时间
	//namedWindow("效果图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	//imshow("效果图", dstImage);
	//dstImage = My_Rraw_histogram(&srcImage);
	//namedWindow("一维直方图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	//imshow("一维直方图", dstImage);
	//imwrite("D:\\opencv_picture_test\\阈值处理\\二值化83.jpg", dstImage);
}


////*--------------------------【练习1】-------------------------------------*/

//int main()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);		//字体为绿色
//	//载入原图
//	Mat g_secImage = imread("D:\\opencv_picture_test\\形态学操作\\coin.png",0);			//读取灰度
//	//判断图像是否加载成功
//	if (g_secImage.empty())
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//	//显示灰度图像
//	namedWindow("灰度图像", WINDOW_NORMAL);     //定义窗口显示属性
//	imshow("灰度图像", g_secImage);
//	//二值化
//	My_artificial(&g_secImage,&g_secImage,84);//固定阈值,此时效果最好。
//	//创建三个窗口
//	namedWindow("【开运算】", WINDOW_NORMAL);
//	namedWindow("【闭运算】", WINDOW_NORMAL);
//	namedWindow("【腐蚀】", WINDOW_NORMAL);
//	namedWindow("【膨胀】", WINDOW_NORMAL);
//	Mat element = getStructuringElement(MORPH_RECT, Size(3,3));		//矩形 3*3
//	Mat g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4;
//	morphologyEx(g_secImage, g_dstImage1, MORPH_OPEN, element);		//开
//	morphologyEx(g_secImage, g_dstImage2, MORPH_CLOSE, element);		//闭
//	morphologyEx(g_secImage, g_dstImage3, MORPH_ERODE, element);		//腐蚀
//	morphologyEx(g_secImage, g_dstImage4, MORPH_DILATE, element);	//膨胀
//	imshow("【开运算】", g_dstImage1);
//	imshow("【闭运算】", g_dstImage2);
//	imshow("【腐蚀】", g_dstImage3);
//	imshow("【膨胀】", g_dstImage4);
//
//	waitKey(0);
//	return 0;
//
//}

////*--------------------------【练习2】-------------------------------------*/

//int main()
//{
//	Mat lableMat;
//	Mat statsMat;
//	Mat centerMat;
//	Mat srcMat = imread("D:\\opencv_picture_test\\形态学操作\\coin.png", 0);			//读取灰度
//	Mat dstMat;
//
//	threshold(srcMat, dstMat, 84, 255, THRESH_BINARY);
//
//	int nComp = cv::connectedComponentsWithStats(dstMat,
//		lableMat,
//		statsMat,
//		centerMat,
//		8,
//		CV_32S);
//
//	for (int i = 1; i < nComp; i++)
//	{		
//		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
//		cout << "width = " << statsMat.at<int>(i, 2) << endl;
//		cout << "height = " << statsMat.at<int>(i, 3) << endl;
//		cout << endl;
//	}
//
//	for (int i = 1; i < nComp; i++)
//	{
//		Rect bndbox;
//		bndbox.x = statsMat.at<int>(i, 0);
//		bndbox.y = statsMat.at<int>(i, 1);
//		bndbox.width = statsMat.at<int>(i, 2);
//		bndbox.height = statsMat.at<int>(i, 3);
//		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
//	}
//	cout << "硬币数目：" << nComp-1 << endl;
//	imshow("src", srcMat);
//	imshow("dst", dstMat);
//	waitKey(0);
//}

////*--------------------------【练习3】-------------------------------------*/

//int main()
//{
//	Mat lableMat;
//	Mat statsMat;
//	Mat centerMat;
//	Mat srcMat = imread("D:\\opencv_picture_test\\形态学操作\\电路图.JPG", 0);			//读取灰度
//	Mat dstMat;
//	//调用阈值函数
//	threshold(srcMat, dstMat, 84, 255,THRESH_BINARY_INV);
//	//腐蚀操作
//	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(9,9));		
//	morphologyEx(dstMat,dstMat, MORPH_ERODE, element);		
//	int nComp = cv::connectedComponentsWithStats(dstMat,
//		lableMat,
//		statsMat,
//		centerMat,
//		8,
//		CV_32S);
//
//	for (int i = 1; i < nComp; i++)
//	{
//		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
//		cout << "width = " << statsMat.at<int>(i, 2) << endl;
//		cout << "height = " << statsMat.at<int>(i, 3) << endl;
//		cout << endl;
//	}
//
//	for (int i = 1; i < nComp; i++)
//	{
//		Rect bndbox;
//		bndbox.x = statsMat.at<int>(i, 0);
//		bndbox.y = statsMat.at<int>(i, 1);
//		bndbox.width = statsMat.at<int>(i, 2);
//		bndbox.height = statsMat.at<int>(i, 3);
//		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
//	}
//	imshow("src", srcMat);
//	imshow("dst", dstMat);
//	waitKey(0);
//}


////*--------------------------【练习4】-------------------------------------*/

int main()
{
	Mat lableMat;
	Mat statsMat;
	Mat centerMat;
	Mat srcMat = imread("D:\\opencv_picture_test\\形态学操作\\clip.png", 0);			//读取灰度
	Mat dstMat;
	//调用阈值函数
	threshold(srcMat, dstMat, 84, 255,THRESH_BINARY_INV);
	//腐蚀操作
	/*Mat element = getStructuringElement(MORPH_ELLIPSE, Size(9,9));		
	morphologyEx(dstMat,dstMat, MORPH_ERODE, element);*/	
	int nComp = cv::connectedComponentsWithStats(dstMat,
		lableMat,
		statsMat,
		centerMat,
		8,
		CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(dstMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	cout << "初步回形针数目：" << nComp-1 << endl;
	for (int i = 1; i < nComp; i++)
	{
		if ((statsMat.at<int>(i, 4) <= 5000))
		{
			nComp--;
		}
	}
	//减去像素小的
	cout << "最终回形针数目：" << nComp - 1 << endl;
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}