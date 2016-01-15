#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
using namespace std;

const double esp = 0.000001;
const double INF = 0x3f3f3f3f + 0.1;
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
	double ***three_Maxrix;
	int i, j;
	three_Maxrix = (double ***)malloc((parameter[0] + 1) * sizeof(double**)); //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
	for (i = 0; i < parameter[0] + 1; i++)
	{
		three_Maxrix[i] = (double **)malloc((parameter[1] + 1)* sizeof(double*));  //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
	}
	for (i = 0; i < parameter[0] + 1; i++)
	{
		for (j = 0; j < parameter[1] + 1; j++)
		{
			three_Maxrix[i][j] = (double *)malloc((parameter[2] + 1) * sizeof(double));  //+1��ԭ�������б߽�,���ж�Ԫ�ظ���
		}
	}
	return three_Maxrix;
}

int** mxCreateCellMatrix() //������ά��λ��
{
	
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