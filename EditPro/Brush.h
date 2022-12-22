#pragma once
#include <opencv2/opencv.hpp>

struct Brush
{
	//the opacity value is between 0 & 255 where 0 is fully transparent
	int opacity = 255;
	//the brush size in pixels
	float size = 50;

	cv::Mat texture;

	bool erase = false;
};