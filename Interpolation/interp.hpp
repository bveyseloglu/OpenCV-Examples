#include "opencv2/opencv.hpp"

int substractAndSquare(cv::Vec3b in1, cv::Vec3b in2);

// resizes the image with bilinear interpolation and returns it
// outWidth is the width of the output image, and outHeight is the height of the output image
cv::Mat interpBilinear(cv::Mat image, int outWidth, int outHeight)
{
	cv::Mat outImage = cv::Mat(outHeight, outWidth, CV_8UC3);

	// calculate the ratio. instead of calculating this value at each loop, calculate it only one time to execute the "for loop" faster.
	float divisionH = (float)image.rows / (float)outHeight;
	float divisionW = (float)image.cols / (float)outWidth;

	// resize
	for (int i = 1; i < outHeight - 1; i++) {
		for (int ii = 1; ii < outWidth - 1; ii++) {
			float x = (float)i * divisionH;
			float y = (float)ii * divisionW;

			float agirlikX = x - (int)x;
			float agirlikY = y - (int)y;

			// it's not necessary to define x, y, agirlikX and agirlikY variables. i defined them just to increase the readibility of the below code.

			cv::Vec3b newColor1 = image.at<cv::Vec3b>((int)x, (int)y) * (float)(1 - agirlikX) * (float)(1 - agirlikY);
			cv::Vec3b newColor2 = image.at<cv::Vec3b>((int)x + 1, (int)y) * (float)agirlikX * (float)(1 - agirlikY);
			cv::Vec3b newColor3 = image.at<cv::Vec3b>((int)x, (int)y + 1) * (float)(1 - agirlikX) * (float)agirlikY;
			cv::Vec3b newColor4 = image.at<cv::Vec3b>((int)x + 1, (int)y + 1) * (float)agirlikX * (float)agirlikY;

			outImage.at<cv::Vec3b>(i, ii) = newColor1 + newColor2 + newColor3 + newColor4;
		}
	}

	return outImage;
}


// resizes the image with nearest neighbor interpolation and returns it
// outWidth is the width of the output image, and outHeight is the height of the output image
cv::Mat interpNN(cv::Mat image, int outWidth, int outHeight)
{
	cv::Mat outImage = cv::Mat(outHeight, outWidth, CV_8UC3);

	// calculate the ratio. instead of calculating this value at each loop, calculate it only one time to execute the "for loop" faster.
	float divisionH = (float)image.rows / (float)outHeight;
	float divisionW = (float)image.cols / (float)outWidth;

	// resize
	for (int i = 0; i < outHeight; i++) 
		for (int ii = 0; ii < outWidth; ii++) 
			outImage.at<cv::Vec3b>(i, ii) = image.at<cv::Vec3b>((int)((float)i * divisionH), (int)((float)ii * divisionW));

	return outImage;
}


// calculates the mean squared error between two images and returns it (see the example below)
// Say we have two 2x2 RGB images:
//         image1                          image2
// (48,219,66)  (108, 205, 51)     (253,176,148) (160,82,117)
// (241,157,220) (155,10,206)       (120,44,174) (154,122,42)
// MSE = (1 / (2*2*3)) * ((48-253)^2 + (219-176)^2 + (66-148)^2 + (108-160)^2 + (205-82)^2 + (51-117)^2 + (241-120)^2 + (157-44)^2 + (220-174)^2 + (155-154)^2 + (10-122)^2 + (206-42)^2)
double mse(cv::Mat image1, cv::Mat image2)
{
	// we can only calculate mse if the images are of the same shape
	// the following 2 lines check this and throw an exception if this is not the case
	if ((image1.rows != image2.rows) || (image1.cols != image2.cols) || (image1.channels() != image2.channels()))
	{
		std::cout << "Inputs to mse() must be of the same shape." << std::endl;
		throw std::runtime_error("Inputs to mse() must be of the same shape.");
	}

	double mse = 0; // INITIALIZE THIS WITH AN APPROPRIATE VALUE
	double divisor = (double)(3 * (double)image1.rows * (double)image1.cols); // instead of calculating this value at each loop, calculate it only one time to execute the "for loop" faster.

	for (int i = 0; i < image1.rows; i++) 
		for (int ii = 0; ii < image1.cols; ii++) 
			mse += (double)substractAndSquare(image1.at<cv::Vec3b>(i, ii), image2.at<cv::Vec3b>(i, ii)) / divisor;
		
	return mse;
}

int substractAndSquare(cv::Vec3b in1, cv::Vec3b in2)
{
	return (in1[0] - in2[0]) * (in1[0] - in2[0]) + (in1[1] - in2[1]) * (in1[1] - in2[1]) + (in1[2] - in2[2]) * (in1[2] - in2[2]);
}
