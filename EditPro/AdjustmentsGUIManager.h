#pragma once

#include "MainWindow.h"
#include "EPProject.h"

class AdjustmentsGUIManager : public QObject
{
	Q_OBJECT

public :
	AdjustmentsGUIManager(EPProject* p_epproject, MainWindow* p_mainWindow);
	~AdjustmentsGUIManager();

public slots:
	void adjustContrast();
	void adjustExposure();
	void adjustHSV();


private:

	EPProject* m_epproject;

	QSlider* m_contrastSlider;
	QSlider* m_exposureSlider;
	QSlider* m_hueSlider;
	QSlider* m_saturationSlider;
	QSlider* m_valueSlider;
};