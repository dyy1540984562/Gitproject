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


//--------------------------------------------------------------非课堂练习部分-----------------------------------------------------------
//#define byte uchar 
//#define WINDOW_NAME "线性混合示例"
//#define WINDOW_NAME "程序窗口"
//#define WINDOW_WIDTH 600 

/*********************************************直方图*****************************************************/

/*
dims:需要统计的特征的数目
bins:组距
range:每个特征空间的取值范围，如灰度值：range=[0,255];

计算直方图：calcHist();
找寻最值：minMaxLoc();
*/
/*--------------------------绘制H-S直方图 色调、饱和度二维直方图-------------------------------------*/
//int main()
//{
//	//【1】载入原图，转化为HSV颜色模型
//	Mat srcImage = imread("D:\\opencv_picture_test\\趣图景图\\test8.jpg", 2|4),hsvImage;			//原图
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	cvtColor(srcImage, hsvImage,COLOR_BGR2HSV);		//完成转化
//	//【2】参数准备
//	//将色调量化为30个等级，将饱和度量化为32个等级
//	int hueBinnum = 30;		//色调直方图的直条数量
//	int saturationBinNum = 32;//饱和度的直方图条数
//	int histSize[] = { hueBinnum,saturationBinNum };//将横坐标分为30份   纵坐标分为32份
//	//定义色调范围为0-179
//	float hueRanges[] = {0,180};
//	//定义饱和度变化为0-255
//	float saturationRanges[] = {0,256};
//	const float* ranges[] = { hueRanges,saturationRanges };
//	MatND dstHist;		//:MatND是直方图对应的数据类型,用来存储直方图.
//
//	//参数准备，calHist函数中将计算第0通道和第1通道的直方图
//	int channels[] = { 0,1 };
//
//	//【3】正式调用calcHist，进行直方图计算
//	calcHist(&hsvImage,	//输入数组
//					 1,	//数组个数
//			  channels,	//通道索引
//				 Mat(),//不使用掩膜
//			   dstHist,	//输出的目标直方图
//				 	 2,	//需要计算的直方图的维数
//			  histSize,	//存放每个维度的直方图尺寸的数组
//				ranges,		//每一维数值的取值范围
//		          true,	//指示直方图是否均匀的标识符，true表示均匀的直方图
//		        false);	//累计标识符，false表示直方图在配置阶段会被清零
//	//【4】为绘制直方图准备参数
//	double maxVal = 0;	//最大值
//	minMaxLoc(dstHist,0,&maxVal,0,0);	//查找数组和子数组的全局最小值和最大值存入maxVal中
//	int scale = 10;
//	Mat histImg = Mat::zeros(saturationBinNum*scale,hueBinnum * scale,CV_8UC3);
//
//	//【5】双层循环，进行直方图绘制
//	for (int hue = 0;hue < hueBinnum;hue++)
//	{
//		for (int saturation = 0;saturation < saturationBinNum;saturation++)
//		{
//			float binVal = dstHist.at<float>(hue, saturation);	//直方图直条的值
//			int intensity = cvRound(binVal * 255 /maxVal);		//强度
//
//			//正式进行绘制
//			rectangle(histImg, Point(hue * scale, saturation * scale), Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1), Scalar::all(intensity), FILLED);
//		}
//	}
//
//
//	//【6】显示效果
//
//	namedWindow("素材图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("素材图", srcImage);
//
//	namedWindow("经过直方图均衡化后的图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("经过直方图均衡化后的图", histImg);
//  //imwrite("D:\\opencv_picture_test\\miku2.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/*--------------------------绘制一维灰度直方图-------------------------------------*/
//Mat	My_Rraw_histogram(Mat* srcImage)		//输入:要处理的灰度图   输出：该图像的直方图
//{
//	//【2】定义变量
//	MatND dstHist;
//	int dims = 1;		//需要计算的直方图的维数
//	float grayranges[] = { 0,255 };
//	const float* ranges[] = { grayranges };	//这里需要为const类型
//	int size = 256;			//表示的是将统计的灰度值分成的等份
//	int channels = 0;	//灰度图只有一个0通道
//
//	//【3】计算图像直方图
//	calcHist(srcImage,	//输入数组
//		1,	//数组个数
//		&channels,	//通道索引
//		Mat(),//不使用掩膜
//		dstHist,	//输出的目标直方图
//		dims,	//需要计算的直方图的维数
//		&size,	//存放每个维度的直方图尺寸的数组
//		ranges);	//每一维数值的取值范围	
//	int scale = 1;		//scale 每一个像素占的格数
//
//	Mat dstImage(size * scale, size, CV_8U, Scalar(0));		//长 ：size*scale ，宽：size ,值为0
//
//	//【4】获取最大值和最小值
//	double minVal = 0;
//	double maxVal = 0;
//	minMaxLoc(dstHist, &minVal, &maxVal, 0, 0);		//获得直方图中最大值和最小值
//
//	//【5】绘制出直方图
//	int hpt = saturate_cast<int>(0.9 * size);			//saturate_cast 是溢出保护    大概意思 ：if(data<0)  data = 0; else if (data > 255) data = 255;
//	for (int i = 0;i < 256;i++)
//	{
//		float binVal = dstHist.at<float>(i);
//		int realVal = saturate_cast<int>(binVal * hpt / maxVal);		//在图像上的高度 = 像素值/最大像素值 * 0.9*256   这里0.9是为了削减图像像素高度，因为最大的时候会触及顶端不美观
//		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realVal), Scalar(255));
//		//要进行绘制的目标图像 矩形的左下顶点 矩阵对角线上的右上顶点 线条的颜色（RGB）或亮度（灰度图）  一共要绘制256个矩形
//	}
//	return dstImage;
//}
//主函数
//int main()
//{
//	//【1】载入原图
//	Mat srcImage = imread("D:\\opencv_picture_test\\新垣结衣\\test2.jpg", 0);			//原图的灰度图
//	namedWindow("灰度图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("灰度图", srcImage);
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	Mat dstImage = My_Rraw_histogram(&srcImage);
//	namedWindow("一维直方图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("一维直方图", dstImage);
//	waitKey(0);
//	return 0;
//}



