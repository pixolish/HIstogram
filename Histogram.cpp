/****
 * Author : Somnath Mukherjee
 * Email :- somnath.7.mukherjee@gmail.com
 * Personal Website:- http://www.pixolish.com 
 * */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Histogram.hpp" 

using namespace std;
using namespace cv;
 

void Histogram::calcHist(Mat image, int histogram[])
{
 
    // initialize all intensity values to 0
    for(int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
 
    // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;
}
     
void Histogram::histogramDisplay(int histogram[], const char* name)
{
    int hist[256];
    for(int i = 0; i < 256; i++)
    {
        hist[i]=histogram[i];
    }
    int total_size=imgcols*imgrows;
    // draw the histograms
    int hist_w = 512;
    int hist_h =500;
    int bin_width = cvRound((double) hist_w/histbin);
 
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
 
    // find the maximum intensity element from histogram
    int max = hist[0];
    for(int i = 1; i < 256; i++){
        if(max < hist[i]){
            max = hist[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows
    for(int i = 0; i < 256; i++)
    {
        hist[i] = ((double)hist[i]/max)*(histImage.rows);
    }
 
 
    // draw the intensity line for histogram
    for(int i = 0; i < 256; i++)
    {
        line(histImage, Point(bin_width*(i), hist_h), Point(bin_width*(i), hist_h - hist[i]),Scalar(0,255,0), 1, 8, 0);
    }
 
    // display histogram
    namedWindow(name, CV_WINDOW_AUTOSIZE);
    imshow(name, histImage);
    waitKey(0);
}

void Histogram::histEqualization(cv::Mat image,int histogram[])
{
    int total_size=imgrows*imgcols;
    float PrRk[256];

    // Calculate the probablity of the histogram
    for(int i = 0; i < 256; i++)
    {
        PrRk[i] = (double)histogram[i] / total_size;
    }
 
    // Generate the equalized histogram
    float PsSk[256];
    for(int i = 0; i < 256; i++)
    {
        PsSk[i] = 0;
    }
 
   // generate cumulative of the probablity and generate the equalize Histogram 
    for(int i = 0; i < 256; i++)
        for(int j=0; j<=i; j++)
          PsSk[i] += PrRk[j];

    int eqHist[256];
    for(int i = 0; i < 256; i++)
        eqHist[i] = cvRound(PsSk[i]*255);

 for(int i = 0; i < 256; i++)
  for(int j=0; j<=255; j++)
          if (eqHist[i]==eqHist[j] && i!=j)
           {
            eqHist[i]+=eqHist[j];
           } 

 int eqHistNorm[256];
    for(int i = 0; i < 256; i++)
    {
     eqHistNorm[i]=0;
    }
  
    for(int i = 0; i < 256; i++)
    {
        eqHistNorm[cvRound(PsSk[i]*255)] =cvRound(PrRk[i]*total_size);
    }

    for(int i = 0; i < 256; i++)
         for(int j=0; j<256; j++)
            if (eqHistNorm[i]==eqHist[j] && i!=j)
             {
                eqHistNorm[i]+=eqHistNorm[j];
                 histogram[i]=eqHistNorm[i];
                 //cout<<"final1["<<i<<"]="<<final1[i]<<endl;
            }

    // Generate the equlized image
    Mat new_image = image.clone();

    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            new_image.at<uchar>(y,x) = saturate_cast<uchar>(eqHist[image.at<uchar>(y,x)]);
   
   new_image.copyTo(image);

}
