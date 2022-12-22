#pragma once

#include <qlabel.h>
#include <qpainter.h>
#include <opencv2/opencv.hpp>
#include <qevent.h>
//#include "ToolsManager.h"
class CanvasView  : public QWidget
{
	Q_OBJECT

public :
	CanvasView(QWidget* parent,int p_width,int p_height);
	~CanvasView();
	void updateCanvas(cv::Mat p_img);
	//void setToolsManager(ToolsManager* p_toolsManager);
	//canvas view offset
	int g_xOffset = 0;
	int g_yOffset = 0;

	//zoom value (the default value is %100)
	int g_zoom = 100;


signals :
	void onMousePress(QMouseEvent* event);
	void onMouseRelease(QMouseEvent* event);
	void onMouseWheel(QWheelEvent* event);
	void onMouseDrag(QMouseEvent* event);

protected :
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
private :
	//the image rendered by epproject is converted into a pixmap & it's called m_canvasPixmap
	QImage* m_canvasImage;
	//canvas size
	int m_width;
	int m_height;

	//these are the old coordinates of the cursor
	int old_cursor_x = -1;
	int old_cursor_y = -1;

	bool m_mouseRightButtonIsPressed = false;
	bool m_mouseLeftButtonIsPressed = false;

	//ToolsManager* m_toolsManager;
};
