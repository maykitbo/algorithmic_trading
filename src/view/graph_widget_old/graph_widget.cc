#include "graph_widget.h"

using namespace s21;

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , static_image_(QSize(1, 1), QImage::Format_RGB16)
    , axis_text_image_(QSize(1, 1), QImage::Format_ARGB32)
    , graph_image_(QSize(1, 1), QImage::Format_ARGB32)
    , draw_graph(&GraphWidget::DrawGraph)
    , names_frame_(this)
{
    static_image_.fill(s_.background_color);
    axis_text_image_.fill(Qt::transparent);
    graph_image_.fill(Qt::transparent);

    names_frame_.setStyleSheet("background-color: " + s_.names_frame_background_color.name() + ";");

    connect(&names_frame_, &NamesFrame::NameRemoved, [this] (GraphName *name) {
        data_.erase(data_.begin() + name->Index());
        s_.colors.push_back(name->Color());
        SetMinMax();
        Draw();
    });
    connect(&names_frame_, &NamesFrame::ReDraw, [this] {
        SetMinMax();
        Draw();
    });

 
    // setAttribute(Qt::WA_AcceptTouchEvents);
    // setMouseTracking(true);
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    const auto &size = event->size();

    height_ = size.height();
    width_ = size.width();

    qreal gh_old = graph_height_;
    qreal gw_old = graph_width_;
    graph_height_ = height_ - s_.top_indent - s_.bottom_indent;
    graph_width_ = width_ - s_.left_indent - s_.right_indent;

    qreal dw = gw_old / graph_width_;
    qreal dh = gh_old / graph_height_;
    x_factor_ /= dw;
    y_factor_ /= dh;
    dx_ /= dw;
    dy_ = (dy_ - gh_old) / dh + graph_height_;

    if (graph_width_ < 16 || graph_height_ < 16)
    {
        return QWidget::resizeEvent(event);
    }
    static_image_ = static_image_.scaled(size, Qt::IgnoreAspectRatio);
    axis_text_image_ = axis_text_image_.scaled(size, Qt::IgnoreAspectRatio);
    graph_image_ = graph_image_.scaled(graph_width_,
                                       graph_height_,
                                       Qt::IgnoreAspectRatio);
    QWidget::resizeEvent(event);
    DrawGrids();
    Draw();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter(this).drawImage(0, 0, static_image_);
    QPainter(this).drawImage(0, 0, axis_text_image_);
    QPainter(this).drawImage(s_.left_indent, s_.top_indent, graph_image_);
    QWidget::paintEvent(event);
}

void GraphWidget::AddName(const QString &name, unsigned index)
{
    QColor color = s_.colors.front();
    s_.colors.pop_front();
    names_frame_.AddName(name,
                        color,
                        QFont(s_.text_font, s_.names_text_size),
                        index == 0 ? false : true,
                        index);
}

void GraphWidget::AddData(const Points &data, const QString &name)
{
    data_.push_back(data);
    AddName(name, data_.size() - 1);

    SetMinMax();
    if (data_.size() == 1)
    {
        UpdateFactors();
    }
    Draw();
}

void GraphWidget::Draw()
{
    // if (ready_)
    // {
    DrawAxisText();
    DrawGraph();
    // }
    update();
}

