#pragma once

#include <vector>
#include <list>
#include <QColor>
#include <QPen>

namespace s21 {

struct GraphStyle
{
    std::list<QColor> colors
    {
        QColor(255, 0, 0),
        QColor(132, 169, 141),
        QColor(174, 124, 124),
        QColor(92, 108, 124),
        QColor(149, 149, 149),
    };
    // std::vector<QColor> point_colors
    // {
    //     QColor(180, 75, 75),
    //     QColor(75, 180, 75),
    //     QColor(75, 75, 180),
    //     QColor(180, 180, 75),
    //     QColor(75, 180, 180),
    // };
    QColor background_color{15, 15, 30};
    QColor names_frame_background_color{50, 50, 75};
    QColor axes_color{184, 134, 11};
    QColor axes_text_color{184, 134, 11};
    QColor grid_color{200, 200, 200, 32};


    static QString number_format(qreal n) { return QString::number(n, 'g', 3); }
    
    // indents
    qreal top_indent{10};
    qreal bottom_indent{30};
    qreal left_indent{50};
    qreal right_indent{10};
    qreal graph_y_indent{0};

    unsigned max_point_on_one_graph{30000};
    
    qreal wheel_scale_factor{1.1};

    // lines width
    qreal graph_width{2};
    qreal axes_width{2};
    qreal gorizontal_grid_width{1};
    qreal year_grid_width{2};
    qreal month_grid_width{1};
    qreal day_grid_width{1};

    QPen gorizontal_grid_pen{grid_color, gorizontal_grid_width, Qt::SolidLine};
    QPen axes_pen{axes_color, axes_width, Qt::SolidLine};

    // text
    QString text_font{"Arial"};
    unsigned axes_text_size{10};
    unsigned names_text_size{10};
    QString date_format{"yyyy-MM-dd"};


    unsigned min_x_grid_step{30};
    unsigned y_grid_step{50};
    unsigned x_grid_step{100};
    unsigned point_radius{3};
};

} // namespace s21
