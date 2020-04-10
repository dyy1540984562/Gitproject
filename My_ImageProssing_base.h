#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
#define byte uchar 
#define WINDOW_NAME "【程序窗口】"			//为窗口标题定义的宏
class My_ImageProssing_base
{
	private:		;
	protected:		;
	public:
		//-----------------------------------绘制一维直方图--------------------------------------------------------
		Mat	My_Rraw_histogram(Mat* srcImage);
		////*--------------------------【练习】阈值分割的若干种方法-------------------------------------*/
		void My_P_tile(Mat* srcImage, Mat* dstImage, int P);
		void My_Iteration(Mat* srcImage, Mat* dstImage, float delta_T);
		byte My_Ostu(Mat* srcImage/*, Mat* dstImage*/);
		//局部自适应法   基于大津阈值  areas_of_H：竖直方向分割的个数  areas_of_W：横坐标方向分割的个数
		void My_local_adaptive(Mat* srcImage, Mat* dstImage, int areas_of_H, int areas_of_W);
		void My_artificial(Mat* srcImage, Mat* dstImage, int Threshold);
		void main_of_diferent_Threshold_types();
		void seed_Connected_Component_labeling(Mat& src_img, Mat& flag_img, Mat& draw_img, int iFlag, int type);
};

My_ImageProssing_base My;	//实例化



Mat My_ImageProssing_base::My_Rraw_histogram(Mat* srcImage)		//输入:要处理的灰度图   输出：该图像的直方图
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
};

////*--------------------------【练习】阈值分割的若干种方法-------------------------------------*/
void My_ImageProssing_base::My_P_tile(Mat* srcImage, Mat* dstImage, int P)
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
void My_ImageProssing_base::My_Iteration(Mat* srcImage, Mat* dstImage, float delta_T)
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
byte My_ImageProssing_base::My_Ostu(Mat* srcImage/*, Mat* dstImage*/)
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
	////【3】二值化
	//for (int j = 0; j < height; j++)
	//{
	//	for (int i = 0; i < width; i++)
	//	{
	//		if ((*srcImage).at<uchar>(j, i) >= Ostu_Threshold)
	//		{
	//			(*dstImage).at<uchar>(j, i) = 255;
	//		}
	//		else
	//		{
	//			(*dstImage).at<uchar>(j, i) = 0;
	//		}

	//	}
	//}
	return Ostu_Threshold;
}
//局部自适应法   基于大津阈值  areas_of_H：竖直方向分割的个数  areas_of_W：横坐标方向分割的个数
void My_ImageProssing_base::My_local_adaptive(Mat* srcImage, Mat* dstImage, int areas_of_H, int areas_of_W)		//基于大津阈值法
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
void My_ImageProssing_base::My_artificial(Mat* srcImage, Mat* dstImage, int Threshold)
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
void My_ImageProssing_base::main_of_diferent_Threshold_types()
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


////*--------------------------【练习形态学操作】-------------------------------------*/

