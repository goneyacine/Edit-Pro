#include "CanvasView.h"

#include <opencv2/opencv.hpp>
#include <qlayout.h>
#include <chrono>
#include <qdebug.h>
CanvasView::CanvasView(QWidget* parent,int p_width,int p_height) : m_width(p_width),m_height(p_height)
{
	m_canvasImage = new QImage(m_width,m_height,QImage::Format_RGB888);
	m_canvasImage->fill(Qt::black);
	setMouseTracking(true);
	m_xOffset = this->width() / 2;
	m_yOffset = this->height() / 2;
}



CanvasView::~CanvasView()
{

}
void CanvasView::updateCanvas(cv::Mat p_img)
{
	auto startTime = std::chrono::high_resolution_clock::now();

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

    double functionDuration =  1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Update Canvas Toke " << functionDuration << "ms to colmplete";
}


void CanvasView::paintEvent(QPaintEvent* event)
{
	auto startTime = std::chrono::high_resolution_clock::now();


	QPainter painter(this);
	painter.fillRect(QRect(0, 0, width(), height()), QColor(80, 80, 80));
	painter.drawImage(QRect(m_xOffset - (m_width / 2), m_yOffset - (m_height / 2),
		m_width * ((float)m_zoom / 100), m_height * ((float)m_zoom / 100))
		, *m_canvasImage);

	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Canvas Paint Toke " << functionDuration << "ms to colmplete";
}

void CanvasView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = QCursor::pos().x();
		old_cursor_y = QCursor::pos().y();
		mouseRightButtonIsPressed = true;
	}
}
void CanvasView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		old_cursor_x = -1;
		old_cursor_y = -1;
		mouseRightButtonIsPressed = false;
	}
}
void CanvasView::mouseMoveEvent(QMouseEvent* event)
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

void CanvasView::wheelEvent(QWheelEvent* event) 
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
