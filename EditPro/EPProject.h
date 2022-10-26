#pragma once
#include <opencv2/opencv.hpp>
#include "ImageViewer.h"
#include <iostream>
#include "Layer.h"
// Quick note : EPProject stands for Edit Pro Project :)

class EPProject
{
public:

	EPProject(ImageViewer* p_imageViewer,int p_width,int p_hieght);
	~EPProject();

	cv::Mat getRenderedImage();
	ImageViewer* getImageViewer();

	//TODO : implement the render and export functions
	void render();

	void importAsNewLayer(cv::Mat p_img);
	void importToCurrentLayer(cv::Mat p_img);

private :
	ImageViewer* m_imageViewer;
	cv::Mat m_renderedImage;
	std::vector<Layer*> m_layers;
	int m_width, m_hieght;
	int m_currentLayer = 0;
};