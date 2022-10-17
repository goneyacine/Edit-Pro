#include "EPProject.h"


EPProject::EPProject(ImageViewer* p_imageViewer,cv::Mat p_baseImage) : m_imageViewer(p_imageViewer),m_baseImage(p_baseImage)
{
	m_saturation = m_baseImage.at<cv::Vec3b>(0, 0)[1];
}
EPProject::~EPProject()
{
	
}


int EPProject::getSaturation()
{
	return m_saturation;
}


cv::Mat EPProject::getBaseImage()
{
	return m_baseImage;
}

cv::Mat EPProject::getRenderedImage()
{
	return m_renderedImage;
}


ImageViewer* EPProject::getImageViewer()
{
	return m_imageViewer;
}

void EPProject::render()
{
	updateSaturation();
}


void EPProject::updateSaturation()
{

	//making sure that the saturation is in range (our range not opencv's range)
	if (m_saturation < 0)
		m_saturation = 0;
	else if (m_saturation > 100)
		m_saturation = 100;


	int cvSaturation = ((float)m_saturation / 100 * 255);

	cv::Mat updatedImage;

	cv::cvtColor(m_baseImage, updatedImage, cv::COLOR_BGR2HSV);

	for (int x = 0; x < updatedImage.rows; x++)
	{
		for (int y = 0; y < updatedImage.cols; y++)
		{
			updatedImage.at < cv::Vec3b >(x, y)[1] = cvSaturation;
		}
	}
	cv::cvtColor(updatedImage, m_renderedImage, cv::COLOR_HSV2BGR);
}

void EPProject::setSaturation(int p_saturation)
{
	m_saturation = p_saturation;
}