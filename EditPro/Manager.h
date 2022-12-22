#pragma once

#include "LayersGUIManager.h"
#include "EPProject.h"
#include "Vectors.h"
#include "MainWindow.h"
#include "EffectsGUIManager.h"
#include "AdjustmentsGUIManager.h"
#include "ToolsManager.h"

/// <summary>
/// The Manager class works like a linker that links between logic side and gui side
/// </summary>
class Manager : public QObject
{
	Q_OBJECT
public :
	Manager(EP::Vector2 p_size, MainWindow* p_mainWindow);
	~Manager();

	LayersGUIManager* getLayersGUIManager();
	EPProject* getEPProject();

private slots:
	void onCanvasMousePress(QMouseEvent* event);
	void onCanvasMouseRelease(QMouseEvent* event);
	void onCanvasMouseDrag(QMouseEvent* event);
	void onCanvasMouseWheel(QWheelEvent* event);
private :
	LayersGUIManager* m_layersGUIManager;
	ToolsManager* m_toolsManager;
	EPProject* m_epproject;
	EffectsGUIManager* m_effectsGUIManager;
	AdjustmentsGUIManager* m_adjustmentsGUIManager;
	EP::Vector2 m_size;

};