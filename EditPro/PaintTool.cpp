#include "PaintTool.h"


PaintTool::PaintTool(EPProject* p_epproject) : Tool(p_epproject)
{
	Brush test;
	test.erase = false;
	test.opacity = 100;
	test.size = 50;
	test.texture = cv::Mat(50, 50, CV_8UC1, 100);

	m_brushs.push_back(test);
	m_selectedBrush = test;
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
	
	for (int y = 0; y < m_selectedBrush.size; y++)
	{
		//p_paintPosition.y - (m_selectedBrush.size / 2)
		if ( y + p_paintPosition.y < 0 ||y + p_paintPosition.y  - (m_selectedBrush.size / 2) >= m_epproject->getSelectedLayer()->getHeight())
			continue;
		for (int x = 0; x < m_selectedBrush.size; x++)
		{
			if (x + p_paintPosition.x< 0 || x + p_paintPosition.x  - (m_selectedBrush.size / 2) >= m_epproject->getSelectedLayer()->getWidth())
				continue;
			//p_paintPosition.x - (m_selectedBrush.size / 2)
			m_epproject->getSelectedLayer()->setPixel(x + p_paintPosition.x - (m_selectedBrush.size / 2), y + p_paintPosition.y  - (m_selectedBrush.size / 2) ,EP::Vector3(m_selectedBrush.texture.at<uchar>(y, x)));
		}
	}
	m_epproject->render();
}

void PaintTool::loadBrushs()
{

}
