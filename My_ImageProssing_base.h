#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
#define byte uchar 
#define WINDOW_NAME "�����򴰿ڡ�"			//Ϊ���ڱ��ⶨ��ĺ�
class My_ImageProssing_base
{
	private:		;
	protected:		;
	public:
		//-----------------------------------����һάֱ��ͼ--------------------------------------------------------
		Mat	My_Rraw_histogram(Mat* srcImage);
		////*--------------------------����ϰ����ֵ�ָ�������ַ���-------------------------------------*/
		void My_P_tile(Mat* srcImage, Mat* dstImage, int P);
		void My_Iteration(Mat* srcImage, Mat* dstImage, float delta_T);
		byte My_Ostu(Mat* srcImage/*, Mat* dstImage*/);
		//�ֲ�����Ӧ��   ���ڴ����ֵ  areas_of_H����ֱ����ָ�ĸ���  areas_of_W�������귽��ָ�ĸ���
		void My_local_adaptive(Mat* srcImage, Mat* dstImage, int areas_of_H, int areas_of_W);
		void My_artificial(Mat* srcImage, Mat* dstImage, int Threshold);
		void main_of_diferent_Threshold_types();
		void seed_Connected_Component_labeling(Mat& src_img, Mat& flag_img, Mat& draw_img, int iFlag, int type);
};

My_ImageProssing_base My;	//ʵ����



Mat My_ImageProssing_base::My_Rraw_histogram(Mat* srcImage)		//����:Ҫ����ĻҶ�ͼ   �������ͼ���ֱ��ͼ
{
	//��2���������
	MatND dstHist;
	int dims = 1;		//��Ҫ�����ֱ��ͼ��ά��
	float grayranges[] = { 0,255 };
	const float* ranges[] = { grayranges };	//������ҪΪconst����
	int size = 256;			//��ʾ���ǽ�ͳ�ƵĻҶ�ֵ�ֳɵĵȷ�
	int channels = 0;	//�Ҷ�ͼֻ��һ��0ͨ��

	//��3������ͼ��ֱ��ͼ
	calcHist(srcImage,	//��������
		1,	//�������
		&channels,	//ͨ������
		Mat(),//��ʹ����Ĥ
		dstHist,	//�����Ŀ��ֱ��ͼ
		dims,	//��Ҫ�����ֱ��ͼ��ά��
		&size,	//���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges);	//ÿһά��ֵ��ȡֵ��Χ	
	int scale = 1;		//scale ÿһ������ռ�ĸ���

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));		//�� ��size*scale ����size ,ֵΪ0

	//��4����ȡ���ֵ����Сֵ
	double minVal = 0;
	double maxVal = 0;
	minMaxLoc(dstHist, &minVal, &maxVal, 0, 0);		//���ֱ��ͼ�����ֵ����Сֵ

	//��5�����Ƴ�ֱ��ͼ
	int hpt = saturate_cast<int>(0.9 * size);			//saturate_cast ���������    �����˼ ��if(data<0)  data = 0; else if (data > 255) data = 255;
	for (int i = 0;i < 256;i++)
	{
		float binVal = dstHist.at<float>(i);
		int realVal = saturate_cast<int>(binVal * hpt / maxVal);		//��ͼ���ϵĸ߶� = ����ֵ/�������ֵ * 0.9*256   ����0.9��Ϊ������ͼ�����ظ߶ȣ���Ϊ����ʱ��ᴥ�����˲�����
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realVal), Scalar(255));
		//Ҫ���л��Ƶ�Ŀ��ͼ�� ���ε����¶��� ����Խ����ϵ����϶��� ��������ɫ��RGB�������ȣ��Ҷ�ͼ��  һ��Ҫ����256������
	}
	return dstImage;
};

