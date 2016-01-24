#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const double esp = 0.000001;
const double INF = 0x3f3f3f3f + 0.1;

double *Create_1_Matrix(int cols) //建立一个矩阵,double型,一维
{
	double *one_Matrix;
	int i;
	one_Matrix = (double *)malloc(cols*sizeof(double *));
	return one_Matrix;
}

/*
parameter为每一维度的个数
*/
double **Create_2_Matrix(const int *parameter) //建立一个矩阵,double型,二维
{
	double **double_Matrix;
	int i;
	double_Matrix = (double **)malloc((parameter[0] + 1) * sizeof(double *)); //+1的原因在于有边界,好判断元素个数
	for (i = 0; i < parameter[0] + 1; i++)
	{
		double_Matrix[i] = (double *)malloc((parameter[1] + 1) * sizeof(double)); //原因同上
	}
	return double_Matrix;
}

double ***Create_3_Matrix(const int *parameter) //建立一个矩阵,double型,三维
{
	double ***three_Matrix;
	int i, j;
	three_Matrix = (double ***)malloc((parameter[0] + 1) * sizeof(double**)); //+1的原因在于有边界,好判断元素个数
	for (i = 0; i < parameter[0] + 1; i++)
	{
		three_Matrix[i] = (double **)malloc((parameter[1] + 1)* sizeof(double*));  //+1的原因在于有边界,好判断元素个数
	}
	for (i = 0; i < parameter[0] + 1; i++)
	{
		for (j = 0; j < parameter[1] + 1; j++)
		{
			three_Matrix[i][j] = (double *)malloc((parameter[2] + 1) * sizeof(double));  //+1的原因在于有边界,好判断元素个数
		}
	}
	return three_Matrix;
}



/*int** mxCreateCellMatrix() 
{
	
}*/

/*void CreateNumericArray(int ndim,int *dims)
{
	
}*/
void DestroyArray_1(double *One_Mat) //销毁一维矩阵
{
	free((void *)One_Mat);
}

void DestroyArray_2(double **Two_Mat, const int *parameter) //销毁二维矩阵
{
	int i;
	for (i = 0; i < parameter[0] + 1; i++)
		free((void *)Two_Mat[i]);
	free((void *)Two_Mat);
}

void DestroyArray_3(double ***Three_Mat, const int *parameter) //销毁三维矩阵
{
	int i, j;
	for (i = 0; i < parameter[0] + 1; i++)
	{
		for (j = 0; j < parameter[1] + 1; j++)
		{
			free((void *)Three_Mat[i][j]);
		}
	}
	for (i = 0; i < parameter[0] + 1; i++)
		free((void *)Three_Mat[i]);
	free((void *)Three_Mat);
}

int GetNumberOfDimensions(double **Dimensions) //返回2维度
{
	return 2;
}

int GetNumberOfDimensions(double ***Dimensions) //返回3维度
{
	return 3;
}

/*
@parameter
total_element:引用,供GetNumberOfElements调用
*/
int *Get2Dimensions(double **Dimensions,int &total_element) //返回各维的元素个数,二维,增加哨兵,就是边界判断,边界为INF
{
	int i, j;
	int *result;
	result = (int *)malloc(5 * sizeof(int *));
	int cnt, cnt1;
	cnt = 0;
	cnt1 = 0;
	for (j = 0; j < 10000; j++) //确定列
	{
		if (fabs(Dimensions[0][j] - INF) <= esp)
		{
			break;
		}
		cnt++;
	}
	for (i = 0; i < 10000; i++) //确定行
	{
		if (fabs(Dimensions[i][0] - INF) <= esp)
		{
			break;
		}
		cnt1++;
	}
	result[0] = cnt1;
	result[1] = cnt;
	total_element = cnt * cnt1;
	//cout << cnt << " " << cnt1 << endl;

	return result;
}

/*
@parameter
total_element:引用,供GetNumberOfElements调用
*/
int *Get3Dimensions(double ***Dimensions, int &total_element) //返回各维度的元素个数,三维
{
	int i, j, k;
	int *result;
	int cnt, cnt1, cnt2;
	cnt = 0, cnt1 = 0, cnt2 = 0;
	result = (int *)malloc(5 * sizeof(int *));
	for (i = 0; i < 10000; i++) //第一维
	{
		if (abs(Dimensions[i][0][0] - INF) <= esp)
		{
			break;
		}
		cnt++;
	}
	for (j = 0; j < 10000; j++)
	{
		if (abs(Dimensions[0][j][0] - INF) <= esp) //第二维
		{
			break;
		}
		cnt1++;
	}
	for (k = 0; k < 10000; k++)
	{
		if (abs(Dimensions[0][0][k] - INF) <= esp) //第三维
		{
			break;
		}
		cnt2++;
	}
	result[0] = cnt;
	result[1] = cnt1;
	result[2] = cnt2;
	total_element = cnt * cnt1 * cnt2;
	return result;
}


