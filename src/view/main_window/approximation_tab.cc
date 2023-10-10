#include "main_window.h"

using namespace s21;

void MainWindow::ApproximationInit() {
  ui_->approximate_frame->setEnabled(false);
  ui_->a_clear_button->setEnabled(false);
  ui_->weight_button->setEnabled(false);
  ui_->a_days_spin->setMinimum(1);
  ui_->a_degree_spin->setMinimum(1);
  ui_->a_degree_spin->setMaximum(6);

  auto layers_frame = ui_->a_graph_widget->DetachFrame();
  layers_frame->setParent(ui_->a_set_frame);
  auto layout = static_cast<QVBoxLayout *>(ui_->a_set_frame->layout());
  layout->insertWidget(layout->count() - 2, layers_frame);

  connect(ui_->a_hide_button, &QPushButton::clicked, this,
          &MainWindow::ApproximationHideButton);
  connect(ui_->a_clear_button, &QPushButton::clicked, this,
          &MainWindow::ApproximationClearButton);
  connect(ui_->a_file_button, &QPushButton::clicked, this,
          &MainWindow::ApproximationFileButton);
  connect(ui_->approximate_button, &QPushButton::clicked, this,
          &MainWindow::ApproximateButton);
  connect(layers_frame, &Graph::Frame::GraphRemoved, this,
          &MainWindow::ApproximationGraphRemove);
  connect(ui_->weight_button, &QPushButton::clicked, this,
          &MainWindow::ApproximateWeightButton);
  connect(ui_->part5_button, &QPushButton::clicked, this,
          &MainWindow::Part5Button);
}

void MainWindow::ApproximationGraphRemove() {
  --a_graphs_;
  ui_->approximate_frame->setEnabled(true);
}

void MainWindow::ApproximateWeightButton() {
  if (weight_dialog_ == nullptr) {
    QMessageBox::critical(this, "Error", "Set weights");
    return;
  }
  weight_dialog_->exec();
}

void MainWindow::Part5Button() {
  if (a_graphs_ == 0) {
    QMessageBox::critical(this, "Error", "Approximate data");
    return;
  }
  while (a_graphs_ > 1) {
    ui_->a_graph_widget->Remove(1);
    --a_graphs_;
  }
  ui_->approximate_frame->setEnabled(true);
  auto weights = weight_dialog_->Get();
  auto data1 = facade_.LeastSquaresData(ui_->a_days_spin->value(), 1, weights);
  auto data2 = facade_.LeastSquaresData(ui_->a_days_spin->value(), 2, weights);
  std::fill(weights.begin(), weights.end(), 1.0);
  auto data3 = facade_.LeastSquaresData(ui_->a_days_spin->value(), 1, weights);
  auto data4 = facade_.LeastSquaresData(ui_->a_days_spin->value(), 2, weights);
  ui_->a_graph_widget->AddGraph(data1, "Approximate1w", false, true);
  ui_->a_graph_widget->AddGraph(data2, "Approximate2w", false, true);
  ui_->a_graph_widget->AddGraph(data3, "Approximate3", false, true);
  ui_->a_graph_widget->AddGraph(data4, "Approximate4", false, true);
}

void MainWindow::ApproximateButton() {
  if (weight_dialog_ == nullptr) {
    QMessageBox::critical(this, "Error", "Set weights");
    return;
  }
  unsigned degree = ui_->a_degree_spin->value();
  auto data = facade_.LeastSquaresData(ui_->a_days_spin->value(), degree,
                                       weight_dialog_->Get());
  ui_->a_graph_widget->AddGraph(data, "Approximate" + QString::number(degree),
                                false, true);
  ++a_graphs_;
  if (a_graphs_ >= a_max_graphs_) {
    ui_->approximate_frame->setEnabled(false);
  }
}

void MainWindow::ApproximationRawData(PointsWeights &data) {
  if (weight_dialog_ != nullptr) {
    delete weight_dialog_;
  }
  weight_dialog_ = new WeightDialog(data, this);
  ui_->a_days_spin->setMaximum(data.first.size() * 4);
  a_graphs_ = 1;
  ui_->a_graph_widget->Clear();
  ui_->a_graph_widget->AddGraph(data.first, "Base", true, false);
  // ui_->a_file_info_lable->setText(FileNameString(a_filename_,
  // data.first.size()));
  ui_->a_clear_button->setEnabled(true);
  ui_->approximate_frame->setEnabled(true);
  ui_->weight_button->setEnabled(true);
}

void MainWindow::ApproximationFileButton() {
  ApproximationFileRead(QFileDialog::getOpenFileName(
      this, "Open file", "../materials", "CSV (*.csv)"));
}

void MainWindow::ApproximationFileRead(const QString &filename) {
  auto result = facade_.ApproximationFile(filename.toStdString());
  if (!result.first && !filename.isEmpty()) {
    QMessageBox::critical(this, "Error", "Incorrect file");
    return;
  }
  // a_filename_ = filename;
  ui_->a_file_info_lable->setText(
      FileNameString(filename, result.second.first.size()));
  ApproximationRawData(result.second);
}

void MainWindow::ApproximationClearButton() {
  a_graphs_ = 0;
  ui_->a_graph_widget->Clear();
  ui_->approximate_frame->setEnabled(false);
  ui_->a_clear_button->setEnabled(false);
  ui_->weight_button->setEnabled(false);
  facade_.ApproximationClear();
  ui_->a_file_info_lable->setText("No file [0]");
}

void MainWindow::ApproximationHideButton() {
  ui_->i_hide_button->setText(a_hide_ ? ">" : "<");
  ui_->approximate_frame->setVisible(a_hide_);
  ui_->a_file_info_lable->setVisible(a_hide_);
  ui_->a_file_button->setVisible(a_hide_);
  ui_->a_clear_button->setVisible(a_hide_);
  ui_->a_graph_widget->GetFrame()->setVisible(a_hide_);
  a_hide_ = !a_hide_;
}
