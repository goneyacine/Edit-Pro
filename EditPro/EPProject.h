#pragma once
#include <opencv2/opencv.hpp>
#include "CanvasView.h"
#include <iostream>
#include "Layer.h"
#include <qlayout.h>
#include "Vectors.h"
// Quick note : EPProject stands for Edit Pro Project
class EPProject : public QObject
{
	Q_OBJECT
public:

	EPProject(EP::Vector2 p_size);
	~EPProject();

	cv::Mat getRenderedImage();
	CanvasView* getCanvasView();

	//TODO : implement the render and export functions
	void render();
	EP::Vector2 getSize();
	void importAsNewLayer(cv::Mat p_img);
	void importToCurrentLayer(cv::Mat p_img);
	std::vector<Layer*>* getLayers();
	void createEmptyLayer();
signals:
	void layersUpdated();
public slots:
	void layerUp(Layer* p_layer);
	void layerDown (Layer* p_layer);
	void deleteLayer(Layer* p_layer);

private :
	CanvasView* m_canvas;
	cv::Mat m_renderedImage;
	std::vector<Layer*> m_layers;
	EP::Vector2 m_size;
	int m_currentLayer = -1;
};