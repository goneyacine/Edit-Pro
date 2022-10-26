#pragma once


#include <opencv2/opencv.hpp>

class Layer
{

public :
	Layer(int p_width, int p_hieght);
	cv::Mat getRenderedImage();
	void import(cv::Mat p_img);

private :
	cv::Mat m_renderedImage;
	int m_width, m_hieght;
};