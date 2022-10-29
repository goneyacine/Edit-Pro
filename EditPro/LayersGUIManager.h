#pragma once

#include <iostream>
#include <qwidget.h>
#include "Layer.h"
#include "LayerGUIElement.h"
#include <qlayout.h>

class LayersGUIManager
{
public :
	LayersGUIManager(QLayout* p_layout,std::vector<Layer*> p_layers);

	void reloadUI(std::vector<Layer*> p_layers);


private :
	//this is the layout where all the ui elements should added to
	QLayout* m_layout;
	std::vector<LayerGUIElement*> m_layerGUIElements;
};