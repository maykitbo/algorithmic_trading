#include "background_frame.h"
#include "../ui_conf/ui_background_frame.h"

using namespace Graph;

BackgroundFrame::BackgroundFrame(Parameters &params, QWidget *parent)
    : AbstractFrame(parent)
    , ui_(new Ui::BackgroundFrame)
    , Background(params)
{
    ui_->setupUi(this);

    HideAndSettingsHelper(ui_->hide_button, ui_->settings_frame, ui_->name_lable, axes_pen_.color());
        
    connect(ui_->color_button, &QPushButton::clicked, this, [&] ()
    {
        QColor color = QColorDialog::getColor(color_, this, "Select color");
        if (color.isValid())
        {
            SetColor(color);
            emit ReDraw();
        }
    });

    LineStyleHelper(ui_->grid_button, ui_->grids_spin, ui_->grids_box, &grid_pen_);
    LineStyleHelper(ui_->axes_button, ui_->axes_spin, ui_->axes_box, &axes_pen_);

    text_font_ = ui_->font_box->currentFont();
    ToolAndSpinHelper(ui_->text_button, ui_->font_spin, &text_pen_);
    connect(ui_->font_box, &QFontComboBox::currentFontChanged, this, [this] (const QFont &font)
    {
        SetTextFont(font);
        emit ReDraw();
    });

    VisibleHelper(ui_->x_radio, &vertical_grid_);
    VisibleHelper(ui_->y_radio, &horizontal_grid_);
    connect(ui_->x_step_spin, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), this, [this] (qreal value)
    {
        SetVerticalGridStep(value);
        emit ReDraw();
    });
    connect(ui_->y_step_spin, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), this, [this] (qreal value)
    {
        SetHorizontalGridStep(value);
        emit ReDraw();
    });
}

void BackgroundFrame::Action()
{
    Draw();
    emit ReDraw();
}

void BackgroundFrame::Resize(QSize size)
{
    image_ = QImage(size, image_.format());
    Update();
}

void BackgroundFrame::Update()
{
    UpdateOneGridSpin(ui_->x_step_spin, GetVerticalGridStep(), p_.GetXDistance());
    UpdateOneGridSpin(ui_->y_step_spin, GetHorizontalGridStep(), p_.GetYDistance());
    Draw();
}

void BackgroundFrame::UpdateOneGridSpin(QDoubleSpinBox *spin, qreal value, qreal distance)
{
    spin->blockSignals(true);
    spin->setMaximum(distance);
    spin->setMinimum(distance / 1000.0);
    spin->setValue(value);
    spin->setSingleStep(value / 10.0);
    spin->blockSignals(false);
}

BackgroundFrame::~BackgroundFrame()
{
    delete ui_;
}

