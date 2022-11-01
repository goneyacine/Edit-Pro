#pragma once

#include <qlabel.h>
#include <qpainter.h>
#include <opencv2/opencv.hpp>
#include <qevent.h>

class Canvas  : public QWidget
{
	Q_OBJECT

public :
	Canvas(QWidget* parent,int p_width,int p_height);
	~Canvas();
	void updateCanvas(cv::Mat p_img);

protected :
	void paintEvent(QPaintEvent* event) override;
private :
	//the image rendered by epproject is converted into a pixmap & it's called m_canvasPixmap
	QImage* m_canvasImage;
	//canvas size
	int m_width;
	int m_height;
	//canvas view offset
	int m_xOffset = 0;
	int m_yOffset = 0;

	//zoom value (the default value is %100)
	int m_zoom = 100;
};
