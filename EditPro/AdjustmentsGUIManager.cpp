#include "AdjustmentsGUIManager.h"



AdjustmentsGUIManager::AdjustmentsGUIManager(EPProject* p_epproject, MainWindow* p_mainWindow)
{
	//basic setup stuff

	m_epproject = p_epproject;

	
	m_contrastSlider = p_mainWindow->getUI()->contrastSlider;
	m_exposureSlider = p_mainWindow->getUI()->exposureSlider;
	m_hueSlider = p_mainWindow->getUI()->hueSlider;
	m_saturationSlider = p_mainWindow->getUI()->saturationSlider;
	m_valueSlider = p_mainWindow->getUI()->valueSlider;

	connect(p_mainWindow->getUI()->applyContrastButton, &QPushButton::clicked, this, &AdjustmentsGUIManager::adjustContrast);
	connect(p_mainWindow->getUI()->applyExposureButton, &QPushButton::clicked, this, &AdjustmentsGUIManager::adjustExposure);
	connect(p_mainWindow->getUI()->applyHSVButton, &QPushButton::clicked, this, &AdjustmentsGUIManager::adjustHSV);
}


AdjustmentsGUIManager::~AdjustmentsGUIManager()
{

}

void AdjustmentsGUIManager::adjustContrast()
{
	m_epproject->getSelectedLayer()->adjustContrast((float)m_contrastSlider->value() / 100);
	m_epproject->render();
}

void AdjustmentsGUIManager::adjustExposure()
{
	m_epproject->getSelectedLayer()->adjustExposure((float)m_exposureSlider->value() / 100);
	m_epproject->render();
}

void AdjustmentsGUIManager::adjustHSV()
{
	m_epproject->getSelectedLayer()->adjustHue((float)m_hueSlider->value() / 1000);
	m_epproject->getSelectedLayer()->adjustSaturation((float)m_saturationSlider->value() / 1000);
	m_epproject->getSelectedLayer()->adjustValue((float)m_valueSlider->value() / 1000);
	m_epproject->render();
}

