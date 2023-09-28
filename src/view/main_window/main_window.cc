#include "main_window.h"
// #include "ui_main_window.h"


using namespace s21;

MainWindow::MainWindow(Facade &facade, QWidget *parent)
    : QMainWindow(parent)
    , facade_(facade)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    
    InterpolationInit();
    ApproximationInit();
}


MainWindow::~MainWindow()
{
    delete ui_;
}

QString MainWindow::NameString(const QString &name, unsigned size)
{
    return name + " [" + QString::number(size) + "]";
}

QString MainWindow::FileNameString(const QString &name, unsigned size)
{
    int index = name.lastIndexOf('/');
    return NameString(name.mid(index + 1), size);
}




void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
    else if (event->key() == Qt::Key_Space)
    {
        if (ui_->tab->currentIndex() == 0)
        {
            InterpolationFileRead(default_file_name_);
        }
        else
        {
            ApproximationFileRead(default_file_name_);
        }
    }
}