//===========================HitMiss变换========================
//输入：待处理图像的灰度图
//参数：变换模板D和W
//输出：模板位置的坐标图
void My_HitMissChange(Mat& srcImage, Mat& dstImage, Mat& D,Mat &W_SUB_D)
{
	Mat binaryMat, binaryMat_inv;
	Mat pic1, pic2;
	//第一步(将原图二值化并获取补图像)
	byte thre = My.My_Ostu(&srcImage);
	threshold(srcImage,binaryMat,thre, 255, 0);		//原图二值图
	threshold(srcImage, binaryMat_inv, thre, 255, 1);//二值图的补
	//用D对A腐蚀
	morphologyEx(binaryMat,pic1,MORPH_ERODE,D);
	//用(W-D)对A（补）腐蚀
	morphologyEx(binaryMat_inv, pic2, MORPH_ERODE, W_SUB_D);
	//取pic1与pic2的交集
	 dstImage = pic1 & pic2;
}
//===========================边界提取========================
//输入：待处理图像的二值图
//参数：模板的大小和形状
//输出：图像的边界
void My_boundary_extraction(Mat& srcImage, Mat& dstImage,int size,int type)
{
	Mat element = getStructuringElement(type, Size(size,size));	//返回的是内核矩阵
	morphologyEx(srcImage, dstImage, MORPH_ERODE, element);
	//边界提取B(A)= A-(AθB)
	dstImage = srcImage - dstImage;
}
//===========================空洞填充========================
//输入：待处理图像的二值图
//参数：背景颜色（黑还是白） 漫水填充的起始点（填充的是背景，一般选择（0,0））
//输出：填充后的二值图
void My_hole_filling(Mat& srcImage, Mat& dstImage,int color,Point &startPoint)
{
	// Floodfill from point (0, 0) 以点(0,0)为种子点，进行漫水填充
	/*int x = startPoint.x;
	int y = startPoint.y;*/
	//srcImage.at<char>(x, y)
	if ( color== 255)		//背景为白
	{
		srcImage = ~srcImage;
	}
	Mat im_floodfill = srcImage.clone();
	floodFill(im_floodfill, startPoint, Scalar(255));
	//255
	// Invert floodfilled image 反转图像
	Mat im_floodfill_inv;
	bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground. 获得前景
	dstImage = (srcImage | im_floodfill_inv);
	dstImage = ~dstImage;
}
////*--------------------------【练习】连通域标记-------------------------------------*/
/*参数说明：
src_img：输入图像
flag_img：作为标记的空间(在函数内部设置为单通道)
draw_img：作为输出的图像，不同的连通域的颜色不同
iFlag：作为判断属于连通域的像素目标值，一般来说我们是对二值图进行连通域分析，所以这个值为0或者255，物体是0/1,则iFlag是0/1
type:		type==4 :用4邻域			type==8 :用8邻域
*/
void My_ImageProssing_base::seed_Connected_Component_labeling(Mat& src_img, Mat& flag_img, Mat& draw_img, int iFlag, int type)
{
	int img_row = src_img.rows;
	int img_col = src_img.cols;
	flag_img = cv::Mat::zeros(cv::Size(img_col, img_row), CV_8UC1);//标志矩阵，为0则当前像素点未访问过
	draw_img = cv::Mat::zeros(cv::Size(img_col, img_row), CV_8UC3);//绘图矩阵
	Point cdd[111000];                  //栈的大小可根据实际图像大小来设置
	long int cddi = 0;
	int next_label = 1;    //连通域标签
	int tflag = iFlag;
	long int nums_of_everylabel[100] = { 0 };	//存放每个区域的像素个数
	//Mat（纵坐标，横坐标）
	//Point（横坐标，纵坐标）
	for (int j = 0; j < img_row; j++)			//height
	{
		for (int i = 0; i < img_col; i++)		//width
		{
			//一行一行来
			if ((src_img).at<uchar>(j, i) == tflag && (flag_img).at<uchar>(j, i) == 0)   //满足条件且未被访问过
			{
				//将该像素坐标压入栈中
				cdd[cddi] = Point(i, j);
				cddi++;
				//将该像素标记
				(flag_img).at<uchar>(j, i) = next_label;
				//将栈中元素取出处理
				while (cddi != 0)
				{
					Point tmp = cdd[cddi - 1];
					cddi--;
					//对4邻域进行标记
					if (type == 4)
					{
						Point p[4];//邻域像素点，这里用的四邻域
						p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//左
						p[1] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//右
						p[2] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//上
						p[3] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//下

						//顺时针
						//p[0] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//上
						//p[1] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//右
						//p[2] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//下
						//p[3] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//左
						//逆时针
						//p[3] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//上
						//p[2] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//右
						//p[1] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//下
						//p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//左
						for (int m = 0; m < 4; m++)
						{
							if ((src_img).at<uchar>(p[m].y, p[m].x) == tflag && (flag_img).at<uchar>(p[m].y, p[m].x) == 0) //满足条件且未被访问过
							{
								//将该像素坐标压入栈中
								cdd[cddi] = p[m];
								cddi++;
								//将该像素标记
								(flag_img).at<uchar>(p[m].y, p[m].x) = next_label;
							}
						}
					}
					//对8邻域进行标记
					else if (type == 8)
					{
						Point p[8];//邻域像素点，这里用的四邻域
						p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y - 1 > 0 ? tmp.y - 1 : 0);		//左上
						p[1] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//上
						p[2] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y - 1 > 0 ? tmp.y - 1 : 0);		//右上

						p[3] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//左
						p[4] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//右

						p[5] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//左下
						p[6] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//下
						p[7] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//右下
						for (int m = 0; m < 7; m++)
						{
							if ((src_img).at<uchar>(p[m].y, p[m].x) == tflag && (flag_img).at<uchar>(p[m].y, p[m].x) == 0) //满足条件且未被访问过
							{
								//将该像素坐标压入栈中
								cdd[cddi] = p[m];
								cddi++;
								//将该像素标记
								(flag_img).at<uchar>(p[m].y, p[m].x) = next_label;
							}
						}
					}

				}
				next_label++;
			}
		}
	}
	next_label = next_label - 1;
	int all_labels = next_label;
	std::cout << "labels : " << next_label << std::endl;
	//给不同连通域的涂色并且记录下每个连通域的像素个数
	for (int j = 0;j < img_row;j++)	//行循环
	{
		for (int i = 0;i < img_col;i++)	//列循环
		{
			int now_label = (flag_img).at<uchar>(j, i);		//当前像素的label
			nums_of_everylabel[now_label]++;
			float scale = now_label * 1.0f / all_labels;
			//-------【开始处理每个像素】---------------
			draw_img.at<Vec3b>(j, i)[0] = 255 - 255 * scale;		//B通道
			draw_img.at<Vec3b>(j, i)[1] = 128 - 128 * scale;		//G通道
			draw_img.at<Vec3b>(j, i)[2] = 255 * scale;		//R通道
			//-------【处理结束】---------------
		}
	}
	for (int i = 1;i <= next_label;i++)
	{
		std::cout << "labels : " << i << "像素个数   " << nums_of_everylabel[i] << std::endl;
	}
}

///*--------------------------【人脸ROI区域处理函数】-------------------------------------*/
//训练文件路径
//string xmlPath = "D:\\opencv\\opencv4.0\\opencv4.0.0\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";


////打马赛克函数
//void mosaic(Mat& srcImage, Mat& dstImage, int times)
//{
//	blur(srcImage, dstImage, Size(times * 2 + 1, times * 2 + 1));
//}
////磨皮函数
//void clearFreckle(Mat& srcImage, Mat& dstImage, int times)
//{
//	bilateralFilter(srcImage, dstImage, times, times * 2, times / 2);
//}
////贴图函数
//void paste(Mat& srcImage, Mat& dstImage)
//{
//	resize(srcImage, dstImage, dstImage.size());
//}
////改变对比度和亮度函数
//void CotrastAndBright(Mat& srcImage, Mat& dstImage,int a,int b)
//{
//	dstImage = a *0.01* srcImage + b;
//}



