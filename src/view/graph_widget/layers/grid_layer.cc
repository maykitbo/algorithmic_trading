#include "grid_layer.h"

using namespace s21;

GridLayer::GridLayer(const ImageParams &params,
                    QPen grid_pen,
                    QPen text_pen,
                    QFont text_font,
                    GridType type,
                    bool show_text,
                    QImage::Format format)
    : ImageLayer(params, Qt::transparent, format)
    , grid_pen_(grid_pen)
    , text_pen_(text_pen)
    , text_font_(text_font)
    , type_(type)
    , show_text_(show_text)
    {}
        
void GridLayer::Draw()
{
    image_.fill(background_);

    qreal bottom = params_.height - params_.bottom_indent;
    qreal right = params_.width - params_.right_indent;
    unsigned min, max;

    painter_.setPen(grid_pen_);
    if (type_ == Vertical || type_ == Both)
    {
        min = params_.left_indent;
        max = right;
        for (unsigned i = min; i < max; i += params_.x_grid_step)
        {
            painter_.drawLine(i, params_.top_indent, i, bottom);
        }
    }
    if (type_ == Horizontal || type_ == Both)
    {
        min = params_.top_indent;
        max = bottom;
        for (unsigned i = min; i < max; i += params_.y_grid_step)
        {
            painter_.drawLine(params_.left_indent, i, right, i);
        }
    }

    painter_.setPen(text_pen_);
    painter_.setFont(text_font_);
    if (show_text_ && (type_ == Vertical || type_ == Both))
    {
        min = params_.top_indent;
        max = bottom;
        for (unsigned i = min; i < max; i += params_.y_grid_step)
        {
            painter_.drawText(params_.left_text_indent, i,
                            (*this.*y_text_func_)(params_.YToDataCords(i)));
        }
    }
    if (show_text_ && (type_ == Horizontal || type_ == Both))
    {
        min = params_.left_indent;
        max = right;
        for (unsigned i = min; i < max; i += params_.x_grid_step)
        {
            // TODO Why 30?
            painter_.drawText(i - 30, bottom + params_.bottom_text_indent,
                            (*this.*x_text_func_)(params_.XToDataCords(i)));
        }
    }
}
