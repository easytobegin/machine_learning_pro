#include"macros.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
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
	Canny(gray_image,canny_result,60,80);
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
	Mat A_matrix = canny_result(Range(1, total_rows-1), Range(2, total_cols));

	Mat B_matrix = canny_result(Range(1, total_rows-1), Range(1, total_cols-1));

	Mat C_matrix = canny_result(Range(2, total_rows), Range(1, total_cols-1));

	Mat D_matrix = canny_result(Range(1, total_rows-1), Range(1, total_cols-1));

	Mat dx = A_matrix - B_matrix;  //dx

	//cout << dx << endl;

	//imshow("dx_Result", dx);
	//waitKey(0);

	Mat dy = C_matrix - D_matrix;  //dy


	// cout << total_rows << " " << total_cols << endl;
	//imshow("dy_Result", dy);
	//waitKey(0);
	
	Mat dst; //�ϲ�dx��dy���ͼ��

	addWeighted(dx,0.5,dy,0.5,0,dst);
	//imshow("Ч��ͼ�ϲ�dx,dy:",dst);

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

	hc = ~((canny_result(Range(1, total_rows-1), Range(1, total_cols-1)) & (dy > 0))  //1 - total_row - 1
		| (canny_result(Range(2, total_rows), Range(1, total_cols-1)) & (dy <= 0)));

	/*imshow("hc:", hc);
	waitKey(0);
	*/

	vc = ~((canny_result(Range(1, total_rows-1), Range(1, total_cols-1)) & (dx > 0))
		| (canny_result(Range(1, total_rows-1), Range(2, total_cols)) & (dx <= 0)));
	
	/*imshow("vc:", vc);
	waitKey(0);
	*/

	hc = hc(Range(1, total_rows-2), Range(1,total_cols-2));  //ȡ-1��bug

	//hc_result = hc(Range(1, total_rows-1), Range(1, total_cols-1));
	
	/*
	imshow("hc:", hc);
	waitKey(0); 
	/*

	vc = vc(Range(1, total_rows-2), Range(1,total_cols-2)); //ȡ-1��bug

	imshow("vc", vc);

	waitKey(0);

	/*Mat dst1;
	GaussianBlur(dst,dst1 , Size(3, 3), 0, 0, BORDER_DEFAULT);
	imshow("����˹ƽ�������:", dst1);
	Mat res = dst - dst1;
	imshow("����:",res);
	waitKey(0);*/




	//��x������ݶ�
	/*Scharr(image, dxx, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dxx, abs_dx);
	imshow("dx_Result", abs_dx);
	*/

	//imshow("dx_Result", dy);
	
	//resultΪcanny���ͼ��

	//srcΪres

	//������˹,Laplace�任------��canny���ͼ�����(1)
	/*Mat src_gray,dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char *window_name = "Laplace Demo";

	int c;
	
	GaussianBlur(result,result,Size(3,3),0,0,BORDER_DEFAULT); //��˹ƽ������

	//cvtColor(result, src_gray, CV_RGB2GRAY); //ת��Ϊ�Ҷ�

	Mat abs_dst;
	Laplacian(result, dst, ddepth, kernel_size, scale,delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
	imshow(window_name,abs_dst);

	waitKey(0);*/

	//��������
	
	/*
	//������˹,Laplace�任------��ԭͼ��image����(2)
	Mat src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char *window_name = "Laplace Demo";

	int c;

	//��˹ƽ������
	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT); //��˹ƽ������

	//ʹ��cvtColorת��Ϊ�Ҷ�ͼ
	//cvtColor(result, src_gray, CV_RGB2GRAY); //ת��Ϊ�Ҷ�

	Mat abs_dst;
	
	//�ԻҶ�ͼʹ��Laplacian����
	Laplacian(image, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	
	//�����ͼ������ת��ΪCV_8U
	convertScaleAbs(dst, abs_dst);
	cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
	imshow(window_name, abs_dst);

	waitKey(0);
	*/
	
}


