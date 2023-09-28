#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QFrame>
#include <QDragEnterEvent>
// #include <QEventFilter>

#include <iostream>
// #include "graph_widget.h"

#include "style.h"

namespace s21 {

class NamesFrame;

class GraphName : public QWidget
{
    friend class NamesFrame;
    Q_OBJECT

    public:
        GraphName(const QString &name, const QColor &color, const QFont &font, bool removable, unsigned index, QWidget *parent = nullptr);
        bool Visible() const noexcept { return visible_; }
        ~GraphName();
        unsigned Index() const noexcept { return index_; }
        const QColor &Color() const noexcept { return color_; }
        void operator--() noexcept { --index_; }
    
    signals:
        void Remove();
        void ReDraw();
    
    private:
        QLabel name_label_;
        QRadioButton visible_button_;
        QPushButton *remove_button_;
        QHBoxLayout layout_;
        QColor color_;
        bool visible_;
        unsigned index_;
};

class NamesFrame : public QFrame
{
    Q_OBJECT

    public:
        NamesFrame(QWidget *parent = nullptr);
        void AddName(const QString &name, const QColor &color, const QFont &font, bool removable, unsigned index);
        void Clear();
        unsigned Size() const noexcept { return layout_.count(); }
        GraphName &operator[](unsigned index) {
            return *static_cast<GraphName *>(layout_.itemAt(index)->widget());
        }
        void ForVisiable(const std::function<void(const GraphName&)> &func);
    
    protected:
        bool eventFilter(QObject *object, QEvent *event) override;
    
    signals:
        void NameRemoved(GraphName *name);
        void ReDraw();
    
    private:
        QVBoxLayout layout_;
        QPoint drag_start_position_;
        GraphName *dragged_name_{nullptr};

        bool LablePressed(QLabel *label, QEvent *event);
        bool LableReleased(QLabel *label, QEvent *event);
        bool LableMove(QLabel *label, QEvent *event);
};

} // namespace s21
