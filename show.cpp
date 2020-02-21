#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("C:\\opencv_picture_test\\test1.jpg");
	if (img.empty())
	{

		printf("Could not find the image!\n");
		return -1;
	}

	imshow("ImputImage", img);

	waitKey(0);
	return 0;
}
