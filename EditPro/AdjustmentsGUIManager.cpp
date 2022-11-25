#include "AdjustmentsGUIManager.h"



AdjustmentsGUIManager::AdjustmentsGUIManager(EPProject* p_epproject, MainWindow* p_mainWindow)
{
	//basic setup stuff

	m_epproject = p_epproject;

	
	m_contrastSlider = p_mainWindow->getUI()->contrastSlider;
	m_hueSlider = p_mainWindow->getUI()->hueSlider;
	m_saturationSlider = p_mainWindow->getUI()->saturationSlider;
	m_valueSlider = p_mainWindow->getUI()->valueSlider;

	connect(p_mainWindow->getUI()->applyContrastButton, &QPushButton::clicked, this, &AdjustmentsGUIManager::adjustContrast);
	connect(p_mainWindow->getUI()->applyHSVButton, &QPushButton::clicked, this, &AdjustmentsGUIManager::adjustHSV);
}


AdjustmentsGUIManager::~AdjustmentsGUIManager()
{

}

void AdjustmentsGUIManager::adjustContrast()
{
	m_epproject->getSelectedLayer()->autoContrast();
	m_epproject->render();
}

void AdjustmentsGUIManager::adjustHSV()
{
	m_epproject->getSelectedLayer()->adjustHue(m_hueSlider->value());
	m_epproject->getSelectedLayer()->adjustSaturation(m_saturationSlider->value());
	m_epproject->getSelectedLayer()->adjustValue(m_valueSlider->value());
	m_epproject->render();
}

