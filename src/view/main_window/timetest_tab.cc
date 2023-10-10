#include "main_window.h"
#include "interpolation_time/compare.h"
#include <thread>

using namespace s21;

void MainWindow::TimeTestInit()
{
    ui_->t_clear_button->setEnabled(false);
    ui_->start_test_button->setEnabled(false);
    ui_->t_points->setEnabled(false);
    ui_->t_points->setMaximum(1e7);
    ui_->t_partitions->setMinimum(4);
    ui_->t_partitions->setMaximum(4);
    ui_->n_subj_spin->setMaximum(16);
    ui_->n_subj_spin->setMinimum(2);
    t_subj_spin_boxes_.push_back(ui_->n_subj_spin);
    t_subj_labels_.push_back(ui_->newton_subj);
    t_subj_layouts_.push_back(ui_->newton_layout);
    ui_->cs_subj->setOpenExternalLinks(true);
    ui_->cs_subj_button->setEnabled(false);
    ui_->subj_minus_button->setEnabled(false);

    auto layers_frame = ui_->t_graph_widget->DetachFrame();
    layers_frame->setParent(ui_->t_set_frame);
    layers_frame->GetBackground()->SetXTextFunc([](double x)
    {
        return QString::number((long)x);
    });
    layers_frame->GetBackground()->SetYTextFunc([](double y)
    {
        return QString::fromStdString(Time::GetAdapt<Time::mcs>(y, 1000));
    });
    layers_frame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QVBoxLayout *layout = static_cast<QVBoxLayout*>(ui_->t_set_frame->layout());
    layout->insertWidget(layout->count() - 2, layers_frame);

    connect(ui_->t_hide_button, &QPushButton::clicked,
        this, &MainWindow::TimeTestHideButton);
    connect(ui_->t_clear_button, &QPushButton::clicked,
        this, &MainWindow::TimeTestClearButton);
    connect(ui_->t_file_button, &QPushButton::clicked,
        this, &MainWindow::TimeTestFileButton);
    connect(ui_->start_test_button, &QPushButton::clicked,
        this, &MainWindow::TimeTestStartButton);
    connect(ui_->cs_subj_button, &QPushButton::clicked,
        this, &MainWindow::CSSubjButton);
    connect(ui_->subj_minus_button, &QPushButton::clicked,
        this, &MainWindow::SubjMinusButton);
    connect(ui_->subj_plus_button, &QPushButton::clicked,
        this, &MainWindow::SubjPlusButton);
    connect(ui_->t_points, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [this](int value)
        {
            ui_->t_partitions->setMaximum(value - t_size_);
        });
}

void MainWindow::TimeTestClearButton()
{
    ui_->t_clear_button->setEnabled(false);
    ui_->start_test_button->setEnabled(false);
    ui_->t_points->setEnabled(false);
    facade_.TimeTestClear();
    ui_->i_file_info_lable->setText("No file [0]");
    ui_->t_graph_widget->Clear();
}

void MainWindow::TimeTestFileButton()
{
    QString filename =
        QFileDialog::getOpenFileName(this, "Open file", "../materials", "CSV (*.csv)");
    int result = facade_.TimeTestFile(filename.toStdString());
    if (filename.isEmpty() || result <= 0)
    {
        QMessageBox::critical(this, "Error", "Incorrect file");
        return;
    }
    ui_->t_file_info_lable->setText(FileNameString(filename, result));

    ui_->t_clear_button->setEnabled(true);
    ui_->start_test_button->setEnabled(true);
    ui_->t_points->setEnabled(true);
    ui_->t_points->setMinimum(result + 4);
    ui_->t_points->setValue(result + 4);
    ui_->t_partitions->setMaximum(4);
    ui_->t_partitions->setValue(4);
    t_size_ = result;
}

