#pragma once

#include <QWidget>

#include "painters/background.h"
#include "painters/painter.h"
#include "abstract_frame.h"



QT_BEGIN_NAMESPACE
namespace Ui { class BackgroundFrame; }
QT_END_NAMESPACE

namespace Graph {


class BackgroundFrame : public AbstractFrame, public Background
{
    Q_OBJECT

    public:
        BackgroundFrame(Parameters &params, QWidget *parent = nullptr);
        ~BackgroundFrame();
        void Resize(QSize size) override;
        void Update();

    private:
        Ui::BackgroundFrame *ui_;
        void UpdateOneGridSpin(QDoubleSpinBox *spin, qreal value, qreal distance);

        void Action() override;

};

} // namespace Graph
