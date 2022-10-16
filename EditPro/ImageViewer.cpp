#include "ImageViewer.h"

#include <opencv2/opencv.hpp>


ImageViewer::ImageViewer(cv::Mat p_img)
{
	m_label = new QLabel();

	updateImage(p_img);
}


ImageViewer::~ImageViewer()
{

}

void ImageViewer::updateImage(cv::Mat p_img)
{
	cv::Mat temp()
}

QLabel* ImageViewer::getQLabel()
{
	return m_label;
}