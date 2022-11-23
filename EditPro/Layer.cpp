#include "Layer.h"
#include "EppMath.h"

#define PI_NUM 3.14159265358979323846 /*the constant number pi*/


Layer::Layer(int p_width, int p_height) : m_width(p_width), m_height(p_height)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_height, CV_8UC3);

	m_name = "New_Layer";
}


Layer::Layer(int p_width, int p_height, QString p_name) : m_width(p_width), m_height(p_height), m_name(p_name)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_height, CV_8UC3);
}

//TODO : this function should reimplemented to later to support the alpha channel
void Layer::import(cv::Mat p_img)
{

	for (int y = 0; y < p_img.rows; y++)
	{
		if (y >= m_height)
			continue;
		for (int x = 0; x < p_img.cols; x++)
		{
			if (x >= m_height)
				continue;

			m_renderedImage.at<cv::Vec3b>(y, x) = p_img.at<cv::Vec3b>(y, x);
		}
	}
}

cv::Mat Layer::getRenderedImage()
{
	return m_renderedImage;
}

void Layer::resize(int p_width, int p_height)
{
	//TODO : implement the resize function
}

int Layer::getWidth()
{
	return m_width;
}

int Layer::getHeight()
{
	return m_height;
}

QString Layer::getName()
{
	return m_name;
}

void Layer::setName(QString p_name)
{
	m_name = p_name;
}

bool Layer::isVisible()
{
	return m_isVisible;
}

void Layer::setVisible(bool p_visible)
{
	m_isVisible = p_visible;
}
/// <summary>
/// applys a wave effect to the layer, currently it uses sin function, maybe we need to add more function later 
/// </summary>
/// <param name="p_xIntensity"> wave size on the horizontal axis</param>
/// <param name="p_yIntensity"> wave size on the vertical axis</param>
/// <param name="p_xFrequency"> wave frequency on the horizontal axis (how many times the wave is repeated)</param>
/// <param name="p_yFrequency"> wave frequency on the vertical axis (how many times the wave is repeated)</param>
void Layer::applyWave(float p_xIntensity, float p_yIntensity, float p_xFrequency, float p_yFrequency)
{

	int newX, newY, xOffset, yOffset;

	cv::Mat tempImg(cv::Size(m_width, m_height), CV_8UC3, cv::Scalar(255, 255, 255));

	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		xOffset = (sin((float)y / (float)m_renderedImage.rows * 2 * PI_NUM * p_xFrequency) * p_xIntensity);

		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			yOffset = (sin((float)x / (float)m_renderedImage.cols * 2 * PI_NUM * p_yFrequency) * p_yIntensity);
			newY = y + yOffset;
			newX = x + xOffset;


			if (newX >= m_width || newY >= m_height || newX < 0 || newY < 0)
				continue;

			tempImg.at<cv::Vec3b>(newY, newX) = m_renderedImage.at<cv::Vec3b>(y, x);
		}
	}

	m_renderedImage = tempImg.clone();
}


void Layer::applyGaussianBlur(float xSize, float ySize)
{
	//TODO : find a max value for the blur size
	 //I need to improve this later
	cv::Mat temp = m_renderedImage.clone();
	cv::GaussianBlur(temp, m_renderedImage, cv::Size(xSize, ySize), 5, 0);
}

void Layer::applyRandomNoise(int p_intensity, int p_opacity)
{
	srand(time(0));


	//checking that all the parameters are in the range
	p_opacity = p_opacity > 255 ? 255 : p_opacity;
	p_opacity = p_opacity < 0 ? 0 : p_opacity;

	p_intensity = p_intensity > 100 ? 100 : p_intensity;
	p_intensity = p_intensity < 0 ? 0 : p_intensity;

	cv::Vec3b* pixelPtr;
	//the probability of noise to be applied to a pixel 
	float noiseProbability = (float)p_intensity / 100;
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			//checking if we should apply noise or not
			if (((float)rand() / (float)RAND_MAX) > noiseProbability)
				continue;


			pixelPtr = &m_renderedImage.at<cv::Vec3b>(y, x);
			//applying noise 
			(*pixelPtr)[0] += ((float)p_opacity / 255) * ((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[0]);
			(*pixelPtr)[1] += ((float)p_opacity / 255) * ((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[2]);
			(*pixelPtr)[2] += ((float)p_opacity / 255) * ((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[1]);
		}
	}
}

//I need to improve this function and apply the cuffoff fraction and do some refactoring later :)
//don't forget to do that XD
// I hate bugs
void Layer::adjustContrast(float p_adjustmentFactor)
{
	if (p_adjustmentFactor == 0)
		return;
	

	p_adjustmentFactor = p_adjustmentFactor > 100 ? 100 : p_adjustmentFactor;
	p_adjustmentFactor = p_adjustmentFactor < 0 ? 0 : p_adjustmentFactor;


	//calculating the min and max values for the original image


	unsigned int min = - 1;
	unsigned int max = -1;

	//these arrays store pixels count for each color intensity value (from 0 to 255)
	unsigned int pixelsCount[256] = {0};
	//counting pixels count
	cv::Vec3b pixel;
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			pixel = m_renderedImage.at<cv::Vec3b>(y, x);
			//increasing the pixels count valuesl 
			pixelsCount[(pixel[0] + pixel[1] + pixel[2]) / 3]++;

		}
	}

	//the intensity value that has the highest pixels count (the most common pixel value)
	unsigned int commonIntensity = 0;
	for (int i = 0; i < 256; i++)
	{
		if (pixelsCount[i] > pixelsCount[commonIntensity])
			commonIntensity = i;
	}

	//we find the min and max values by finding the min and max values that have specific pixel number count (in percent %)
	//we do this to prevent extreme pixel values from effecting the adjustment too much

	
	//first we try to find the min
	for (int i = 0; i <= 255; i++)
	{
		//checking the min value 
		if (pixelsCount[i] >= pixelsCount[commonIntensity] / 5 && min == -1)
		{
			min = i;
		}
	}

	//second we try to find the max 
	for (int i = 255; i >= 0; i--)
	{
		//checking the max value 
		if (pixelsCount[i] >= pixelsCount[commonIntensity] / 5 && max == -1)
		{
			max = i;
		}
	}

	if (max == -1 || min == -1)
		return;

	cv::Vec3b* tempPixel;
	unsigned int r, g, b;
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			tempPixel = &m_renderedImage.at<cv::Vec3b>(y, x);
			/*
			newBlue = slope * (*tempPixel)[0] + offset;
			newGreen = slope * (*tempPixel)[1] + offset;
			newRed = slope * (*tempPixel)[2] + offset;
			*/

			r = (*tempPixel)[2];
			g = (*tempPixel)[1];
			b = (*tempPixel)[0];

			/*
			r += (r - (r - oldMin) * (255 / (oldMax - oldMin)))* (p_adjustmentFactor / 100);
			g += (g - (g - oldMin) * (255 / (oldMax - oldMin))) * (p_adjustmentFactor / 100);
			b += (b - (b - oldMin) * (255 / (oldMax - oldMin))) * (p_adjustmentFactor / 100);
            */

			r = (r - min) * (255 / (max - min));
			g = (g - min) * (255 / (max - min));
			b = (b - min) * (255 / (max - min));

			//I'm doing this to make sure that the color values are in the range (between 0 and 255)

			if (b > 255)
				(*tempPixel)[0] = 255;
			else if (b < 0)
				(*tempPixel)[0] = 0;
			else
				(*tempPixel)[0] = b;


			if (g > 255)
				(*tempPixel)[1] = 255;
			else if (g < 0)
				(*tempPixel)[1] = 0;
			else
				(*tempPixel)[1] = g;

			if (r > 255)
				(*tempPixel)[2] = 255;
			else if (r < 0)
				(*tempPixel)[2] = 0;
			else
				(*tempPixel)[2] = r;
		}
	}


}

