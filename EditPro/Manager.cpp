#include "Manager.h"
#include "Vectors.h"
Manager::Manager(EP::Vector2 p_size,MainWindow* p_mainWindow)
{
	m_size = p_size;

	m_epproject = new EPProject(p_size);
	m_toolsManager = new ToolsManager(m_epproject);
	//m_epproject->getCanvasView()->setToolsManager(m_toolsManager);

	p_mainWindow->getUI()->canvasLayout->addWidget(m_epproject->getCanvasView());

	m_layersGUIManager = new LayersGUIManager(p_mainWindow->getUI()->layersGUIElementPanel->layout(), m_epproject);
	m_effectsGUIManager = new EffectsGUIManager(m_epproject, p_mainWindow);
	m_adjustmentsGUIManager = new AdjustmentsGUIManager(m_epproject, p_mainWindow);

	
	connect(m_epproject->getCanvasView(), &CanvasView::onMousePress, this, &Manager::onCanvasMousePress);
	connect(m_epproject->getCanvasView(), &CanvasView::onMouseRelease, this, &Manager::onCanvasMouseRelease);
	connect(m_epproject->getCanvasView(), &CanvasView::onMouseDrag, this, &Manager::onCanvasMouseDrag);
	connect(m_epproject->getCanvasView(), &CanvasView::onMouseWheel, this, &Manager::onCanvasMouseWheel);

	
	connect(p_mainWindow->getUI()->createLayerButton, &QPushButton::clicked, m_epproject, &EPProject::createEmptyLayer);
	connect(p_mainWindow, &MainWindow::importFile, m_epproject, &EPProject::importFile);
}

Manager::~Manager()
{
	delete m_layersGUIManager;
	delete m_epproject;
	delete m_effectsGUIManager;
	delete m_adjustmentsGUIManager;
}

LayersGUIManager* Manager::getLayersGUIManager()
{
	return m_layersGUIManager;
}

EPProject* Manager::getEPProject()
{
	return m_epproject;
}


void Manager::onCanvasMousePress(QMouseEvent* event)
{
	qDebug() << "Mouse Press Test Is Working";
}

void Manager::onCanvasMouseRelease(QMouseEvent* event)
{
	qDebug() << "Mouse Release Test Is Working";
}

void Manager::onCanvasMouseDrag(QMouseEvent* event)
{
	qDebug() << "Mouse Drag Test Is Working";
}


void Manager::onCanvasMouseWheel(QWheelEvent* event)
{
	qDebug() << "Mouse Wheel Test Is Working";
}