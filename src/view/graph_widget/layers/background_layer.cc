#include "background_layer.h"

using namespace s21;

BackgroundLayer::BackgroundLayer(const ImageParams &params,
                QColor background,
                QPen axis_pen,
                BackgroundType type,
                QImage::Format format)
    : ImageLayer(params, background, format)
    , type_(type)
    , axis_pen_(axis_pen)
    {}

void BackgroundLayer::Draw()
{
    image_.fill(background_);
    if (type_ == Axis)
    {
        qreal bottom = params_.height - params_.bottom_indent;
        qreal right = params_.width - params_.right_indent;
        painter_.setPen(axis_pen_);
        // draw vertical axes
        painter_.drawLine(params_.left_indent, params_.top_indent,
                          params_.left_indent, bottom);
        // draw horizontal axes
        painter_.drawLine(params_.left_indent, bottom,
                          right, bottom);
    }
}
