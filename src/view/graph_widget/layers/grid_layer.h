#pragma once

#include "image_layer.h"

namespace s21 {

enum GridType
{
    Vertical,
    Horizontal,
    Both,
};

enum GridTextType
{
    Number,
    Date,
};

class GridLayer : public ImageLayer
{
    public:
        GridLayer(const ImageParams &params,
                    QPen grid_pen,
                    QPen text_pen,
                    QFont text_font,
                    GridType type = Both,
                    bool show_text = false,
                    QImage::Format format = QImage::Format_ARGB32);
        
        void Draw() override;
        void SetType(GridType type)
            { type_ = type; }
        void SetShowText(bool show)
            { show_text_ = show; }
        void SetGridPen(QPen pen)
            { grid_pen_ = pen; }
        void SetTextPen(QPen pen)
            { text_pen_ = pen; }
        void SetTextFont(QFont font)
            { text_font_ = font; }
        void SetXTextType(GridTextType type)
            { x_text_func_ = type == Number ? &GridLayer::NumberFormat : &GridLayer::DateFormat; }
        void SetYTextType(GridTextType type)
            { y_text_func_ = type == Number ? &GridLayer::NumberFormat : &GridLayer::DateFormat; }
    
    private:
        QPen grid_pen_;
        QPen text_pen_;
        QFont text_font_;
        GridType type_;
        bool show_text_;

        QString NumberFormat(double n) const noexcept
            { return QString::number(n, params_.number_format.first,
                                    params_.number_format.second); }

        QString DateFormat(double n) const noexcept
            { return QDateTime::fromSecsSinceEpoch(n).toString(params_.date_format); }

        using TextFunc = QString (GridLayer::*)(double) const noexcept;

        TextFunc x_text_func_{&GridLayer::DateFormat};
        TextFunc y_text_func_{&GridLayer::NumberFormat};
};







} // namespace s21
