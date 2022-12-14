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
	if (event->button() == Qt::LeftButton)
	{
		m_toolsManager->getSelectedTool()->onMousePress
		(event, EP::Vector2(
			/*
			(float)((QCursor::pos().x() - m_epproject->getCanvasView()->g_xOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) ,
			(float)((QCursor::pos().y() - m_epproject->getCanvasView()->g_yOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) )
			*/
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).x() - (m_epproject->getCanvasView()->g_xOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100),
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).y() - (m_epproject->getCanvasView()->g_yOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100)
		));
	}
}
void Manager::onCanvasMouseRelease(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_toolsManager->getSelectedTool()->onMouseRelease
		(event, EP::Vector2(
			/*
			(float)((QCursor::pos().x() - m_epproject->getCanvasView()->g_xOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) ,
			(float)((QCursor::pos().y() - m_epproject->getCanvasView()->g_yOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) )
			*/
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).x() - (m_epproject->getCanvasView()->g_xOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100),
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).y() - (m_epproject->getCanvasView()->g_yOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100)
		));
	}
}

void Manager::onCanvasMouseDrag(QMouseEvent* event)
{

	m_toolsManager->getSelectedTool()->onMouseDrag(
		event, EP::Vector2(
			/*
			(float)((QCursor::pos().x() - m_epproject->getCanvasView()->g_xOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) ,
			(float)((QCursor::pos().y() - m_epproject->getCanvasView()->g_yOffset)) / ((float)m_epproject->getCanvasView()->g_zoom / 100) )
			*/
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).x() - (m_epproject->getCanvasView()->g_xOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100),
			(m_epproject->getCanvasView()->mapFromGlobal(QCursor::pos()).y() - (m_epproject->getCanvasView()->g_yOffset * ((float)m_epproject->getCanvasView()->g_zoom / 100))) / ((float)m_epproject->getCanvasView()->g_zoom / 100)
		));
}


void Manager::onCanvasMouseWheel(QWheelEvent* event)
{
	m_toolsManager->getSelectedTool()->onMouseWheel(event);
}