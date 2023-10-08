#pragma once

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QFileDialog>
#include <QVBoxLayout>

#include <list>

#include "background_frame.h"
#include "painter_frame.h"
#include "painters/colors_set.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Frame; }
QT_END_NAMESPACE

namespace Graph {


class Frame : public QWidget
{
    Q_OBJECT

    public:
        Frame(Parameters &params, QWidget *parent = nullptr);
        void AddGraph(const QString &name, const data_t &data, bool points = true, bool removeable = true);
        void AddGraph(const QString &name, data_t &&data, bool points = true, bool removeable = true);

        BackgroundFrame *GetBackground() { return background_; }
        void Draw();
        void ForVisible(const std::function<void(PainterFrame*)> &func);
        void ForGraphLayers(const std::function<void(PainterFrame*)> &func);

        void Clear();
        void Resize();

        ~Frame();
    
    signals:
        void GraphRemoved();
        void ReDraw();

    protected:
        bool eventFilter(QObject *object, QEvent *event) override;

    private slots:
        void Hide();
        void Save();

    private:
        Ui::Frame *ui_;
        Parameters &p_;

        BackgroundFrame *background_;

        // QWidget *widget_;
        QVBoxLayout *layout_;
        QPoint drag_start_pos_;
        PainterFrame *dragged_layer_{nullptr};


        int visible_count_{0};

        bool LablePressed(QLabel *label, QEvent *event);
        bool LableReleased(QLabel *label, QEvent *event);
        bool LableMove(QLabel *label, QEvent *event);

        QPen CreatePen();
        void AddLayer(PainterFrame *ptr, bool points, bool removeable);

        void ProcessMinMax();

        void SetStyles();

        ColorsSet<std::list<QColor>> colors_;
};


} // namespace Graph

