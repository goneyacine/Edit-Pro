#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qevent.h>
#include "EPProject.h"
#include <qpushbutton.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindowClass* getUI();

signals:
    void importFile(QString p_filePath);
public slots: 
    void onImportFileAction();
private:
    Ui::MainWindowClass ui;
};
