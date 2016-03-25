#include"macros.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

double* Mat_change_to_1_Matrix(Mat image); //Matת������ͨ��һά���󲢷���
double *Create_1_Matrix(int cols);//����һ������,double��,һά
double **Create_2_Matrix(const int *parameter); //����һ������,double��,��ά
double ***Create_3_Matrix(const int *parameter); //����һ������,double��,��ά
void DestroyArray_1(double *One_Mat); //����һά����
void DestroyArray_1(int *One_Mat);
void DestroyArray_2(double **Two_Mat, const int *parameter); //���ٶ�ά����
void DestroyArray_3(double ***Three_Mat, const int *parameter); //������ά����
int GetNumberOfDimensions(double **Dimensions); //����2ά��
int GetNumberOfDimensions(double ***Dimensions); //����3ά��
int *Get2Dimensions(double **Dimensions,int &total_element); //���ظ�ά��Ԫ�ظ���,��ά,�����ڱ�,���Ǳ߽��ж�,�߽�ΪINF
int *Get3Dimensions(double ***Dimensions, int &total_element); //���ظ�ά�ȵ�Ԫ�ظ���,��ά
int Get_2_NumberOfElements(double **Dimensions); //��ά,��ȡԪ�ظ���
int Get_3_NumberOfElements(double ***Dimensions); //��ά,��ȡԪ�ظ���