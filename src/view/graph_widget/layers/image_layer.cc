#include "image_layer.h"

using namespace s21;


ImageLayer::ImageLayer(const ImageParams &params,
                    QColor background,  
                    QImage::Format format)
    : image_(params.size, format)
    , params_(params)
    , background_(background)
    , painter_(&image_)
    {}

void ImageLayer::Resize()
{
    image_ = QImage(params_.size, image_.format());
    Draw();
}
