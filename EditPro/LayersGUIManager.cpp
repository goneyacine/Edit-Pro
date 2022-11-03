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
			for (auto& layer : *m_epproject->getLayers())
			{
				LayerGUIElement* element = new LayerGUIElement(layer);
				connect(element, SIGNAL(update()), this, SLOT(onUpdate()));
				m_layerGUIElements.push_back(element);
				m_layout->addWidget(element->getMainWidget());
			}

}
