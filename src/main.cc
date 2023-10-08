#include "main_window.h"
#include "facade.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    s21::Facade facade;
    s21::MainWindow main_window(facade);
    main_window.showMaximized();
    return application.exec();
}