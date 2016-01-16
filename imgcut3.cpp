#include<iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double **Create_2_Matrix(const int *parameter); //建立一个矩阵,double型,二维
double ***Create_3_Matrix(const int *parameter); //建立一个矩阵,double型,三维
void DestroyArray_2(double **Two_Mat, const int *parameter); //销毁二维矩阵
void DestroyArray_3(double ***Three_Mat, const int *parameter); //销毁三维矩阵
int GetNumberOfDimensions(double **Dimensions); //返回2维度
int GetNumberOfDimensions(double ***Dimensions); //返回3维度
int *Get2Dimensions(double **Dimensions, int &total_element); //返回各维的元素个数,二维,增加哨兵,就是边界判断,边界为INF
int *Get3Dimensions(double ***Dimensions, int &total_element); //返回各维度的元素个数,三维
int Get_2_NumberOfElements(double **Dimensions); //二维,获取元素个数
int Get_3_NumberOfElements(double ***Dimensions); //三维,获取元素个数


/*
matlab调试结果:
hc 98 * 399
lap 99 * 399
vc 99 * 398
wgt.*hc = 98 * 399
wgt.*vc = 99 * 398
*/
void imgcut3(Mat para1, Mat para2, Mat para3, Mat para4)  //四个参数都是矩阵类型，都是二维矩阵
{
	int i, j;
	int ndim = 2; //维度为2
	long n, m, nmin;
	double *src, *snk, *nbr;
	double flow = 0;
	double *out;

	//建立一个图像矩阵转普通矩阵的函数
	//mxGetDimensions不用那么麻烦,直接返回行数和列数
	int *dim1;
	int *dim2;
	dim1 = (int *)malloc(10 * sizeof(int *));
	dim2 = (int *)malloc(10 * sizeof(int *));
	dim1[0] = para1.rows; //参数1的行
	dim1[1] = para1.cols; //参数1的列
	dim2[0] = para2.rows; //参数2的行
	dim2[1] = para2.cols; //参数2的列
	/*
	cout<<dim1[0]<<"*"<<dim1[1]<<endl;
	cout<<dim2[0]<<"*"<<dim2[1]<<endl;
	打印的结果值相同
	*/
	for (i = 0; i<ndim; i++)
	{
		if (i == 0)  //mxGetDimensions(prhs[2+i])
		{
			dim2[0] = para3.rows; //参数3的行
			dim2[1] = para3.cols; //参数3的列
		}
		else //mxGetDimensions(prhs[2+i])
		{
			dim2[0] = para4.rows; //参数4的行
			dim2[1] = para4.cols; //参数4的列
		}
	}

}