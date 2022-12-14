#include "PaintTool.h"


PaintTool::PaintTool(EPProject* p_epproject) : Tool(p_epproject)
{
	g_paintColor = { 200,0,0};

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

//this function should take the cursor position as an input to solve the problem of skiping the paint points
void PaintTool::onMouseDrag(QMouseEvent* p_event,EP::Vector2 p_mouseRelativePosition)
{
	paint(p_mouseRelativePosition);
}

void PaintTool::onMousePress(QMouseEvent* p_event,EP::Vector2 p_mouseRelativePosition)
{
	paint(p_mouseRelativePosition);
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

			//the aplha value of the current brush texture pixel
			int alpha = m_selectedBrush.texture.at<uchar>(y, x);
			//the color of the current layer pixel
			cv::Vec4b pixelColor = m_epproject->getSelectedLayer()->getRenderedImage().at<cv::Vec4b>(y + p_paintPosition.y - (m_selectedBrush.size / 2), x + p_paintPosition.x - (m_selectedBrush.size / 2));

			double newAlpha = alpha + pixelColor[3] * (1 - ((float)alpha / 255));

			EP::Vector4 newBGRA = 
			{
				//the new red
				(g_paintColor.x * alpha + pixelColor[2] * pixelColor[3] * (1 - (float)alpha / 255)) / newAlpha,
				//the new green
				(g_paintColor.y * alpha + pixelColor[1] * pixelColor[3] * (1 - (float)alpha / 255)) / newAlpha,
				//the new blue
				(g_paintColor.z * alpha + pixelColor[0] * pixelColor[3] * (1 - (float)alpha / 255)) / newAlpha,
				//the alpha 
				newAlpha
			};

			m_epproject->getSelectedLayer()->setPixel(x + p_paintPosition.x - (m_selectedBrush.size / 2), y + p_paintPosition.y  - (m_selectedBrush.size / 2) ,newBGRA);
		}
	}
	m_epproject->render();
}

void PaintTool::loadBrushs()
{

}
