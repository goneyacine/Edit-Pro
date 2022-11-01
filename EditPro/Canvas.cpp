#include "Canvas.h"

#include <opencv2/opencv.hpp>
#include <qlayout.h>

Canvas::Canvas(QWidget* parent,int p_width,int p_height) : m_width(p_width),m_height(p_height)
{
	m_canvasImage = new QImage(m_width,m_height,QImage::Format_RGB888);
	m_canvasImage->fill(Qt::black);
	setMouseTracking(true);
	m_xOffset = this->width() / 2;
	m_yOffset = this->height() / 2;
}



Canvas::~Canvas()
{

}
void Canvas::updateCanvas(cv::Mat p_img)
{
	if(m_canvasImage == NULL)
		m_canvasImage = new QImage(m_width, m_height, QImage::Format_RGB888);


	m_canvasImage->fill(Qt::white);


	//swaping the red and blue values to convert the format from BGR (used by opencv) to RGB (used by qt)

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

}


void Canvas::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(QRect(0, 0, width(), height()), QColor(80, 80, 80));
	painter.drawImage(QRect(m_xOffset - (m_width / 2), m_yOffset - (m_height / 2),
		m_width * ((float)m_zoom / 100), m_height * ((float)m_zoom / 100))
		, *m_canvasImage);
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = QCursor::pos().x();
		old_cursor_y = QCursor::pos().y();
		mouseRightButtonIsPressed = true;
	}
}
void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = -1;
		old_cursor_y = -1;
		mouseRightButtonIsPressed = false;
	}
}
void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (mouseRightButtonIsPressed)
	{
		m_xOffset += (QCursor::pos().x() - old_cursor_x);
		m_yOffset += (QCursor::pos().y() - old_cursor_y);

		old_cursor_x = QCursor::pos().x();
		old_cursor_y = QCursor::pos().y();
		update();
	}
}

void Canvas::wheelEvent(QWheelEvent* event) 
{
	if (event->angleDelta().y() > 0)
	{
		if (m_zoom + 25 <= 500)
		{
			m_zoom += 25;
			update();
		}
	}
	else
	{
		if (m_zoom - 25 >= 25)
		{
			m_zoom -= 25;
			update();
		}
	}
}
