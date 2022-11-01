#include "Canvas.h"

#include <opencv2/opencv.hpp>
#include <qlayout.h>

Canvas::Canvas(QWidget* parent) 
{
	m_canvasPixmap = new QPixmap(m_);
}



Canvas::~Canvas()
{

}

void Canvas::updateCanvas(cv::Mat p_img)
{

	/*
	//setting up a blank canvas
	cv::Mat canvas(height(), width(), CV_8UC3, cv::Scalar(100, 100, 100));

	//swaping the red and blue values to convert the format from BGR (used by opencv) to RGB (used by qt)

	cv::Vec3b color;
	int tempRed;
	QPixmap pixmap(width(),height());
	for (int y = 0; y < p_img.rows; y++)
	{

		if (y < 0 || y  >= height())
			continue;
		for (int x = 0; x < p_img.cols; x++)
		{
			if (x < 0 || x  >= width())
				continue;

			color = p_img.at<cv::Vec3b>(y, x);

			//swaping the red and blue channels
			tempRed = color[2];
			color[2] = color[0];
			color[0] = tempRed;
			canvas.at<cv::Vec3b>(y, x) = color;



		}
	}

	m_label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)canvas.data, canvas.cols, canvas.rows, QImage::Format_RGB888)));
	*/
}


void Canvas::paintEvent(QPaintEvent* event)
{
	QPainter qp(this);
	qp.fillRect(QRect(0, 0, width(), height()), Qt::gray);
}