/*--------------------------绘制RGB三色一维直方图-------------------------------------*/
//Mat	My_Rraw_histogram(Mat* srcImage,int type)		//输入:要处理的灰度图   输出：该图像的直方图
//{
//	if (type == TYEPE_GRAY)		//一维灰度直方图绘制
//	{
//		//【1】将原图转化为灰度图
//		Mat gray_srcImage;
//		cvtColor(*srcImage,gray_srcImage, COLOR_BGR2GRAY);
//		//【2】定义变量
//		MatND dstHist;
//		int dims = 1;		//需要计算的直方图的维数
//		float grayranges[] = { 0,255 };
//		const float* ranges[] = { grayranges };	//这里需要为const类型
//		int size = 256;			//表示的是将统计的灰度值分成的等份
//		int Height = 256;
//		int channels = 0;	//灰度图只有一个0通道
//
//		//【3】计算图像直方图
//		calcHist(srcImage,	//输入数组
//			1,	//数组个数
//			&channels,	//通道索引
//			Mat(),//不使用掩膜
//			dstHist,	//输出的目标直方图
//			dims,	//需要计算的直方图的维数
//			&size,	//存放每个维度的直方图尺寸的数组
//			ranges);	//每一维数值的取值范围	
//		int scale = 1;		//scale 每一个像素占的格数
//
//		Mat dstImage(size * scale, size, CV_8U, Scalar(0));		//长 ：size*scale ，宽：size ,值为0
//
//		//【4】获取最大值和最小值
//		double minVal = 0;
//		double maxVal = 0;
//		minMaxLoc(dstHist, &minVal, &maxVal, 0, 0);		//获得直方图中最大值和最小值
//
//		//【5】绘制出直方图
//		int hpt = saturate_cast<int>(0.9 * Height);			//saturate_cast 是溢出保护    大概意思 ：if(data<int的负范围)  data = 负最大; else if (data > int的正范围) data = int 正最大;
//		for (int i = 0;i < 256;i++)
//		{
//			float binVal = dstHist.at<float>(i);
//			int realVal = saturate_cast<int>(binVal * hpt / maxVal);		//在图像上的高度 = 像素数目/像素值最大数目 * 0.9*256   这里0.9是为了削减图像像素高度，因为最大的时候会触及顶端不美观
//			rectangle(dstImage, Point(i * scale, Height - 1), Point((i + 1) * scale - 1, Height - realVal), Scalar(255));
//			//要进行绘制的目标图像 矩形的左下顶点 矩阵对角线上的右上顶点 线条的颜色（RGB）或亮度（灰度图）  一共要绘制256个矩形
//		}
//		return dstImage;
//	}
//	else if (type == TYEPE_RGB)
//	{
//		//【1】定义变量
//		MatND redHist,greenHist,blueHist;
//		int dims = 1;		//需要计算的直方图的维数
//		float grayranges[] = { 0,256 };
//		const float* ranges[] = { grayranges };	//这里需要为const类型
//		int size = 256;			//表示的是将统计的灰度值分成的等份
//		int channels_r[] = { 2 };	
//		int channels_g[] = { 1 };	
//		int channels_b[] = { 0 };	
//		//疑问 ： RGB图像的R、G、B是对应channel[0]、channel[1]、channel[2]还是对应channel[2]、channel[1]、channel[0] ？
//		//经过验证是channel[2]、channel[1]、channel[0]
//		//【2】计算图像直方图
//		//--------------------red--------------------------
//		calcHist(srcImage,	//输入数组
//			1,	//数组个数
//			channels_r,	//通道索引
//			Mat(),//不使用掩膜
//			redHist,	//输出的目标直方图
//			dims,	//需要计算的直方图的维数
//			&size,	//存放每个维度的直方图尺寸的数组
//			ranges,//每一维数值的取值范围	
//			true,//指示直方图是否均匀的标识符，true表示均匀的直方图
//			false);	//累计标识符，false表示直方图在配置阶段会被清零
//		//--------------------green--------------------------
//		calcHist(srcImage,	//输入数组
//			1,	//数组个数
//			channels_g,	//通道索引
//			Mat(),//不使用掩膜
//			greenHist,	//输出的目标直方图
//			dims,	//需要计算的直方图的维数
//			&size,	//存放每个维度的直方图尺寸的数组
//			ranges,//每一维数值的取值范围	
//			true,//指示直方图是否均匀的标识符，true表示均匀的直方图
//			false);	//累计标识符，false表示直方图在配置阶段会被清零
//		//--------------------blue--------------------------
//		calcHist(srcImage,	//输入数组
//			1,	//数组个数
//			channels_b,	//通道索引
//			Mat(),//不使用掩膜
//			blueHist,	//输出的目标直方图
//			dims,	//需要计算的直方图的维数
//			&size,	//存放每个维度的直方图尺寸的数组
//			ranges,//每一维数值的取值范围	
//			true,//指示直方图是否均匀的标识符，true表示均匀的直方图
//			false);	//累计标识符，false表示直方图在配置阶段会被清零
//
//		//【3】获取最大值和最小值
//		double minVal_r = 0, minVal_g = 0, minVal_b = 0;
//		double maxVal_r = 0, maxVal_g = 0,maxVal_b = 0;
//		minMaxLoc(redHist, &minVal_r, &maxVal_r, 0, 0);		//获得r直方图中最大值和最小值
//		minMaxLoc(greenHist, &minVal_g, &maxVal_g, 0, 0);		//获得g直方图中最大值和最小值
//		minMaxLoc(blueHist, &minVal_b, &maxVal_b, 0, 0);		//获得b直方图中最大值和最小值
//
//		int scale = 1;		//scale 每一个像素占的格数
//		int Height = 256;	//直方图高度
//		Mat dstImage(Height, size*3, CV_8UC3, Scalar(0,0,0));		//长 ：size*scale ，宽：size*3 ,值为0  将三个直方图横放在一起
//		//【4】绘制出直方图
//		int hpt = saturate_cast<int>(0.9 * Height);			//saturate_cast 是溢出保护    大概意思 ：if(data<int的负范围)  data = 负最大; else if (data > int的正范围) data = int 正最大;
//		for (int i = 0;i < 256;i++)
//		{
//			float binVal_r = redHist.at<float>(i);
//			float binVal_g = greenHist.at<float>(i);
//			float binVal_b = blueHist.at<float>(i);
//			//疑问：是否存在一张图片中maxVal_r or maxVal_g or maxVal_b 有一个值为0？这样算出来的值将会是0/0， 而实际值应该是 0
//			int intensityl_r = saturate_cast<int>(binVal_r * hpt / maxVal_r);		//在图像上的高度 = 像素数目/像素值最大数目 * 0.9*256   这里0.9是为了削减图像像素高度，因为最大的时候会触及顶端不美观
//			int intensityl_g = saturate_cast<int>(binVal_g * hpt / maxVal_g);
//			int intensityl_b = saturate_cast<int>(binVal_b * hpt / maxVal_b);
//			
//			rectangle(dstImage, Point(i * scale, Height - 1), Point((i + 1) * scale - 1, Height - intensityl_r), Scalar(0,0,255));
//			rectangle(dstImage, Point((i+size)* scale, Height - 1), Point((i + size + 1)* scale - 1, Height - intensityl_g), Scalar(0,255,0));
//			rectangle(dstImage, Point((i + 2*size)* scale, Height - 1), Point((i + 2*size + 1)* scale - 1, Height - intensityl_b), Scalar(255,0,0));
//			//要进行绘制的目标图像 矩形的左下顶点 矩阵对角线上的右上顶点 线条的颜色（RGB）或亮度（灰度图）  一共要绘制256个矩形
//		}
//		return dstImage;
//	}
//	else
//	{
//
//	}
//}
////主函数
//int main()
//{
//	//【1】载入原图
//	Mat srcImage = imread("D:\\opencv_picture_test\\RGB纯色图\\red.jpg", 2|4);			//原图
//	//Mat srcImage = imread("D:\\opencv_picture_test\\JQ\\JQ14.jpg", 2 | 4);			//原图
//	namedWindow("原图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("原图", srcImage);
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	Mat dstImage = My_Rraw_histogram(&srcImage, TYEPE_RGB);
//	namedWindow("一维直方图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("一维直方图", dstImage);
//	waitKey(0);
//	return 0;
//}