int Get_2_NumberOfElements(double **Dimensions) //二维,获取元素个数
{
	int total_number;
	Get2Dimensions(Dimensions, total_number);
	return total_number;
}

int Get_3_NumberOfElements(double ***Dimensions) //三维,获取元素个数
{
	int total_number;
	Get3Dimensions(Dimensions, total_number);
	return total_number;
}

double* Mat_change_to_1_Matrix(Mat image) //Mat转换成普通的一维矩阵并返回
{
	int i,j;
	double *Matrix;
	double *Mi;
	Matrix = Create_1_Matrix((image.rows + 10) * (image.cols + 10) * 30 );
	Mi = (double *)malloc((image.rows *image.cols * 30) * sizeof(double *));
	for(i=0;i<image.rows;i++)  //行列遍历Mat,逐个像素点赋值给Matrix1这个普通矩阵
	{
		Mi = image.ptr<double>(i);
		for(j=0;j<image.cols;j++)
		{
			 double value = Mi[j];
			 Matrix[i*image.cols + j] = Mi[j];
		}
	}
	return Matrix;
}

double** Mat_change_to_2_Matrix(Mat image)  //Mat转换成普通的二维矩阵并返回
{
	int i,j;
	double **Matrix1;
	double *Mi;
	int *aa; //二维行乘以列
	aa = (int *)malloc(5*sizeof(int *));
	aa[0] = image.rows + 10;
	aa[1] = image.cols + 10;
	Mi = (double *)malloc(1000*sizeof(double *));
	Matrix1 = Create_2_Matrix(aa);
	for(i=0;i<image.rows;i++)  //行列遍历Mat,逐个像素点赋值给Matrix1这个普通矩阵
	{
		Mi = image.ptr<double>(i);
		for(j=0;j<image.cols;j++)
		{
			 double value = Mi[j];
			 Matrix1[i][j] = Mi[j];
			 cout<<Matrix1[i][j]<<endl;
		}
	}
	return Matrix1;
}


/*void Mat_Change_To_Matrix(Mat image)
{
	int i,j;
	int div = 64;
    int nr= image.rows; // number of rows  
    int nc= image.cols * image.channels(); // total number of elements per line  
    for (int j=0; j<nr; j++) {  
	uchar* data= image.ptr<uchar>(j);  
          for (int i=0; i<nc; i++) {  
				  *data++= *data/div*div + div/2;  
				 double v = *data;
				 cout<<v<<endl;
					
            } // end of row                   
      }  
}*/

//输入的时候再判断isDouble and isComplex
/*
int main()
{
int res[3];
int i,j;
double **p;
int *res2;

res2 = (int *)malloc(5*sizeof(int *));

res[0] = 3;
res[1] = 4;

p = Create_2_Matrix(res);
double res1 = 0;

for(i=0;i<res[0]+1;i++)
{
for(j=0;j<res[1]+1;j++)
{
if(i == res[0] || j == res[1])
{
p[i][j] = INF;
}
else
{
p[i][j] = 1.1;
cout<<p[i][j]<<endl;
}
}
}
res2 = Get2Dimensions(p);
cout<<res2[0]<<" "<<res2[1]<<endl;
//	cout<<len<<endl;
return 0;
}


int main()
{
int res[4];
int i,j,k;
double ***p;
int *res2;

res2 = (int *)malloc(5*sizeof(int *));

res[0] = 3;
res[1] = 4;
res[2] = 100;

p = Create_3_Matrix(res);
double res1 = 0;

for(i=0;i<res[0]+1;i++)
{
for(j=0;j<res[1]+1;j++)
{
for(k=0;k<res[2]+1;k++)
{
if(i == res[0] || j == res[1] || k == res[2])
{
p[i][j][k] = INF;
}
else
{
p[i][j][k] = 1.1;
cout<<p[i][j][k]<<endl;
}
}
printf("\n");
}
printf("\n");
}
res2 = Get3Dimensions(p);
cout<<res2[0]<<" "<<res2[1]<<" "<<res2[2]<<endl;
//	cout<<len<<endl;
return 0;
}

*/