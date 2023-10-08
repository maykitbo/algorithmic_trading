#include "painter_frame.h"
#include "../ui_conf/ui_painter_frame.h"

using namespace Graph;

PainterFrame::PainterFrame(Parameters &params,
                const QString &name,
                const QPen &graph_pen,
                QWidget *parent)
    : AbstractFrame(parent)
    , Painter(params, name, graph_pen)
    , ui_(new Ui::PainterFrame)
{
    Init();
}


PainterFrame::PainterFrame(Parameters &params,
                const QString &name,
                const data_t &data,
                const QPen &graph_pen,
                QWidget *parent)
    : AbstractFrame(parent)
    , Painter(params, name, data, graph_pen)
    , ui_(new Ui::PainterFrame)
{
    Init();
}


PainterFrame::PainterFrame(Parameters &params,
                const QString &name,
                data_t &&data,
                const QPen &graph_pen,
                QWidget *parent)
    : AbstractFrame(parent)
    , Painter(params, name, data, graph_pen)
    , ui_(new Ui::PainterFrame)
{
    Init();
}

void PainterFrame::Action()
{
    Draw();
    emit ReDraw();
}

void PainterFrame::Init()
{
    ui_->setupUi(this);

    HideAndSettingsHelper(ui_->hide_button, ui_->settings_frame, ui_->name_lable, graph_pen_.color());

    ui_->name_lable->setCursor(Qt::OpenHandCursor);
    ui_->name_lable->setText(name_);

    ui_->visible_radio->setStyleSheet(visible_resources);

    connect(ui_->remove_button, &QPushButton::clicked, this, &PainterFrame::Removed);
    connect(ui_->visible_radio, &QRadioButton::toggled, this, [&] (bool checked)
    {
        emit ChangeVisible(checked);
        emit ReDraw();
    });
    connect(ui_->save_button, &QPushButton::clicked, this, [&] ()
    {
        QString file_name = SaveImageDialog(this);
        if (!file_name.isEmpty())
        {
            image_.save(file_name);
        }
    });

    LineStyleHelper(ui_->line_tool, ui_->line_spin, ui_->line_box, &graph_pen_);
    PointStyleHelper(ui_->points_tool, ui_->points_spin, ui_->points_box, &points_pen_);

    VisibleHelper(ui_->line_radio, &draw_lines_);
    VisibleHelper(ui_->points_radio, &draw_points_);
}

QLabel *PainterFrame::NameLabel()
{
    return ui_->name_lable;
}

void PainterFrame::SetRemoveable(bool removeable)
{
    ui_->remove_button->setEnabled(removeable);
}

bool PainterFrame::Visible() const
{
    return ui_->visible_radio->isChecked();
}

PainterFrame::~PainterFrame()
{
    delete ui_;
}

