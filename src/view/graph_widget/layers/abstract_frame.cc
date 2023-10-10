#include "abstract_frame.h"

using namespace Graph;

void AbstractFrame::LineStyleHelper(QToolButton *button, QSpinBox *spin, QComboBox *box, QPen *pen)
{
    ToolAndSpinHelper(button, spin, pen);
    box->addItems({"Solid", "Dash", "Dot", "DashDot"});
    connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, pen] (int index)
    {
        pen->setStyle(static_cast<Qt::PenStyle>(index + 1));
        Action();
    });
}

void AbstractFrame::PointStyleHelper(QToolButton *button, QSpinBox *spin, QComboBox *box, QPen *pen)
{
    ToolAndSpinHelper(button, spin, pen);
    pen->setCapStyle(Qt::RoundCap);
    box->addItems({"Circle", "Square"});
    connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, pen] (int index)
    {
        pen->setCapStyle(index == 0 ? Qt::RoundCap : Qt::SquareCap);
        Action();
    });
}

void AbstractFrame::ToolAndSpinHelper(QToolButton *button, QSpinBox *spin, QPen *pen)
{
    button->setStyleSheet(RGBAStyle(pen->color()));
    spin->setValue(pen->width());
    spin->setMaximum(32);
    spin->setMinimum(1);
    spin->setSuffix(" px");
    connect(button, &QToolButton::clicked, this, [this, button, pen] ()
    {
        QColorDialog color_dialog(pen->color(), this);
        color_dialog.setOption(QColorDialog::ShowAlphaChannel, true);
        if (color_dialog.exec() == QDialog::Accepted) {
            QColor color = color_dialog.selectedColor();
            if (color.isValid()) {
                pen->setColor(color);
                Action();
                button->setStyleSheet(RGBAStyle(color));
            }
        }
    });
    connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), this, [this, pen] (int value)
    {
        pen->setWidth(value);
        Action();
    });
}

QString AbstractFrame::RGBAStyle(const QColor &color)
{
    return "QToolButton { background-color: rgba(" +
         QString::number(color.red()) + "," +
         QString::number(color.green()) + "," +
         QString::number(color.blue()) + "," +
         QString::number(color.alpha()) + "); }";
}

void AbstractFrame::VisibleHelper(QRadioButton *radio, bool *visible)
{
    radio->setChecked(*visible);
    radio->setStyleSheet(visible_resources);
    connect(radio, &QRadioButton::clicked, this, [this, radio, visible] ()
    {
        *visible = radio->isChecked();
        Action();
    });
}

void AbstractFrame::HideAndSettingsHelper(QPushButton *button, QFrame *settings, QLabel *lable, const QColor &color)
{
    settings->setVisible(false);
    settings->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    settings->setStyleSheet("QFrame#settings_frame { border: 1px solid " + color.name() + "; }");
    lable->setStyleSheet("QLabel { color : " +color.name() + "; }");
    button->setText("+");
    connect(button, &QPushButton::clicked, this, [button, settings] ()
    {
        bool hide = settings->isVisible();
        button->setText(hide ? "+" : "-");
        settings->setVisible(!hide);
    });
}

QString AbstractFrame::SaveImageDialog(QWidget *parent)
{
    return QFileDialog::getSaveFileName(parent,
        "Save graph", "", "PNG (*.png);;JPG (*.jpg);;BMP (*.bmp)");
}


