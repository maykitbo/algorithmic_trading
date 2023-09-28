#include <QApplication>

#include "graph_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::GraphWidget w;
    w.show();
    return a.exec();
}
