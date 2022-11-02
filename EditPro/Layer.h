#pragma once

#include <opencv2/opencv.hpp>
#include <qstring.h>
class Layer
{

public :
	Layer(int p_width, int p_height);
	Layer(int p_width, int p_height,QString p_name);
	/// <summary>
	///TODO : implement the resize function
	/// </summary>
	/// <param name="p_width"></param>
	/// <param name="p_height"></param>
	void resize(int p_width, int p_height);
	int getWidth();
	int getHeight();
	QString getName();
	void setName(QString p_name);
	cv::Mat getRenderedImage();
	void import(cv::Mat p_img);
	bool isVisible();
	void setVisible(bool p_visible);

private :
	cv::Mat m_renderedImage;
	int m_width, m_height;
	QString m_name;
	bool m_isVisible = true;
};