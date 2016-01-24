#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const double esp = 0.000001;
const double INF = 0x3f3f3f3f + 0.1;

double *Create_1_Matrix(int cols) //����һ������,double��,һά
{
	double *one_Matrix;
	int i;
	one_Matrix = (double *)malloc(cols*sizeof(double *));
	return one_Matrix;
}

/*
parameterΪÿһά�ȵĸ���
*/
double **Create_2_Matrix(const int *parameter) //����һ������,double��,��ά
{
	double **double_Matrix;
	int i;
	double_Matrix = (double **)malloc((parameter[0] + 1) * sizeof(double *)); //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
	for (i = 0; i < parameter[0] + 1; i++)
	{
		double_Matrix[i] = (double *)malloc((parameter[1] + 1) * sizeof(double)); //ԭ��ͬ��
	}
	return double_Matrix;
}

double ***Create_3_Matrix(const int *parameter) //����һ������,double��,��ά
{
	double ***three_Matrix;
	int i, j;
	three_Matrix = (double ***)malloc((parameter[0] + 1) * sizeof(double**)); //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
	for (i = 0; i < parameter[0] + 1; i++)
	{
		three_Matrix[i] = (double **)malloc((parameter[1] + 1)* sizeof(double*));  //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
	}
	for (i = 0; i < parameter[0] + 1; i++)
	{
		for (j = 0; j < parameter[1] + 1; j++)
		{
			three_Matrix[i][j] = (double *)malloc((parameter[2] + 1) * sizeof(double));  //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
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
void DestroyArray_1(double *One_Mat) //����һά����
{
	free((void *)One_Mat);
}

void DestroyArray_2(double **Two_Mat, const int *parameter) //���ٶ�ά����
{
	int i;
	for (i = 0; i < parameter[0] + 1; i++)
		free((void *)Two_Mat[i]);
	free((void *)Two_Mat);
}

void DestroyArray_3(double ***Three_Mat, const int *parameter) //������ά����
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

int GetNumberOfDimensions(double **Dimensions) //����2ά��
{
	return 2;
}

int GetNumberOfDimensions(double ***Dimensions) //����3ά��
{
	return 3;
}

/*
@parameter
total_element:����,��GetNumberOfElements����
*/
int *Get2Dimensions(double **Dimensions,int &total_element) //���ظ�ά��Ԫ�ظ���,��ά,�����ڱ�,���Ǳ߽��ж�,�߽�ΪINF
{
	int i, j;
	int *result;
	result = (int *)malloc(5 * sizeof(int *));
	int cnt, cnt1;
	cnt = 0;
	cnt1 = 0;
	for (j = 0; j < 10000; j++) //ȷ����
	{
		if (fabs(Dimensions[0][j] - INF) <= esp)
		{
			break;
		}
		cnt++;
	}
	for (i = 0; i < 10000; i++) //ȷ����
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
total_element:����,��GetNumberOfElements����
*/
int *Get3Dimensions(double ***Dimensions, int &total_element) //���ظ�ά�ȵ�Ԫ�ظ���,��ά
{
	int i, j, k;
	int *result;
	int cnt, cnt1, cnt2;
	cnt = 0, cnt1 = 0, cnt2 = 0;
	result = (int *)malloc(5 * sizeof(int *));
	for (i = 0; i < 10000; i++) //��һά
	{
		if (abs(Dimensions[i][0][0] - INF) <= esp)
		{
			break;
		}
		cnt++;
	}
	for (j = 0; j < 10000; j++)
	{
		if (abs(Dimensions[0][j][0] - INF) <= esp) //�ڶ�ά
		{
			break;
		}
		cnt1++;
	}
	for (k = 0; k < 10000; k++)
	{
		if (abs(Dimensions[0][0][k] - INF) <= esp) //����ά
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


int Get_2_NumberOfElements(double **Dimensions) //��ά,��ȡԪ�ظ���
{
	int total_number;
	Get2Dimensions(Dimensions, total_number);
	return total_number;
}

int Get_3_NumberOfElements(double ***Dimensions) //��ά,��ȡԪ�ظ���
{
	int total_number;
	Get3Dimensions(Dimensions, total_number);
	return total_number;
}

double* Mat_change_to_1_Matrix(Mat image) //Matת������ͨ��һά���󲢷���
{
	int i,j;
	double *Matrix;
	double *Mi;
	Matrix = Create_1_Matrix((image.rows + 10) * (image.cols + 10) * 30 );
	Mi = (double *)malloc((image.rows *image.cols * 30) * sizeof(double *));
	for(i=0;i<image.rows;i++)  //���б���Mat,������ص㸳ֵ��Matrix1�����ͨ����
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

double** Mat_change_to_2_Matrix(Mat image)  //Matת������ͨ�Ķ�ά���󲢷���
{
	int i,j;
	double **Matrix1;
	double *Mi;
	int *aa; //��ά�г�����
	aa = (int *)malloc(5*sizeof(int *));
	aa[0] = image.rows + 10;
	aa[1] = image.cols + 10;
	Mi = (double *)malloc(1000*sizeof(double *));
	Matrix1 = Create_2_Matrix(aa);
	for(i=0;i<image.rows;i++)  //���б���Mat,������ص㸳ֵ��Matrix1�����ͨ����
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

//�����ʱ�����ж�isDouble and isComplex
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