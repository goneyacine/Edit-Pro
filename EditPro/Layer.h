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

    //filters and effects
	void applyWave(float p_xIntensity,float p_yIntensity, float p_xFrequency, float p_yFrequency);
	void applyGaussianBlur(float xSize, float ySize);
	/// <summary>
	/// apply a random noise filter
	/// </summary>
	/// <param name="p_intensity">the noise intesity ranging from 0 to 100 (100 fills the whole image with noise)</param>
	/// <param name="p_opacity"> the noise opacity ranging from 0 to 255 where 0 is fully transparent</param>
	void applyRandomNoise(int p_intensity,int p_opacity);

private :
	cv::Mat m_renderedImage;
	int m_width, m_height;
	QString m_name;
	bool m_isVisible = true;
};