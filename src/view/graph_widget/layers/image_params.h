#pragma once

#include <QSize>
#include <QDateTime>

namespace s21 {

struct ImageParams
{
    QSize size;
    qreal dx;
    qreal dy;

    qreal x_min;
    qreal x_max;
    qreal y_min;
    qreal y_max;

    qreal x_factor;
    qreal y_factor;

    qreal left_indent;
    qreal right_indent;
    qreal top_indent;
    qreal bottom_indent;
    qreal bottom_text_indent{15};
    qreal left_text_indent{5};

    qreal width;
    qreal height;
    qreal graph_width;
    qreal graph_height;

    unsigned x_grid_step;
    unsigned y_grid_step;

    QString date_format{"yyyy-MM-dd"};
    std::pair<char, int> number_format{'g', 3};

    qreal XToImageCords(double x) const noexcept;
    qreal YToImageCords(double y) const noexcept;
    double XToDataCords(qreal x) const noexcept;
    double YToDataCords(qreal y) const noexcept;
};


} // namespace s21
