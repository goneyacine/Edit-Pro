#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Manager* manager = new Manager(EP::Vector2(1000,1000),&w);
    w.show();
    return a.exec();
}
