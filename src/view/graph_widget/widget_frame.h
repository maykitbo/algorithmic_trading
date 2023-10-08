#pragma once

#include "frame.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QGridLayout>
#include <QResource>

namespace Graph {

class WidgetFrame : public QWidget
{
    Q_OBJECT

    public:
        WidgetFrame(bool attach_frame = true, QWidget *parent = 0);
        virtual ~WidgetFrame() = default;
        void AddGraph(const data_t &data, const QString &name, bool points = false, bool removeable = true);
        void AddGraph(data_t &&data, const QString &name, bool points = false, bool removeable = true);

        void Clear();
        Frame *GetFrame();
        Frame *DetachFrame();
        void AttachFrame();
    
    private:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

        Parameters p_;

        QGridLayout *layout_;
    
        QPoint mouse_pos_{0, 0};
        bool mouse_pressed_;
        bool ready_{false};

        qreal wheel_scale_factor_{1.1};
        qreal min_width_{256};
        qreal min_height_{256};

        int scale_{0};

        Frame *frame_;
};


} // namespace Graph

