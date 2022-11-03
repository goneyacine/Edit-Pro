#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qevent.h>
#include "EPProject.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLayout* getLayersGUILayout();
    QLayout* getCanvasViewLayout();

private:
    Ui::MainWindowClass ui;
};
