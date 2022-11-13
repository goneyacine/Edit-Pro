#include "Layer.h"


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
	//adjustContrast(1.4);
	adjustExposure(2);
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
	if (p_intensity > 100)
		p_intensity = 100;
	else if (p_intensity < 0)
		p_intensity = 0;

	if (p_opacity > 255)
		p_opacity = 255;
	else if (p_opacity < 0)
		p_opacity = 0;

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


//TODO : applying smoothing function
void Layer::adjustContrast(float p_slope)
{
	if (p_slope == 1)
		return;
	else if (p_slope <= 0)
		p_slope = .01;


	cv::Vec3b* pixel;
	float red, green, blue;

	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			pixel = &m_renderedImage.at<cv::Vec3b>(y, x);

			//applying the slope
			red = p_slope * (*pixel)[2];
			green = p_slope * (*pixel)[1];
			blue = p_slope * (*pixel)[0];

			if (red > 255)
				red = 255;
			else if (red < 0)
				red = 0;

			if (green > 255)
				green = 255;
			else if (red < 0)
				green = 0;

			if (blue > 255)
				blue = 255;
			else if (blue < 0)
				blue = 0;

			
			
			(*pixel)[2] = red;
			(*pixel)[1] = green;
			(*pixel)[0] = blue;
		
		}
	}
}

void Layer::adjustExposure(float p_x)
{
	cv::Vec3b* pixel;
	float red, green, blue;
	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			pixel = &m_renderedImage.at<cv::Vec3b>(y, x);

			red = pow(2, p_x) * (*pixel)[2];
			green = pow(2, p_x) * (*pixel)[1];
			blue = pow(2, p_x) * (*pixel)[0];

			if (red > 255)
				red = 255;
			else if (red < 0)
				red = 0;

			if (green > 255)
				green = 255;
			else if (red < 0)
				green = 0;

			if (blue > 255)
				blue = 255;
			else if (blue < 0)
				blue = 0;



			(*pixel)[2] = red;
			(*pixel)[1] = green;
			(*pixel)[0] = blue;
		}
	}
}