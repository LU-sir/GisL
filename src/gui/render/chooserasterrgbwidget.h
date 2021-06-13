//
// Created by km on 6/13/21.
//

#ifndef GISL_CHOOSERASTERRGBWIDGET_H
#define GISL_CHOOSERASTERRGBWIDGET_H

#include "QWidget"
#include "src/core/provider/rasterprovider.h"
namespace Ui {
class ChooseRasterRgb;
}
class ChooseRasterRgbWidget : public QWidget {
  Q_OBJECT
public:
  explicit ChooseRasterRgbWidget(QWidget* parent);
  void initRgb(QStringList& q);
  void setPRasterProvider(gisl::RasterProvider* pRasterProvider);
  void on_pushButton_clicked();

protected:
  Ui::ChooseRasterRgb* ui;
  gisl::RasterProvider* pRasterProvider;
};

#endif // GISL_CHOOSERASTERRGBWIDGET_H
