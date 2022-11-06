#include "LayerGUIElement.h"
#include <qlayout.h>

LayerGUIElement::LayerGUIElement(Layer* p_connectedLayer) :
	m_connectedLayer(p_connectedLayer)
{

	m_mainWidget = new QWidget();
	m_layout = new QVBoxLayout;


	m_mainWidget->setMaximumSize(200, 140);
	m_mainWidget->setMinimumSize(150, 140);

	m_layerNameLineEdit = new QLineEdit();
	m_upButton = new QPushButton();
	m_downButton = new QPushButton();
	m_showHideButton = new QPushButton();

	m_layerNameLineEdit->setText(m_connectedLayer->getName());
	m_upButton->setText("Up");
	m_downButton->setText("Down");

	if (m_connectedLayer->isVisible())
		m_showHideButton->setText("Hide");
	else
		m_showHideButton->setText("Show");


	m_layout->addWidget(m_layerNameLineEdit);
	m_layout->addWidget(m_upButton);
	m_layout->addWidget(m_downButton);
	m_layout->addWidget(m_showHideButton);

	m_mainWidget->setLayout(m_layout);


	connect(m_upButton, &QPushButton::clicked, this, &LayerGUIElement::onLayerUpCliked);
	connect(m_downButton, &QPushButton::clicked, this, &LayerGUIElement::onLayerDownCliked);
	connect(m_showHideButton, &QPushButton::clicked, this, &LayerGUIElement::onLayerShowHideCliked);
	connect(m_layerNameLineEdit, &QLineEdit::textEdited,this, &LayerGUIElement::layerRename);

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

void LayerGUIElement::onLayerUpCliked()
{
	emit layerUp(m_connectedLayer);
}
void LayerGUIElement::onLayerDownCliked()
{
	emit layerDown(m_connectedLayer);
}

void LayerGUIElement::layerRename(QString p_name)
{
	m_connectedLayer->setName(p_name);
}

void LayerGUIElement::onLayerShowHideCliked()
{
	m_connectedLayer->setVisible(!(m_connectedLayer->isVisible()));

	if (m_connectedLayer->isVisible())
		m_showHideButton->setText("Hide");
	else
		m_showHideButton->setText("Show");

	emit layerStatusUpdated();
}




