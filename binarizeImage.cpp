#include"macros.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

IplImage *g_pSrcImage, *g_pCannyImg; //ԭʼͼ,Ŀ��ͼ
const char *pstrWindowsCannyTitle = "��Ե���ͼ";

Mat Gauss_sommth(Mat image, double sigma, double radius, string method); //����
//cvCreateTrackbar�Ļص�����
void on_trackbar(int threshold)
{
	//canny��Ե���
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowsCannyTitle, g_pCannyImg);
}

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char* str) //�涨��������û��ֵ
{
	/*int nargin = 1; //image��һ������
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
	*/

	//cout << "��:" << image.rows << " " << "��:" << image.cols << endl;  //ԭͼ640 * 1024
	/*
	//�Ҷȴ���
	//cout << "wgt:" << wgt << " " << "thi:" << thi << " " << "tlo:" << tlo << " " << "sigE:" << sigE << endl;
	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//ת��ͼƬ��ɫ���Ҷȴ���

	//imwrite("C:/Users/Administrator/Documents/Visual Studio 2013/Projects/Machine_Learning/Machine_Learning", gray_image);
	imshow("Gray Image", gray_image);//��ʾ�Ҷ�ͼ��
	waitKey(0);//�ȴ�ֱ���û�����һ������֮���˳���
	*/

	Mat gray_image;
	cvtColor(image, gray_image, CV_RGB2GRAY);//ת��ͼƬ��ɫ���Ҷȴ���

	//canny��Ե���
	Mat canny_result;
	Canny(gray_image, canny_result, 60, 80);
	//cvNamedWindow("cannyResult");
	//imshow("cannyResult", canny_result);
	//waitKey(0);

	//imshow("ԭʼͼ:", image);
	//const CvArr *after_deal = (CvArr *)&canny_result; //��canny���ת��ΪCvArr����
	int total_rows = canny_result.rows; //��ȡͼ�����
	int total_cols = canny_result.cols; //��ȡͼ�����

	//opencv����ͨ��[0] = b,[1] = g,[2] = r

	/*
	�������ĵ��㷨:�������,����΢�����Ч��ͼ,��������˹��̫һ��
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

	Mat lap; //�ϲ�dx��dy���ͼ��

	addWeighted(dx, 0.5, dy, 0.5, 0, lap);
	//imshow("Ч��ͼ�ϲ�dx,dy:",dst);

	cout << "��:" << lap.rows << " " << "��:" << lap.cols << endl;


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

	hc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dy > 0))  //638 * 1022
		| (canny_result(Range(2, total_rows), Range(1, total_cols - 1)) & (dy <= 0)));

	//cout << "��:" << hc.rows << " " << "��:" << hc.cols << endl;
	/*imshow("hc:", hc);
	waitKey(0);
	*/

	vc = ~((canny_result(Range(1, total_rows - 1), Range(1, total_cols - 1)) & (dx > 0))  //638 * 1022
		| (canny_result(Range(1, total_rows - 1), Range(2, total_cols)) & (dx <= 0)));

	//cout << "��:" << vc.rows << " " << "��:" << vc.cols << endl;
	/*imshow("vc:", vc);
	waitKey(0);
	*/

	hc = hc(Range(1, total_rows - 2), Range(1, total_cols - 2));  //638 * 1022


	//cout << "��:" << vc.rows << " " << "��:" << vc.cols << endl;
	//hc_result = hc(Range(1, total_rows-1), Range(1, total_cols-1));

	/*
	imshow("hc:", hc);
	waitKey(0);
	*/

	vc = vc(Range(1, total_rows - 2), Range(1, total_cols - 2)); //638 * 1022

	/*imshow("vc", vc);
	waitKey(0);*/
	//cout << 1500 - lap << endl;
	//cout << lap << endl;

	//Mat_<float> b;
	//lap.convertTo(b, CV_32F);

	//cout << b << endl;

}