////*--------------------------����ϰ����ֵ�ָ�������ַ���-------------------------------------*/
void My_ImageProssing_base::My_P_tile(Mat* srcImage, Mat* dstImage, int P)
{
	//��1������һά�Ҷ�ֱ��ͼ
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
	//��2������ֱ��ͼ����,�����ҳ���ֵ
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
	cout << "P_tile������ֵΪ��" << threshold << endl;
	//��3����ֵ��
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
	//��1�������ҶȺ���С�Ҷ�
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
	cout << "����������ֵΪ��" << new_T << endl;
	//���ݵó�����ֵ��ֵ��ͼ��
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
	int Ostu_Threshold = 0; //�����ֵ
	int size = height * width;
	float variance;   //��䷽��
	float maxVariance = 0, w1 = 0, w2 = 0, avgValue = 0;
	float u0 = 0, u1 = 0, u2 = 0;
	//���ɻҶ�ֱ��ͼ
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
	//�����ҳ���䷽�����maxVariance������ֵ��Ostu_Threshold��
	for (int i = 0;i <= 255;i++)
	{
		w1 = 0;
		w2 = 0;
		u1 = 0;
		u2 = 0;
		//���㱳������ռ��,ƽ���Ҷ�
		for (int j = 0;j <= i;j++)
		{
			w1 += histgram[j];
			u1 += histgram[j] * j;
		}
		u1 = u1 / w1;
		//����ǰ������ռ��,ƽ���Ҷ�
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
		//������䷽��
		variance = w1 * w2 * (u1 - u2) * (u1 - u2);
		if (variance > maxVariance)
		{ //�ҵ�ʹ�ҶȲ�����ֵ
			maxVariance = variance;
			Ostu_Threshold = i;            //�Ǹ�ֵ������ֵ
		}
	}
	cout << "�����ֵΪ��" << Ostu_Threshold << endl;
	////��3����ֵ��
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
//�ֲ�����Ӧ��   ���ڴ����ֵ  areas_of_H����ֱ����ָ�ĸ���  areas_of_W�������귽��ָ�ĸ���
void My_ImageProssing_base::My_local_adaptive(Mat* srcImage, Mat* dstImage, int areas_of_H, int areas_of_W)		//���ڴ����ֵ��
{
	int height = (*srcImage).rows / areas_of_H;			//ÿһС���height
	int width = (*srcImage).cols / areas_of_W;			//ÿһС���width
	int Ostu_Threshold = 0; //�����ֵ
	int size = height * width / areas_of_H / areas_of_W;		//ÿһС���size
	//һ��һ�е���
	for (int y = 0; y < areas_of_H; y++)
	{
		for (int x = 0; x < areas_of_W; x++)
		{
			float variance = 0;   //��䷽��
			float maxVariance = 0, w1 = 0, w2 = 0, avgValue = 0;
			float u0 = 0, u1 = 0, u2 = 0;
			//����areas_of_W*areas_of_H���ֲ��Ҷ�ֱ��ͼ
			int pixels[256];
			float histgram[256];
			for (int i = 0; i < 256; i++)
			{
				pixels[i] = 0;
			}
			//������ÿ��С�����Ҷ�ֵ����
			//������ֱ��ͼ��
			for (int j = y * height; j < ((y + 1 == areas_of_H) ? (*srcImage).rows : (y + 1) * height); j++) //? : ��һ����Ŀ�������Ҳ��Ψһ��һ����Ŀ���������ǰ����߼���������ǰ��Ҳ���ǣ������ʾ��������ʱ��ֵ�������������������ʱ��ֵ�����磬��a > bʱ��x = 1����x = 0������д��x = a > b ? 1 : 0��
			{
				for (int i = x * width; i < ((x + 1 == areas_of_W) ? (*srcImage).cols : (x + 1) * width); i++)
				{
					pixels[(*srcImage).at<uchar>(j, i)]++;
				}
			}
			//��ֱ��ͼ��һ����
			for (int i = 0; i < 256; i++)
			{
				histgram[i] = pixels[i] * 1.0f / size;
			}
			//�����ҳ���䷽�����maxVariance������ֵ��Ostu_Threshold��
			for (int i = 0;i <= 255;i++)
			{
				w1 = 0;
				w2 = 0;
				u1 = 0;
				u2 = 0;
				//���㱳������ռ��,ƽ���Ҷ�
				for (int j = 0;j <= i;j++)
				{
					w1 += histgram[j];
					u1 += histgram[j] * j;
				}
				u1 = u1 / w1;
				//����ǰ������ռ��,ƽ���Ҷ�
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
				//������䷽��
				variance = w1 * w2 * (u1 - u2) * (u1 - u2);
				if (variance > maxVariance)
				{ //�ҵ�ʹ�ҶȲ�����ֵ
					maxVariance = variance;
					Ostu_Threshold = i;            //�Ǹ�ֵ������ֵ
				}
			}
			cout << "�����ֵΪ��" << Ostu_Threshold << endl;
			//��3����ֵ��
			for (int j = y * height; j < ((y + 1 == areas_of_H) ? (*srcImage).rows : (y + 1) * height); j++) //? : ��һ����Ŀ�������Ҳ��Ψһ��һ����Ŀ���������ǰ����߼���������ǰ��Ҳ���ǣ������ʾ��������ʱ��ֵ�������������������ʱ��ֵ�����磬��a > bʱ��x = 1����x = 0������д��x = a > b ? 1 : 0��
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
	//Mat srcImage = imread("D:\\opencv_picture_test\\��ԫ����\\test2.jpg", 0);	//�����ʱ��ת��Ϊ�Ҷ�ͼ
	//Mat srcImage = imread("D:\\opencv_picture_test\\miku\\miku2.jpg", 0);	//�����ʱ��ת��Ϊ�Ҷ�ͼ
	Mat srcImage = imread("D:\\opencv_picture_test\\��ֵ����\\Ӳ��.png", 0);	//�����ʱ��ת��Ϊ�Ҷ�ͼ
	//Mat srcImage = imread("D:\\opencv_picture_test\\JQ\\JQ32.jpg", 0);	//�����ʱ��ת��Ϊ�Ҷ�ͼ
	namedWindow("ԭʼͼ", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	imshow("ԭʼͼ", srcImage);

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);
	double time0 = static_cast<double>(getTickCount());	//��¼��ʼʱ��
	//��ֵ����+��ֵ��
	//My_P_tile(&srcImage,&dstImage,20);			//��PΪ20
	//My_Iteration(&srcImage, &dstImage,0.1);
	//My_Ostu(&srcImage, &dstImage);
	//My_local_adaptive(&srcImage, &dstImage, 5, 5);
	My_artificial(&srcImage, &dstImage, 83);
	//һϵ�д���֮��
	//time0 = ((double)getTickCount() - time0) / getTickFrequency();
	//cout << "�˷�������ʱ��Ϊ��" << time0 << "��" << endl;	//�������ʱ��
	//namedWindow("Ч��ͼ", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	//imshow("Ч��ͼ", dstImage);
	//dstImage = My_Rraw_histogram(&srcImage);
	//namedWindow("һάֱ��ͼ", WINDOW_NORMAL);//WINDOW_NORMAL�����û�������������
	//imshow("һάֱ��ͼ", dstImage);
	//imwrite("D:\\opencv_picture_test\\��ֵ����\\��ֵ��83.jpg", dstImage);
}


////*--------------------------����ϰ��̬ѧ������-------------------------------------*/

//===========================HitMiss�任========================
//���룺������ͼ��ĻҶ�ͼ
//�������任ģ��D��W
//�����ģ��λ�õ�����ͼ
void My_HitMissChange(Mat& srcImage, Mat& dstImage, Mat& D,Mat &W_SUB_D)
{
	Mat binaryMat, binaryMat_inv;
	Mat pic1, pic2;
	//��һ��(��ԭͼ��ֵ������ȡ��ͼ��)
	byte thre = My.My_Ostu(&srcImage);
	threshold(srcImage,binaryMat,thre, 255, 0);		//ԭͼ��ֵͼ
	threshold(srcImage, binaryMat_inv, thre, 255, 1);//��ֵͼ�Ĳ�
	//��D��A��ʴ
	morphologyEx(binaryMat,pic1,MORPH_ERODE,D);
	//��(W-D)��A��������ʴ
	morphologyEx(binaryMat_inv, pic2, MORPH_ERODE, W_SUB_D);
	//ȡpic1��pic2�Ľ���
	 dstImage = pic1 & pic2;
}
//===========================�߽���ȡ========================
//���룺������ͼ��Ķ�ֵͼ
//������ģ��Ĵ�С����״
//�����ͼ��ı߽�
void My_boundary_extraction(Mat& srcImage, Mat& dstImage,int size,int type)
{
	Mat element = getStructuringElement(type, Size(size,size));	//���ص����ں˾���
	morphologyEx(srcImage, dstImage, MORPH_ERODE, element);
	//�߽���ȡB(A)= A-(A��B)
	dstImage = srcImage - dstImage;
}
//===========================�ն����========================
//���룺������ͼ��Ķ�ֵͼ
//������������ɫ���ڻ��ǰף� ��ˮ������ʼ�㣨�����Ǳ�����һ��ѡ��0,0����
//���������Ķ�ֵͼ
void My_hole_filling(Mat& srcImage, Mat& dstImage,int color,Point &startPoint)
{
	// Floodfill from point (0, 0) �Ե�(0,0)Ϊ���ӵ㣬������ˮ���
	/*int x = startPoint.x;
	int y = startPoint.y;*/
	//srcImage.at<char>(x, y)
	if ( color== 255)		//����Ϊ��
	{
		srcImage = ~srcImage;
	}
	Mat im_floodfill = srcImage.clone();
	floodFill(im_floodfill, startPoint, Scalar(255));
	//255
	// Invert floodfilled image ��תͼ��
	Mat im_floodfill_inv;
	bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground. ���ǰ��
	dstImage = (srcImage | im_floodfill_inv);
	dstImage = ~dstImage;
}
////*--------------------------����ϰ����ͨ����-------------------------------------*/
/*����˵����
src_img������ͼ��
flag_img����Ϊ��ǵĿռ�(�ں����ڲ�����Ϊ��ͨ��)
draw_img����Ϊ�����ͼ�񣬲�ͬ����ͨ�����ɫ��ͬ
iFlag����Ϊ�ж�������ͨ�������Ŀ��ֵ��һ����˵�����ǶԶ�ֵͼ������ͨ��������������ֵΪ0����255��������0/1,��iFlag��0/1
type:		type==4 :��4����			type==8 :��8����
*/
void My_ImageProssing_base::seed_Connected_Component_labeling(Mat& src_img, Mat& flag_img, Mat& draw_img, int iFlag, int type)
{
	int img_row = src_img.rows;
	int img_col = src_img.cols;
	flag_img = cv::Mat::zeros(cv::Size(img_col, img_row), CV_8UC1);//��־����Ϊ0��ǰ���ص�δ���ʹ�
	draw_img = cv::Mat::zeros(cv::Size(img_col, img_row), CV_8UC3);//��ͼ����
	Point cdd[111000];                  //ջ�Ĵ�С�ɸ���ʵ��ͼ���С������
	long int cddi = 0;
	int next_label = 1;    //��ͨ���ǩ
	int tflag = iFlag;
	long int nums_of_everylabel[100] = { 0 };	//���ÿ����������ظ���
	//Mat�������꣬�����꣩
	//Point�������꣬�����꣩
	for (int j = 0; j < img_row; j++)			//height
	{
		for (int i = 0; i < img_col; i++)		//width
		{
			//һ��һ����
			if ((src_img).at<uchar>(j, i) == tflag && (flag_img).at<uchar>(j, i) == 0)   //����������δ�����ʹ�
			{
				//������������ѹ��ջ��
				cdd[cddi] = Point(i, j);
				cddi++;
				//�������ر��
				(flag_img).at<uchar>(j, i) = next_label;
				//��ջ��Ԫ��ȡ������
				while (cddi != 0)
				{
					Point tmp = cdd[cddi - 1];
					cddi--;
					//��4������б��
					if (type == 4)
					{
						Point p[4];//�������ص㣬�����õ�������
						p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//��
						p[1] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//��
						p[2] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//��
						p[3] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//��

						//˳ʱ��
						//p[0] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//��
						//p[1] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//��
						//p[2] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//��
						//p[3] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//��
						//��ʱ��
						//p[3] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//��
						//p[2] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//��
						//p[1] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//��
						//p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//��
						for (int m = 0; m < 4; m++)
						{
							if ((src_img).at<uchar>(p[m].y, p[m].x) == tflag && (flag_img).at<uchar>(p[m].y, p[m].x) == 0) //����������δ�����ʹ�
							{
								//������������ѹ��ջ��
								cdd[cddi] = p[m];
								cddi++;
								//�������ر��
								(flag_img).at<uchar>(p[m].y, p[m].x) = next_label;
							}
						}
					}
					//��8������б��
					else if (type == 8)
					{
						Point p[8];//�������ص㣬�����õ�������
						p[0] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y - 1 > 0 ? tmp.y - 1 : 0);		//����
						p[1] = Point(tmp.x, tmp.y - 1 > 0 ? tmp.y - 1 : 0);//��
						p[2] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y - 1 > 0 ? tmp.y - 1 : 0);		//����

						p[3] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y);		//��
						p[4] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y);//��

						p[5] = Point(tmp.x - 1 > 0 ? tmp.x - 1 : 0, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//����
						p[6] = Point(tmp.x, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//��
						p[7] = Point(tmp.x + 1 < img_col - 1 ? tmp.x + 1 : img_col - 1, tmp.y + 1 < img_row - 1 ? tmp.y + 1 : img_row - 1);//����
						for (int m = 0; m < 7; m++)
						{
							if ((src_img).at<uchar>(p[m].y, p[m].x) == tflag && (flag_img).at<uchar>(p[m].y, p[m].x) == 0) //����������δ�����ʹ�
							{
								//������������ѹ��ջ��
								cdd[cddi] = p[m];
								cddi++;
								//�������ر��
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
	//����ͬ��ͨ���Ϳɫ���Ҽ�¼��ÿ����ͨ������ظ���
	for (int j = 0;j < img_row;j++)	//��ѭ��
	{
		for (int i = 0;i < img_col;i++)	//��ѭ��
		{
			int now_label = (flag_img).at<uchar>(j, i);		//��ǰ���ص�label
			nums_of_everylabel[now_label]++;
			float scale = now_label * 1.0f / all_labels;
			//-------����ʼ����ÿ�����ء�---------------
			draw_img.at<Vec3b>(j, i)[0] = 255 - 255 * scale;		//Bͨ��
			draw_img.at<Vec3b>(j, i)[1] = 128 - 128 * scale;		//Gͨ��
			draw_img.at<Vec3b>(j, i)[2] = 255 * scale;		//Rͨ��
			//-------�����������---------------
		}
	}
	for (int i = 1;i <= next_label;i++)
	{
		std::cout << "labels : " << i << "���ظ���   " << nums_of_everylabel[i] << std::endl;
	}
}

///*--------------------------������ROI����������-------------------------------------*/
//ѵ���ļ�·��
//string xmlPath = "D:\\opencv\\opencv4.0\\opencv4.0.0\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";


////�������˺���
//void mosaic(Mat& srcImage, Mat& dstImage, int times)
//{
//	blur(srcImage, dstImage, Size(times * 2 + 1, times * 2 + 1));
//}
////ĥƤ����
//void clearFreckle(Mat& srcImage, Mat& dstImage, int times)
//{
//	bilateralFilter(srcImage, dstImage, times, times * 2, times / 2);
//}
////��ͼ����
//void paste(Mat& srcImage, Mat& dstImage)
//{
//	resize(srcImage, dstImage, dstImage.size());
//}
////�ı�ԱȶȺ����Ⱥ���
//void CotrastAndBright(Mat& srcImage, Mat& dstImage,int a,int b)
//{
//	dstImage = a *0.01* srcImage + b;
//}



