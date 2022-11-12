#include "EffectsGUIManager.h"


EffectsGUIManager::EffectsGUIManager(EPProject* p_epproject, MainWindow* p_mainWindow)
{

	//basic setup
	m_epproject = p_epproject;
    
	 //random noise stuff
	m_randomNoiseIntensitySpinBox = p_mainWindow->getUI()->randomNoiseIntensity;
	m_randomNoiseOpacitySpinBox = p_mainWindow->getUI()->randomNoiseOpacity;
     //wave effect stuff
	m_waveEffectHorizontalIntensitySpingBox = p_mainWindow->getUI()->waveEffectXIntensity;
	m_waveEffectHorizontalFrequencySpingBox = p_mainWindow->getUI()->waveEffectXFrequency;

	m_waveEffectVerticalIntensitySpingBox = p_mainWindow->getUI()->waveEffectVerticalIntensity;
	m_waveEffectVerticalFrequencySpingBox = p_mainWindow->getUI()->waveEffectVerticalFrequency;

	//gaussian blur stuff
	m_gaussianBlurHorizontalSizeSpinBox = p_mainWindow->getUI()->gaussianBlurXSize;
	m_gaussianBlurVerticalSizeSpinBox = p_mainWindow->getUI()->gaussianBlurYSize;

	//connecting the effects apply buttons
	connect(p_mainWindow->getUI()->randomNoiseApplyButton, &QPushButton::clicked, this, &EffectsGUIManager::applyRandomNoise);
	connect(p_mainWindow->getUI()->waveEffectApplyButton, &QPushButton::clicked, this, &EffectsGUIManager::applyWaveEffect);
	connect(p_mainWindow->getUI()->gaussianBlurApplyButton, &QPushButton::clicked, this, &EffectsGUIManager::applyGaussianBlur);

}
EffectsGUIManager::~EffectsGUIManager()
{

}


void EffectsGUIManager::applyRandomNoise()
{
	//checking if there is a selected layer
	if (m_epproject->getSelectedLayer() == NULL)
		return;

	//reading user inputs
	int intensity = m_randomNoiseIntensitySpinBox->value();
	int opacity = m_randomNoiseOpacitySpinBox->value();
	//applying noise effect to the selected layer
	m_epproject->getSelectedLayer()->applyRandomNoise(intensity, opacity);
	//calling the render function to refresh the canvas
	m_epproject->render();
}

void EffectsGUIManager::applyWaveEffect()
{
	//checking if there is a selected layer
	if (m_epproject->getSelectedLayer() == NULL)
		return;

	//reading user inputs
	int horizontalIntensity = m_waveEffectHorizontalIntensitySpingBox->value();
	int horizontalFrequency = m_waveEffectHorizontalFrequencySpingBox->value();

	int verticalIntensity = m_waveEffectVerticalIntensitySpingBox->value();
	int verticalFrequency = m_waveEffectVerticalFrequencySpingBox->value();
	//applying wave effect to the selected layer
	m_epproject->getSelectedLayer()->applyWave(horizontalIntensity, verticalIntensity, horizontalFrequency, verticalFrequency);
	//calling the render function to refresh the canvas
	m_epproject->render();
}

void EffectsGUIManager::applyGaussianBlur()
{
	//checking if there is a selected layer
	if (m_epproject->getSelectedLayer() == NULL)
		return;

	//reading user inputs
	int horizontalSize = m_gaussianBlurHorizontalSizeSpinBox->value();
	int verticalSize = m_gaussianBlurVerticalSizeSpinBox->value();
	//applying gaussian blur effect to the selected layer
	m_epproject->getSelectedLayer()->applyGaussianBlur(horizontalSize, verticalSize);
	//calling the render function to refresh the canvas
	m_epproject->render();
}


