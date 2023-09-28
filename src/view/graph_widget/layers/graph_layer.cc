#include "graph_layer.h"

using namespace s21;


GraphLayer::GraphLayer(const ImageParams &params,
                    const QPen &graph_pen_,
                    GraphPoints draw_points,
                    QColor points_color,
                    QImage::Format format)
    : ImageLayer(params, Qt::transparent, format)
    , draw_points_(draw_points)
    , points_pen_(points_color)
    , graph_pen_(graph_pen_)
    {}

GraphLayer::GraphLayer(const ImageParams &params,
                    const QPen &graph_pen_,
                    const std::vector<std::pair<double, double>> &data,
                    GraphPoints draw_points,
                    QColor points_color,
                    QImage::Format format)
    : ImageLayer(params, Qt::transparent, format)
    , draw_points_(draw_points)
    , points_pen_(points_color)
    , graph_pen_(graph_pen_)
    , data_(data)
    {}

GraphLayer::GraphLayer(const ImageParams &params,
            const QPen &graph_pen_,
            std::vector<std::pair<double, double>> &&data,
            GraphPoints draw_points,
            QColor points_color,
            QImage::Format format)
    : ImageLayer(params, Qt::transparent, format)
    , draw_points_(draw_points)
    , points_pen_(points_color)
    , graph_pen_(graph_pen_)
    , data_(std::move(data))
    {}

void GraphLayer::Draw()
{
    // painter_.begin(&image_);
    image_.fill(background_);
    std::vector<QPointF> points;
    unsigned step = 1 + data_.size() / max_points_number_;
    points.reserve(data_.size() / step);
    for (unsigned i = 0; i < data_.size(); i += step)
    {
        points.emplace_back(params_.XToImageCords(data_[i].first),
                            params_.YToImageCords(data_[i].second));
    }
    
    painter_.setPen(graph_pen_);
    painter_.drawPolyline(points.data(), points.size());
    if (draw_points_ == Full)
    {
        painter_.setPen(points_pen_);
        painter_.drawPoints(points.data(), points.size());
    }
}

