#include "Layer.h"


Layer::Layer(int p_width, int p_height) : m_width(p_width),m_height(p_height)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_height, CV_8UC3);

	m_name = "New Layer";
}


Layer::Layer(int p_width, int p_height,QString p_name) : m_width(p_width), m_height(p_height),m_name(p_name)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_height, CV_8UC3);
}

//TODO : this function should reimplemented to later to support the alpha channel
void Layer::import(cv::Mat p_img)
{

	int xOffset = (m_width / 2) - (p_img.rows / 2);
	int yOffset = (m_height / 2) - (p_img.cols/ 2);

	for (int x = 0; x < p_img.rows; x++)
	{
		if (x + xOffset >= m_width)
			continue;
		for (int y = 0; y < p_img.cols; y++)
		{
			if (y + yOffset >= m_height)
				continue;

			m_renderedImage.at<cv::Vec3b>(x + xOffset, y + yOffset) = p_img.at<cv::Vec3b>(x, y);
		}
	}

}

cv::Mat Layer::getRenderedImage()
{
	return m_renderedImage;
}

void Layer::resize(int p_width, int p_height)
{
	//TODO : implement the resize function
}

int Layer::getWidth()
{
	return m_width;
}

int Layer::getHeight()
{
	return m_height;
}

QString Layer::getName()
{
	return m_name;
}

void Layer::setName(QString p_name)
{
	m_name = p_name;
}

bool Layer::isVisible()
{
	return m_isVisible;
}

void Layer::setVisible(bool p_visible)
{
	m_isVisible = p_visible;
}