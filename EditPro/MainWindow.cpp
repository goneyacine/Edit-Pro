#include "MainWindow.h"
#include "ImageViewer.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ImageViewer* imageViewer = new ImageViewer(NULL);


    ui.tab->layout()->addWidget(imageViewer->getQLabel());
    cv::Mat img = cv::imread("C:\\Users\\TMAX27\\Pictures\\Camera Roll\\WIN_20221001_09_49_12_Pro.jpg", cv::IMREAD_COLOR);


    m_openedProject = new EPProject(imageViewer, img);
    m_openedProject->setSaturation(10);
    m_openedProject->render();
}

MainWindow::~MainWindow()
{}
