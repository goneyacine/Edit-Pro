#include "EPProject.h"
#include "ColorConvension.h"

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
	m_renderedImage = m_baseImage.clone();
	updateSaturation();
	m_imageViewer->updateImage(&m_renderedImage);
}


void EPProject::updateSaturation()
{

	//making sure that the saturation is in range (our range not opencv's range)
	if (m_saturation < 0)
		m_saturation = 0;
	else if (m_saturation > 100)
		m_saturation = 100;



	float h, s, v,r,g,b;
	

	for (int x = 0; x < m_renderedImage.rows; x++)
	{
		for (int y = 0; y < m_renderedImage.cols; y++)
		{

			b = m_renderedImage.at < cv::Vec3b >(x, y)[0];
			g = m_renderedImage.at < cv::Vec3b >(x, y)[1];
			r = m_renderedImage.at < cv::Vec3b >(x, y)[2];

			colorConvension::RGB2HSV(r, g, b, h, s, v);

			if (s * ((float)m_saturation / 50) > 1)
				continue;

			colorConvension::HSV2RGB(r, g, b, h, s * ((float)m_saturation / 50), v);

			m_renderedImage.at < cv::Vec3b >(x, y)[0] = b;
			m_renderedImage.at < cv::Vec3b >(x, y)[1] = g;
			m_renderedImage.at < cv::Vec3b >(x, y)[2] = r;
		}
	}
}

void EPProject::setSaturation(int p_saturation)
{
	m_saturation = p_saturation;
	render();
}