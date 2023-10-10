#include "frame.h"

#include "../ui_conf/ui_frame.h"

using namespace Graph;

Frame::Frame(Parameters &params, QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::Frame),
      p_(params),
      background_(new BackgroundFrame(p_)) {
  ui_->setupUi(this);
  if (ui_->widget->layout() != nullptr) {
    std::cerr << "Graph::Frame (Constructor): ui_->widget has layout\n";
    delete ui_->widget->layout();
  }
  SetStyles();

  layout_ = new QVBoxLayout(ui_->widget);
  layout_->setContentsMargins(2, 0, 2, 0);

  layout_->addWidget(background_);

  connect(background_, &BackgroundFrame::ReDraw, this, [&] {
    SetStyles();
    emit ReDraw();
  });
  connect(ui_->save_button, &QPushButton::clicked, this, &Frame::Save);
  connect(ui_->hide_button, &QPushButton::clicked, this, &Frame::Hide);
}

void Frame::SetStyles() {
  setStyleSheet(
      "background-color: " + background_->GetColor().name() +
      "; color: " + background_->GetTextPen().color().name() +
      "; border: 1px solid " + background_->GetColor().lighter(200).name() +
      "; Graph::Frame { background-color: " + background_->GetColor().name() +
      "; }");
}

void Frame::Hide() {
  bool visible = !ui_->save_button->isVisible();
  ui_->save_button->setVisible(visible);
  ui_->widget->setVisible(visible);
}

void Frame::Save() {
  QString file_name = AbstractFrame::SaveImageDialog(this);
  if (file_name.isEmpty()) return;
  QImage image(p_.Size(), QImage::Format_ARGB32);
  QPainter painter(&image);
  painter.drawImage(0, 0, background_->GetImage());
  ForVisible([&](PainterFrame *layer) {
    painter.drawImage(p_.Left(), p_.Top(), layer->GetImage());
  });
  image.save(file_name);
}

void Frame::Draw() {
  if (visible_count_ != 0) {
    background_->SetShowText(true);
    background_->Update();
    ForVisible([&](PainterFrame *layer) { layer->Draw(); });
  } else {
    background_->SetShowText(false);
    background_->Draw();
  }
  emit ReDraw();
}

void Frame::ForGraphLayers(const std::function<void(PainterFrame *)> &func) {
  for (unsigned i = 1; i < layout_->count(); ++i) {
    PainterFrame *layer =
        dynamic_cast<PainterFrame *>(layout_->itemAt(i)->widget());
    if (layer != nullptr) func(layer);
  }
}

void Frame::ForVisible(const std::function<void(PainterFrame *)> &func) {
  ForGraphLayers([&](PainterFrame *layer) {
    if (layer->Visible()) func(layer);
  });
}

PainterFrame *Frame::operator[](unsigned index) {
  if (index >= layout_->count() - 1) return nullptr;
  return dynamic_cast<PainterFrame *>(layout_->itemAt(index + 1)->widget());
}

void Frame::Remove(unsigned index) {
  PainterFrame *layer = operator[](index);
  if (layer == nullptr) return;
  layout_->removeWidget(layer);
  delete layer;
  --visible_count_;
  ProcessMinMax();
  Draw();
  // emit GraphRemoved();
  // emit ReDraw();
}

void Frame::AddGraph(const QString &name, const Graph::data_t &data,
                     bool points, bool removeable) {
  AddLayer(new PainterFrame(p_, name, data, CreatePen(), this), points,
           removeable);
}

void Frame::AddGraph(const QString &name, Graph::data_t &&data, bool points,
                     bool removeable) {
  AddLayer(new PainterFrame(p_, name, data, CreatePen(), this), points,
           removeable);
}

void Frame::AddGraph(const QString &name, bool points, bool removeable) {
  AddLayer(new PainterFrame(p_, name, CreatePen(), this), points, removeable);
}

QPen Frame::CreatePen() {
  QPen pen(colors_.c.front(), 2);
  colors_.c.pop_front();
  return pen;
}

