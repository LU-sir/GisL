//
// Created by km on 6/13/21.
//

#ifndef GISL_LAYERTREEWIDGET_H
#define GISL_LAYERTREEWIDGET_H

#include <QTreeWidget>

#include "src/core/layer/layertree.h"

namespace gisl {
class LayerTreeWidget : public QTreeWidget {
  Q_OBJECT

public slots:
  void on_item_double_clicked(QTreeWidgetItem* item, int column);

public:
  explicit LayerTreeWidget(QWidget* parent);
  ~LayerTreeWidget() override {}
  void setSelectionModel(QItemSelectionModel* selectionModel) override {
    QTreeWidget::setSelectionModel(selectionModel);
  }
  void updateLayerTree();

protected:
  void dropEvent(QDropEvent* event) override { QTreeWidget::dropEvent(event); }
  void itemDoubleClicked(QTreeWidgetItem* item, int column);
  LayerTree* layerTree;
};
} // namespace gisl
#endif // GISL_LAYERTREEWIDGET_H
