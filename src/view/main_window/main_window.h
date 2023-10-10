#pragma once

#include <QEventLoop>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>

#include "./ui_main_window.h"
#include "facade.h"
#include "weight_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Facade &facade, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void InterpolationHideButton();
  void InterpolationClearButton();
  void InterpolationFileButton();
  void CubicSplineButton();
  void NewtonPolynomialButton();
  void InterpolationGraphRemove();
  void InterpolationCalcButton();

  void ApproximationHideButton();
  void ApproximationClearButton();
  void ApproximationFileButton();
  void ApproximateButton();
  void ApproximationGraphRemove();
  void ApproximateWeightButton();
  void Part5Button();

  void TimeTestHideButton();
  void TimeTestClearButton();
  void TimeTestFileButton();
  void TimeTestStartButton();
  void CSSubjButton();
  void SubjMinusButton();
  void SubjPlusButton();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Ui::MainWindow *ui_;

  Facade &facade_;

  void InterpolationInit();
  void InterpolationRawData(Points &data);
  void InterpolationFileRead(const QString &filename);

  void ApproximationInit();
  void ApproximationRawData(PointsWeights &data);
  void ApproximationFileRead(const QString &filename);

  void TimeTestInit();

  bool i_hide_{false};
  unsigned i_graphs_{0};
  unsigned i_max_graphs_{5};

  bool a_hide_{false};
  unsigned a_graphs_{0};
  unsigned a_max_graphs_{5};

  bool t_hide_{false};
  unsigned t_size_{0};
  std::list<QSpinBox *> t_subj_spin_boxes_{};
  std::list<QLabel *> t_subj_labels_{};
  std::list<QHBoxLayout *> t_subj_layouts_{};

  WeightDialog *weight_dialog_{nullptr};

  void InterpolationClearHelper();
  QString FileNameString(const QString &name, unsigned size);

  QString default_file_name_{"../materials/AAPL.csv"};
};

}  // namespace s21
