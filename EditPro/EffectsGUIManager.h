#pragma once
#include "EPProject.h"
#include "MainWindow.h"

class EffectsGUIManager : public QObject
{
	Q_OBJECT

public:
	EffectsGUIManager(EPProject* p_epproject,MainWindow* p_mainWindow);
	~EffectsGUIManager();


public slots:
	void applyRandomNoise();
	void applyWaveEffect();
	void applyGaussianBlur();
private :

	EPProject* m_epproject;

	//random noise inputs
	QSpinBox* m_randomNoiseIntensitySpinBox;
	QSpinBox* m_randomNoiseOpacitySpinBox;

	//wave effect inputs
	QSpinBox* m_waveEffectHorizontalIntensitySpingBox;
	QSpinBox* m_waveEffectHorizontalFrequencySpingBox;
	QSpinBox* m_waveEffectVerticalIntensitySpingBox;
	QSpinBox* m_waveEffectVerticalFrequencySpingBox;

    //gaussian blur inputs
	QSpinBox* m_gaussianBlurHorizontalSizeSpinBox;
	QSpinBox* m_gaussianBlurVerticalSizeSpinBox;

};
