#include "MainWindow.h"
#include <qfiledialog.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionImport, &QAction::triggered, this, &MainWindow::onImportFileAction);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onImportFileAction()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Import File", QDir::currentPath(), "Image Files (*.png *.jpg *.bmp)");
    emit importFile(filePath);
}

Ui::MainWindowClass* MainWindow::getUI()
{
    return &ui;
}




