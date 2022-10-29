#include "LayersGUIManager.h"



LayersGUIManager::LayersGUIManager(QLayout* p_layout,std::vector<Layer*> p_layers) : m_layout(p_layout)
{
	reloadUI(p_layers);
}

void LayersGUIManager::reloadUI(std::vector<Layer*> p_layers)
{
  //deleting old elements
		for (auto& element : m_layerGUIElements)
		{
			m_layout->removeWidget(element->getMainWidget());
			delete element;
		}

	
		m_layerGUIElements.clear();
			for (auto& layer : p_layers)
			{
				LayerGUIElement* element = new LayerGUIElement(layer);
				m_layerGUIElements.push_back(element);
				m_layout->addWidget(element->getMainWidget());
			}

}