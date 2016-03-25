#include"mx_function.h"
#include"graph.h"
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include"mx_function.h"
#include<cmath>

using namespace cv;
using namespace std;

const double esp = 10e-9;
const double inf = 0x3f3f3f3f + 0.1;

void imgcutmulti(Mat para1, Mat para2, Mat para3, Mat para4, double *mult)
{
	
	int i, j, imult;
	int ndim = 2;
	long n, m, min, nmult;
	double *src, *snk, *nbr;
	double flow = 0;
	double *cost;

	for (i = 0; i < 33; i++)
	{
		cout << mult[i] << endl;
	}

	//mxArray *cell 一 维例如矩阵[[3*4],[1*2],[4*100]]
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

	int row1 = para1.rows; int col1 = para1.cols;
	int row2 = para2.rows; int col2 = para2.cols;
	int row3 = para3.rows; int col3 = para3.cols;
	int row4 = para4.rows; int col4 = para4.cols;
	int result1 = (row1 + 10) * (col1 + 10);
	int result2 = (row2 + 10) * (col2 + 10);
	int result3 = (row3 + 10) * (col3 + 10);
	int result4 = (row4 + 10) * (col4 + 10);

	src = (double *)malloc(result1 * sizeof(double *));
	snk = (double *)malloc(result2 * sizeof(double *));

	src = Mat_change_to_1_Matrix(para1); //Mat转普通矩阵

	snk = Mat_change_to_1_Matrix(para2); //Mat转普通矩阵
	int cnt = 0;
	for (i = 0; i < 10000000; i++)
	{
		if (fabs(mult[i] - inf) < esp) //到了边界了,跳出循环
		{
			break;
		}
		else
		{
			cnt++;
		}
	}
	nmult = cnt;  //nmult = mxGetNumberOfElements(prhs[4]);

	typedef Graph<double, double, double> GraphType;
	GraphType *g = new GraphType(dim1[0] * dim1[1],
		(dim1[0] - 1)*dim1[1] + dim1[0] * (dim1[1] - 1));

	for (i = 0; i < dim1[0] * dim1[1]; i++) 
	{
		g->add_node();
	}

	for (i = 0; i < dim1[0] * dim1[1]; i++) 
	{
		g->add_tweights(i, src[i], snk[i]);
	}

	for (i = 0; i < dim1[0] * dim1[1]; i++) 
	{
		g->add_tweights(i, src[i], snk[i]);
	}

	nbr = (double *)malloc(result3 * sizeof(double *));
	nbr = Mat_change_to_1_Matrix(para3);

	for (i = 0; i < dim1[0] - 1; i++) 
	{
		for (j = 0; j < dim1[1]; j++) 
		{
			//mexPrintf("At (%d,%d).\n",i,j);
			if (nbr[i + j*(dim1[0] - 1)] == 0) 
			{   //  >0可能有问题,先不改
				//mexPrintf("  Adding edge.\n",i,j);
				g->add_edge(i + j*dim1[0], i + j*dim1[0] + 1,
					mult[0] * nbr[i + j*(dim1[0] - 1)],
					mult[0] * nbr[i + j*(dim1[0] - 1)]);
			}
		}
	}

	nbr = Mat_change_to_1_Matrix(para4);
	for (i = 0; i < dim1[0]; i++) 
	{
		for (j = 0; j < dim1[1] - 1; j++) 
		{
			if (nbr[i + j * dim1[0]] == 0) 
			{    
				// >0可能有问题先不改
				g->add_edge(i + j * dim1[0], i + (j + 1)*dim1[0],
					mult[0] * nbr[i + j*dim1[0]], mult[0] * nbr[i + j*dim1[0]]);
			}
		}
	}
	/*
	第一个输出参数是胞矩阵   plhs[0] = mxCreateCellMatrix(1,nmult);
	第二个输出参数是double型的矩阵   cost = mxGetPr(plhs[1]);
	nmult为传递进来clist的个数
	*/
	for (imult = 0; imult < nmult; imult++)
	{
		if (imult == 0)
		{
			flow = g->maxflow();
		}
		else
		{
			GraphType::arc_id a = g->get_first_arc();
			GraphType::arc_id a2 = g->get_next_arc(a);
			nbr = Mat_change_to_1_Matrix(para3);

			for (i = 0; i < dim1[0] - 1; i++) 
			{
				for (j = 0; j < dim1[1]; j++) 
				{
					if (nbr[i + j*(dim1[0] - 1)] == 0) //> 
					{
						// if edge was saturated, mark nodes for reconsideration
						if ((g->get_rcap(a) == 0) || (g->get_rcap(a2) == 0)) 
						{
							g->mark_node(i + j*dim1[0]);
							g->mark_node(i + j*dim1[0] + 1);
						}
						g->set_rcap(a, g->get_rcap(a) +
							(mult[imult] - mult[imult - 1])*nbr[i + j*(dim1[0] - 1)]);
						g->set_rcap(a2, g->get_rcap(a2) +
							(mult[imult] - mult[imult - 1])*nbr[i + j*(dim1[0] - 1)]);
						a = g->get_next_arc(a2);
						a2 = g->get_next_arc(a);

					}
				}
			}
			DestroyArray_1(nbr);
			nbr = Mat_change_to_1_Matrix(para4);
			for (i = 0; i < dim1[0]; i++) 
			{
				for (j = 0; j < dim1[1] - 1; j++) 
				{
					if (nbr[i + j*dim1[0]] == 0) 
					{
						// if edge was saturated, mark nodes for reconsideration
						if ((g->get_rcap(a) == 0) || (g->get_rcap(a2) == 0)) 
						{
							g->mark_node(i + j*dim1[0]);
							g->mark_node(i + (j + 1)*dim1[0]);
						}
						g->set_rcap(a, g->get_rcap(a) +
							(mult[imult] - mult[imult - 1])*nbr[i + j*dim1[0]]);
						g->set_rcap(a2, g->get_rcap(a2) +
							(mult[imult] - mult[imult - 1])*nbr[i + j*dim1[0]]);
						a = g->get_next_arc(a2);
						a2 = g->get_next_arc(a);
					}
				}
			}
			flow = g->maxflow(true);
		}
		long allo = dim1[0] * dim1[1] + 10000;

		vector<int> out(allo);

		for (i = 0; i < dim1[0]; i++)
		{
			for (j = 0; j < dim1[1]; j++)
			{
				out[i + j*dim1[0]] = g->what_segment(i + j * dim1[0]) == GraphType::SINK;
				//cout<<g->what_segment(i+j*dim1[0])<<" ";
				//printf("%d ",out[i+j*dim1[0]]);
			}
			//printf("\n");
		}

		int *out_test;
		out_test = (int *)malloc(allo * sizeof(int *));


		int cnt9 = 0, cnt10 = 0;
		for (i = 0; i<dim1[0]; i++)
		{
			for (j = 0; j<dim1[1]; j++)
			{
				//cout<<out[j+i*dim1[1]]<<endl;
				if (out[i + j*dim1[0]] == 0)
				{
					out_test[i + j *dim1[0]] = 0;
					cnt9++;
				}
				else
				{
					out_test[i + j *dim1[0]] = 255;
					cnt10++;
				}
				//cout<<out_test[i + j *dim1[0]]<<" ";
			}
			//printf("\n");
		}
		cout << "黑:" << cnt10 << "白:" << cnt9 << endl;

		//Mat res(dim1[0],dim1[1],CV_16SC1,out_test);
		Mat res(dim1[0], dim1[1], CV_8UC1);
		//res.at<uchar>(0,0) = 0;
		for (i = 0; i<dim1[0]; i++)
		{
			for (j = 0; j<dim1[1]; j++)
			{
				res.at<uchar>(i, j) = out_test[j + i*dim1[1]];   //33个res
			}
		}
		DestroyArray_1(nbr);  //销毁
		DestroyArray_1(out_test);
		imshow("imgcutmulti图像:", res);
		waitKey(0);

		//cost为第二个参数
		cost = (double *)malloc(nmult * sizeof(double *));
		cost[imult] = flow;
		cout << cost[imult] << endl;
	}

	
	/*
	//必须开二维数组
	int **out;
	int i;
	out = (int **)malloc((imult + 1) * sizeof(int *)); //+1的原因在于有边界,好判断元素个数
	for (i = 0; i < imult + 1; i++)
	{
		out[i] = (int *)malloc(((dim1[0] * dim1[1]) + 1) * sizeof(int)); //原因同上
	}

	int k;
	for (i = 0; i < imult; i++) //一共有33个
	{
		for (j = 0; j < dim1[0]; j++)
		{
			for (k = 0; k < dim1[1]; k++)
			{
				out[i][j + k*dim1[0]] = g->what_segment(j + k * dim1[0]) == GraphType::SINK;
			}
		}
	}*/

	delete g;
}