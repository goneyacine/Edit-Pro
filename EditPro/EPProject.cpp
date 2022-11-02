#include "EPProject.h"


EPProject::EPProject(int p_width,int p_hieght, QLayout* p_layersGUIElementsLayout)
	:  m_width(p_width),m_height(p_hieght)
{
	m_canvas = new Canvas(NULL,m_width,m_height);
	m_layersGUIManager = new LayersGUIManager(p_layersGUIElementsLayout,m_layers);
	render();
}
EPProject::~EPProject()
{
	
}

cv::Mat EPProject::getRenderedImage()
{
	return m_renderedImage;
}


Canvas* EPProject::getCanvas()
{
	return m_canvas;
}

//TODO : adding support for alpha color channel
void EPProject::render()
{
	if (m_layers.size() == 0)
		return;

	cv::Mat tempImg(cv::Size(m_width, m_height), CV_8UC3, cv::Scalar(255,255,255));

	for (auto layer : m_layers)
	{
		if (!layer->isVisible())
			continue;

		for (int y = 0; y < layer->getRenderedImage().rows; y++)
		{
			if (y >= tempImg.rows)
				continue;
			for (int x = 0; x < layer->getRenderedImage().cols; x++)
			{
				if (x >= tempImg.cols)
					continue;
				tempImg.at<cv::Vec3b>(y, x) = layer->getRenderedImage().at<cv::Vec3b>(y, x);
			}
		}
	}
   
	m_renderedImage = tempImg.clone();

	m_canvas->updateCanvas(m_renderedImage);
}


void EPProject::importAsNewLayer(cv::Mat p_img)
{
	Layer* newLayer = new Layer(m_width, m_height);
	newLayer->import(p_img);
	m_layers.push_back(newLayer);

	m_currentLayer = m_layers.size() -1 ; 
	render();
	m_layersGUIManager->reloadUI(m_layers);
}

void EPProject::importToCurrentLayer(cv::Mat p_img)
{
	if (m_currentLayer < 0 || m_layers.size() == 0)
		return;

	m_layers.at(m_currentLayer)->import(p_img);
	render();
	m_layersGUIManager->reloadUI(m_layers);
}


