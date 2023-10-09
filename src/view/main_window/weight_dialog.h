#pragma once

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <vector>
#include "data_struct.h"

namespace s21 {

class WeightDialog : public QDialog
{
    Q_OBJECT

    public:
        WeightDialog(const PointsWeights &data, QWidget* parent = nullptr);
        ~WeightDialog();

        Weights Get();

    private:
        QVBoxLayout* main_layout_;
        QGridLayout* layout_;
        QScrollArea* scroll_area_;
        QWidget* scroll_widget_;
        std::vector<QDoubleSpinBox*> weights_;
        std::vector<QLabel*> labels_;

};

} // namespace s21