//直方图对比
/*
double compareHist(Inputarray H1,Inputarray H2, int method);
//前两个参数是要比较的大小相同的直方图，第三个变量是所选择的距离标准
有四种：
1、相关 correlation               method = CV_COMP_CORREL			 (  sum of (H1(i)-aveH1)*(H2(i)-aveH2) )  / sqrt(  sum of (H1(i)-aveH1)^2  *sum of (H2(i)-aveH2)^2 )
2、卡方 Chi-Square                method = CV_COMP_CHISQR				sum of (H1(i)-H2(i))^2/H1(i)
3、直方图相交 Intersection        method = CV_COMP_INTERSECT			sum of (min(H1(i),H2(i)))
4、Bhattacharyya 距离(巴氏距离)   method = CV_COMP_BHATTACHARYYA     
*/
/*--------------------二维直方图计算及绘制函数-------------------*/
//描述 输入 ：要处理的图  type1:转化到不同类型的二维直方图   type2： 绘制直方图 还是 仅计算归一化直方图
//Mat	My_Rraw_histogram_2D(Mat* srcImage,int type1,int type2)		//输入:要处理的图   输出：该图像的二维直方图
//{
//	if (type1 == TYEPE_HS2D)		//H-S直方图 色调、饱和度二维直方图绘制
//	{
//		if (type2 == CAL_AND_DRAW)
//		{
//			Mat hsvImage;
//			//【1】转化到HSV空间
//			cvtColor(*srcImage, hsvImage, COLOR_BGR2HSV);		//完成转化
//			//【2】参数准备
//			//将色调量化为30个等级，将饱和度量化为32个等级
//			int hueBinnum = 30;		//色调直方图的直条数量
//			int saturationBinNum = 32;//饱和度的直方图条数
//			int histSize[] = { hueBinnum,saturationBinNum };//将横坐标分为30份   纵坐标分为32份
//			//定义色调范围为0-179
//			float hueRanges[] = { 0,180 };
//			//定义饱和度变化为0-255
//			float saturationRanges[] = { 0,256 };
//			const float* ranges[] = { hueRanges,saturationRanges };
//			MatND dstHist;		//:MatND是直方图对应的数据类型,用来存储直方图.
//
//			//参数准备，calHist函数中将计算第0通道和第1通道的直方图
//			int channels[] = { 0,1 };
//
//			//【3】正式调用calcHist，进行直方图计算
//			calcHist(&hsvImage,	//输入数组
//				1,	//数组个数
//				channels,	//通道索引
//				Mat(),//不使用掩膜
//				dstHist,	//输出的目标直方图
//				2,	//需要计算的直方图的维数
//				histSize,	//存放每个维度的直方图尺寸的数组
//				ranges,		//每一维数值的取值范围
//				true,	//指示直方图是否均匀的标识符，true表示均匀的直方图
//				false);	//累计标识符，false表示直方图在配置阶段会被清零
//			//【4】为绘制直方图准备参数
//			double maxVal = 0;	//最大值
//			minMaxLoc(dstHist, 0, &maxVal, 0, 0);	//查找数组和子数组的全局最小值和最大值存入maxVal中
//			int scale = 10;
//			Mat histImg = Mat::zeros(saturationBinNum * scale, hueBinnum * scale, CV_8UC3);
//
//			//【5】双层循环，进行直方图绘制
//			for (int hue = 0;hue < hueBinnum;hue++)
//			{
//				for (int saturation = 0;saturation < saturationBinNum;saturation++)
//				{
//					float binVal = dstHist.at<float>(hue, saturation);	//直方图直条的值
//					int intensity = cvRound(binVal * 255 / maxVal);		//强度
//
//					//正式进行绘制
//					rectangle(histImg, Point(hue * scale, saturation * scale), Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1), Scalar::all(intensity), FILLED);
//				}
//			}
//			return histImg;
//		}
//		else
//		{
//			Mat hsvImage;
//			//【1】转化到HSV空间
//			cvtColor(*srcImage, hsvImage, COLOR_BGR2HSV);		//完成转化
//			//【2】参数准备
//			//将色调量化为30个等级，将饱和度量化为32个等级
//			int hueBinnum = 30;		//色调直方图的直条数量
//			int saturationBinNum = 32;//饱和度的直方图条数
//			int histSize[] = { hueBinnum,saturationBinNum };//将横坐标分为30份   纵坐标分为32份
//			//定义色调范围为0-179
//			float hueRanges[] = { 0,180 };
//			//定义饱和度变化为0-255
//			float saturationRanges[] = { 0,256 };
//			const float* ranges[] = { hueRanges,saturationRanges };
//			MatND dstHist;		//:MatND是直方图对应的数据类型,用来存储直方图.
//
//			//参数准备，calHist函数中将计算第0通道和第1通道的直方图
//			int channels[] = { 0,1 };
//
//			//【3】正式调用calcHist，进行直方图计算
//			calcHist(&hsvImage,	//输入数组
//				1,	//数组个数
//				channels,	//通道索引
//				Mat(),//不使用掩膜
//				dstHist,	//输出的目标直方图
//				2,	//需要计算的直方图的维数
//				histSize,	//存放每个维度的直方图尺寸的数组
//				ranges,		//每一维数值的取值范围
//				true,	//指示直方图是否均匀的标识符，true表示均匀的直方图
//				false);	//累计标识符，false表示直方图在配置阶段会被清零
//			normalize(dstHist, dstHist, 0, 1, NORM_MINMAX, -1, Mat());	//归一化
//			return dstHist;
//		}
//	}
//	else
//	{
//
//	}
//}