/// <summary>
/// 
/// </summary>
/// <param name="p_adjustmentFactor">adjustment factor should be between -180 and 180</param>
void Layer::adjustHue(float p_adjustmentFactor)
{
	if (p_adjustmentFactor == 0)
		return;
	
	p_adjustmentFactor = p_adjustmentFactor > 180 ? 180 : p_adjustmentFactor;
	p_adjustmentFactor = p_adjustmentFactor < -180 ? -180 : p_adjustmentFactor;


	cv::Mat tempHSVBuffer;


	cv::Vec3b* pixel;


	cv::cvtColor(m_renderedImage, tempHSVBuffer, cv::COLOR_BGR2HSV);
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			pixel = &tempHSVBuffer.at<cv::Vec3b>(y, x);

			(*pixel)[0] += (p_adjustmentFactor) / 2;

			//checking that the hue value is in the range (0, 180)
			(*pixel)[0] = (*pixel)[0] > 180 ? (*pixel)[0] - 180 : (*pixel)[0];
		    (*pixel)[0] = (*pixel)[0] < 0 ? 180 + (*pixel)[0] : (*pixel)[0];
		}
	}
	cv::cvtColor(tempHSVBuffer, m_renderedImage, cv::COLOR_HSV2BGR);
}

void Layer::adjustSaturation(float p_adjustmentFactor)
{
	if (p_adjustmentFactor == 0)
		return;

	p_adjustmentFactor = p_adjustmentFactor > 100 ? 100 : p_adjustmentFactor;
	p_adjustmentFactor = p_adjustmentFactor < -100 ? -100 : p_adjustmentFactor;

	cv::Mat tempHSVBuffer;

	cv::Vec3b* pixel;

	cv::cvtColor(m_renderedImage, tempHSVBuffer, cv::COLOR_BGR2HSV);

	for (int y = 0; y < tempHSVBuffer.rows; y++)
	{
		for (int x = 0; x < tempHSVBuffer.cols; x++)
		{
			pixel = &tempHSVBuffer.at<cv::Vec3b>(y, x);

			if (p_adjustmentFactor > 0)
				(*pixel)[1] += (255 - (*pixel)[1]) * p_adjustmentFactor / 100;
			else
				(*pixel)[1] += (*pixel)[1] * p_adjustmentFactor / 100;


		}
	}
	cv::cvtColor(tempHSVBuffer, m_renderedImage, cv::COLOR_HSV2BGR);
}

void Layer::adjustValue(float p_adjustmentFactor)
{
	if (p_adjustmentFactor == 0)
		return;

	p_adjustmentFactor = p_adjustmentFactor > 100 ? 100 : p_adjustmentFactor;
	p_adjustmentFactor = p_adjustmentFactor < -100 ? -100 : p_adjustmentFactor;

	cv::Mat tempHSVBuffer;

	cv::Vec3b* pixel;

	cv::cvtColor(m_renderedImage, tempHSVBuffer, cv::COLOR_BGR2HSV);

	for (int y = 0; y < tempHSVBuffer.rows; y++)
	{
		for (int x = 0; x < tempHSVBuffer.cols; x++)
		{
			pixel = &tempHSVBuffer.at<cv::Vec3b>(y, x);
			if (p_adjustmentFactor > 0)
				(*pixel)[2] += (255 - (*pixel)[2]) * p_adjustmentFactor / 100;
			else
				(*pixel)[2] += (*pixel)[2] * p_adjustmentFactor / 100;

		}
	}
	cv::cvtColor(tempHSVBuffer, m_renderedImage, cv::COLOR_HSV2BGR);
}