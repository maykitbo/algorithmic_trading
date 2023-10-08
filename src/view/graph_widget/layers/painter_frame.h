#pragma once

#include "painters/painter.h"
#include "abstract_frame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PainterFrame; }
QT_END_NAMESPACE

namespace Graph {

class PainterFrame : public AbstractFrame, public Painter
{
    Q_OBJECT

    public:
        PainterFrame(Parameters &params,
                        const QString &name,
                        const QPen &graph_pen,
                        QWidget *parent = nullptr);
        PainterFrame(Parameters &params,
                        const QString &name,
                        const data_t &data,
                        const QPen &graph_pen,
                        QWidget *parent = nullptr);
        PainterFrame(Parameters &params,
                        const QString &name,
                        data_t &&data,
                        const QPen &graph_pen,
                        QWidget *parent = nullptr);
        ~PainterFrame();

        bool Visible() const;
        QLabel *NameLabel();
        void SetRemoveable(bool removeable);
    
    signals:
        void Removed();
        void ReDraw();
        void ChangeVisible(bool visible);

    private:
        Ui::PainterFrame *ui_;

        void Action() override;
        void Init();
};

} // namespace Graph
