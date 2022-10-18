#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "EPProject.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void changeSaturation(int p_saturation);
private:
    Ui::MainWindowClass ui;
    EPProject* m_openedProject;
};
