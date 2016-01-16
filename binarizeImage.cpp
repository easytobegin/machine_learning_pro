#include"macros.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

IplImage *g_pSrcImage, *g_pCannyImg; //原始图,目标图
const char *pstrWindowsCannyTitle = "边缘检测图";

Mat Gauss_sommth(Mat image, double sigma, double radius, string method); //声明
void Mat_Change_To_Matrix(Mat image);
void imgcut3(Mat para1, Mat para2, Mat para3, Mat para4);  //四个参数都是矩阵类型，都是二维矩阵
//cvCreateTrackbar的回调函数
void on_trackbar(int threshold)
{
	//canny边缘检测
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowsCannyTitle, g_pCannyImg);
}

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char* str) //规定负数代表没有值
{
	/*int nargin = 1; //image算一个参数
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	if (wgt >= 0)
	{
	cnt1++;
	nargin++;
	}
	if (thi >= 0)
	{
	cnt2++;
	nargin++;
	}
	if (tlo >= 0)
	{
	cnt3++;
	nargin++;
	}
	if (sigE >= 0)
	{
	cnt4++;
	nargin++;
	}
	//默认值
	if (nargin < 2 || cnt1 == 0)
	wgt = 160;
	if (nargin < 3 || cnt2 == 0)
	thi = 0.4;
	if (nargin < 4 || cnt3 == 0)
	tlo = 0.1;
	if (nargin < 5 || cnt4 == 0)
	sigE = 0.6;
	*/

	//cout << "行:" << image.rows << " " << "列:" << image.cols << endl;  //原图640 * 1024
	/*
	//灰度处理
	//cout << "wgt:" << wgt << " " << "thi:" << thi << " " << "tlo:" << tlo << " " << "sigE:" << sigE << endl;
	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//转换图片颜色，灰度处理

	//imwrite("C:/Users/Administrator/Documents/Visual Studio 2013/Projects/Machine_Learning/Machine_Learning", gray_image);
	imshow("Gray Image", gray_image);//显示灰度图；
	waitKey(0);//等待直到用户按下一个按键之后退出。
	*/

	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//转换图片颜色，灰度处理

	//canny边缘检测
	Mat canny_result;
	Canny(gray_image, canny_result, 60, 80);
	//cvNamedWindow("cannyResult");
	//imshow("cannyResult", canny_result);
	//waitKey(0);

	//imshow("原始图:", image);
	//const CvArr *after_deal = (CvArr *)&canny_result; //把canny结果转换为CvArr类型
	int total_rows = canny_result.rows; //获取图像的行
	int total_cols = canny_result.cols; //获取图像的列

	//opencv三个通道[0] = b,[1] = g,[2] = r

	/*
	根据论文的算法:矩阵相减,二阶微分求得效果图,和拉普拉斯不太一样
	*/
	Mat A_matrix = canny_result(Range(1, total_rows - 1), Range(2, total_cols));

	Mat B_matrix = canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1));

	Mat C_matrix = canny_result(Range(2, total_rows), Range(1, total_cols - 1));

	Mat D_matrix = canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1));

	Mat dx = A_matrix - B_matrix;  //dx

	//cout << dx << endl;

	//imshow("dx_Result", dx);
	//waitKey(0);

	Mat dy = C_matrix - D_matrix;  //dy

	//cout << total_rows << " " << total_cols << endl;
	//imshow("dy_Result", dy);
	//waitKey(0);

	Mat lap; //合并dx和dy后的图像

	addWeighted(dx, 0.5, dy, 0.5, 0, lap);
	//imshow("效果图合并dx,dy:",dst);

	cout << "lap行:" << lap.rows << " " << "列:" << lap.cols << endl;


	//waitKey(0);



	/*
	% Bias high-confidence background pixels
	*/

	int sr = 20; //no need found to vary this parameter
	//Gauss_sommth(dst, sr, 3 * sr, "mirror");

	/*
	先跳过高斯平滑
	*/


	/*
	% Assemble matrices of edge connections -- horizontal and vertical
	*/
	Mat hc;
	Mat vc;

	Mat test1, test2;
	Mat test3, test4;

	hc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dy > 0))  //638 * 1022
		| (canny_result(Range(2, total_rows), Range(1, total_cols - 1)) & (dy <= 0)));

	cout << "hc行:" << hc.rows << " " << "列:" << hc.cols << endl;
	waitKey(0);
	/*imshow("hc:", hc);
	waitKey(0);
	*/

	vc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dx > 0))  //638 * 1022
		| (canny_result(Range(1, total_rows - 1), Range(2, total_cols)) & (dx <= 0)));

	//cout << "行:" << vc.rows << " " << "列:" << vc.cols << endl;
	/*imshow("vc:", vc);
	waitKey(0);
	*/

	hc = hc(Range(1, total_rows - 2), Range(1, total_cols - 2));  //638 * 1022


	cout << "vc行:" << vc.rows << " " << "列:" << vc.cols << endl;
	waitKey(0);
	//hc_result = hc(Range(1, total_rows-1), Range(1, total_cols-1));

	/*
	imshow("hc:", hc);
	waitKey(0);
	*/

	vc = vc(Range(1, total_rows - 2), Range(1, total_cols - 2)); //638 * 1022


	//imshow("vc", vc);
	//waitKey(0);
	//cout << 1500 - lap << endl;
	//cout << lap << endl;



	/*lap.convertTo(lap,CV_64FC1,-1.0/255.0,1.0/255.0); //范围-1.0 / 255.0 ~ 1.0 / 255.0之间
	imshow("lap:", lap);
	cout<<1500-lap<<endl;
	waitKey(0);*/

	/*
	test
	*/
	//lap.convertTo(lap,CV_64FC1,1.0/255,-1.0/255);

	//Mat_Change_To_Matrix(lap);
	//cout<<lap<<endl;

	//Mat_<float> b;
	//lap.convertTo(b, CV_32F);

	//cout << b << endl;

	//cout<<1500 - lap<<endl;

	//imshow("1500-lap",1500-lap);
	//imshow("1500+lap",1500+lap);
	//waitKey(0);

	lap.convertTo(lap, CV_64FC1, 1.0 / 255, -1.0 / 255);

	/*cout<<lap<<endl;
	waitKey(0);*/
	int i, j;
	double *Mi;
	Mi = (double *)malloc(1000 * sizeof(double *));
	for (i = 0; i<lap.rows; i++)
	{
		Mi = lap.ptr<double>(i);
		for (j = 0; j<lap.cols; j++)
		{
			double value = Mi[j];
			cout << value << endl;
		}
	}
	//imgcut3(1500-lap,1500+lap,wgt*hc,wgt*vc);
}


