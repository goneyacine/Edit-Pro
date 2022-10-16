#pragma once

#include <qlabel.h>
#include <opencv2/opencv.hpp>


class ImageViewer 
{

public :
	ImageViewer(cv::Mat p_img);
	~ImageViewer();
	QLabel* getQLabel();
	void updateImage(cv::Mat p_img);
private :

	QLabel* m_label;
};