//int main()
//{
//	//【1】load两幅图片
//	//Mat srcImage1 = imread("D:\\opencv_picture_test\\JQ\\JQ5.jpg", 2 | 4);			//原图
//	//Mat srcImage2 = imread("D:\\opencv_picture_test\\JQ\\JQ18.jpg", 2|4);			//原图
//	Mat srcImage1 = imread("D:\\opencv_picture_test\\miku\\miku2.jpg", 2 | 4);			//原图
//	Mat srcImage2 = imread("D:\\opencv_picture_test\\miku\\miku5.jpg", 2 | 4);			//原图
//	if (srcImage1.empty() || srcImage2.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//【2】show两幅图片
//	namedWindow("素材图1", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("素材图1", srcImage1);
//	namedWindow("素材图2", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("素材图2", srcImage2);
//	//【2】计算直方图并且归一化
//	Mat histImg1, histImg2;
//	histImg1 = My_Rraw_histogram_2D(&srcImage1, TYEPE_HS2D, CAL_AND_NOMALIZE);
//	histImg2 = My_Rraw_histogram_2D(&srcImage2, TYEPE_HS2D, CAL_AND_NOMALIZE);
//
//	//利用库函数来比较
//	double src_src1 = compareHist(histImg1, histImg2, 0);
//	double src_src2 = compareHist(histImg1, histImg2, 1);
//	double src_src3 = compareHist(histImg1, histImg2, 2);
//	double src_src4 = compareHist(histImg1, histImg2, 3);
//
//	cout << "相关性 : " << src_src1 << endl;
//	cout << "卡方 : " << src_src2 << endl;
//	cout << "直方图相交 : " << src_src3 << endl;
//	cout << "巴氏距离 : " << src_src4 << endl;
//	waitKey(0);
//	return 0;
//}









/*********************************************直方图均衡化*****************************************************/
//原图像的直方图分布范围较小，扩大图像的动态范围，增强图像
/*
概念：直方图均衡化是通过拉伸像素强度分布范围来增强图像对比度的一种方法
伪轮廓的概念：均衡化处理后的图像只能是近似均匀分布，均衡化图像的动态范围扩大了，但其本质是扩大了量化间隔，而量化级别减少了，因此，原来不同灰度的像素经过处理后可能变得相同，形成一片相同灰度的区域，各区域之间有明显的边界，从而形成了为轮廓。
在原始图像对比度本来就比较高的情况下，如果再均衡化则灰度调和，对比度下降。
均衡化后的图像如果再瓷器均衡化，则图像不会有任何变化
*/
/*
算法步骤：
1、计算输入图像的直方图 H
2、进行直方图归一化，直方图的组距的和为255
3、计算直方图积分 H'(i) =for(int j=0;j<=i;j++) H(j);//求和
4、以H'作为查询表进行图像变换 dst(x,y) = H'(src(x,y));
简而言之：equalizeHist()函数实现的灰度直方图均衡化算法，就是把直方图每个灰度级进行归一化处理，求每种灰度的累积分布，得到一个映射的灰度映射表，然后根据相应的灰度值来修正原图中的每个像素
*/
//------------示例程序------------------
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\趣图景图\\test8.jpg", 2|4),dstImage;			//原图
//	if (srcImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//【转化为灰度图】
//	cvtColor(srcImage, srcImage,COLOR_BGR2GRAY);	
//	//【进行直方图均衡化】
//	equalizeHist(srcImage, dstImage);
//
//	//【显示结果】
//	namedWindow("经过直方图均衡化后的图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("经过直方图均衡化后的图", dstImage);
//  //imwrite("D:\\opencv_picture_test\\miku2.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}






/*********************************************分离颜色通道、多通道图像混合*****************************************************/
//split()函数：将一个多通道数组分离成几个单通道数组
/*
void split(const Mat& src,Mat* mvbegin);  or   void split(InputArray src,OutputArrayOfArrays mv);
第一个参数：需要分离的多通道数组
第二个参数：函数的输出数组或者输出的vector容器
*/
//merge()函数：通道合并
/*
void merge(const Mat* mv,size_tcount,OutputArray dst);  or  void merge(InputArrayOfArrays mv,OutputArray dst);
第一个参数：需要被合并的输入矩阵或者vector容器的阵列，参数中的所有矩阵必须有着一样的尺寸和深度
第二个参数： count 当mv为一个空白的C数组时，代表着输入矩阵的个数，显然必须大于1
第三个参数：dst 输出矩阵，和mv[0]具有一样的尺寸和深度，通道数是矩阵阵列中通道数的总数

/*
int main()
{
	Mat srcImage;
	Mat imageROI;
	vector<Mat> channels;		//这句话什么意思？
	srcImage= imread("D:\\opencv_picture_test\\test1.jpg");
	namedWindow("test1", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
	imshow("test1", srcImage);

	//把一个3通道图像转换成3个单通道图像
	split(srcImage,channels);	//分离色彩通道		这个channels有何意义？
	imageROI = channels.at(0);

	waitKey(0);
	return 0;
}

/**********************************************************************************************************************/







