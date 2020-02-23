#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//#define byte uchar 

/************图像的显示与保存示例**********************/
//imread 功能是加载图像文件成为一个 Mat 对象，其中第一个参数表示 图像文件名称 。第二个参数表示 读取图像的颜色类型（默认参数是1） ，返回3通道图像，支持常见的三个参数值：
//IMREAD_UNCHANGED ：表示加载原图，不做任何改变
//IMREAD_GRAYSCALE ：表示把原图作为灰度图像加载进来
//0：该函数返回单通道图像
//大于0：函数强制返回3通道图像
//小于0：函数不对图像进行通道转化
//int main()
//{
//	Mat img1 = imread("C:\\opencv_picture_test\\test1.jpg", 1);
//	Mat img2 = imread("C:\\opencv_picture_test\\test1.jpg", 0);
//	Mat img3 = imread("C:\\opencv_picture_test\\test1.jpg", -1);
//	if (img1.empty() || img2.empty() || img3.empty())
//	{
//		printf("Could not find the image!\n");
//		return -1;
//	}
//
//	imshow("单通道图像", img1);
//	imshow("3通道图像", img2);
//	imshow("不对图像进行通道转化", img3);
//    //imwrite("C:\\opencv_picture_test\\test5.jpg", img1);//保存图片
//	waitKey(0);
//	return 0;
//}

/************修改图片大小示例**********************/
//int main()
//{
//	Mat srcImage = imread("C:\\opencv_picture_test\\test4.jpg");//打开原图
//	Mat dstImage;          //目标图
//	imshow("未矫正过的图像", srcImage);//显示未矫正的原图
//	resize(srcImage, dstImage, Size(), 0.5, 0.5);//由于指定缩放的比例，Size()直接给，后面就分别是x、y方向的缩放比例
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

/****mat的基本操作示例**********/
//int main()
//{
//	std::cout << "hello opencv!" << std::endl;
//	/*cv::Mat secImage = imread("C:\\opencv_picture_test\\test1.jpg");
//	cv::imshow("secImage", secImage);
//	waitKey(0);
//	return 0;*/
//	cv::Mat M1(2,2,CV_8UC3,Scalar(0,0,255));	//Mat 尺寸为2,2类型：8为uchar类型，Mat通道数为3，分别为0 0 255	通常用CV_8UC3来描述RGB图像
//	std::cout << "M1_1st" << std::endl;
//	std::cout << M1 << std::endl;
//
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

/****图像腐蚀示例**********/
//int main()
//{
//	//载入原图
//	Mat img = imread("C:\\opencv_picture_test\\test1.jpg");
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
//	Mat secImage = imread("C:\\opencv_picture_test\\test1.jpg");
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
//	Mat secImage = imread("C:\\opencv_picture_test\\test1.jpg");//加载原图
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
//	VideoCapture capture("C:\\opencv_picture_test\\video1.avi");		//类似于 int a=1;
//	//调用摄像头
//	//VideoCapture capture(0);		//类似于 int a=1;
//	/*
//		先实例化
//		VideoCapture capture;
//		再初始化
//		capture.open("C:\\opencv_picture_test\\video1.avi");
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
int main()
{
	//实例化的同时初始化
	VideoCapture capture("C:\\opencv_picture_test\\video1.avi");		//类似于 int a=1;
	//调用摄像头
	//VideoCapture capture(0);		//类似于 int a=1;
	/*
		先实例化
		VideoCapture capture;
		再初始化
		capture.open("C:\\opencv_picture_test\\video1.avi");
	*/
	Mat egdes;
	//循环显示 canny
	//while (1)
	//{
	//	Mat frame;	//存储每一帧的图像
	//	capture >> frame;	//读取当前帧
	//	imshow("原视频", frame);	//显示当前帧
	//	cvtColor(frame, egdes, COLOR_BGR2GRAY);		//转化为灰度图
	//	blur(egdes, egdes, Size(7, 7));				//降噪
	//	Canny(egdes, egdes, 0, 30, 3);
	//	imshow("处理后的视频", egdes);	//显示当前帧
	//	if(waitKey(10) >= 0) break;	//延时10ms
	//}
	//循环显示 腐蚀
	while (1)
	{
		Mat frame;	//存储每一帧的图像
		capture >> frame;	//读取当前帧
		imshow("原视频", frame);	//显示当前帧
		//进行腐蚀操作
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//返回的是内核矩阵
		Mat dstImage;
		erode(frame, dstImage, element);					//腐蚀操作
		imshow("处理后的视频", dstImage);	//显示当前帧
		if(waitKey(10) >= 0) break;	//延时10ms
	}
	return 0;
}