#include "PaintTool.h"


PaintTool::PaintTool(EPProject* p_epproject) : Tool(p_epproject)
{
	Brush test;
	test.erase = false;
	test.opacity = 100;
	test.size = 50;
	test.texture = cv::Mat(50, 50, CV_8UC1, 100);
}

PaintTool::~PaintTool()
{

}

void PaintTool::onMouseDrag(QMouseEvent* p_event,EP::Vector2 p_mouseRelativePosition)
{
	paint(p_mouseRelativePosition);
}

void PaintTool::onMousePress(QMouseEvent* p_event,EP::Vector2 p_mouseRelativePosition)
{

}

void PaintTool::onMouseRelease(QMouseEvent* p_event, EP::Vector2 p_mouseRelativePosition)
{

}

void PaintTool::onMouseWheel(QWheelEvent* p_event)
{

}

void PaintTool::paint(EP::Vector2 p_paintPosition)
{
	for (int y = p_paintPosition.y - (m_selectedBrush.size / 2); y < p_paintPosition.y + (m_selectedBrush.size / 2); y++)
	{
		for (int x = p_paintPosition.x - (m_selectedBrush.size / 2); x < p_paintPosition.x + (m_selectedBrush.size / 2); x++)
		{
			m_epproject->getSelectedLayer()->setPixel(y,x,EP::Vector3(m_selectedBrush.texture.at<uchar>(y, x)));
		}
	}
}

void PaintTool::loadBrushs()
{

}
