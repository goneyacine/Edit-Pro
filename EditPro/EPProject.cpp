#include "EPProject.h"


EPProject::EPProject(ImageViewer* p_imageViewer,int p_width,int p_hieght, QLayout* p_layersGUIElementsLayout)
	: m_imageViewer(p_imageViewer), m_width(p_width),m_hieght(p_hieght)
{
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


ImageViewer* EPProject::getImageViewer()
{
	return m_imageViewer;
}


//TODO : the render function should be implemented and this code should be replaced
void EPProject::render()
{
	if (m_currentLayer < 0 || m_layers.size() == 0)
		return;

	m_renderedImage = m_layers.at(m_currentLayer)->getRenderedImage().clone();

	m_imageViewer->updateImage(&m_renderedImage);
}


void EPProject::importAsNewLayer(cv::Mat p_img)
{
	Layer* newLayer = new Layer(m_width, m_hieght);
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


