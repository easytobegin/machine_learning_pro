#include"macros.h"
#include<cstdio>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char *str); //����

int main(int argc, char* argv[]){
	/*FILE *stream;
	freopen_s( &stream, "1.txt", "w", stdout );*/
	const char* imagename = "sample.jpg";
	//���ļ��ж���ͼ��
	Mat img = imread(imagename);

	//�������ͼ��ʧ��,����
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}

	binarizeImage(img, -1, -1, -1, -1, imagename);
	//imshow("image", res);
	//waitKey();

	/*
	//��ʾͼ��
	imshow("image", img);

	//�˺����ȴ�������������������ͷ���
	waitKey();
	*/

	return 0;
}