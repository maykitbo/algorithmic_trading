#include <QApplication>

#include "facade.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QApplication application(argc, argv);
  s21::Facade facade;
  s21::MainWindow main_window(facade);
  main_window.showMaximized();
  return application.exec();
}
