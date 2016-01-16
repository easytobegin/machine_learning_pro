#include<iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double **Create_2_Matrix(const int *parameter); //����һ������,double��,��ά
double ***Create_3_Matrix(const int *parameter); //����һ������,double��,��ά
void DestroyArray_2(double **Two_Mat, const int *parameter); //���ٶ�ά����
void DestroyArray_3(double ***Three_Mat, const int *parameter); //������ά����
int GetNumberOfDimensions(double **Dimensions); //����2ά��
int GetNumberOfDimensions(double ***Dimensions); //����3ά��
int *Get2Dimensions(double **Dimensions, int &total_element); //���ظ�ά��Ԫ�ظ���,��ά,�����ڱ�,���Ǳ߽��ж�,�߽�ΪINF
int *Get3Dimensions(double ***Dimensions, int &total_element); //���ظ�ά�ȵ�Ԫ�ظ���,��ά
int Get_2_NumberOfElements(double **Dimensions); //��ά,��ȡԪ�ظ���
int Get_3_NumberOfElements(double ***Dimensions); //��ά,��ȡԪ�ظ���


/*
matlab���Խ��:
hc 98 * 399
lap 99 * 399
vc 99 * 398
wgt.*hc = 98 * 399
wgt.*vc = 99 * 398
*/
void imgcut3(Mat para1, Mat para2, Mat para3, Mat para4)  //�ĸ��������Ǿ������ͣ����Ƕ�ά����
{
	int i, j;
	int ndim = 2; //ά��Ϊ2
	long n, m, nmin;
	double *src, *snk, *nbr;
	double flow = 0;
	double *out;

	//����һ��ͼ�����ת��ͨ����ĺ���
	//mxGetDimensions������ô�鷳,ֱ�ӷ�������������
	int *dim1;
	int *dim2;
	dim1 = (int *)malloc(10 * sizeof(int *));
	dim2 = (int *)malloc(10 * sizeof(int *));
	dim1[0] = para1.rows; //����1����
	dim1[1] = para1.cols; //����1����
	dim2[0] = para2.rows; //����2����
	dim2[1] = para2.cols; //����2����
	/*
	cout<<dim1[0]<<"*"<<dim1[1]<<endl;
	cout<<dim2[0]<<"*"<<dim2[1]<<endl;
	��ӡ�Ľ��ֵ��ͬ
	*/
	for (i = 0; i<ndim; i++)
	{
		if (i == 0)  //mxGetDimensions(prhs[2+i])
		{
			dim2[0] = para3.rows; //����3����
			dim2[1] = para3.cols; //����3����
		}
		else //mxGetDimensions(prhs[2+i])
		{
			dim2[0] = para4.rows; //����4����
			dim2[1] = para4.cols; //����4����
		}
	}

}