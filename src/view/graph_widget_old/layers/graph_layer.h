#pragma once

#include "image_layer.h"

#include <QPainterPath>

namespace s21 {

enum GraphPoints
{
    None,
    Punctured,
    Full
};

struct GraphLayerParams
{
    GraphPoints draw_points{None};
    QPen graph_pen;
    QPen points_pen{Qt::transparent};
    QColor background{Qt::transparent};
    unsigned max_points_number_{30000};
};

class GraphLayer : public ImageLayer
{
    Q_OBJECT
    public:
        GraphLayer(const ImageParams &params,
                    const QPen &pen,
                    const QColor &background,
                    const std::vector<std::pair<double, double>> &data,
                    GraphPoints draw_points = None,
                    QImage::Format format = QImage::Format_ARGB32);

        GraphLayer(const ImageParams &params,
                    const QPen &pen,
                    const QColor &background,
                    std::vector<std::pair<double, double>> &&data,
                    GraphPoints draw_points = None,
                    QImage::Format format = QImage::Format_ARGB32);

        void Draw() override;
        void DrawingPoints(GraphPoints draw_points) { draw_points_ = draw_points; }

    private:
        std::vector<std::pair<double, double>> data_;
        GraphPoints draw_points_;
};


} // namespace s21
