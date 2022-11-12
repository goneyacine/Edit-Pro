#pragma once

#include "LayersGUIManager.h"
#include "EPProject.h"
#include "Vectors.h"
#include "MainWindow.h"
#include "EffectsGUIManager.h"
/// <summary>
/// The Manager class works like a linker that links between logic side and gui side
/// </summary>
class Manager : QObject
{
	Q_OBJECT
public :
	Manager(EP::Vector2 p_size, MainWindow* p_mainWindow);
	~Manager();

	LayersGUIManager* getLayersGUIManager();
	EPProject* getEPProject();

private :
	LayersGUIManager* m_layersGUIManager;
	EPProject* m_epproject;
	EffectsGUIManager* m_effectsGUIManager;
	EP::Vector2 m_size;

};