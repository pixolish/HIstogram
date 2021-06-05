/****
 * Author : Somnath Mukherjee
 * Email :- somnath.7.mukherjee@gmail.com
 * Personal Website:- http://www.pixolish.com 
 * */


#include "Histogram.hpp"
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
 
int main(int argc,char **argv)
{
    // Load the image

    Mat imageColor = imread(argv[1]);
    Mat grayimage;

    cv::cvtColor(imageColor,grayimage,CV_BGR2GRAY);


    int histogrambin=atoi(argv[2]);

    Histogram histogram(grayimage.rows,grayimage.cols,histogrambin);

    // Generate the histogram
    int histogramMat[MaxHist];

    // Calculate the Histogram
    histogram.calcHist(grayimage, histogramMat);
 
    // Display the original Histogram
    histogram.histogramDisplay(histogramMat, "OriginalHistogram");
    
    // Calcualtion Histogram Equalization
    histogram.histEqualization(grayimage,histogramMat);
    // Display the equilzed histogram
    histogram.histogramDisplay(histogramMat, "EquilizedHistogram");

    // Display equilized image
    namedWindow("Equilized Image");
    imshow("Equilized Image",grayimage);

    waitKey(0);
    return 0;
}
