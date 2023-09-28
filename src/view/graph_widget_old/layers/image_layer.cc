#include "image_layer.h"

using namespace s21;


qreal ImageParams::XToImageCords(double x) const noexcept
{
    return (x * x_factor) + dx;
}

qreal ImageParams::YToImageCords(double y) const noexcept
{
    return (y * y_factor) + dy;
}

double ImageParams::XToDataCords(qreal x) const noexcept
{
    return (x - dx) / x_factor;
}

double ImageParams::YToDataCords(qreal y) const noexcept
{
    return (y - dy) / y_factor;
}



ImageLayer::ImageLayer(const ImageParams &params,
                    const QPen &pen,
                    const QColor &background,
                    QImage::Format format)
    : image_(params.size, format)
    , params_(params)
    , painter_(&image_)
    , pen_(pen)
    , background_(background)
{
    painter_.setPen(pen_);
}

void ImageLayer::Resize()
{
    image_.fill(background_);
    image_ = QImage(params_.size, image_.format());
    Draw();
}


void ImageLayer::SetBackground(const QColor &background)
{
    background_ = background;
}

void ImageLayer::SetPen(const QPen &pen)
{
    pen_ = pen;
}


