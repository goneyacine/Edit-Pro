#include "MainWindow.h"
#include "ImageViewer.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ImageViewer* imageViewer = new ImageViewer(cv::Mat(500, 500, CV_8UC3));

    imageViewer->getQLabel()->setText("");
    imageViewer->getQLabel()->setPixmap(QPixmap("C:\\Users\\TMAX27\\Pictures\\Camera Roll\\WIN_20220922_19_19_08_Pro.jpg"));

    ui.tab->layout()->addWidget(imageViewer->getQLabel());

}

MainWindow::~MainWindow()
{}
