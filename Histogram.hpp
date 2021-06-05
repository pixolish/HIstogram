/****
 * Author : Somnath Mukherjee
 * Email :- somnath.7.mukherjee@gmail.com
 * Personal Website:- http://www.pixolish.com 
 * */


#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define MaxHist 256

class Histogram
{

public:
int imgrows;
int imgcols;
int histbin;
Histogram(int rows,int cols,int bin)
{
imgrows=rows;
imgcols=cols;
histbin=bin;
}

void calcHist(cv::Mat image, int histogram[]);
void histogramDisplay(int histogram[], const char* caption);
void histEqualization(cv::Mat image,int histogram[]);

};
