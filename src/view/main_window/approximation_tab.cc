#include "main_window.h"

using namespace s21;



void MainWindow::ApproximationInit()
{
    ui_->approximate_frame->setEnabled(false);
    ui_->a_clear_button->setEnabled(false);
    ui_->a_days_spin->setMinimum(1);
    ui_->a_degree_spin->setMinimum(1);
    ui_->a_degree_spin->setMaximum(6);
    
    auto name_frame = ui_->a_graph_widget->GetNamesFrame();
    name_frame->setLineWidth(ui_->i_time_frame->lineWidth());
    name_frame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    name_frame->setFrameShape(QFrame::StyledPanel);
    auto layout = static_cast<QVBoxLayout*>(ui_->a_set_frame->layout());
    layout->insertWidget(layout->count() - 2, name_frame);

    connect(ui_->a_hide_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationHideButton);
    connect(ui_->a_clear_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationClearButton);
    connect(ui_->a_file_button, &QPushButton::clicked,
        this, &MainWindow::ApproximationFileButton);
    connect(ui_->approximate_button, &QPushButton::clicked,
        this, &MainWindow::ApproximateButton);
    connect(name_frame, &NamesFrame::NameRemoved,
        this, &MainWindow::ApproximationGraphRemove);
}

void MainWindow::ApproximationGraphRemove(GraphName *name)
{
    --a_graphs_;
    ui_->approximate_frame->setEnabled(true);
}

void MainWindow::ApproximateButton()
{
    unsigned degree = ui_->a_degree_spin->value();
    auto data = facade_.LeastSquaresData(ui_->a_days_spin->value(), degree);
    ui_->a_graph_widget->AddData(data, NameString("Approximate"  + QString::number(degree), data.size()));
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
    ui_->a_graph_widget->AddData(data, NameString("Base", data.size()));
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
    ui_->a_graph_widget->GetNamesFrame()->setVisible(a_hide_);
    a_hide_ = !a_hide_;
}

