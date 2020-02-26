#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//#define byte uchar 
//#define WINDOW_NAME "线性混合示例"
//#define WINDOW_NAME "程序窗口"
//#define WINDOW_WIDTH 600 

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
/*****************************计时函数*******************************************/
/*
double time0 = static_cast<double>(getTickCount());	//记录起始时间
//一系列处理之后
time0 = ((double)getTickCount()-time0)/getTickFrequency();
cout << "此方法运行时间为：" << time0 << "秒" <<endl;	//输出运行时间
*/

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


/*************利用轨迹条控制两幅图片的alpha混合******************/
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
//	addWeighted(srcImage1, alpha, srcImage2, beta,0.0 ,dstImage);
//	imshow(WINDOW_NAME, dstImage);
//}
////==============================main函数========================================
//int main()
//{
//	Mat img1 = imread("D:\\opencv_picture_test\\test1.jpg", 2 | 4);		//无损原图像
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
int main()
{
	//载入原图
	Mat img = imread("D:\\opencv_picture_test\\test1.jpg");
	if (img.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}
	//显示原图
	imshow("【原图】", img);
	//进行腐蚀操作
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));	//返回的是内核矩阵
	Mat dstImage;
	erode(img, dstImage, element);					//腐蚀操作
	//显示效果图
	imshow("【效果图】", dstImage);


	waitKey(0);
	return 0;
}

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

