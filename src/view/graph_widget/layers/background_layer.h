#pragma once

#include "image_layer.h"

namespace s21 {

enum BackgroundType
{
    None,
    Axis,
};

class BackgroundLayer : public ImageLayer
{
    public:
        BackgroundLayer(const ImageParams &params,
                        QColor background,
                        QPen axis_pen,
                        BackgroundType type = Axis,
                        QImage::Format format = QImage::Format_RGB16);

        void Draw() override;

        void SetAxisPen(QPen pen)
            { axis_pen_ = pen; }
        void SetType(BackgroundType type)
            { type_ = type; }
    
    private:
        BackgroundType type_;
        QPen axis_pen_;

};














} // namespace s21