/*****************************Core 模块***********************************/
/****输出常见的数据结构与函数**********/
//int main()
//{
//
//	//Point_<int>、Point2i、Point 互相等价，Point_<float>、Point2f 互相等价。
//	//Scalar( a, b，c)那么定义的RGB颜色值:红色分量为c，绿色分量为b，蓝色分量为a。
//	//		  B  G  R
//	//	Size(5，5);//构造出的 Size宽度和高度都为5，即xxx.width和xXx. height都为5
//	//Rect rect = rectl & rect2; Rect rect = rect | rect2;
//	// 取两个矩形的交集和并集
//	//Rect rectShift = rect + point;		平移
//	//Rect rectScale = rect + size;			缩放
//	//cvtColor()函数：颜色空间转换函数 可以实现RGB颜色向HSV HSI等颜色空间的转换，也可以转化为灰度图像
//	/*void cvtColor(InputArray src， OutputArray dst， int code, intdstCn = 0)
//		第一个参数为输入图像，第二个参数为输出图像，第三个参数为颜色空间转
//		换的标识符， 第四个参数为目标图像的通道数，若该参数是0,
//		表示目标图像取源图像的通道数。下 面是一个调用示例 :
//		COLOR GRAY2BGR	//转化为灰度
//		*/
//	Point2f p(6,2);
//	Point3f w(1,1,1);
//	cout << "【二维点】P" << p << ";\n" << endl;
//	cout << "【三维点】w" << w << ";\n" << endl;
//	vector<float> v;
//	v.push_back(3);
//	v.push_back(5);
//	v.push_back(7);
//	cout << " 【基于Mat的vector】 shortvec =" << Mat(v) << ";\n" << endl;
//
//	vector<Point2f> points(20);
//	for (size_t i = 0;i < points.size();++i)
//	{
//		points[i] = Point2f((float)(i * 5), (float)(i % 7));
//	}
//	cout << " 【二维点向量】 points=" << points << ";\n" <<endl;
//	waitKey(0);
//	return -1;
//}
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

创建多维度矩阵
int sz[3] = {2,2,2};
Mat L(3,sz，CV_ 8UC，Scalar::al1(0)) ;
上面的例子演示了如何创建- -个超过两维的矩阵:指定维数，然后传递一-个
指向一个数组的指针，这个数组包含每个维度的尺寸;后续的两个参数与方法一
中的相同。
M. create(4,4，CV_ 8UC(2)) ;
cout << "M = "<< endl << " "<<M<<endl<<endl;

*/
//int main()
//{
//	std::cout << "hello opencv!" << std::endl;
//	/*cv::Mat secImage = imread("D:\\opencv_picture_test\\test1.jpg");
//	cv::imshow("secImage", secImage);
//	waitKey(0);
//	return 0;*/
//	cv::Mat M1(2,2,CV_8UC3,Scalar(0,0,255));	//Mat 尺寸为2,2类型：8为uchar类型，Mat通道数为3，分别为0 0 255	通常用CV_8UC3来描述RGB图像
//	std::cout << "M1_1st" << std::endl;
//	std::cout << M1 << std::endl;
//	//CV_ [位数][带符号与否][类型前缀]C[通道数]
//	cv::Mat M2(2, 2, CV_8UC3,1);	//Mat 尺寸为2,2类型：8为uchar类型，Mat通道数为3，分别为1 0 0 只对第一个元素进行赋值
//	std::cout << "M1_1st" << std::endl;
//	std::cout << M2 << std::endl;
//	int height = M2.rows;
//	int width = M2.cols;
//	std::cout << "size :"  << height << "," << width<< std::endl;
//
//	/*****深复制与浅复制*******/
//	cv::Mat M3;
//	M3.create(3,4,CV_8UC3);				//也是一种赋值语句
//
//	cv::Mat M4;
//	cv::Mat M5;
//	M4 = M3;	//M4是M3的浅复制他们指向的是同一块内存区域，相当于对同一个区域的两个不同名称。所以当M3变化时M4的值也变了
//	M3.copyTo(M5);//M5是M3的深复制，占用的是另外一个区域，他的值相当于代码运行这一行时的M3的值且不会因为M3的值改变而改变
//
//	randu(M3, Scalar(0), Scalar(255));		
//	std::cout << "M3_1st" << std::endl;
//	std::cout << M3 << std::endl;
//	std::cout << "M4_1st" << std::endl;
//	std::cout << M4 << std::endl;
//	std::cout << "M5_1st" << std::endl;
//	std::cout << M5 << std::endl;
//
//	/******遍历Mat*************/
//	//1、利用指针
//	//cv::Mat M6;
//	//cv::Mat M7;
//	//M6.create(3, 4, CV_8UC1);
//	//M7.create(3, 4, CV_8UC3);
//	////1个通道的
//	//for (int j = 0;j <= M6.rows;j++)
//	//{
//	//	uchar* data = M6.ptr<uchar>(j);
//	//	for (int i = 0;i < M6.cols;i++)
//	//	{
//	//		data[i] = j;
//	//	}
//	//
//	//}
//	////3个通道的
//	//for (int j = 0;j <= M7.rows;j++)
//	//{
//	//	
//	//	for (int i = 0;i < M7.cols;i++)
//	//	{
//	//		M7.at<Vec3b>(j, i)[0] = j;
//	//		M7.at<Vec3b>(j, i)[1] = j+1;
//	//		M7.at<Vec3b>(j, i)[2] = j+2;
//	//	}
//
//	//}
//	//std::cout << "M6" << std::endl;
//	//std::cout << M6 << std::endl;
//	//std::cout << "M7" << std::endl;
//	//std::cout << M7 << std::endl;
//	//显示像素值
//	//cv::Mat M6;
//	//M6.create(3, 4, CV_8UC1);				//也是一种赋值语句
//	//randu(M6, Scalar(0), Scalar(255));
//	//std::cout << "M6_1st" << std::endl;
//	//std::cout << M6 << std::endl;
//	//int value1 = M6.at<Vec3b>(2,1)[0];
//	//int value2= M6.at<uchar>(2,1);
//	//int value3 = M6.at<uchar>(0,2);
//	//std::cout << "value1  " << value1 <<std::endl;
//	//std::cout << "value2  "<< value2 <<std::endl;
//	//std::cout << "value3  " << value3 << std::endl;
//	waitKey(0);
//	return 0;
//
//}


