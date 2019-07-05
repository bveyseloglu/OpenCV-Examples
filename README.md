## OpenCV-Examples
This repository contains example C++ codes related to Interpolation, histogram equalization on the y-channel, and adaptive median filtering.

## Project Descriptions
### Interpolation
Interpolation is an operation commonly required for resizing, rotating, and other geometric operations on an image. The interpolation method used in these operations affects the output image quality. This program implements two resizing functions that use bilinear interpolation and nearest neighbor interpolation. In addition to that, it can calculates mean squared error between two images to verify the implementation is consistent with OpenCV’s implementation.

### Histogram Equalization on the Y-channel
Implements a histogram equalization function that operates on the Y-channel (a.k.a. luminance). To do this, converts the image to the YCrCb color space, applies histogram equalization to the Y-channel then converts the image back to the RGB color space.

Uses following OpenCV functions:
cv::COLOR_BGR2YCrCb, cv::COLOR_YCrCb2BGR

### Adaptive Median Filtering
Implementation of an adaptive median filtering function that operates on a grayscale image. An example filtering shown below:

<p align="center"> 
  <img src="https://dl.dropboxusercontent.com/s/63s5k0jm2o78emx/lisa.png">
</p>

## License
Licensed under MIT License.
