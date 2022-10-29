#include "LayerGUIElement.h"
#include <qlayout.h>

LayerGUIElement::LayerGUIElement(Layer* p_connectedLayer) : m_connectedLayer(p_connectedLayer)
{
	m_mainWidget = new QWidget();
	m_layout = new QVBoxLayout;


	m_mainWidget->setMaximumSize(200, 100);
	m_mainWidget->setMinimumSize(150, 100);



	m_layerNameLineEdit = new QLineEdit();
	m_upButton = new QPushButton();
	m_downButton = new QPushButton();
	m_showHideButton = new QPushButton();

	m_layout->addWidget(m_layerNameLineEdit);
	m_layout->addWidget(m_upButton);
	m_layout->addWidget(m_downButton);
	m_layout->addWidget(m_showHideButton);

	m_mainWidget->setLayout(m_layout);
}
LayerGUIElement::~LayerGUIElement()
{
	delete m_layerNameLineEdit;
	delete m_upButton;
	delete m_downButton;
	delete m_showHideButton;
	delete m_layout;
}

QWidget* LayerGUIElement::getMainWidget()
{
	return m_mainWidget;
}


