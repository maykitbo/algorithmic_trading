#pragma once

#include <QImage>
#include <QPainter>
#include <QPen>

namespace s21 {

struct ImageParams
{
    QSize size;
    qreal dx;
    qreal dy;

    qreal x_min;
    qreal x_max;
    qreal y_min;
    qreal y_max;

    qreal x_factor;
    qreal y_factor;

    qreal XToImageCords(double x) const noexcept;
    qreal YToImageCords(double y) const noexcept;
    double XToDataCords(qreal x) const noexcept;
    double YToDataCords(qreal y) const noexcept;
};

class ImageLayer
{
    Q_OBJECT

    public:
        ImageLayer(const ImageParams &params,
                    const QPen &pen,
                    const QColor &background,
                    QImage::Format format = QImage::Format_ARGB32);
        virtual void Draw() = 0;
        virtual void Resize();

        void SetBackground(const QColor &background);
        void SetPen(const QPen &pen);



    protected:
        QImage image_;
        const ImageParams &params_;
        QPainter painter_;
        QPen pen_;
        QColor background_;
};





} // namespace s21


