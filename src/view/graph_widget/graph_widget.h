#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGestureEvent>
#include <QPainterPath>
#include <QWheelEvent>
#include <QtMath>
#include <QDateTime>
#include <QSpacerItem>

#include "data_struct.h"
#include "utility/utility.h"
#include "style.h"
#include "graph_name.h"


#include <algorithm>
#include <functional>

namespace s21 {

class NamesFrame;

class GraphWidget : public QWidget
{
    friend class NamesFrame;
    Q_OBJECT

    public:
        GraphWidget(QWidget *parent = 0);
        virtual ~GraphWidget() = default;

        void AddData(const Points &data, const QString &name);
        // void AddPoint(const Point &point, unsigned index);
        void SetDrawPoints(bool draw_points);
        GraphStyle &Style() { return s_; }
        void Clear();
        // void AddNamesFrame(NamesFrame *names_frame);
        NamesFrame *GetNamesFrame() { return &names_frame_; }
    
    signals:
        void GraphRemoved(unsigned index);
    
    private:
        // void DrawAxes();
        void DrawGraph();
        void DrawGraphWithPoints();
        void Draw();
        using DrawFunction = void (GraphWidget::*)();
        DrawFunction draw_graph;

        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        // void gestureEvent(QGestureEvent *event) override;
        // bool event(QEvent *event) override;

        void AddName(const QString &name, unsigned index);

        // for testing
        void keyPressEvent(QKeyEvent *event) override;

        void SetMinMax();
        void UpdateFactors();

        void SetDx(qreal dx);
        void SetDy(qreal dy);
        void DrawGrids();
        void DrawAxisText();
        qreal X_(qreal x) const;
        qreal Y_(qreal y) const;

        GraphStyle s_;

        QPainter painter_;
        QImage static_image_;
        QImage graph_image_;
        QImage axis_text_image_;
    
        qreal width_;
        qreal height_;
        qreal graph_width_;
        qreal graph_height_;
        qreal y_min_{0};
        qreal y_max_{0};
        qreal x_min_{0};
        qreal x_max_{0};
        int scale_{0};
        qreal x_factor_;
        qreal y_factor_;
        qreal dy_{0};
        qreal dx_{0};
        unsigned size_{0};
        QPoint mouse_pos_{0, 0};
        bool mouse_pressed_;
        bool ready_{false};

        std::vector<Points> data_;
        // std::vector<GraphName*> names_;
        // QHBoxLayout *names_layout_;
        // QVBoxLayout *main_layout_;
        std::vector<int> years_;
        std::vector<int> months_;
        NamesFrame names_frame_;
};

} // namespace s21


