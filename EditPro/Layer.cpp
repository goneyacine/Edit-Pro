#include "Layer.h"
#include "EppMath.h"
#include <chrono>
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
	auto startTime = std::chrono::high_resolution_clock::now();

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
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Import Function Toke " << functionDuration << "ms to colmplete";
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
	auto startTime = std::chrono::high_resolution_clock::now();

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
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Apply Wave Function Toke " << functionDuration << "ms to colmplete";
}


void Layer::applyGaussianBlur(float xSize, float ySize)
{
	auto startTime = std::chrono::high_resolution_clock::now();

	//TODO : find a max value for the blur size
	 //I need to improve this later
	cv::Mat temp = m_renderedImage.clone();
	cv::GaussianBlur(temp, m_renderedImage, cv::Size(xSize, ySize), 5, 0);

	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Apply Gaussian Blur Function Toke " << functionDuration << "ms to colmplete";
}

void Layer::applyRandomNoise(int p_intensity, int p_opacity)
{
	auto startTime = std::chrono::high_resolution_clock::now();

	srand(time(0));


	//checking that all the parameters are in the range
	p_opacity = p_opacity > 255 ? 255 : p_opacity;
	p_opacity = p_opacity < 0 ? 0 : p_opacity;

	p_intensity = p_intensity > 100 ? 100 : p_intensity;
	p_intensity = p_intensity < 0 ? 0 : p_intensity;

	cv::Vec3b* pixel;
	//the probability of noise to be applied to a pixel 
	float noiseProbability = (float)p_intensity / 100;

	for (int y = 0; y < m_renderedImage.rows; y++)
	{
		for (int x = 0; x < m_renderedImage.cols; x++)
		{
			//checking if we should apply noise or not
			if (((float)rand() / (float)RAND_MAX) > noiseProbability)
				continue;

            ;

			pixel = &m_renderedImage.at<cv::Vec3b>(y, x);
			//applying noise 
			(*pixel)[0] +=  ((float)rand() / (float)RAND_MAX) * ((float)p_opacity / 255) * (255 - (*pixel)[0]);
			(*pixel)[1] +=  ((float)rand() / (float)RAND_MAX) * ((float)p_opacity / 255) * (255 - (*pixel)[2]);
			(*pixel)[2] +=  ((float)rand() / (float)RAND_MAX) * ((float)p_opacity / 255) * (255 - (*pixel)[1]);
		}
	}
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Random Noise Function Toke " << functionDuration << "ms to colmplete";
}


void Layer::autoContrast()
{
	auto startTime = std::chrono::high_resolution_clock::now();

	/*
	we're using AGCIE algorithm for constrast adjustment.
	we can Implement more algorithms later and give the user more control but for now we're using only AGCIE.
	there is this great article about AGCIE : https://link.springer.com/article/10.1186/s13640-016-0138-1#Equ1
	there is also this great github repository to learn more : https://github.com/dengyueyun666/Image-Contrast-Enhancement
	*/

	//converting the input image from rgb into hsv
	cv::Mat tempHSV;

	cv::cvtColor(m_renderedImage, tempHSV, cv::COLOR_BGR2HSV);

	//the V channel values for the HSV image (but they are normlized to be between 0 and 1 instead of 0 and 255)
	std::vector<double> VChannel(tempHSV.rows * tempHSV.cols);

	for (int y = 0; y < tempHSV.rows; y++)
	{
		for (int x = 0; x < tempHSV.cols; x++)
		{
			VChannel[x * tempHSV.rows + y] = (double)tempHSV.at<cv::Vec3b>(y, x)[2] / 255;
		}
	}

	double tau = 3.0;
	//the average V value (between 0 and 1)
	double mean = EppMath::mean(VChannel);
	//the standard deviation 
	double sigma = EppMath::stdDeviation(VChannel, mean);

	double gamma;

	if (4 * sigma < 1 / tau) //low contrast image
		gamma = -std::log2(sigma);
	else //higher contrast image
		gamma = std::exp((1 - (mean + sigma)) / 2);


	if (mean > 0.5) //bright image 
	{
		for (int i = 0; i < VChannel.size(); i++)
			VChannel[i] = std::pow(VChannel[i], gamma);
	}
	else //dark image
	{
		//mean value to the power of gamma 
		double gammaMean = std::pow(mean, gamma);
		for (int i = 0; i < VChannel.size(); i++)
		{
			//V value to the power of gamma
			double gammaV = std::pow(VChannel[i], gamma);
			VChannel[i] = gammaV / (gammaV + (1 - gammaV) * gammaMean);
		}
	}

	//assinging the new V values to hsv image and then convert it again to rgb
	for (int y = 0; y < tempHSV.rows; y++)
	{
		for (int x = 0; x < tempHSV.cols; x++)
		{

			tempHSV.at<cv::Vec3b>(y, x)[2] = VChannel[x * tempHSV.rows + y] * 255;
		}
	}

	cv::cvtColor(tempHSV, m_renderedImage, cv::COLOR_HSV2BGR);
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Auto Contrast Function Toke " << functionDuration << "ms to colmplete";
}

/// <summary>
/// 
/// </summary>
/// <param name="p_adjustmentFactor">adjustment factor should be between -180 and 180</param>
void Layer::adjustHue(float p_adjustmentFactor)
{
	auto startTime = std::chrono::high_resolution_clock::now();

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
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Adjust Hue Function Toke " << functionDuration << "ms to colmplete";
}

void Layer::adjustSaturation(float p_adjustmentFactor)
{
	auto startTime = std::chrono::high_resolution_clock::now();

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
	double functionDuration = 1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Adjust Saturation Function Toke " << functionDuration << "ms to colmplete";
}

void Layer::adjustValue(float p_adjustmentFactor)
{
	auto startTime = std::chrono::high_resolution_clock::now();

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
	double functionDuration =  1000 * std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count();
	qDebug() << "Adjust Value Function Toke " << functionDuration << "ms to colmplete";
}