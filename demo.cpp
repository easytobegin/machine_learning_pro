#include"macros.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char *str); //声明

int main(int argc, char* argv[])
{
	const char* imagename = "sample.jpg";

	//从文件中读入图像
	Mat img = imread(imagename);

	//如果读入图像失败,调试
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}

	binarizeImage(img, -1, -1, -1, -1, imagename);
	//imshow("image", res);
	//waitKey();

	/*
	//显示图像
	imshow("image", img);

	//此函数等待按键，按键盘任意键就返回
	waitKey();
	*/

	return 0;
}