void GraphWidget::SetMinMax()
{
    qreal dxminmax = x_max_ - x_min_;
    qreal dyminmax = y_max_ - y_min_;

    y_min_ = std::numeric_limits<qreal>::max();
    y_max_ = std::numeric_limits<qreal>::min();
    x_min_ = std::numeric_limits<qreal>::max();
    x_max_ = std::numeric_limits<qreal>::min();
    size_ = 0;

    names_frame_.ForVisiable([&] (const GraphName &name)
    {
        const auto &data = data_[name.Index()];
        auto minmax = std::minmax_element(data.begin(), data.end(),
            [] (const Point &p1, const Point &p2)
            {
                return p1.y < p2.y;
            });
        y_min_ = std::min(y_min_, minmax.first->y);
        y_max_ = std::max(y_max_, minmax.second->y);
        x_min_ = std::min(x_min_, data.front().x);
        x_max_ = std::max(x_max_, data.back().x);
        size_ = std::max(size_, (unsigned)data.size());
    });
    if (x_min_ >= x_max_ || y_min_ >= y_max_ || size_ == 0)
    {
        ready_ = false;
    }
    else
    {
        ready_ = true;

        qreal fx = dxminmax / (x_max_ - x_min_);
        qreal fy = dyminmax / (y_max_ - y_min_);
        x_factor_ *= fx;
        y_factor_ *= fy;
        dx_ *= fx;
        dy_ = (dy_ - graph_height_) * fy + graph_height_;

        SetDx(dx_);
        SetDy(dy_);
    }
    
}

void GraphWidget::UpdateFactors()
{
    x_factor_ = graph_width_ / (x_max_ - x_min_);
    dx_ = -1.0 * x_min_ * x_factor_;

    y_factor_ = graph_height_ / (y_min_ - y_max_);
    dy_ = graph_height_ - y_min_ * y_factor_;

    scale_ = 0;
}

qreal GraphWidget::X_(qreal x) const
{
    return (x * x_factor_) + dx_;
}

qreal GraphWidget::Y_(qreal y) const
{
    return (y * y_factor_) + dy_;
}

void GraphWidget::DrawGraph()
{
    graph_image_.fill(Qt::transparent);
    if (!ready_) return;

    painter_.begin(&graph_image_);
    names_frame_.ForVisiable([&] (const GraphName &name)
    {
        unsigned k = name.Index();
        unsigned size = data_[k].size();
        QPainterPath path(QPoint(X_(data_[k][0].x), Y_(data_[k][0].y)));
        unsigned del = 1 * ((size / s_.max_point_on_one_graph) + 1);
        for (unsigned i = 1; i < size; i += del)
        {
            path.lineTo(X_(data_[k][i].x), Y_(data_[k][i].y));
        }
        painter_.setPen(QPen(name.Color(), s_.graph_width));
        painter_.drawPath(path);
    });
    painter_.end();
}

void GraphWidget::DrawGraphWithPoints()
{
    for (unsigned k = 0; k < data_.size(); ++k)
    {
        // {
        //     painter_.setPen(QPen(s_.point_colors[k], s_.point_radius));
        //     QPainterPath path(QPoint(X_(0), Y_(data_[k][0].y)));
        //     for (unsigned i = 1; i < size_; ++i)
        //     {
        //         qreal x = X_(i);
        //         qreal y = Y_(data_[k][i].y);
        //         path.lineTo(x, y);void DrawGrids();
        void DrawAxisText();
        //         painter_.drawPoint(x, y);
        //     }
        //     painter_.setPen(QPen(s_.colors[k], s_.graph_width));
        //     painter_.drawPath(path);
        // }
    }
}

void GraphWidget::DrawGrids()
{
    static_image_.fill(s_.background_color);
    painter_.begin(&static_image_);
    qreal buttom = height_ - s_.bottom_indent;
    qreal right = width_ - s_.right_indent;

    painter_.setPen(s_.axes_pen);
    // draw vertical axes
    painter_.drawLine(s_.left_indent, s_.top_indent,
                      s_.left_indent, buttom);

    // draw horizontal axes
    painter_.drawLine(s_.left_indent, buttom, right, buttom);

    // draw horizontal grids
    painter_.setPen(s_.gorizontal_grid_pen);
    int min = s_.top_indent;
    int max = buttom;
    for (int i = max; i > min; i -= s_.y_grid_step)
    {
        painter_.drawLine(s_.left_indent, i, right, i);
    }

    // draw vertical grids
    min = s_.left_indent;
    max = right;
    for (int i = min; i < max; i += s_.x_grid_step)
    {
        painter_.drawLine(i, s_.top_indent, i, buttom);
    }
    painter_.end();
}

