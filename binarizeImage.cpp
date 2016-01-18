#include"macros.h"
#include"mx_function.h"
#include"imgcut3.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

IplImage *g_pSrcImage, *g_pCannyImg; //ԭʼͼ,Ŀ��ͼ
const char *pstrWindowsCannyTitle = "��Ե���ͼ";

Mat Gauss_sommth(Mat image, double sigma, double radius, string method); //����


void on_trackbar(int threshold)
{
	//canny��Ե���
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowsCannyTitle, g_pCannyImg);
}

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char* str) //�涨��������û��ֵ
{
	int nargin = 1; //image��һ������
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
	//Ĭ��ֵ
	if (nargin < 2 || cnt1 == 0)
	wgt = 160;
	if (nargin < 3 || cnt2 == 0)
	thi = 0.4;
	if (nargin < 4 || cnt3 == 0)
	tlo = 0.1;
	if (nargin < 5 || cnt4 == 0)
	sigE = 0.6;
	

	/*
	//�Ҷȴ���
	//cout << "wgt:" << wgt << " " << "thi:" << thi << " " << "tlo:" << tlo << " " << "sigE:" << sigE << endl;
	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//ת��ͼƬ��ɫ���Ҷȴ���

	//imwrite("C:/Users/Administrator/Documents/Visual Studio 2013/Projects/Machine_Learning/Machine_Learning", gray_image);
	imshow("Gray Image", gray_image);//��ʾ�Ҷ�ͼ��
	waitKey(0);//�ȴ�ֱ���û�����һ������֮���˳���
	*/
	Mat lap; //�ϲ�dx��dy���ͼ��
	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//ת��ͼƬ��ɫ���Ҷȴ���
	threshold(gray_image,gray_image,140,255,THRESH_BINARY);
	GaussianBlur( gray_image, gray_image, Size(3,3), 0, 0, BORDER_DEFAULT );

	imshow("gray_image",gray_image);
	//canny��Ե���
	Mat canny_result;
	//Canny(gray_image, canny_result, 0, 0);

	/*������˹*/
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int kernel_size = 3; 
	Laplacian( gray_image, lap, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );


	//cvNamedWindow("cannyResult");
	//convertScaleAbs( canny_result, canny_result );
	Canny(gray_image,canny_result,120,130);
	/*imshow("cannyResult", canny_result);
	waitKey(0); */
	//imshow("ԭʼͼ:", image);
	//const CvArr *after_deal = (CvArr *)&canny_result; //��canny���ת��ΪCvArr����
	int total_rows = gray_image.rows; //��ȡͼ�����
	int total_cols = gray_image.cols; //��ȡͼ�����

	//opencv����ͨ��[0] = b,[1] = g,[2] = r

	/*
	�������ĵ��㷨:�������,����΢�����Ч��ͼ,��������˹��̫һ��
	*/
	Mat A_matrix = gray_image(Range(1, total_rows - 1), Range(2, total_cols));  //����������˹

	Mat B_matrix = gray_image(Range(1, total_rows - 1), Range(1, total_cols - 1));

	Mat C_matrix = gray_image(Range(2, total_rows), Range(1, total_cols - 1));

	Mat D_matrix = gray_image(Range(1, total_rows - 1), Range(1, total_cols - 1));

	Mat dx = A_matrix - B_matrix;  //dx

	//cout << dx << endl;

	//imshow("dx_Result", dx);
	//waitKey(0);

	Mat dy = C_matrix - D_matrix;  //dy

	//cout << total_rows << " " << total_cols << endl;
	//imshow("dy_Result", dy);
	//waitKey(0);

	

	addWeighted(dx, 0.5, dy, 0.5, 0, lap);
	//imshow("Ч��ͼ�ϲ�dx,dy:",dst);
	cout << "lap��:" << lap.rows << " " << "��:" << lap.cols << endl;


	//waitKey(0);



	/*
	% Bias high-confidence background pixels
	*/

	int sr = 20; //no need found to vary this parameter
	//Gauss_sommth(dst, sr, 3 * sr, "mirror");

	/*
	��������˹ƽ��
	*/


	/*
	% Assemble matrices of edge connections -- horizontal and vertical
	*/
	Mat hc;
	Mat vc;

	Mat test1, test2;
	Mat test3, test4;
	/*
	canny_result���
	*/
	hc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dy > 0))  //638 * 1022
		| (canny_result(Range(2, total_rows), Range(1, total_cols - 1)) & (dy <= 0)));

	cout << "hc��:" << hc.rows << " " << "��:" << hc.cols << endl;
	//waitKey(0);
	/*imshow("hc:", hc);
	waitKey(0);*/

	vc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dx > 0))  //638 * 1022
		| (canny_result(Range(1, total_rows - 1), Range(2, total_cols)) & (dx <= 0)));

	//cout << "��:" << vc.rows << " " << "��:" << vc.cols << endl;
	/*imshow("vc:", vc);
	waitKey(0);
	*/

	hc = hc(Range(1, total_rows - 2), Range(1, total_cols - 2));  //638 * 1022


	cout << "vc��:" << vc.rows << " " << "��:" << vc.cols << endl;
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
	


	/*lap.convertTo(lap,CV_64FC1,-1.0/255.0,1.0/255.0); //��Χ-1.0 / 255.0 ~ 1.0 / 255.0֮��
	imshow("lap:", lap);
	cout<<1500-lap<<endl;
	waitKey(0);*/
	
	/*
	test
	*/
	//lap.convertTo(lap,CV_64FC1,1.0/255,-1.0/255);

	//Mat_Change_To_Matrix(lap);
	//cout<<lap<<endl;
	//cout<<1500 - lap<<endl;

	//imshow("1500-lap",1500-lap);
	//imshow("1500+lap",1500+lap);
	//waitKey(0);
	//imshow("lap:",lap);
	//lap.convertTo(lap,CV_64FC1,-1.0/255,1.0/255);
	lap.convertTo(lap,CV_64FC1,-1.0/255,1.0/255);
	hc.convertTo(hc,CV_64FC1,1.0/255);
	//cout<<hc<<endl;
	vc.convertTo(vc,CV_64FC1,1.0/255);
	//cout<<vc<<endl;
	int test_rows = hc.rows;
	int test_cols = hc.cols;
	int test_rows1 = vc.rows;
	int test_cols1 = vc.cols;
	int i,j;
	
	imgcut3(1500-lap,1500+lap,wgt*hc,wgt*vc);
}


