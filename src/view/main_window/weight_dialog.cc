#include "weight_dialog.h"

using namespace s21;

WeightDialog::WeightDialog(const PointsWeights &data, QWidget *parent)
    : QDialog(parent),
      weights_(data.second.size(), nullptr),
      labels_(data.first.size() * 2 + 3, nullptr),
      layout_(new QGridLayout()),
      main_layout_(new QVBoxLayout(this)),
      scroll_area_(new QScrollArea(this)),
      scroll_widget_(new QWidget(scroll_area_)) {
  QLabel *x_label = new QLabel("x");
  QLabel *y_label = new QLabel("y");
  QLabel *weight_label = new QLabel("weight");
  labels_[0] = x_label;
  labels_[1] = y_label;
  labels_[2] = weight_label;
  layout_->addWidget(x_label, 0, 0);
  layout_->addWidget(y_label, 0, 1);
  layout_->addWidget(weight_label, 0, 2);

  for (unsigned i = 0; i < data.first.size(); ++i) {
    x_label = new QLabel(QString::number(data.first[i].first));
    y_label = new QLabel(QString::number(data.first[i].second));
    QDoubleSpinBox *weight = new QDoubleSpinBox();
    weight->setValue(data.second[i]);
    weight->setRange(0.01, 32);
    weight->setSingleStep(0.05);
    layout_->addWidget(x_label, i + 1, 0);
    layout_->addWidget(y_label, i + 1, 1);
    layout_->addWidget(weight, i + 1, 2);
    labels_[i * 2 + 3] = x_label;
    labels_[i * 2 + 4] = y_label;
    weights_[i] = weight;
  }

  scroll_widget_->setLayout(layout_);
  scroll_area_->setWidget(scroll_widget_);
  scroll_area_->setWidgetResizable(true);
  main_layout_->addWidget(scroll_area_);
}

WeightDialog::~WeightDialog() {
  for (auto &w : weights_) {
    delete w;
  }
  for (auto &l : labels_) {
    delete l;
  }
  delete layout_;
  delete scroll_widget_;
  delete scroll_area_;
  delete main_layout_;
}

Weights WeightDialog::Get() {
  unsigned n = weights_.size();
  Weights weights(n);
  for (unsigned i = 0; i < n; ++i) {
    weights[i] = weights_[i]->value();
  }
  return weights;
}
