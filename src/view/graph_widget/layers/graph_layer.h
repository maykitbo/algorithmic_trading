#pragma once

#include "image_layer.h"

#include <QPainterPath>

namespace s21 {

enum GraphPoints
{
    None,
    Full
};

class GraphLayer : public ImageLayer
{
    Q_OBJECT
    public:
        GraphLayer(const ImageParams &params,
                    const QPen &graph_pen_,
                    GraphPoints draw_points = None,
                    QColor points_color = Qt::red,
                    QImage::Format format = QImage::Format_ARGB32);

        GraphLayer(const ImageParams &params,
                    const QPen &graph_pen_,
                    const std::vector<std::pair<double, double>> &data,
                    GraphPoints draw_points = None,
                    QColor points_color = Qt::red,
                    QImage::Format format = QImage::Format_ARGB32);

        GraphLayer(const ImageParams &params,
                    const QPen &graph_pen_,
                    std::vector<std::pair<double, double>> &&data,
                    GraphPoints draw_points = None,
                    QColor points_color = Qt::red,
                    QImage::Format format = QImage::Format_ARGB32);

        void Draw() override;

        void DrawingPoints(GraphPoints draw_points)
            { draw_points_ = draw_points; }
        void SetPointsColor(QColor color)
            { points_pen_.setColor(color); }
        void SetGraphColor(QColor color)
            { graph_pen_.setColor(color); }
        void SetMaxPointsNumber(unsigned max_points_number)
            { max_points_number_ = max_points_number; }
        void SetData(const std::vector<std::pair<double, double>> &data)
            { data_ = data; }
        void SetData(std::vector<std::pair<double, double>> &&data)
            { data_ = std::move(data); }
        void AddPoint(const std::pair<double, double> &point)
            { data_.push_back(point); }
        void AddData(const std::vector<std::pair<double, double>> &data)
            { data_.insert(data_.end(), data.begin(), data.end()); }
        void AddData(std::vector<std::pair<double, double>> &&data)
            { data_.insert(data_.end(), std::make_move_iterator(data.begin()), std::make_move_iterator(data.end())); }

    private:
        std::vector<std::pair<double, double>> data_;
        GraphPoints draw_points_;
        QPen points_pen_;
        QPen graph_pen_;
        unsigned max_points_number_{30000};
};


} // namespace s21
