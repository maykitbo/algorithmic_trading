#include "graph_layer.h"

using namespace s21;


GraphLayer::GraphLayer(const ImageParams &params,
            const QPen &pen,
            const QColor &background,
            const std::vector<std::pair<double, double>> &data,
            GraphPoints draw_points,
            QImage::Format format)
    : ImageLayer(params, pen, background, format)
    , data_(data)
    , draw_points_(draw_points)
    {}

GraphLayer::GraphLayer(const ImageParams &params,
            const QPen &pen,
            const QColor &background,
            std::vector<std::pair<double, double>> &&data,
            GraphPoints draw_points,
            QImage::Format format)
    : ImageLayer(params, pen, background, format)
    , data_(std::move(data))
    , draw_points_(draw_points)
    {}

void GraphLayer::Draw()
{
    image_.fill(background_);
    QPainterPath path(QPointF(params_.XToImageCords(data_[0].first),
                              params_.YToImageCords(data_[0].second)));
    unsigned step = 1 + data_.size() / params_.max_points_number_;
    for (unsigned i = 1; i < data_.size(); i += step)
    {
        path.lineTo(params_.XToImageCords(data_[i].first),
                    params_.YToImageCords(data_[i].second));
    }
    painter_.drawPath(path);
}

