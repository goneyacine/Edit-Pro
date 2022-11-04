#include "EPProject.h"

/// <summary>
/// 
/// </summary>
/// <param name="p_size">the canvas size (width & height)</param>
EPProject::EPProject(EP::Vector2 p_size)
	: m_size(p_size)
{
	m_canvas = new CanvasView(NULL,m_size.x,m_size.y);

	render();
}
EPProject::~EPProject()
{
	
}

cv::Mat EPProject::getRenderedImage()
{
	return m_renderedImage;
}

///
CanvasView* EPProject::getCanvasView()
{
	return m_canvas;
}

//TODO : adding support for alpha color channel
void EPProject::render()
{
	if (m_layers.size() == 0)
		return;

	//creating an empty white background
	cv::Mat tempImg(cv::Size(m_size.x, m_size.y), CV_8UC3, cv::Scalar(255,255,255));

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
	Layer* newLayer = new Layer(m_size.x, m_size.y);
	newLayer->import(p_img);
	m_layers.push_back(newLayer);

	m_currentLayer = m_layers.size() -1 ; 
	render();
	emit layersUpdated();
}

void EPProject::importToCurrentLayer(cv::Mat p_img)
{
	if (m_currentLayer < 0 || m_layers.size() == 0)
		return;

	m_layers.at(m_currentLayer)->import(p_img);
	render();
	emit layersUpdated();
}

std::vector<Layer*>* EPProject::getLayers()
{
	return &m_layers;
}


