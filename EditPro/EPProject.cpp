#include "EPProject.h"


EPProject::EPProject(ImageViewer* p_imageViewer,int p_width,int p_hieght) 
	: m_imageViewer(p_imageViewer), m_width(p_width),m_hieght(p_hieght)
{
	Layer* backgroundLayer = new Layer(p_width,p_hieght);
	m_layers.push_back(backgroundLayer);
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
}

void EPProject::importToCurrentLayer(cv::Mat p_img)
{
	m_layers.at(m_currentLayer)->import(p_img);
	render();
}