void Frame::AddLayer(PainterFrame *ptr, bool points, bool removeable) {
  ptr->SetRemoveable(removeable);
  ptr->DrawingPoints(points);
  layout_->insertWidget(layout_->count(), ptr);
  ptr->NameLabel()->installEventFilter(this);

  ProcessMinMax();
  p_.SetFactors();

  ++visible_count_;
  Draw();
  connect(ptr, &PainterFrame::Removed, this, [&]() {
    PainterFrame *sender = dynamic_cast<PainterFrame *>(QObject::sender());
    QColor color = sender->GetGraphPen().color();
    colors_.c.push_front(color);
    layout_->removeWidget(sender);
    delete sender;
    ProcessMinMax();
    Draw();
    emit GraphRemoved();
    // emit ReDraw();
  });
  connect(ptr, &PainterFrame::ReDraw, this, &Frame::ReDraw);
  connect(ptr, &PainterFrame::ChangeVisible, this, [&](bool visible) {
    visible_count_ += visible ? 1 : -1;
    ProcessMinMax();
    Draw();
    // emit ReDraw();
  });
  connect(ptr, &PainterFrame::MinMaxUpdate, this, [&]() {
    ProcessMinMax();
    p_.SetFactors();
    Draw();
    // emit ReDraw();
  });
  // emit ReDraw();
}

void Frame::ProcessMinMax() {
  qreal min_x = std::numeric_limits<qreal>::max();
  qreal max_x = std::numeric_limits<qreal>::min();
  qreal min_y = std::numeric_limits<qreal>::max();
  qreal max_y = std::numeric_limits<qreal>::min();
  ForVisible([&](PainterFrame *layer) {
    min_x = std::min(min_x, layer->MinX());
    max_x = std::max(max_x, layer->MaxX());
    min_y = std::min(min_y, layer->MinY());
    max_y = std::max(max_y, layer->MaxY());
  });
  p_.SetMinMax(min_x, max_x, min_y, max_y);
}

void Frame::Clear() {
  while (layout_->count() > 1) {
    PainterFrame *layer =
        dynamic_cast<PainterFrame *>(layout_->itemAt(1)->widget());
    if (layer != nullptr) {
      layout_->removeWidget(layer);
      delete layer;
    }
  }
  colors_.Update();
}

void Frame::Resize() {
  background_->Resize(p_.Size());
  ForVisible([&](PainterFrame *layer) { layer->Resize(p_.GraphSize()); });
}

bool Frame::eventFilter(QObject *object, QEvent *event) {
  if (object == nullptr) return false;

  QLabel *name_label = qobject_cast<QLabel *>(object);
  if (name_label) {
    QMouseEvent *mouseEvent = nullptr;

    switch (event->type()) {
      case QEvent::MouseButtonPress:
        if (LablePressed(name_label, event)) return true;
        break;
      case QEvent::MouseButtonRelease:
        if (LableReleased(name_label, event)) return true;
        break;
      case QEvent::MouseMove:
        if (LableMove(name_label, event)) return true;
        break;
    }
  }
  return QObject::eventFilter(object, event);
}

bool Frame::LablePressed(QLabel *label, QEvent *event) {
  if (dynamic_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
    dragged_layer_ = dynamic_cast<PainterFrame *>(label->parentWidget());
    if (dragged_layer_ == nullptr) return false;
    label->setCursor(Qt::ClosedHandCursor);
    return true;
  }
  return false;
}

bool Frame::LableReleased(QLabel *label, QEvent *event) {
  if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
    label->setCursor(Qt::OpenHandCursor);
    dragged_layer_ = nullptr;
    return true;
  }
  return false;
}

bool Frame::LableMove(QLabel *label, QEvent *event) {
  if (dragged_layer_ == nullptr) return false;

  QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
  auto pos = mapFromGlobal(mouse_event->globalPos());
  pos.setY(pos.y() - ui_->widget->pos().y());

  int k = layout_->indexOf(dragged_layer_);

  if (k < layout_->count() - 1) {
    auto pos_under = layout_->itemAt(k + 1)->widget()->pos();
    if (pos.y() > pos_under.y() + 2 * dragged_layer_->height() / 3) {
      layout_->removeWidget(dragged_layer_);
      layout_->insertWidget(k + 1, dragged_layer_);
      emit ReDraw();
      return true;
    }
  }
  if (k > 1) {
    auto pos_above = layout_->itemAt(k - 1)->widget()->pos();
    if (pos.y() < pos_above.y() + dragged_layer_->height() / 3) {
      layout_->removeWidget(dragged_layer_);
      layout_->insertWidget(k - 1, dragged_layer_);
      emit ReDraw();
      return true;
    }
  }

  return false;
}

Frame::~Frame() {
  ForGraphLayers([&](PainterFrame *layer) {
    layout_->removeWidget(layer);
    delete layer;
  });
  delete ui_;
  if (layout_ != nullptr) delete layout_;
}
