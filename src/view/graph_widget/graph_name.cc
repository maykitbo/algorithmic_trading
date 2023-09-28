#include "graph_name.h"

using namespace s21;

GraphName::GraphName(const QString &name, const QColor &color, const QFont &font, bool removable, unsigned index, QWidget *parent)
    : QWidget(parent)
    , layout_(this)
    , name_label_(name, this)
    , visible_button_("", this)
    , remove_button_(nullptr)
    , index_(index)
    , visible_(true)
    , color_(color)
{
    
    name_label_.setStyleSheet("QLabel { color: " + color_.name() + ";\
                                background-color: rgba(0,0,0,0%); }");
    name_label_.setFont(font);
    name_label_.setMaximumSize(250, 20);
    visible_button_.setMaximumSize(20, 20);
    // visible_button_.setStyleSheet("QRadioButton { background-color: rgb(255,255,255); }");
    layout_.addWidget(&visible_button_);
    visible_button_.setChecked(true);
    layout_.addWidget(&name_label_);

    name_label_.setCursor(Qt::OpenHandCursor);


    if (removable)
    {
        remove_button_ = new QPushButton("X", this);
        remove_button_->setMaximumSize(20, 20);
        layout_.addWidget(remove_button_);
        connect(remove_button_, &QPushButton::clicked, this, &GraphName::Remove);
    }

    connect(&visible_button_, &QRadioButton::toggled, this, [&] (bool checked [[maybe_unused]])
    {
        visible_ = !visible_;
        emit ReDraw();
    });

    setLayout(&layout_);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

}

GraphName::~GraphName()
{
    if (remove_button_ != nullptr)
        delete remove_button_;
}

NamesFrame::NamesFrame(QWidget *parent)
    : QFrame(parent)
    , layout_(this)
{
    setAcceptDrops(true);
    layout_.setSpacing(6);
}

void NamesFrame::AddName(const QString &name, const QColor &color, const QFont &font, bool removable, unsigned index)
{
    GraphName *ptr = new GraphName(name, color, font, removable, index, this);
    layout_.addWidget(ptr);

    ptr->name_label_.installEventFilter(this);

    connect(ptr, &GraphName::Remove, this, [this, ptr] ()
    {
        layout_.removeWidget(ptr);
        for (unsigned i = 0; i < layout_.count(); ++i)
        {
            auto &name = (*this)[i];
            if (name.Index() > ptr->Index())
                --name;
        }
        emit NameRemoved(ptr);
        delete ptr;
    });
    connect(ptr, &GraphName::ReDraw, this, &NamesFrame::ReDraw);

}

void NamesFrame::ForVisiable(const std::function<void(const GraphName&)> &func)
{
    for (int i = 0; i < layout_.count(); ++i)
    {
        const auto &name = (*this)[i];
        if (name.Visible())
        {
            func(name);
        }
    }

}

void NamesFrame::Clear()
{
    while (layout_.count() > 0)
    {
        delete layout_.itemAt(0)->widget();
        layout_.removeItem(layout_.itemAt(0));
    }
}

bool NamesFrame::LablePressed(QLabel *label, QEvent *event)
{
    if (static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
    {
        dragged_name_ = static_cast<GraphName*>(label->parentWidget());
        label->setCursor(Qt::ClosedHandCursor);
        return true;
    }
    return false;
}

bool NamesFrame::LableReleased(QLabel *label, QEvent *event)
{
    if (static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
    {
        label->setCursor(Qt::OpenHandCursor);
        dragged_name_ = nullptr;
        return true;
    }
    return false;
}

bool NamesFrame::LableMove(QLabel *label, QEvent *event)
{
    if (dragged_name_ == nullptr)
        return false;

    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    auto pos = mapFromGlobal(mouse_event->globalPos());

    int k = layout_.indexOf(dragged_name_);

    if (k < layout_.count() - 1)
    {
        auto pos_under = layout_.itemAt(k + 1)->widget()->pos();
        if (pos.y() > pos_under.y() + 2 * dragged_name_->height() / 3)
        {
            layout_.removeWidget(dragged_name_);
            layout_.insertWidget(k + 1, dragged_name_);
            emit ReDraw();
            return true;
        }
    }
    if (k > 0)
    {
        auto pos_above = layout_.itemAt(k - 1)->widget()->pos();
        if (pos.y() < pos_above.y() + dragged_name_->height() / 3)
        {
            layout_.removeWidget(dragged_name_);
            layout_.insertWidget(k - 1, dragged_name_);
            emit ReDraw();
            return true;
        }
    }

    return true;

}

bool NamesFrame::eventFilter(QObject *object, QEvent *event)
{
    if (object == nullptr)
        return false;

    QLabel *name_label = qobject_cast<QLabel*>(object);
    if (name_label)
    {
        QMouseEvent *mouseEvent = nullptr;

        switch (event->type())
        {
        case QEvent::MouseButtonPress:
            if (LablePressed(name_label, event))
                return true;
            break;
        case QEvent::MouseButtonRelease:
            if (LableReleased(name_label, event))
                return true;
            break;
        case QEvent::MouseMove:
            if (LableMove(name_label, event))
                return true;
            break;
        }
    }
    return QObject::eventFilter(object, event);
}
