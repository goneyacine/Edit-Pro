#include "Layer.h"


Layer::Layer(int p_width, int p_hieght) : m_width(p_width),m_hieght(p_hieght)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_hieght, CV_8UC3);
}

//TODO : this function should reimplemented to later to support the alpha channel
void Layer::import(cv::Mat p_img)
{

	int xOffset = (m_width / 2) - (p_img.rows / 2);
	int yOffset = (m_hieght / 2) - (p_img.cols/ 2);

	for (int x = 0; x < p_img.rows; x++)
	{
		if (x + xOffset >= m_width)
			continue;
		for (int y = 0; y < p_img.cols; y++)
		{
			if (y + yOffset >= m_hieght)
				continue;

			m_renderedImage.at<cv::Vec3b>(x + xOffset, y + yOffset) = p_img.at<cv::Vec3b>(x, y);
		}
	}

}

cv::Mat Layer::getRenderedImage()
{
	return m_renderedImage;
}