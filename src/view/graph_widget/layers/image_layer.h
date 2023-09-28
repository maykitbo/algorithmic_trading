#pragma once

#include <QImage>
#include <QPainter>
#include <QPen>

#include "image_params.h"

namespace s21 {

class ImageLayer
{
    Q_OBJECT

    public:
        ImageLayer(const ImageParams &params,
                    QColor background,
                    QImage::Format format = QImage::Format_ARGB32);
        virtual void Draw() = 0;
        virtual void Resize();
        const QImage &GetImage() const noexcept
            { return image_; }
        void SetBackground(QColor color)
            { background_ = color; }

    protected:
        QImage image_;
        const ImageParams &params_;
        QPainter painter_;
        QColor background_;
};


} // namespace s21


