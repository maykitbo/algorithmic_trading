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
    TimeTestInit();
}


MainWindow::~MainWindow()
{
    delete ui_;
    if (weight_dialog_ != nullptr)
    {
        delete weight_dialog_;
    }
    for (auto &i : t_subj_spin_boxes_) {
        if (i != nullptr) {
            delete i;
        }
    }
    for (auto &i : t_subj_labels_) {
        if (i != nullptr) {
            delete i;
        }
    }
    for (auto &i : t_subj_layouts_) {
        if (i != nullptr) {
            delete i;
        }
    }
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

