#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//#define byte uchar 

//图像的显示与保存
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


//修改图片大小
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





/****mat的基本操作**********/
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




//图像腐蚀
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



