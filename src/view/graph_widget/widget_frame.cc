#include "widget_frame.h"

static void InitializeResources() {
    Q_INIT_RESOURCE(resources);
}

using namespace Graph;

WidgetFrame::WidgetFrame(bool attach_frame, QWidget *parent)
    : QWidget(parent)
    , frame_(new Frame(p_, nullptr))
    , layout_(new QGridLayout(this))
{
    InitializeResources();
    connect(frame_, &Frame::ReDraw, this, [&] ()
    {
        update();
    });
    setMinimumHeight(min_height_);
    setMinimumWidth(min_width_);
    layout_->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0, 2, 1);
    layout_->addItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding), 1, 1, 1, 1);


    if (attach_frame)
        AttachFrame();
}


void WidgetFrame::resizeEvent(QResizeEvent *event)
{
    const auto &size = event->size();

    p_.Resize(size.width(), size.height());

    QWidget::resizeEvent(event);
    frame_->Resize();
    update();
}

void WidgetFrame::paintEvent(QPaintEvent *event)
{
    QPainter(this).drawImage(0, 0, frame_->GetBackground()->GetImage());
    frame_->ForVisible([&] (PainterFrame *layer)
    {
        QPainter(this).drawImage(p_.Left(), p_.Top(), layer->GetImage());
    });
    QWidget::paintEvent(event);
}

void WidgetFrame::AddGraph(const data_t &data, const QString &name, bool points, bool removeable)
{
    frame_->AddGraph(name, data, points, removeable);
    update();
}

void WidgetFrame::AddGraph(data_t &&data, const QString &name, bool points, bool removeable)
{
    frame_->AddGraph(name, data, points, removeable);
    update();
}


void WidgetFrame::wheelEvent(QWheelEvent *event)
{
    qreal scale_factor = 1.0;
    if (event->angleDelta().y() > 0)
    {
        ++scale_;
        scale_factor = wheel_scale_factor_;
    }
    else
    {
        if (scale_ == 0)
        {
            return QWidget::wheelEvent(event);
        }
        --scale_;
        scale_factor = 1.0 / wheel_scale_factor_;
    }

    p_.WheelScale(scale_factor, event->position());

    frame_->Draw();
    update();
    QWidget::wheelEvent(event);
}


void WidgetFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_pressed_)
    {
        p_.Move(event->pos().x() - mouse_pos_.x(),
                event->pos().y() - mouse_pos_.y());
        frame_->Draw();
        update();
        mouse_pos_ = event->pos();
    }
    QWidget::mouseMoveEvent(event);
}

void WidgetFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_pressed_ = true;
        mouse_pos_ = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void WidgetFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_pressed_ = false;
    }
    QWidget::mouseReleaseEvent(event);
}


void WidgetFrame::Clear()
{
    scale_ = 0;
    frame_->Clear();
    update();
}

Frame *WidgetFrame::DetachFrame()
{
    layout_->removeWidget(frame_);
    frame_->setParent(nullptr);
    return frame_;
}

Frame *WidgetFrame::GetFrame()
{
    return frame_;
}

void WidgetFrame::AttachFrame()
{
    frame_->setParent(this);
    layout_->addWidget(frame_, 0, 1, 1, 1);
}

