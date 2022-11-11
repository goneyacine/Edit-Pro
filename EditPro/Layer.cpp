#include "Layer.h"


#define PI_NUM 3.14159265358979323846 /*the constant number pi*/


Layer::Layer(int p_width, int p_height) : m_width(p_width),m_height(p_height)
{
	//initializing the rendered image
	m_renderedImage = cv::Mat::zeros(m_width, m_height, CV_8UC3);

	m_name = "New Layer";
}


Layer::Layer(int p_width, int p_height,QString p_name) : m_width(p_width), m_height(p_height),m_name(p_name)
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

	applyWave(0, 100);
	applyRandomNoise(10,100);
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

void Layer::applyWave(float p_xIntensity,float p_yIntensity)
{

	int newX, newY;

	cv::Mat tempImg(cv::Size(m_width, m_height), CV_8UC3, cv::Scalar(255, 255, 255));

	for (int y = 0; y < m_renderedImage.rows; y++)
	{

		for (int x = 0; x < m_renderedImage.cols; x++)
		{
		    newY = y + (sin((float)x / (float)m_renderedImage.cols * 2 * PI_NUM) * p_yIntensity);
			newX = x + (sin((float)y / (float)m_renderedImage.rows * 2 * PI_NUM) * p_xIntensity);
			

			if (newX >= m_width || newY >= m_height || newX < 0 || newY < 0)
				continue;

			tempImg.at<cv::Vec3b>(newY, newX) = m_renderedImage.at<cv::Vec3b>(y,x);
		}
	}

	m_renderedImage = tempImg.clone();
}


void Layer::applyGaussianBlur(float xSize, float ySize)
{
    //TODO : find a max value for the blur size
	 //I need to improve this later
	cv::Mat temp = m_renderedImage.clone();
	cv::GaussianBlur(temp, m_renderedImage, cv::Size(xSize, ySize),5,0);
}

void Layer::applyRandomNoise(int p_intensity,int p_opacity)
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
            (* pixelPtr)[0] += ((float)p_opacity / 255) *((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[0]);
            (* pixelPtr)[1] += ((float)p_opacity / 255) *((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[2]);
            (* pixelPtr)[2] += ((float)p_opacity / 255) *((float)rand() / (float)RAND_MAX) * (255 - (*pixelPtr)[1]);


		}
	}
}