/****其他**********/
//Matx是个轻量级的Mat, 必须在使用前规定好大小，比如一一个2 * 3的float
//型的Matx，可以声明为Matx23f。
//Vec是Matx的 - 一个派生类, 是一个--维的Matx, 跟vector很相似。在OpenCV
//源码中有如下定义。
//template<typename_ Tp, int n> class Vec : public Matx<_ _Tp, n, 1> { ... };
//typedef Vec<uchar, 2> Vec2b;
//Range类其实就是为了使OpenCV的使用更像MATLAB而产生的。比如
//Range : all()其实就是MATLAB里的符号。而Range(a, b)其实就是MATLAB
//中的a : b, 注意这里的a和b都应为整型。.
//OpenCV中防止内存溢出的函数有alignPtr、 alignSize、 allocate、 deallocate、
//fastMalloc、 fastFree 等。
//<math.h>.里的一 些函数使用起来很方便，有计算向量角度的函数fastAtan2、
//计算立方根的函数cubeRoot、向上取整函数cvCeil、向下取整函数cvFloor、
//四舍五入函数cvRound等。还有一 - 些类似MATLAB里面的函数, 比如cvIsInf
//判断自变量是否无穷大，cvIsNaN判断自变量是否不是 - -个数。
//显示文字相关的函数有getTextSize、cvInitFont、 putText。
//作图相关的函数有circle、 clipLine、 ellipse、 ellipse2Poly、 line、 rectangle、
//polylines、 类LineIterator.
//填充相关的函数有fllConvexPoly、 fllPoly。
//OpenCV中RNG(函数的作用为初始化随机数状态的生成器。

/*********************************基本图形绘制先跳过*******************************/
/*********************************************************************************/

/******************************颜色空间缩减*******************************************/
//颜色空间缩减：将现有的颜色空间值除以某个输入值，以获得较少的颜色数，比如：颜色值0-9->0,10-19->10，以此类推
//公式：I_new = (I_old/10)*10;	//利用int类型向下取整的特点
//可以将256种计算结果存入表table中
/*
int divdeWith = 10;
uchar table[256];
for(int i=0;i<256;++i)
{
	table[i]= divdeWith * (i/divdeWith);		//table[i]存放的是值为i的像素缩小颜色空间的结果
}
p[j]=table[p[j]];
算法步骤：
1、遍历图像矩阵的每一个像素
2、对像素应用上述公式
*/

/******************************LUT：Look up table 操作*******************************************/
/*
Mat lookUpTable(1,256,CV_8U);
uchar *p =lookUpTable.data;
for(int i =0;i<256 ;++i) p[i]=table[i];
//I输入 J输出
for(int i=0;i<times;++i) LUT(I,lookUpTable,J);
*/
/*****************************计时函数***********可以用来查看算法运行时间********************************/
/*
double time0 = static_cast<double>(getTickCount());	//记录起始时间
//一系列处理之后
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout << "此方法运行时间为：" << time0 << "秒" <<endl;	//输出运行时间
*/


/************************通过指针、迭代器、动态地址访问元素 进行颜色缩减****************************************/
/*
访问像素的三种方法：
1、指针访问：C操作符[];
2、迭代器 ：iterator
3、动态地址计算
*/

//-----------------------------------------------颜色缩减函数------------------------------------------------
//void colorReduce(Mat& inputImage,Mat& outputImage,int div,int type);
//
////-----------------------------------------------主函数------------------------------------------------
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\miku\\miku2.jpg", 2 | 4);
//	namedWindow("原始图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("原始图", srcImage);
//
//	Mat dstImage;
//	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());	//大小类型和原图一样
//
//	double time0 = static_cast<double>(getTickCount());	//记录起始时间
//	//颜色缩减
//	colorReduce(srcImage, dstImage,128,3);
//
//	//一系列处理之后
//	time0 = ((double)getTickCount() - time0) / getTickFrequency();
//	cout << "此方法运行时间为：" << time0 << "秒" << endl;	//输出运行时间
//	namedWindow("效果图", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("效果图", dstImage);
//	//imwrite("D:\\opencv_picture_test\\miku5.jpg", dstImage);
//
//	waitKey(0);
//	return 0;
//
//}
//-----------------------------------------------colorReduce()函数------------------------------------------------
//void colorReduce(Mat& inputImage, Mat& outputImage, int div, int type)
//{
//	//描述：使用指针访问 ，很好理解，和C类似
//	if (type == 1)
//	{
//		outputImage = inputImage.clone();		//因为我们需要进行处理时不对原图像产生影响，所以这里使用深复制
//		int row_num = outputImage.rows;			//行数
//		int col_num = outputImage.cols * outputImage.channels();			//列数*通道数 = 每一行元素的个数   灰度图通道数为1，彩色的为3
//		//双重循环，遍历所有像素值
//		for (int i = 0;i < row_num;i++)	//行循环
//		{
//			uchar* data = outputImage.ptr<uchar>(i);		//获取第i行的首地址
//			for (int j = 0;j < col_num;j++)	//列循环
//			{
//				data[j] = data[j] / div * div;	//颜色缩减，也可以是其他的一些处理
//			}
//		}
//	}
//	//描述：使用迭代器访问
//	/*
//	我们仅仅需要获得图像矩阵的begin和end，然后增加迭代直至begin到end。将*操作符添加在迭代指针前，即可访问当前指向的内容，
//	相比用指针直接访问可能出现的越界问题，迭代器绝对是非常安全的
//	*/
//	else if (type == 2)
//	{
//		outputImage = inputImage.clone();		//因为我们需要进行处理时不对原图像产生影响，所以这里使用深复制
//		//获取迭代器
//		Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();		//初始位置的迭代器
//		Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();		//初始位置的迭代器
//
//		//存取彩色图像像素
//		for (;it != itend;++it)
//		{
//			//-------【开始处理每个像素】---------------
//			(*it)[0] = (*it)[0] / div * div;
//			(*it)[1] = (*it)[1] / div * div;
//			(*it)[2] = (*it)[2] / div * div;
//			//-------【处理结束】---------------
//		}
//
//	}
//	//描述：使用动态地址运算配合at访问
//	else
//	{
//		outputImage = inputImage.clone();		//因为我们需要进行处理时不对原图像产生影响，所以这里使用深复制
//		int row_num = outputImage.rows;			//行数
//		int col_num = outputImage.cols ;			//列数
//		//双重循环，遍历所有像素值
//		for (int i = 0;i < row_num;i++)	//行循环
//		{	
//			for (int j = 0;j < col_num;j++)	//列循环
//			{
//				//-------【开始处理每个像素】---------------
//				outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div;		//B通道
//				outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div;		//G通道
//				outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div;		//R通道
//				//-------【处理结束】---------------
//			}
//		}
//		/*
//		讲解：成员函数at(int y,int x)可以用来存取图像元素，但在编译时需要知道图像的数据类型，at方法本身不会对任何数据类型进行转化，十分重要！！！
//		存取彩色图像的代码可以写成如下形式：
//		image.at<Vec3b>(j,i)[channel] =value;
//		opencv彩色图像的顺序存储是按照BGR不是RGB！！！！
//		*/		
//	}
//}
/****************************************************************/


