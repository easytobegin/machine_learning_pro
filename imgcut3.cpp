#include<iostream>
#include"graph.h"
#include"mx_function.h"
#include <opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;



/*
matlab���Խ��:
hc 98 * 399
lap 99 * 399
vc 99 * 398
wgt.*hc = 98 * 399
wgt.*vc = 99 * 398
*/
void imgcut3(Mat para1,Mat para2,Mat para3,Mat para4)  //�ĸ��������Ǿ������ͣ����Ƕ�ά����
{
	int i,j;
	int ndim = 2; //ά��Ϊ2
	long n,m,nmin;
	double *src,*snk,*nbr;
	double flow = 0;

	//����һ��ͼ�����ת��ͨ����ĺ���
	//mxGetDimensions������ô�鷳,ֱ�ӷ�������������
	int *dim1;
	int *dim2;
	dim1 = (int *)malloc(10*sizeof(int *));
	dim2 = (int *)malloc(10*sizeof(int *));
	dim1[0] = para1.rows; //����1����
	dim1[1] = para1.cols; //����1����
	dim2[0] = para2.rows; //����2����
	dim2[1] = para2.cols; //����2����
	/*
	cout<<dim1[0]<<"*"<<dim1[1]<<endl;
	cout<<dim2[0]<<"*"<<dim2[1]<<endl;
	��ӡ�Ľ��ֵ��ͬ
	*/
	for(i=0;i<ndim;i++)
	{
		if(i == 0)  //mxGetDimensions(prhs[2+i])
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
	

	/*
	��ȡ����Mat����ķ�Χ
	*/
	int row1 = para1.rows;int col1 = para1.cols;
	int row2 = para2.rows;int col2 = para2.cols;
	int row3 = para3.rows;int col3 = para3.cols;
	int row4 = para4.rows;int col4 = para4.cols;
	int result1 = (row1 + 10) * (col1 + 10);
	int result2 = (row2 + 10) * (col2 + 10);
	int result3 = (row3 + 10) * (col3 + 10);
	int result4 = (row4 + 10) * (col4 + 10);
	
	src = (double *)malloc(result1 * sizeof(double *));
	snk = (double *)malloc(result2 * sizeof(double *));

	src = Mat_change_to_1_Matrix(para1); //Matת��ͨ����
	
	snk = Mat_change_to_1_Matrix(para2); //Matת��ͨ����
	
	typedef Graph<double,double,double> GraphType;
	GraphType *g = new GraphType(dim1[0]*dim1[1],
                               (dim1[0]-1)*dim1[1]+dim1[0]*(dim1[1]-1));

	// add nodes
	for (i = 0; i < dim1[0]*dim1[1]; i++) {
		g -> add_node(); 
	}
	// add source/sink weights
	for (i = 0; i < dim1[0]*dim1[1]; i++) {
		g -> add_tweights(i,src[i],snk[i]);
	}

	// add neighbor links
	nbr = (double *)malloc(result3 * sizeof(double *)); 

	nbr = Mat_change_to_1_Matrix(para3); 
	int cnt = 0,cnt1 = 0;
	 
	for (i = 0; i < dim1[0]-1; i++) //��para3������
	{
		for (j = 0; j < dim1[1]; j++) 
		{
			if (int(nbr[i+j*(dim1[0]-1)]) == 0) //��ɫ����
			{
				g -> add_edge(i+j*dim1[0],i+j*dim1[0]+1,
                      nbr[i+j*(dim1[0]-1)],nbr[i+j*(dim1[0]-1)]);
			}
		}
	}
	nbr = Mat_change_to_1_Matrix(para4); //%lf
	
	
	/*for(int i=0;i<para4.rows;i++)
	{
		for(int j=0;j<para4.cols;j++)
		{
			if(nbr[i*para4.cols+j] > 0) //��ɫ��ʾ��
			{
				cnt++;
				//cout<<i<<" "<<j<<endl;  //׼ȷ��
			}
			else
			{
				cnt1++;
				//cout<<nbr[i*para4.cols+j]<<endl;
			}
		}
	}*/

	
	//Mat res2(para4.rows,para4.cols,CV_64FC1,nbr);
	//cout<<"res2:"<<res2<<endl;
	/*imshow("res2",res2);
	waitKey(0);
	printf("%d����ɫ����%d��ɫ���ص�",cnt,cnt1);*/
	for (i = 0; i < dim1[0]; i++)   //��para4������
	{
		for (j = 0; j < dim1[1]-1; j++) 
		{
			if (int(nbr[i+j*dim1[0]]) == 0) //����,���ߣ���ɫ����,��ɫΪ����
			{	
				//cout<<nbr[i+j*dim1[0]]<<endl;
				g -> add_edge(i+j*dim1[0],i+(j+1)*dim1[0],
                      nbr[i+j*dim1[0]],nbr[i+j*dim1[0]]);
				//cout<<"i:"<<i<<"j:"<<j<<endl;
			}
			/*else //��
			{
				cout<<"i:"<<i<<"j:"<<j<<endl;
			}*/
		}
	}
	// do calculation
	flow = g -> maxflow();


	//���Ϊһά����,outΪ���������һ��
	vector<int> out(dim1[0]*dim1[1]+10000);
	
	for (i = 0; i < dim1[0]; i++) 
	{
		for (j = 0; j < dim1[1]; j++) 
		{
			out[i+j*dim1[0]] = g->what_segment(i+j*dim1[0]) == GraphType::SINK;
			//cout<<g->what_segment(i+j*dim1[0])<<" ";
			//printf("%d ",out[i+j*dim1[0]]);
		}
		//printf("\n");
	}
	int *out_test;
	out_test = (int *)malloc(dim1[0] * dim1[1] * sizeof(int *));

	int cnt10 = 0,cnt9 = 0;
	for(i=0;i<dim1[0];i++)
	{
		for(j=0;j<dim1[1];j++)
		{
			//cout<<out[j+i*dim1[1]]<<endl; //��������0
			if(out[i+j*dim1[0]] == 0)
			{
				out_test[i + j *dim1[0]] = 255;
				cnt9++;
			}
			else
			{
				out_test[i + j *dim1[0]] = 0;
				cnt10++;
			}
			//cout<<out_test[i + j *dim1[0]]<<" ";
		}
		//printf("\n");
	}
	cout<<"��:"<<cnt10<<"��:"<<cnt9<<endl;
	
	//Mat res(dim1[0],dim1[1],CV_16SC1,out_test);
	Mat res(dim1[0],dim1[1],CV_8UC1);
	//res.at<uchar>(0,0) = 0;
	for(i=0;i<dim1[0];i++)
	{
		for(j=0;j<dim1[1];j++)
		{
			res.at<uchar>(i,j) = out_test[j+i*dim1[1]];
		}
	}
	/*
	for(i=0;i<dim1[0];i++)
	{
		for(j=0;j<dim1[1];j++)
		{
			res.at<uchar>(i,j) = out_test[i+j*dim1[0]];
		}
	}*/
	//cout<<res.rows<<" "<<res.cols<<endl;
	//waitKey(0);

	/*IplImage *src1;

    src1 = &IplImage(res);

	FillInternalContours(src1, 200); */
	imshow("Do_imgcut3_result",res);
	waitKey(0);

	/*cvNamedWindow("img");  
    cvShowImage("img", src1);  
	waitKey(0);*/

	//���ܻ�������һ���������,�ڶ���
	double out_2;
	out_2 = flow;

	delete g;
}