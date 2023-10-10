#pragma once

#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QPen>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QToolButton>
#include <QWidget>

namespace Graph {

class AbstractFrame : public QWidget {
  Q_OBJECT

 public:
  AbstractFrame(QWidget *parent = nullptr) : QWidget(parent) {}
  virtual ~AbstractFrame() = default;

  static QString SaveImageDialog(QWidget *parent);

 signals:
  void ReDraw();

 protected:
  void LineStyleHelper(QToolButton *button, QSpinBox *spin, QComboBox *box,
                       QPen *pen);
  void PointStyleHelper(QToolButton *button, QSpinBox *spin, QComboBox *box,
                        QPen *pen);
  void ToolAndSpinHelper(QToolButton *button, QSpinBox *spin, QPen *pen);
  void VisibleHelper(QRadioButton *radio, bool *visible);
  void HideAndSettingsHelper(QPushButton *button, QFrame *settings,
                             QLabel *lable, const QColor &color);
  QString RGBAStyle(const QColor &color);
  virtual void Action() = 0;

  inline const static QString visible_resources{
      "QRadioButton::indicator { border-image: url(:/resources/invisible.png); "
      "}"
      "QRadioButton::indicator:checked { border-image: "
      "url(:/resources/visible.png); }"};
};

}  // namespace Graph
