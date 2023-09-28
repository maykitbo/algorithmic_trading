#include "main_window.h"

using namespace s21;


void MainWindow::InterpolationInit()
{
    ui_->i_add_graph_frame->setEnabled(false);
    ui_->i_time_frame->setEnabled(false);
    ui_->i_clear_button->setEnabled(false);
    ui_->i_points_spin_box->setMaximum(1e7);
    ui_->N_degree_spin_ag->setMaximum(16);
    ui_->N_degree_spin_ag->setMinimum(2);
    ui_->N_degree_spin_val->setMaximum(16);
    ui_->N_degree_spin_val->setMinimum(2);

    auto names_frame = ui_->i_graph_widget->GetNamesFrame();
    names_frame->setLineWidth(ui_->i_time_frame->lineWidth());
    names_frame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    names_frame->setFrameShape(QFrame::StyledPanel);
    auto layout = static_cast<QVBoxLayout*>(ui_->i_set_frame->layout());
    layout->insertWidget(layout->count() - 2, names_frame);

    connect(ui_->i_hide_button, &QPushButton::clicked,
        this, &MainWindow::InterpolationHideButton);
    connect(ui_->i_clear_button, &QPushButton::clicked,
        this, &MainWindow::InterpolationClearButton);
    connect(ui_->i_file_button, &QPushButton::clicked,
        this, &MainWindow::InterpolationFileButton);
    connect(ui_->CS_button, &QPushButton::clicked,
        this, &MainWindow::CubicSplineButton);
    connect(ui_->N_button, &QPushButton::clicked,
        this, &MainWindow::NewtonPolynomialButton);
    connect(names_frame, &NamesFrame::NameRemoved,
        this, &MainWindow::InterpolationGraphRemove);
    connect(ui_->calc_button, &QPushButton::clicked,
        this, &MainWindow::InterpolationCalcButton);
    
}

void MainWindow::InterpolationCalcButton()
{
    auto q_time = ui_->i_date_time_edit->dateTime();
    double time = Point::ToDays(q_time.toSecsSinceEpoch());
    unsigned degree = ui_->N_degree_spin_val->value();
    auto result = facade_.InterpolationClac(time, degree);
    ui_->CS_value_label->setText(QString::number(result.first));
    ui_->N_value_label->setText(QString::number(result.second));
}

void MainWindow::InterpolationGraphRemove(GraphName *name [[maybe_unused]])
{
    --i_graphs_;
    ui_->i_add_graph_frame->setEnabled(true);
}

void MainWindow::InterpolationRawData(Points &data)
{
    ui_->i_date_time_edit->setMinimumDateTime(QDateTime::fromSecsSinceEpoch(Point::ToSeconds(data[0].x)));
    ui_->i_date_time_edit->setMaximumDateTime(QDateTime::fromSecsSinceEpoch(Point::ToSeconds(data.back().x)));
    ui_->i_points_spin_box->setMinimum(data.size());
    InterpolationClearHelper();
    ui_->i_graph_widget->AddData(data, NameString("Base", data.size()));
    ui_->i_file_info_lable->setText(FileNameString(i_filename_, data.size()));
    ++i_graphs_;
    ui_->i_time_frame->setEnabled(true);
    ui_->i_add_graph_frame->setEnabled(true);
    ui_->i_clear_button->setEnabled(true);
}


void MainWindow::CubicSplineButton()
{
    auto data = facade_.CubicSplineData(ui_->i_points_spin_box->value());
    ui_->i_graph_widget->AddData(data, NameString("Cubic spline", data.size()));
    ++i_graphs_;
    if (i_graphs_ == i_max_graphs_)
    {
        ui_->i_add_graph_frame->setEnabled(false);
    }
}

void MainWindow::NewtonPolynomialButton()
{
    unsigned degree = ui_->N_degree_spin_ag->value();
    auto data = facade_.NewtonPolynomialData(ui_->i_points_spin_box->value(), degree);
    ui_->i_graph_widget->AddData(
            data,
            NameString("Newton " + QString::number(degree), data.size()));
    ++i_graphs_;
    if (i_graphs_ == i_max_graphs_)
    {
        ui_->i_add_graph_frame->setEnabled(false);
    }
}

void MainWindow::InterpolationFileButton()
{
    InterpolationFileRead(
        QFileDialog::getOpenFileName(this, "Open file", "../materials", "CSV (*.csv)"));
}

void MainWindow::InterpolationFileRead(const QString &filename)
{
    auto result = facade_.InterpolationFile(filename.toStdString());
    if (!result.first && !filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Incorrect file");
        return;
    }
    i_filename_ = filename;
    InterpolationRawData(result.second);
}


void MainWindow::InterpolationClearButton()
{
    InterpolationClearHelper();
    ui_->i_time_frame->setEnabled(false);
    ui_->i_add_graph_frame->setEnabled(false);
    ui_->i_clear_button->setEnabled(false);
    facade_.InterpolationClear();
    ui_->i_file_info_lable->setText("No file [0]");
}

void MainWindow::InterpolationClearHelper()
{
    i_graphs_ = 0;
    ui_->i_graph_widget->Clear();
}

void MainWindow::InterpolationHideButton()
{
    ui_->i_hide_button->setText(i_hide_ ? ">" : "<");
    ui_->i_add_graph_frame->setVisible(i_hide_);
    ui_->i_time_frame->setVisible(i_hide_);
    ui_->i_clear_button->setVisible(i_hide_);
    ui_->i_file_button->setVisible(i_hide_);
    ui_->i_file_info_lable->setVisible(i_hide_);
    ui_->i_graph_widget->GetNamesFrame()->setVisible(i_hide_);
    i_hide_ = !i_hide_;
}
