#include"macros.h"
#include <opencv2/opencv.hpp>
#include<cmath>
using namespace cv;
using namespace std;

const double esp = 10e-9;
const double inf = 0x3f3f3f3f+0.1;

void binarizeImageAlg1(Mat image, double thi, double tlo, double sigE) //�涨��������û��ֵ
{
	int nargin = 1; //image��һ������
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;

	/*
	X=linspace(5,100,20) % ������5��100��Χ�ڵ�20�����ݣ��������ݿ����ͬ
	5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100
	*/
	double *clist;

	clist = (double *)malloc(40 * sizeof(double *));
	int i,num;
	double endx, startx;
	endx = log(5120);
	startx = log(20);
	num = 33;
	double interval = (endx - startx) / (double)(num - 1); //ÿ��Ԫ�صļ��
	for (i = 0; i < num; i++)
	{
		clist[i] = startx + interval * i;
	}
	if (thi >= 0)
	{
		cnt1++;
		nargin++;
	}
	if (tlo >= 0)
	{
		cnt2++;
		nargin++;
	}
	if (sigE >= 0)
	{
		cnt3++;
		nargin++;
	}
	//Ĭ��ֵ
	if (nargin < 2 || cnt1 == 0)
		thi = 0.3;
	if (nargin < 3 || cnt2 == 0)
		tlo = 0.1;
	if (nargin < 4 || cnt3 == 0)
		sigE = 0.4;
	if (nargin < 5 || cnt4 == 0)
	{
		for (i = 0; i < num; i++)
		{
			clist[i] = exp(clist[i]);
		}
	}
	clist[num] = inf; //�߽�

	double *bsd;
	bsd = (double *)malloc(34 * sizeof(double *));
	for (i = 0; i < 32; i++) //numel(clist) = 33,�����
	{
		bsd[i] = 0;
	}
}