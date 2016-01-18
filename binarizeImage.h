#include"macros.h"
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void binarizeImage(Mat image, double wgt, double thi, double tlo, double sigE, const char* str); //规定负数代表没有值