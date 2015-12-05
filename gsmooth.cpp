#include"macros.h"
#include<string>
#include<cmath>
#include <opencv2/opencv.hpp>

const double inf = 999.5;  //参数缺省时置inf

using namespace cv;
using namespace std;



/*
没有参数时,sigma,radius分别等于inf,而method没有方法时为NULL
*/
Mat Gauss_sommth(Mat image,double sigma,double radius,string method)
{
	Mat sm;
	Mat a1 = image;
	Mat a2 = image; //浅拷贝图像
	Mat origin = image.clone(); //原图像,深拷贝
	IplImage *origin1; //原图像,深拷贝
	origin1 = &IplImage(origin);
	IplImage *src,*hcol,*hrow;
	src = &IplImage(image);
	hcol = &IplImage(a1);
	hrow = &IplImage(a2);
	//cvShowImage("src:", src);
	//waitKey(0);
	if (sigma == inf)
	{
		sigma = 1;
	}
	if (radius == inf)
	{
		radius = ceil(2.5 * sigma);
	}
	else
	{
		radius = ceil(1.0*radius);
	}
	/*if (method == NULL)
	{
		method = "none";
	}*/
	if (sigma == 0)
	{
		sm = image;
	}
	else  //matlab : H = FSPECIAL('gaussian', HSIZE, SIGMA)
	{ 
		//hcol = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		//hrow = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

		//高斯滤波
		cvShowImage("原图:", origin1); //原图
		waitKey(0);

		cvSmooth(origin1, hcol, CV_GAUSSIAN, 2 * radius + 1, 1, sigma);
		cvShowImage("高斯滤波col:", hcol);
		waitKey(0);
		cvSmooth(origin1, hrow, CV_GAUSSIAN, 1, 2 * radius + 1, sigma);

		cvShowImage("高斯滤波row:", hrow);
		//cvShowImage("show row:", hrow);
		waitKey(0);

	}
	return sm;
}