/****************************************************************/



/******************************************鼠标操作画矩形****************************************************************************/
////------------------------------------【声明全局函数】--------------------------------------------------------------
//void on_MouseHandle(int event, int x, int y, int flags, void* param);
//void DrawRectangle(cv::Mat img,cv::Rect box);
////void ShowHelpText();
////------------------------------------【声明全局变量】--------------------------------------------------------------
//Rect g_rectangle;
//bool g_bDrawingBox = false;		//是否进行绘制
//RNG g_rng(12345);
////------------------------------------【main函数】--------------------------------------------------------------
//int main(int argc,char** argv)
//{
//	//【1】准备参数
//	g_rectangle = Rect(-1,-1,0,0);	//Rect(int x, int y, int width, int height);	Rect（左上角x坐标 ， 左上角y坐标，矩形的宽，矩形的高）
//	Mat srcImage(600,800,CV_8UC3),tempImage;
//	srcImage.copyTo(tempImage);	//深复制，相当于两个不同的参数
//	g_rectangle = Rect(-1,-1,0,0);
//	srcImage = Scalar::all(0);	//三个通道值为0
//	//【2】设置鼠标回调函数
//	namedWindow(WINDOW_NAME, WINDOW_NORMAL);
//	setMouseCallback(WINDOW_NAME, on_MouseHandle,(void*)&srcImage);
//	//主程序循环
//	while(1)
//	{
//		srcImage.copyTo(tempImage);	//深复制，相当于两个不同的参数
//		if (g_bDrawingBox) DrawRectangle(tempImage, g_rectangle);		//标识符为真 进行绘制
//		imshow(WINDOW_NAME, tempImage);
//		if (waitKey(10) == 27) break;		//按下Esc 退出
//	}
//	return 0;
//}
//
//
////------------------------------------【on_MouseHandle函数】--------------------------------------------------------------
////描述：		鼠标回调函数，根据不同的鼠标事件进行不同的操作
//void on_MouseHandle(int event, int x, int y, int flags, void* param)
//{
//	Mat image = *(cv::Mat*) param;
//	switch (event)
//	{
//		case EVENT_MOUSEMOVE:				//鼠标移动消息
//		{
//			if (g_bDrawingBox)		//如果是否进行绘制的标识符为真，则记录下长宽到RECT型变量中
//			{
//				g_rectangle.width = x - g_rectangle.x;
//				g_rectangle.height = y - g_rectangle.y;
//
//			}		
//		}
//		break;
//		//鼠标左键按下消息
//		case EVENT_LBUTTONDOWN:
//		{
//			g_bDrawingBox = true;
//			g_rectangle = Rect(x,y,0,0);	//记录起始点
//		}
//		break;
//		//鼠标左键抬起消息
//		case EVENT_LBUTTONUP:
//		{
//			g_bDrawingBox = false;
//			//对宽和高小于0的处理
//			if (g_rectangle.width < 0)
//			{
//				g_rectangle.x += g_rectangle.width;
//				g_rectangle.width *= -1;
//			}
//			if (g_rectangle.height < 0)
//			{
//				g_rectangle.y += g_rectangle.height;
//				g_rectangle.height *= -1;
//			}
//			//调用函数进行绘制
//			DrawRectangle(image, g_rectangle);
//		}
//		break;
//	}
//}
////------------------------------------【DrawRectangle函数】--------------------------------------------------------------
////描述：		自定义的矩形绘制函数
//void DrawRectangle(cv::Mat img, cv::Rect box)
//{
//	rectangle(img,box.tl(),box.br(),Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255), g_rng.uniform(0, 255)));	//随机颜色
//}
/**********************************************************************************************************************/


/*************利用轨迹条控制两幅图片的alpha混合（利用addWeighted函数）******************/
//------------------------------------【声明全局变量】--------------------------------------------------------------
//const int maxalpha = 100;	//alpha 的最大值
//int valueslider;		//滑动条对应的变量
//double alpha;
//double beta;
//
////声明存储图像的变量
//Mat srcImage1;
//Mat srcImage2;
//Mat dstImage;

//==============================响应滑动条的回调函数========================================
//void on_Tracker(int, void*)
//{
//	//求出当前alpha占maxalpha的比例
//	alpha = (double)valueslider/maxalpha;
//	beta = 1 - alpha;
//	//线性混合
//	addWeighted(srcImage1, alpha, srcImage2, beta,0.0 ,dstImage);	//第五个参数：gamma，一个加到权重总和的标量值
// //dstImage = alpha * srcImage1 + beta * srcImage2 + gamma ;
//	imshow(WINDOW_NAME, dstImage);
//}
//==============================main函数========================================
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\miku5.jpg", 2 | 4);		//无损原图像
//	Mat img2 = imread("D:\\opencv_picture_test\\miku2.jpg", 2 | 4);		
//	if (img1.empty() || img2.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	srcImage1 = img1;		//浅复制
//	resize(img2, srcImage2, Size(srcImage1.cols, srcImage1.rows)); //对图片进行修改;横坐标 纵坐标长度		
//	//现在图1和图2大小一样
//	//设置滑动条初值
//	valueslider = 70;
//	//创建窗口
//	//namedWindow(WINDOW_NAME, 1);
//	namedWindow(WINDOW_NAME, WINDOW_NORMAL);
//	//创建滑动条控件
//	char slider_name[50];
//	sprintf_s(slider_name,"透明度 %d", maxalpha);
//	createTrackbar(slider_name, WINDOW_NAME,&valueslider, maxalpha, on_Tracker);
//	//结果在回调函数中显示
//	on_Tracker(valueslider,0);
//	int weizhi = getTrackbarPos(slider_name, WINDOW_NAME);
//	cout << "weizhi :"   << weizhi << std::endl;			//1068 600
//	waitKey(0);
//	return 0;
//}
/**********************************************************************************************************************/


