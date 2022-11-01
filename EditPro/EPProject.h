#pragma once
#include <opencv2/opencv.hpp>
#include "Canvas.h"
#include <iostream>
#include "Layer.h"
#include <qlayout.h>
#include "LayersGUIManager.h"

// Quick note : EPProject stands for Edit Pro Project :)
class EPProject
{
public:

	EPProject(int p_width,int p_hieght,QLayout* p_layersGUIElementsLayout);
	~EPProject();

	cv::Mat getRenderedImage();
	Canvas* getCanvas();

	//TODO : implement the render and export functions
	void render();

	void importAsNewLayer(cv::Mat p_img);
	void importToCurrentLayer(cv::Mat p_img);

private :
	Canvas* m_canvas;
	cv::Mat m_renderedImage;
	std::vector<Layer*> m_layers;
	int m_width, m_hieght;
	int m_currentLayer = -1;
	LayersGUIManager* m_layersGUIManager;
};