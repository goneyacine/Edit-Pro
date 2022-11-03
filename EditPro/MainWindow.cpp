#include "MainWindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

QLayout* MainWindow::getLayersGUILayout()
{
    return ui.layersGUIElementPanel->layout();
}

QLayout* MainWindow::getCanvasViewLayout()
{
    return ui.tab->layout();
}




