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

QString MainWindow::FileNameString(const QString &name, unsigned size)
{
    int index = name.lastIndexOf('/');
    return name.mid(index + 1) + " [" + QString::number(size) + "]";
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
    else if (event->key() == Qt::Key_Space)
    {
        if (ui_->tab->currentIndex() == 0 && i_graphs_ == 0)
        {
            InterpolationFileRead(default_file_name_);
        }
        else if (ui_->tab->currentIndex() == 1 && a_graphs_ == 0)
        {
            ApproximationFileRead(default_file_name_);
        }
    }
}

