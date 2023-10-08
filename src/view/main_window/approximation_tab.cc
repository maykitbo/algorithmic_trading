#include "main_window.h"

using namespace s21;



void MainWindow::ApproximationInit()
{
    ui_->approximate_frame->setEnabled(false);
    ui_->a_clear_button->setEnabled(false);
    ui_->a_days_spin->setMinimum(1);
    ui_->a_degree_spin->setMinimum(1);
    ui_->a_degree_spin->setMaximum(6);
    
    auto layers_frame = ui_->a_graph_widget->DetachFrame();
    layers_frame->setParent(ui_->a_set_frame);
    // layers_frame->setLineWidth(ui_->approximate_frame->lineWidth());
    // layers_frame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    // ui_->a_set_spacer->changeSize(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    // layers_frame->setFrameShape(QFrame::StyledPanel);
    auto layout = static_cast<QVBoxLayout*>(ui_->a_set_frame->layout());
    layout->insertWidget(layout->count() - 2, layers_frame, 2);

    connect(ui_->a_hide_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationHideButton);
    connect(ui_->a_clear_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationClearButton);
    connect(ui_->a_file_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationFileButton);
    connect(ui_->approximate_button, &QPushButton::clicked,
        this, &MainWindow::ApproximateButton);
    connect(layers_frame, &Graph::Frame::GraphRemoved,
        this, &MainWindow::ApproximationGraphRemove);
}

void MainWindow::ApproximationGraphRemove()
{
    --a_graphs_;
    ui_->approximate_frame->setEnabled(true);
}

void MainWindow::ApproximateButton()
{
    unsigned degree = ui_->a_degree_spin->value();
    auto data = facade_.LeastSquaresData(ui_->a_days_spin->value(), degree);
    ui_->a_graph_widget->AddGraph(data, "Approximate"  + QString::number(degree), false, true);
    ++a_graphs_;
    if (a_graphs_ >= a_max_graphs_)
    {
        ui_->approximate_frame->setEnabled(false);
    }
}

void MainWindow::ApproximationRawData(Points &data)
{
    ui_->a_days_spin->setMaximum(data.size() * 4);
    a_graphs_ = 0;
    ui_->a_graph_widget->Clear();
    ui_->a_graph_widget->AddGraph(data, "Base", true, false);
    ui_->a_file_info_lable->setText(FileNameString(i_filename_, data.size()));
    ++a_graphs_;
    ui_->a_clear_button->setEnabled(true);
    ui_->approximate_frame->setEnabled(true);
}

void MainWindow::ApproximationFileButton()
{
    ApproximationFileRead(
        QFileDialog::getOpenFileName(this, "Open file", "../materials", "CSV (*.csv)"));
}

void MainWindow::ApproximationFileRead(const QString &filename)
{
    auto result = facade_.ApproximationFile(filename.toStdString());
    if (!result.first && !filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Incorrect file");
        return;
    }
    a_filename_ = filename;
    ApproximationRawData(result.second);
}


void MainWindow::ApproximationClearButton()
{
    a_graphs_ = 0;
    ui_->a_graph_widget->Clear();
    ui_->approximate_frame->setEnabled(false);
    ui_->a_clear_button->setEnabled(false);
    facade_.ApproximationClear();
    ui_->a_file_info_lable->setText("No file [0]");
}

void MainWindow::ApproximationHideButton()
{
    ui_->i_hide_button->setText(a_hide_ ? ">" : "<");
    ui_->approximate_frame->setVisible(a_hide_);
    ui_->a_file_info_lable->setVisible(a_hide_);
    ui_->a_file_button->setVisible(a_hide_);
    ui_->a_clear_button->setVisible(a_hide_);
    ui_->a_graph_widget->GetFrame()->setVisible(a_hide_);
    a_hide_ = !a_hide_;
}

