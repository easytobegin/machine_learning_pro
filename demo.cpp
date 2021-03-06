#include"macros.h"
#include<cstdio>
#include"binarizeImage.h"
#include"binarizeImageAlg1.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
	/*FILE *stream;
	freopen_s( &stream, "1.txt", "w", stdout );*/
	const char* imagename = "value.jpg";
	//从文件中读入图像
	Mat img = imread(imagename);

	//如果读入图像失败,调试
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
	Mat hc1;
	Mat	vc1;
	Mat lap1;
	binarizeImage(img, -1, -1, -1, -1, imagename,hc1,vc1,lap1); //hc1,vc1引用

	binarizeImageAlg1(img,-1,-1,-1,hc1,vc1,lap1);
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