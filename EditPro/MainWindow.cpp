#include "MainWindow.h"
#include "ImageViewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ImageViewer* imageViewer = new ImageViewer(NULL);
    ui.tab->layout()->addWidget(imageViewer->getQLabel());

    
    
  

    m_openedProject = new EPProject(imageViewer,1000,1000,ui.layersGUIElementPanel->layout());

    //TODO : I need to implement that import sytem later
    import();
  // connect(ui.actionImport, &QAction::trigger, this, &MainWindow::import);
}

MainWindow::~MainWindow()
{}

void MainWindow::import()
{
    m_openedProject->importAsNewLayer(cv::imread("C:\\Users\\TMAX27\\Desktop\\test.png"));
}



