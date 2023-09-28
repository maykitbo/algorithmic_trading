#include "controller.h"

using namespace s21;

Controller::Controller(MainWindow &main_window, Facade &facade)
    : view_(main_window)
    , model_(facade)
{
    // connect(&main_window_, &MainWindow::IFile, this, &Controller::StartInterpolation);
}

