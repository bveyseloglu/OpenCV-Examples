/*
 * For better readibility, I wrote the code the way it can be read easily without taking care of efficiency.
 */

#include "opencv2/opencv.hpp"

double cumulativeArraySum(double arrayIn[], int from);
int roundNumber(double input);

cv::Mat histeq(cv::Mat image)
{
	// convert the input image to the YUV color space

	cv::Mat inputLum(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
	cvtColor(image, inputLum, cv::COLOR_BGR2YCrCb);

	// find the density of each pixel in y channel

	int densY[256] = { 0 };

	for (int i = 0; i < image.rows; i++)
		for (int ii = 0; ii < image.cols; ii++) 
			densY[inputLum.at<cv::Vec3b>(i, ii)[0]]++;

	// find the probabilities of each pixel value

	double probY[256] = { 0 };

	int imagePixelCount = image.rows * image.cols;

	for (int i = 0; i<256; i++)
		probY[i] = (double)densY[i] / (double)imagePixelCount;

	// find the corresponding value for each pixel

	int newY[256] = { 0 };

	for (int i = 0; i<256; i++)
		newY[i] = roundNumber(255 * cumulativeArraySum(probY, i));

	// build the new image

	for (int i = 0; i < image.rows; i++) 
		for (int ii = 0; ii < image.cols; ii++) 
			inputLum.at<cv::Vec3b>(i, ii)[0] = newY[inputLum.at<cv::Vec3b>(i, ii)[0]];

	// convert the image back to the RGB color space

	cv::Mat outImage(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
	cvtColor(inputLum, outImage, cv::COLOR_YCrCb2BGR);

	// return the output
	
	return outImage;
}


// This method sums the values of the input array from 'arrayInt[i]' to 'arrayInt[0]'.
double cumulativeArraySum(double arrayIn[], int i)
{
	if (i == 0)
		return arrayIn[0];
	else
		return arrayIn[i] + cumulativeArraySum(arrayIn, i - 1);
}


// This method rounds the input double to the nearest int value.
int roundNumber(double input)
{
	if (input < (double)((int)input + 0.5))
		return (int)input;
	else
		return (int)input + 1;
}