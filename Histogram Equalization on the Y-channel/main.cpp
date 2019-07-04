#include "opencv2/opencv.hpp"
#include "histeq.hpp"

void main()
{
	cv::Mat image = cv::imread("reflection.jpg");

	image = histeq(image);

	cv::imwrite("reflection_eq.jpg", image);
}