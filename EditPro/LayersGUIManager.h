#pragma once

#include <iostream>
#include <qwidget.h>
#include "Layer.h"
#include "LayerGUIElement.h"
#include <qlayout.h>
#include "EPProject.h"

class LayersGUIManager : public QObject
{

	Q_OBJECT

public:
	LayersGUIManager(QLayout* p_layout,EPProject* p_epproject);

	void reloadUI();

private:
	//this is the layout where all the ui elements should added to
	QLayout* m_layout;
	EPProject* m_epproject;
	std::vector<LayerGUIElement*> m_layerGUIElements;

};