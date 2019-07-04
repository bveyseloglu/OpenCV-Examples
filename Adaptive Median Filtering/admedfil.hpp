#include "opencv2/opencv.hpp"
#include <algorithm>

using namespace std;

int StageA(int filterMaxSize, int filterCurrentSize, int x, int y, cv::Mat inputImage);
int StageB(int filterCurrentHeight, int x, int y, cv::Mat inputImage);
int MedianKernel(int kernelWidth, int kernelCenterX, int kernelCenterY, cv::Mat inputImage);
int MinKernel(int kernelHeight, int kernelCenterX, int kernelCenterY, cv::Mat inputImage);
int MaxKernel(int kernelHeight, int kernelCenterX, int kernelCenterY, cv::Mat inputImage);

// this function operates on grayscale images
cv::Mat adaptiveMedian(cv::Mat image)
{
	cv::Mat outImage(image.rows, image.cols, CV_8UC1);

	int incorrectInput = 1;
	int filterMaxHeight = 0;

	// get user input
	while (incorrectInput) {
		
		cout << "Please enter the filter's max size (should be an odd number):" << endl;
		cin >> filterMaxHeight;

		if ((float)filterMaxHeight / 2 - filterMaxHeight / 2 == 0)
			cout << "Please enter an odd number!" << endl << endl;
		else
			incorrectInput = 0;
	}

	// apply filter for each pixel of the image
	for (int i = 0; i < image.rows; i++) 
		for (int ii = 0; ii < image.cols; ii++) 
			outImage.at<uchar>(i, ii) = StageA(filterMaxHeight, 1, i, ii, image);

	cout << endl << "Done.";

	return outImage;
}

int StageA(int filterMaxHeight, int filterCurrentHeight, int x, int y, cv::Mat inputImage)
{
	int a1 = MedianKernel(filterCurrentHeight, x, y, inputImage) - MinKernel(filterCurrentHeight, x, y, inputImage), a2 = MedianKernel(filterCurrentHeight, x, y, inputImage) - MaxKernel(filterCurrentHeight, x, y, inputImage);

	if (a1 > 0 && a2 < 0)
		return StageB(filterCurrentHeight, x, y, inputImage);
	else {
		if (filterCurrentHeight == filterMaxHeight)
			return MedianKernel(filterCurrentHeight, x, y, inputImage);
		else
			return StageA(filterMaxHeight, filterCurrentHeight + 2, x, y, inputImage);
	}


}

int StageB(int filterCurrentHeight, int x, int y, cv::Mat inputImage)
{
	int b1 = (int)inputImage.at<uchar>(x, y) - MinKernel(filterCurrentHeight, x, y, inputImage), b2 = (int)inputImage.at<uchar>(x, y) - MaxKernel(filterCurrentHeight, x, y, inputImage);

	if (b1 > 0 && b2 < 0)
		return (int)inputImage.at<uchar>(x, y);
	else
		return MedianKernel(filterCurrentHeight, x, y, inputImage);
}

// returns the median value of the "kernelHeight x kernelHeight" sized window that has a center located in (kernelCenterX, kernelCenterY).
int MedianKernel(int kernelHeight, int kernelCenterX, int kernelCenterY, cv::Mat inputImage)
{
	int *values = new int[kernelHeight * kernelHeight];
	int temp = 0;

	// gather the values that lying in the window
	for (int i = -kernelHeight / 2; i <= kernelHeight / 2; i++) 
		for (int ii = -kernelHeight / 2; ii <= kernelHeight / 2; ii++, temp++) 
			kernelCenterX + i < 0 || kernelCenterY + ii < 0 || kernelCenterX + i > inputImage.rows-1 || kernelCenterY + ii > inputImage.cols -1 ? values[temp] = 0 : values[temp] = inputImage.at<uchar>(kernelCenterX + i, kernelCenterY + ii);

	// sort the values
	sort(values, values + kernelHeight * kernelHeight);

	int ret = values[kernelHeight * kernelHeight / 2];
	delete[] values;

	return ret;
}

// returns the minumum value of the "kernelHeight x kernelHeight" sized window that has a center located in (kernelCenterX, kernelCenterY).
int MinKernel(int kernelHeight, int kernelCenterX, int kernelCenterY, cv::Mat inputImage)
{
	int *values = new int[kernelHeight * kernelHeight];
	int temp = 0;

	// gather the values that lying in the window
	for (int i = -kernelHeight / 2; i <= kernelHeight / 2; i++)
		for (int ii = -kernelHeight / 2; ii <= kernelHeight / 2; ii++, temp++)
			kernelCenterX + i < 0 || kernelCenterY + ii < 0 || kernelCenterX + i > inputImage.rows -1 || kernelCenterY + ii > inputImage.cols -1 ? values[temp] = 0 : values[temp] = inputImage.at<uchar>(kernelCenterX + i, kernelCenterY + ii);

	// sort the values
	sort(values, values + kernelHeight * kernelHeight);

	int ret = values[0];
	delete[] values;

	return ret;
}

// returns the maximum value of the "kernelHeight x kernelHeight" sized window that has a center located in (kernelCenterX, kernelCenterY).
int MaxKernel(int kernelHeight, int kernelCenterX, int kernelCenterY, cv::Mat inputImage)
{
	int *values = new int[kernelHeight * kernelHeight];
	int temp = 0;

	// gather the values that lying in the window
	for (int i = -kernelHeight / 2; i <= kernelHeight / 2; i++)
		for (int ii = -kernelHeight / 2; ii <= kernelHeight / 2; ii++, temp++)
			kernelCenterX + i < 0 || kernelCenterY + ii < 0 || kernelCenterX + i > inputImage.rows -1 || kernelCenterY + ii > inputImage.cols-1 ? values[temp] = 0 : values[temp] = inputImage.at<uchar>(kernelCenterX + i, kernelCenterY + ii);

	// sort the values
	sort(values, values + kernelHeight * kernelHeight);

	int ret = values[kernelHeight * kernelHeight - 1];
	delete[] values;

	return ret;
}