void MainWindow::TimeTestStartButton()
{
    ui_->t_graph_widget->Clear();
    bool cs = (ui_->cs_subj_button->text() == "-");
    unsigned k = 0;
    if (cs)
    {
        ++k;
        ui_->t_graph_widget->AddGraph("Cubic spline", false, true);
    }
    std::vector<unsigned> degrees;
    for (auto spin : t_subj_spin_boxes_)
    {
        ++k;
        ui_->t_graph_widget->AddGraph("Newton " + spin->text(), false, true);
        degrees.push_back(spin->value());
    }
    QCoreApplication::processEvents();
    unsigned points = ui_->t_points->value();
    unsigned partitions = ui_->t_partitions->value();
    unsigned vg_step = 0, vg_i = 0;
    facade_.TimeCompare(cs, degrees, points, partitions,
        [this, k, &vg_step, &vg_i](const InterpolationTime::result_data &result)
        {
            for (unsigned i = 0; i < k; ++i)
            {
                std::pair<double, double> res{result[i].second, result[i].first};
                (*ui_->t_graph_widget)[i]->AddData(res);
            }
            if (++vg_i > 2) {
                ui_->t_graph_widget->GetBackground()->SetVerticalGridStep(result[0].second - vg_step);
            }
            ui_->t_graph_widget->repaint();
            vg_step = result[0].second;
        });
    ui_->t_graph_widget->Draw();
}

void MainWindow::CSSubjButton()
{
    if (ui_->cs_subj_button->text() == "+")
    {
        ui_->cs_subj_button->setText("-");
        ui_->cs_subj->setText("Cubic spline");
        if (t_subj_spin_boxes_.size() == 4) {
            ui_->subj_plus_button->setEnabled(false);
        }
        ui_->subj_minus_button->setEnabled(true);
    }
    else if (t_subj_spin_boxes_.size() > 1)
    {
        ui_->cs_subj_button->setText("+");
        QString text = "<font style='text-decoration: line-through;'>Cubic spline</font>";
        ui_->cs_subj->setText(text);
        if (t_subj_spin_boxes_.size() == 2) {
            ui_->subj_minus_button->setEnabled(false);
        }
        ui_->subj_plus_button->setEnabled(true);
    }
}

void MainWindow::SubjMinusButton()
{
    bool cs = (ui_->cs_subj_button->text() == "-");
    ui_->subj_plus_button->setEnabled(true);
    if (!cs) {
        ui_->cs_subj_button->setEnabled(true);
    }

    auto subj_layout = dynamic_cast<QVBoxLayout*>(ui_->subj_frame->layout());

    subj_layout->removeItem(t_subj_layouts_.back());
    delete t_subj_layouts_.back();
    t_subj_layouts_.pop_back();

    delete t_subj_spin_boxes_.back();
    t_subj_spin_boxes_.pop_back();

    delete t_subj_labels_.back();
    t_subj_labels_.pop_back();

    if (t_subj_spin_boxes_.size() + (cs ? 1 : 0) <= 2) {
        ui_->subj_minus_button->setEnabled(false);
        if (cs) {
            ui_->cs_subj_button->setEnabled(false);
        }
    }
}

void MainWindow::SubjPlusButton()
{
    bool cs = (ui_->cs_subj_button->text() == "-");
    ui_->subj_minus_button->setEnabled(true);
    if (cs) {
        ui_->cs_subj_button->setEnabled(true);
    }

    auto subj_layout = dynamic_cast<QVBoxLayout*>(ui_->subj_frame->layout());

    QSpinBox *spin = new QSpinBox();
    spin->setMaximum(16);
    spin->setMinimum(2);
    int value = t_subj_spin_boxes_.back()->value() + 1;
    spin->setValue(value > 16 ? 2 : value);
    t_subj_spin_boxes_.push_back(spin);

    QLabel *label = new QLabel("Newton " + QString::number(t_subj_spin_boxes_.size()));
    t_subj_labels_.push_back(label);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(spin);
    t_subj_layouts_.push_back(layout);

    subj_layout->insertLayout(subj_layout->count() - 1, layout);

    if (t_subj_spin_boxes_.size() + (cs ? 1 : 0) >= 5) {
        ui_->subj_plus_button->setEnabled(false);
        if (!cs) {
            ui_->cs_subj_button->setEnabled(false);
        }
    }
}

void MainWindow::TimeTestHideButton()
{
    ui_->t_hide_button->setText(t_hide_ ? ">" : "<");
    ui_->time_frame->setVisible(i_hide_);
    ui_->t_clear_button->setVisible(i_hide_);
    ui_->t_file_button->setVisible(i_hide_);
    ui_->t_file_info_lable->setVisible(i_hide_);
    ui_->t_graph_widget->GetFrame()->setVisible(i_hide_);
    i_hide_ = !i_hide_;
}

