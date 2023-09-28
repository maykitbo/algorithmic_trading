#include "image_params.h"

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
