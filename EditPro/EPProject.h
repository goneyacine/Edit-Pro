#pragma once
#include <opencv2/opencv.hpp>
#include "ImageViewer.h"
// Quick note : EPProject stands for Edit Pro Project :)

class EPProject
{
public:

	EPProject(ImageViewer* p_imageViewer,cv::Mat p_baseImage);
	~EPProject();

	cv::Mat getBaseImage();
	cv::Mat getRenderedImage();
	ImageViewer* getImageViewer();
	int getSaturation();
	int getHue();
	void setSaturation(int p_saturation);
	void setHue(int p_hue);

	//TODO : implement the render and export functions
	void render();

	void updateSaturation();
	void updateHue();


private :
	ImageViewer* m_imageViewer;
	cv::Mat m_baseImage;
	cv::Mat m_renderedImage;
	//NOTE : opencv range for saturation is from 0 to 255 and our range is from 0 to 100 
	//so the value of saturation should be normalized in the render function to match opencv's range
	int m_saturation = 50;
	int m_hue = 50;
};