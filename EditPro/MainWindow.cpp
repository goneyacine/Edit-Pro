#include "MainWindow.h"
#include "ImageViewer.h"

#include <qslider.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ImageViewer* imageViewer = new ImageViewer(NULL);


    ui.tab->layout()->addWidget(imageViewer->getQLabel());
    cv::Mat img = cv::imread("C:\\Users\\TMAX27\\Pictures\\Camera Roll\\WIN_20221001_09_49_12_Pro.jpg", cv::IMREAD_COLOR);


    m_openedProject = new EPProject(imageViewer, img);
    m_openedProject->render();

    connect(ui.saturation_slider, &QSlider::valueChanged, this, &MainWindow::changeSaturation);
}

MainWindow::~MainWindow()
{}

void MainWindow::changeSaturation(int p_saturation)
{
    m_openedProject->setSaturation(p_saturation);
}

