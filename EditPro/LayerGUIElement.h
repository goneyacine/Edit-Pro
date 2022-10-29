#pragma once


#include <qwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include "Layer.h"
class LayerGUIElement
{

public :
	LayerGUIElement(Layer* p_connectedLayer);
	~LayerGUIElement();
	QWidget* getMainWidget();
private : 
	Layer* m_connectedLayer;
	QWidget* m_mainWidget;
	QLineEdit* m_layerNameLineEdit;
	QPushButton* m_upButton;
	QPushButton* m_downButton;
	QVBoxLayout* m_layout;
	QPushButton* m_showHideButton;
};