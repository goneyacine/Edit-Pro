#include "LayersGUIManager.h"



LayersGUIManager::LayersGUIManager(QLayout* p_layout,EPProject* p_epproject) :
	m_layout(p_layout), m_epproject(p_epproject)
{
	connect(m_epproject, &EPProject::layersUpdated, this, &LayersGUIManager::reloadUI);
	reloadUI();
}

void LayersGUIManager::reloadUI()
{
	//deleting old elements
	for (auto& element : m_layerGUIElements)
	{
		m_layout->removeWidget(element->getMainWidget());
		delete element;
	}

	m_layerGUIElements.clear();


	for (int i = m_epproject->getLayers()->size() - 1; i >= 0; i--)
	{
		LayerGUIElement* element = new LayerGUIElement(m_epproject->getLayers()->at(i));
		//the "layerStatusUpdated" signal is emitted whenever the user changes the visibility of the layer (Show/Hide)
		connect(element, &LayerGUIElement::layerStatusUpdated, m_epproject, &EPProject::render);

		connect(element, &LayerGUIElement::layerUp, m_epproject, &EPProject::layerUp);
		connect(element, &LayerGUIElement::layerDown, m_epproject, &EPProject::layerDown);
		connect(element, &LayerGUIElement::deleteLayer, m_epproject, &EPProject::deleteLayer);
		m_layerGUIElements.push_back(element);
		m_layout->addWidget(element->getMainWidget());
	}

}
