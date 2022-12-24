#include "EPProject.h"
#include <chrono>
#include <qdebug.h>
/// <summary>
/// 
/// </summary>
/// <param name="p_size">the canvas size (width & height)</param>
EPProject::EPProject(EP::Vector2 p_size)
	: m_size(p_size)
{
	m_canvas = new CanvasView(NULL,m_size.x,m_size.y);
	m_renderedImage = cv::Mat(cv::Size(m_size.x, m_size.y), CV_8UC4, cv::Scalar(255, 255, 255,255));
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

	//BGRA
	cv::Vec4b newColor;
	double newAlpha;
	cv::Vec4b topPixel, buttomPixel;
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			m_renderedImage.at<cv::Vec4b>(y, x) = cv::Vec4b(0,0,0,255);
			for (int i = m_layers.size() - 1; i >= 0;i--)
			{
				if (x < m_layers[i]->getRenderedImage().cols && y < m_layers[i]->getRenderedImage().rows)
				{

					buttomPixel = m_renderedImage.at<cv::Vec4b>(y, x);
					topPixel = m_layers[i]->getRenderedImage().at<cv::Vec4b>(y, x);

					newAlpha = topPixel[3] + buttomPixel[3] * (1 - (float)topPixel[3] / 255);

					//the new blue value
					newColor[0] = (topPixel[0] * topPixel[3] + buttomPixel[0] * buttomPixel[3] * (1 - (float)topPixel[3] / 255)) / newAlpha;

					//the new green value
					newColor[1] = (topPixel[1] * topPixel[3] + buttomPixel[1] * buttomPixel[3] * (1 - (float)topPixel[3] / 255)) / newAlpha;

					//the new red value
					newColor[2] = (topPixel[2] * topPixel[3] + buttomPixel[2] * buttomPixel[3] * (1 - (float)topPixel[3] / 255)) / newAlpha;

					//the new alpha value
					newColor[3] = newAlpha;


					m_renderedImage.at<cv::Vec4b>(y, x) = newColor;
				}
				else
					continue;
			}
		}
	}


	//refreshing the canvas
	m_canvas->updateCanvas(m_renderedImage);
}

/// <summary>
/// imports an image to a new layer
/// </summary>
/// <param name="p_img"></param>
void EPProject::importAsNewLayer(cv::Mat p_img)
{
	Layer* newLayer = new Layer(m_size.x, m_size.y);
	newLayer->import(p_img);
	m_layers.push_back(newLayer);

	m_selectedLayerIndex = m_layers.size() -1 ; 
	render();
	emit layersUpdated();
}
/// <summary>
/// imports a layer to current selected file
/// </summary>
/// <param name="p_img"></param>
void EPProject::importToCurrentLayer(cv::Mat p_img)
{
	if (m_selectedLayerIndex < 0 || m_layers.size() == 0)
		return;

	m_layers.at(m_selectedLayerIndex)->import(p_img);
	m_selectedLayerIndex = m_layers.size() - 1;
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

	//itreating through layer to find the target layer
	for (int i = 0; i < m_layers.size(); i++)
	{
		if (p_layer == m_layers.at(i))
		{
			//removing the layer from the layers vector and deleting it from the memory
			m_layers.erase(m_layers.begin() + i);
			delete p_layer;
		}
	}
	//calling the render function to renfresh the canvas
	render();

	if (m_layers.size() == 0)
		m_selectedLayerIndex = -1;
	else
		m_selectedLayerIndex = 0;

	emit layersUpdated();
}

void EPProject::importFile(QString p_filePath)
{
	importAsNewLayer(cv::imread(p_filePath.toStdString(), cv::IMREAD_UNCHANGED));
}


Layer* EPProject::getSelectedLayer()
{
	if (m_selectedLayerIndex < 0)
		return NULL;

	return m_layers.at(m_selectedLayerIndex);
}

