#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace cv;

# define HISTSIZE 128
/******** Constant variables **************/
// the number of bins
int histSize[] = {HISTSIZE};

// save 10 grayscale histograms of 10 different images
// each of them is made up of 25 distinct frames extracted from video feed
// Input: an array of type Mat to stores 10 histograms
// Output: none
Mat computeGrayHistogram(Mat src_base)
{	
	Mat gray_base, hist;
	cvtColor( src_base, gray_base, CV_BGR2GRAY );

	// grayscale varies from 0 to 255
	float g_ranges[] = { 0.0, 255.0 };
	const float* ranges[] = { g_ranges };
	// Use the only channel available 
	int channels[] = { 0};
    
	// calculate histogram
	calcHist( &gray_base, 1, channels, Mat(), hist, 1, histSize, ranges, true, false );
	//normalize( hist, hist, 0, 1, NORM_MINMAX, -1, Mat() );
	
	return hist;
}

// Computes the 1D histogram and returns an image of it.
// INPUT: a gray-scale histogram's matrix data
// OUTPUT: a matrix data of the original image's 1D histogram
Mat getHistogramImage(const Mat &hist)
{
	// Get min and max bin values
	double maxVal=0;
	double minVal=0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	
	// Image on which to display histogram
	Mat histImg(histSize[0], histSize[0],CV_8U,Scalar(255));
	
	// set highest point at 90% of nbins
	int hpt = static_cast<int>(0.9*histSize[0]);
	
	// Draw a vertical line for each bin
	for( int h = 0; h < histSize[0]; h++ ) 
	{
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt/maxVal);
		// This function draws a line between 2 points
		line(histImg,Point(h,histSize[0]),
			Point(h,histSize[0]-intensity),
			Scalar::all(0));
	}
	return histImg;
}



int main()
{
	
	Mat src1, src2, src3, src4, src5, src6, src7, src8, src9, src10, src11, src12;
	
	src1 = imread("Picture 366.jpg", 1);
	src2 = imread("Picture 364.jpg", 1);

	src3 = imread("Picture 360.jpg", 1);
	src4 = imread("Picture 361.jpg", 1);
	src5 = imread("Picture 362.jpg", 1);
	src6 = imread("Picture 363.jpg", 1);
	src7 = imread("Picture 338.jpg", 1);
	
	Mat g1 = computeGrayHistogram(src1);
	Mat g2 = computeGrayHistogram(src2);
	Mat g3 = computeGrayHistogram(src3);
	Mat g4 = computeGrayHistogram(src4);
	Mat g5 = computeGrayHistogram(src5);
	Mat g6 = computeGrayHistogram(src6);
	Mat g7 = computeGrayHistogram(src7);

	
	cout<<"1"<<"\n";
	for (int i=0; i<HISTSIZE; i++)
	{		
		cout<<g1.at<float>(i,0)<<"\n";
	}
	cout<<"\n ******************************* \n";

	cout<<"2"<<"\n";
	for (int i=0; i<HISTSIZE; i++)
	{		
		cout<<g2.at<float>(i,0)<<"\n";
	}
	cout<<"\n ******************************* \n";

	
	// use the first correlation method of the openCV compareHist() method
	// to compare and contrast small parts of several histograms
	int start = 0; // start bin
	int end = 24;   // end bin
	Mat test1(end - start, 1, CV_32FC1);
	Mat test2(end - start, 1, CV_32FC1);
	Mat test3(end - start, 1, CV_32FC1);
	Mat test7(end - start, 1, CV_32FC1);

	for (int i = start; i<end; i++)
	{
		test1.at<float>(i - start, 0) = g1.at<float>(i, 0);
		test2.at<float>(i - start, 0) = g2.at<float>(i, 0);
		test7.at<float>(i - start, 0) = g7.at<float>(i, 0);		
	}

	int compare_method = 0; 				
	// obtain the correlation value
	double value1 = compareHist( test1, test2, compare_method );
	double value2 = compareHist( test1, test7, compare_method );
	cout<<value1<<"\n";
	cout<<value2<<"\n";

	waitKey(0);
	return 0;
	
}

