#include "MainWindow.h"
#include "Canvas.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

 
    m_openedProject = new EPProject(300,1000,ui.layersGUIElementPanel->layout());
    ui.tab->layout()->addWidget(m_openedProject->getCanvas());
    

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






