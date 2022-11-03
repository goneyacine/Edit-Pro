#pragma once

#include "LayersGUIManager.h"
#include "EPProject.h"
#include "Vectors.h"
/// <summary>
/// The Manager class works like a linker that links between logic side and gui side
/// </summary>
class Manager
{
public :
	Manager(EP::Vector2 p_size, QLayout* p_layersGUILayout, QLayout* p_canvasViewLayout);
	~Manager();

	LayersGUIManager* getLayersGUIManager();
	EPProject* getEPProject();

private :
	LayersGUIManager* m_layersGUIManager;
	EPProject* m_epproject;
	EP::Vector2 m_size;

};