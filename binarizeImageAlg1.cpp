#include"macros.h"
#include"imgcutmulti.h"
#include <opencv2/opencv.hpp>
#include<algorithm>
#include<cmath>
using namespace cv;
using namespace std;

const double esp = 10e-9;
const double inf = 0x3f3f3f3f+0.1;

void binarizeImageAlg1(Mat image, double thi, double tlo, double sigE,Mat hc1,Mat vc1,Mat lap1) //规定负数代表没有值
{
	int nargin = 1; //image算一个参数
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;

	/*
	X=linspace(5,100,20) % 产生从5到100范围内的20个数据，相邻数据跨度相同
	5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100
	*/
	double *clist;

	clist = (double *)malloc(40 * sizeof(double *));
	int i,num;
	double endx, startx;
	endx = log(5120);
	startx = log(20);
	num = 33;
	double interval = (endx - startx) / (double)(num - 1); //每个元素的间隔
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
	//默认值
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
	clist[num] = inf; //边界
	//double *bsd;
	/*bsd = (double *)malloc(34 * sizeof(double *));
	for (i = 0; i < 32; i++) //numel(clist) = 33,零矩阵
	{
		bsd[i] = 0;
	}*/
	sort(clist, clist + num + 1);
	/*imshow("1500-lap1",1500-lap1);
	imshow("1500+lap1", 1500 + lap1);
	imshow("hc1:",hc1);
	imshow("vc1:",vc1);
	waitKey(0);*/
	imgcutmulti(1500-lap1,1500+lap1,hc1,vc1,clist);   //imgcutmulti(1500-lap,1500+lap,double(hc),double(vc),sort(wgt));
}