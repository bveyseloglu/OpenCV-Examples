#include "opencv2/opencv.hpp"
#include "interp.hpp"

using cv::Mat;


void main()
{
	// read the image from file
	// note that the original resolution is 1280x720
	Mat image = cv::imread("C:\\eem.jpg");
	
	// resize the image with OpenCV's linear interpolation
	Mat opencvResized;
	cv::resize(image, opencvResized, cv::Size(640, 360), 0, 0, CV_INTER_LINEAR);

	// resize the image with your linear interpolation
	Mat myResized = interpBilinear(image, 640, 360);

	// check if the two images are the same using your mean square error calculation function
	// the error should be very low
	std::cout << "Downscaled the image from 1280x720 to 640x360 using bilinear interpolation" << std::endl;
	std::cout << "MSE: " << mse(opencvResized, myResized) << std::endl;

	// now try the same for upscaling the image
	cv::resize(image, opencvResized, cv::Size(1920, 1080), 0, 0, CV_INTER_LINEAR);

	myResized = interpBilinear(image, 1920, 1080);

	std::cout << "Upscaled the image from 1280x720 to 1920x1080 using bilinear interpolation" << std::endl;
	std::cout << "MSE: " << mse(opencvResized, myResized) << std::endl;

	// repeat the above two experiments with nearest neighbor interpolation
	cv::resize(image, opencvResized, cv::Size(640, 360), 0, 0, CV_INTER_NN);

	myResized = interpNN(image, 640, 360);

	std::cout << "Downscaled the image from 1280x720 to 640x360 using nearest neighbor interpolation" << std::endl;
	std::cout << "MSE: " << mse(opencvResized, myResized) << std::endl;

	cv::resize(image, opencvResized, cv::Size(1920, 1080), 0, 0, CV_INTER_NN);

	myResized = interpNN(image, 1920, 1080);

	std::cout << "Upscaled the image from 1280x720 to 1920x1080 using nearest neighbor interpolation" << std::endl;
	std::cout << "MSE: " << mse(opencvResized, myResized) << std::endl;
}