void GraphWidget::DrawAxisText()
{
    axis_text_image_.fill(Qt::transparent);
    if (!ready_) return;

    painter_.begin(&axis_text_image_);
    qreal buttom = height_ - s_.bottom_indent;
    qreal right = width_ - s_.right_indent;

    // draw vertical axes text
    painter_.setPen(QPen(s_.axes_text_color));
    painter_.setFont(QFont(s_.text_font, s_.axes_text_size));
    int min = s_.top_indent;
    int max = buttom;
    for (int i = max; i > min; i -= s_.y_grid_step)
    {
        painter_.drawText(5, i, s_.number_format(((qreal)i - dy_) / y_factor_));
    }

    // draw horizontal axes text
    for (int i = (int)s_.left_indent; i < right; i += s_.x_grid_step)
    {
        time_t time = ((time_t)(((qreal)i - dx_ - (int)s_.left_indent) / x_factor_)) * 60 * 60 * 24;
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(time);
        painter_.drawText(i - 30, buttom + 15, dateTime.toString(s_.date_format));
    }
    painter_.end();
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    qreal scale_factor = 1.0;
    if (event->angleDelta().y() > 0)
    {
        ++scale_;
        scale_factor = s_.wheel_scale_factor;
    }
    else
    {
        if (scale_ == 0)
        {
            return QWidget::wheelEvent(event);
        }
        --scale_;
        scale_factor = 1.0 / s_.wheel_scale_factor;
    }

    QPointF cursor_pos = event->position();
    qreal pos_x = cursor_pos.x() - s_.left_indent;
    qreal pos_y = cursor_pos.y() - s_.top_indent;

    x_factor_ *= scale_factor;
    y_factor_ *= scale_factor;

    SetDx(pos_x - scale_factor * (pos_x - dx_));

    SetDy(pos_y - scale_factor * (pos_y - dy_));

    Draw();
    QWidget::wheelEvent(event);
}

void GraphWidget::SetDx(qreal dx)
{
    dx_ = std::max(std::min(dx, -1.0 * x_min_ * x_factor_), graph_width_ - x_max_ * x_factor_);
}

void GraphWidget::SetDy(qreal dy)
{
    dy_ = std::min(std::max(dy, graph_height_ - y_min_ * y_factor_), -1.0 * y_max_ * y_factor_);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_pressed_)
    {
        SetDx(dx_ - mouse_pos_.x() + event->pos().x());
        SetDy(dy_ - mouse_pos_.y() + event->pos().y());
        Draw();
        mouse_pos_ = event->pos();
    }
    QWidget::mouseMoveEvent(event);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_pressed_ = true;
        mouse_pos_ = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_pressed_ = false;
    }
    QWidget::mouseReleaseEvent(event);
}


void GraphWidget::Clear()
{
    data_.clear();
    
    s_.colors =
    {
        QColor(255, 0, 0),
        QColor(132, 169, 141),
        QColor(174, 124, 124),
        QColor(92, 108, 124),
        QColor(149, 149, 149),
    };

    names_frame_.Clear();
    ready_ = false;

    Draw();
}


void GraphWidget::SetDrawPoints(bool draw_points)
{
    if (draw_points)
    {
        draw_graph = &GraphWidget::DrawGraphWithPoints;
    } else
    {
        draw_graph = &GraphWidget::DrawGraph;
    }
}


// for testing
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    // SetDrawPoints(true);
    // if (event->key() == Qt::Key_Space)
    // {
    //     unsigned size = 100;
    //     Points data(size);
    //     for (unsigned i = 0; i < size; ++i)
    //     {
    //         // point.x = Random::Int(738395, 738395 + 365);
    //         // data[i].x = 738395 + i;
    //         // data[i].x.year = 2018 + i / 365;
    //         // data[i].x.month = 1 + i / 30 - (i / 365) * 12;
    //         // data[i].x.day = i - (i / 30) * 30 - (i / 365) * 365;
    //         data[i].y = Random::Normal<double>(30.0, 100.0);
    //     }
    //     AddData(data);
    // }
    QWidget::keyPressEvent(event);
}
