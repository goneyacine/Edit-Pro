#include "Manager.h"
#include "Vectors.h"
Manager::Manager(EP::Vector2 p_size,MainWindow* p_mainWindow)
{
	m_size = p_size;
	m_epproject = new EPProject(p_size);
	p_mainWindow->getUI()->canvasLayout->addWidget(m_epproject->getCanvasView());
	connect(p_mainWindow, &MainWindow::importFile, m_epproject, &EPProject::importFile);
	connect(p_mainWindow->getUI()->createLayerButton, &QPushButton::clicked, m_epproject, &EPProject::createEmptyLayer);
	m_layersGUIManager = new LayersGUIManager(p_mainWindow->getUI()->layersGUIElementPanel->layout(), m_epproject);
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
