#include "Manager.h"
#include "Vectors.h"
Manager::Manager(EP::Vector2 p_size,QLayout* p_layersGUILayout,QLayout* p_canvasViewLayout,QPushButton* p_createLayerButton)
{
	m_size = p_size;
	m_epproject = new EPProject(p_size);
	p_canvasViewLayout->addWidget(m_epproject->getCanvasView());
	connect(p_createLayerButton,&QPushButton::clicked,m_epproject,&EPProject::createEmptyLayer);
	m_layersGUIManager = new LayersGUIManager(p_layersGUILayout, m_epproject);
	m_epproject->importAsNewLayer(cv::imread("C:\\Users\\TMAX27\\Desktop\\test2.png"));
	m_epproject->importAsNewLayer(cv::imread("C:\\Users\\TMAX27\\Desktop\\test.png"));
	//m_layersGUIManager->reloadUI();
}

Manager::~Manager()
{
	delete m_layersGUIManager;
	delete m_epproject;
}

LayersGUIManager* Manager::getLayersGUIManager()
{
	return m_layersGUIManager;
}

EPProject* Manager::getEPProject()
{
	return m_epproject;
}
