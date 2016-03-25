#include"macros.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

double* Mat_change_to_1_Matrix(Mat image); //Mat转换成普通的一维矩阵并返回
double *Create_1_Matrix(int cols);//建立一个矩阵,double型,一维
double **Create_2_Matrix(const int *parameter); //建立一个矩阵,double型,二维
double ***Create_3_Matrix(const int *parameter); //建立一个矩阵,double型,三维
void DestroyArray_1(double *One_Mat); //销毁一维矩阵
void DestroyArray_1(int *One_Mat);
void DestroyArray_2(double **Two_Mat, const int *parameter); //销毁二维矩阵
void DestroyArray_3(double ***Three_Mat, const int *parameter); //销毁三维矩阵
int GetNumberOfDimensions(double **Dimensions); //返回2维度
int GetNumberOfDimensions(double ***Dimensions); //返回3维度
int *Get2Dimensions(double **Dimensions,int &total_element); //返回各维的元素个数,二维,增加哨兵,就是边界判断,边界为INF
int *Get3Dimensions(double ***Dimensions, int &total_element); //返回各维度的元素个数,三维
int Get_2_NumberOfElements(double **Dimensions); //二维,获取元素个数
int Get_3_NumberOfElements(double ***Dimensions); //三维,获取元素个数