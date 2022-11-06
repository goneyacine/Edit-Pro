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

EP::Vector2 EPProject::getSize()
{
	return m_size;
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


void EPProject::layerUp(Layer* p_layer)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		//checking if the current layer in the layers list is the same as the input layer, if not then continue the iteration
		if (p_layer == m_layers.at(i))
		{

			//if the target layer is already on the top then there is no need to move it up
			if (i < m_layers.size() - 1)
			{
				//move the target layer up by swaping it's position in layers list
				Layer* tempLayer = m_layers.at(i + 1);
				m_layers.at(i + 1) = m_layers.at(i);
				m_layers.at(i) = tempLayer;
			}

		}
	}
	render();
	emit layersUpdated();
}

void EPProject::layerDown(Layer* p_layer)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		//checking if the current layer in the layers list is the same as the input layer, if not then continue the iteration
		if (p_layer == m_layers.at(i))
		{

			//if the target layer is already on the buttom then there is no need to move it down
			if (i > 0)
			{
				//move the target layer up by swaping it's position in layers list
				Layer* tempLayer = m_layers.at(i - 1);
				m_layers.at(i - 1) = m_layers.at(i);
				m_layers.at(i) = tempLayer;
			}

		}
	}
	render();
	emit layersUpdated();
}

void EPProject::createEmptyLayer()
{
	Layer* layer = new Layer(m_size.x,m_size.y,"Created Layer");
	m_layers.push_back(layer);
	render();
	emit layersUpdated();
}
void EPProject::deleteLayer(Layer* p_layer)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		if (p_layer == m_layers.at(i))
		{
			m_layers.erase(m_layers.begin() + i);
			delete p_layer;
		}
	}
	render();
	emit layersUpdated();
}

void EPProject::importFile(QString p_filePath)
{
	importAsNewLayer(cv::imread(p_filePath.toStdString()));
}


