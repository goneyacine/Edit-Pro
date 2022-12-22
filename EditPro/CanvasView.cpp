#include "CanvasView.h"

#include <opencv2/opencv.hpp>
#include <qlayout.h>
#include <chrono>
#include <qdebug.h>
CanvasView::CanvasView(QWidget* parent, int p_width, int p_height) :
	m_width(p_width), m_height(p_height)
{
	m_canvasImage = new QImage(m_width,m_height,QImage::Format_RGB888);
	m_canvasImage->fill(Qt::black);
	setMouseTracking(true);
	g_xOffset = this->width() / 2;
	g_yOffset = this->height() / 2;
}



CanvasView::~CanvasView()
{

}
/*
void CanvasView::setToolsManager(ToolsManager* p_toolsManager)
{
	m_toolsManager = p_toolsManager;
}
*/
void CanvasView::updateCanvas(cv::Mat p_img)
{

	if(m_canvasImage == NULL)
		m_canvasImage = new QImage(m_width, m_height, QImage::Format_RGB888);


	m_canvasImage->fill(Qt::white);


    //converting OpenCV Mat (p_img) into QImage (m_canvasImage) to be displayed in screen
	cv::Vec3b color;
	QColor qcolor;
	for (int y = 0; y < p_img.rows; y++)
	{
		for (int x = 0; x < p_img.cols; x++)
		{
			color = p_img.at<cv::Vec3b>(y, x);

			qcolor.setRgb(color[2], color[1], color[0]);

			m_canvasImage->setPixelColor(x, y, qcolor);


		}
	}
	//calling update (it's a QWidget function) function to call paint event
	update();

}


void CanvasView::paintEvent(QPaintEvent* event)
{

	QPainter painter(this);
	painter.fillRect(QRect(0, 0, width(), height()), QColor(80, 80, 80));
	painter.drawImage(QRect(g_xOffset - (m_width / 2), g_yOffset - (m_height / 2),
		m_width * ((float)g_zoom / 100), m_height * ((float)g_zoom / 100))
		, *m_canvasImage);

}

void CanvasView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = QCursor::pos().x();
		old_cursor_y = QCursor::pos().y();
		m_mouseRightButtonIsPressed = true;
	}
	else if (event->button() == Qt::LeftButton)
	{
		m_mouseLeftButtonIsPressed = true;
	}
	
	emit onMousePress(event);
	//m_toolsManager->getSelectedTool()->onMousePress(event, EP::Vector2((old_cursor_x - m_xOffset) * ((float)m_zoom / 100),
	//	(old_cursor_y - m_yOffset) * ((float)m_zoom / 100)));
}
void CanvasView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = -1;
		old_cursor_y = -1;
		m_mouseRightButtonIsPressed = false;
	}
	else if (event->button() == Qt::LeftButton)
	{
		m_mouseLeftButtonIsPressed = false;
	}
	emit onMouseRelease(event);
	//m_toolsManager->getSelectedTool()->onMouseRelease(event, EP::Vector2((old_cursor_x - m_xOffset) * ((float)m_zoom / 100),
		//(old_cursor_y - m_yOffset) * ((float)m_zoom / 100)));

}
void CanvasView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_mouseRightButtonIsPressed)
	{
		g_xOffset += (QCursor::pos().x() - old_cursor_x);
		g_yOffset += (QCursor::pos().y() - old_cursor_y);

		old_cursor_x = QCursor::pos().x();
		old_cursor_y = QCursor::pos().y();
		update();
	}
	
	if (m_mouseLeftButtonIsPressed)
		emit onMouseDrag(event);
		//m_toolsManager->getSelectedTool()->onMouseDrag(event, EP::Vector2((old_cursor_x - m_xOffset) * ((float)m_zoom / 100),
		//	(old_cursor_y - m_yOffset) * ((float)m_zoom / 100)));

}

void CanvasView::wheelEvent(QWheelEvent* event) 
{
	if (event->angleDelta().y() > 0)
	{
		if (g_zoom + 25 <= 500)
		{
			g_zoom += 25;
			update();
		}
	}
	else
	{
		if (g_zoom - 25 >= 25)
		{
			g_zoom -= 25;
			update();
		}
	}
	emit onMouseWheel(event);
	//m_toolsManager->getSelectedTool()->onMouseWheel(event);
}
