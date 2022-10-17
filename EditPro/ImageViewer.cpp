#include "ImageViewer.h"

#include <opencv2/opencv.hpp>


ImageViewer::ImageViewer(cv::Mat* p_img)
{
	m_label = new QLabel();

	updateImage(p_img);
}


ImageViewer::~ImageViewer()
{

}

void ImageViewer::updateImage(cv::Mat* p_img)
{

	if (p_img == NULL)
		return;

	//swaping the red and blue values to convert the format from BGR (used by opencv) to RGB (used by qt)
	uchar red;
	uchar blue;
	cv::Vec3b* color;

	for (int y = 0; y < p_img->rows; y++)
	{
		for (int x = 0; x < p_img->cols; x++)
		{
			color = &p_img->at<cv::Vec3b>(y, x);


			red = (*color)[2];
			blue = (*color)[0];


			(*color)[0] = red;
			(*color)[2] = blue;

		}
	}


	m_label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)p_img->data, p_img->cols, p_img->rows, QImage::Format_RGB888)));
}

QLabel* ImageViewer::getQLabel()
{
	return m_label;
}