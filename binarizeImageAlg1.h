#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void binarizeImageAlg1(Mat image, double thi, double tlo, double sigE,Mat hc1,Mat vc1,Mat lap1); //规定负数代表没有值