/************图像的显示与保存示例**********************/
//imread 功能是加载图像文件成为一个 Mat 对象，其中第一个参数表示 图像文件名称 。第二个参数表示 读取图像的颜色类型（默认参数是1） ，返回3通道图像，支持常见的三个参数值：
//IMREAD_UNCHANGED ：表示加载原图，不做任何改变
//IMREAD_GRAYSCALE ：表示把原图作为灰度图像加载进来
//0：该函数返回单通道图像
//大于0：函数强制返回3通道图像
//小于0：函数不对图像进行通道转化
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\test1.jpg", 2 | 4);		//无损原图像
//	Mat img2 = imread("D:\\opencv_picture_test\\test1.jpg", 0);			//灰度图
//	Mat img3 = imread("D:\\opencv_picture_test\\test1.jpg",199);	//3通道彩色
//	if (img1.empty() || img2.empty() || img3.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//
//	imshow("无损原图像", img1);
//	imshow("灰度图", img2);
//	imshow("3通道彩色", img3);
//    //imwrite("D:\\opencv_picture_test\\test5.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/************创建窗口namedwindow以及roi处理**********************/
//参考网站 https://jingyan.baidu.com/article/c910274bb73d5acd361d2d28.html
/*
定义ROI区域有两种方法：
1、指定矩形坐标，并规定好长宽；
Mat img = imread("1.jpg");
Mat roi = img(Rect(500, 200, 100, 300));
//Rect四个形参分别是：x坐标，y坐标，长，高；注(x,y)指矩形的左上角点；
2、指定感兴趣行或列的范围(Range),Range是指从起始索引到终止索引的一段联系序列
Mat img = imread("1.jpg");
Mat roi = img(Range(250, 250 +xleng), Range(200, 200 + yleng));
//Range两个形参分别是：起始行或列，起始行或列+偏移量
*/
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\test1.jpg", 2 | 4);		//无损原图像
//	if (img1.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//show the H and W of img1
//	int height = img1.rows;			//1068
//	int width = img1.cols;			//600
//	cout << "size of test1 :"  << height << "," << width<< std::endl;			//1068 600
//	//载入后先显示
//	namedWindow("test1", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("test1", img1);
//	//定义一个Mat存放图像的ROI
//	Mat image_ori;
//	image_ori = img1(Rect(0,0,100,100));		//从img1抠出
//	namedWindow("image_ori", WINDOW_NORMAL);//WINDOW_NORMAL允许用户自由伸缩窗口
//	imshow("image_ori", image_ori);
//	//imwrite("D:\\opencv_picture_test\\test5.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}


/************修改图片大小示例**********************/
//int main()
//{
//	Mat srcImage = imread("D:\\opencv_picture_test\\test4.jpg");//打开原图
//	Mat dstImage;          //目标图
//	imshow("未矫正过的图像", srcImage);//显示未矫正的原图
//	resize(srcImage, dstImage, Size(), 0.5, 0.5);//由于指定缩放的比例，Size()直接给，后面就分别是x、y方向的缩放比例
//	resize(srcImage, dstImage, Size(64, 128)); //对图片进行修改
//	imshow("矫正后的图像", dstImage);
//	//进行腐蚀操作
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//返回的是内核矩阵
//	Mat erode_dstImage;
//	erode(dstImage, erode_dstImage, element);					//腐蚀操作
//	//显示效果图
//	imshow("【矫正后的图像的效果图】", erode_dstImage);
//	waitKey(0);
//	return 0;
//}


/****图像腐蚀示例**********/
//int main()
//{
//	//载入原图
//	Mat img = imread("D:\\opencv_picture_test\\test1.jpg");
//	if (img.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//显示原图
//	imshow("【原图】", img);
//	//进行腐蚀操作
//	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));	//返回的是内核矩阵
//	Mat dstImage;
//	erode(img, dstImage, element);					//腐蚀操作
//	//显示效果图
//	imshow("【效果图】", dstImage);
//
//
//	waitKey(0);
//	return 0;
//}

/****图像模糊示例**********/
//int main()
//{
//	//载入原图
//	Mat secImage = imread("D:\\opencv_picture_test\\test1.jpg");
//	if (secImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	//进行均值滤波操作
//	Mat dstImage;
//	blur(secImage, dstImage,Size(7,7));
//	//显示效果图
//	imshow("均值滤波【效果图】", dstImage);
//
//
//	waitKey(0);
//	return 0;
//}


/****canny算子检测示例**********/
//int main()
//{
//	//载入原图
//	Mat secImage = imread("D:\\opencv_picture_test\\test1.jpg");//加载原图
//	if (secImage.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//	Mat edge, dstImage;
//	dstImage.create(secImage.size(), secImage.type());		//创建一个同大小类型的矩阵
//	cvtColor(secImage, dstImage,COLOR_BGR2GRAY);
//	imshow("【原图的灰度图】", dstImage);
//	//进行均值滤波操作
//	blur(dstImage, edge, Size(3, 3));
//	//运行canny算子
//	Canny(edge,edge,3,9,3);
//	imshow("canny算子检测【效果图】", edge);
//	waitKey(0);
//	return 0;
//}

/****读取并播放视屏示例**********/
//int main()
//{
//	//实例化的同时初始化
//	VideoCapture capture("D:\\opencv_picture_test\\video1.avi");		//类似于 int a=1;
//	//调用摄像头
//	//VideoCapture capture(0);		//类似于 int a=1;
//	/*
//		先实例化
//		VideoCapture capture;
//		再初始化
//		capture.open("D:\\opencv_picture_test\\video1.avi");
//	*/
//	//循环显示
//	while (1)
//	{
//		Mat frame;	//存储每一帧的图像
//		capture >> frame;	//读取当前帧
//		imshow("读取视频",frame);	//显示当前帧
//		waitKey(30);	//延时30ms
//	}
//	return 0;
//}

/****对视频进行处理示例**********/
//int main()
//{
//	//实例化的同时初始化
//	VideoCapture capture("D:\\opencv_picture_test\\video1.avi");		//类似于 int a=1;
//	//调用摄像头
//	//VideoCapture capture(0);		//类似于 int a=1;
//	/*
//		先实例化
//		VideoCapture capture;
//		再初始化
//		capture.open("D:\\opencv_picture_test\\video1.avi");
//	*/
//	Mat egdes;
//	//循环显示 canny
//	//while (1)
//	//{
//	//	Mat frame;	//存储每一帧的图像
//	//	capture >> frame;	//读取当前帧
//	//	imshow("原视频", frame);	//显示当前帧
//	//	cvtColor(frame, egdes, COLOR_BGR2GRAY);		//转化为灰度图
//	//	blur(egdes, egdes, Size(7, 7));				//降噪
//	//	Canny(egdes, egdes, 0, 30, 3);
//	//	imshow("处理后的视频", egdes);	//显示当前帧
//	//	if(waitKey(10) >= 0) break;	//延时10ms
//	//}
//	//循环显示 腐蚀
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








//--------------------------------------------------------------课堂练习部分-----------------------------------------------------------
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