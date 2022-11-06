#pragma once


#include <qwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include "Layer.h"
class LayerGUIElement : public QObject
{
	Q_OBJECT
public :
	LayerGUIElement(Layer* p_connectedLayer);
	~LayerGUIElement();
	QWidget* getMainWidget();

signals:
	void layerStatusUpdated();
	void layerUp(Layer* p_layer);
	void layerDown(Layer* p_layer);
	void deleteLayer(Layer* p_layer);
public slots:
	void onLayerUpCliked();
	void onLayerDownCliked();
	void layerRename(QString p_name);
	void onLayerShowHideCliked();
	void onDeleteLayerButtonCliked();

private : 
	Layer* m_connectedLayer;
	QWidget* m_mainWidget;
	QLineEdit* m_layerNameLineEdit;
	QPushButton* m_upButton;
	QPushButton* m_downButton;
	QVBoxLayout* m_layout;
	QPushButton* m_showHideButton;
	QPushButton* m_deleteButton;
};