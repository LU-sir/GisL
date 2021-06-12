//
// Created by omega on 6/11/21.
//

#include <iostream>

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "openrastercommand.h"
#include "src/gui/render/rasterimgview.h"
#include <src/core/layer/layertree.h>

void gisl::OpenRasterCommand::testExecute(QWidget* parent) {
  fileName = "/home/km/dev/gisl/tests/data/fwi-200902.tif";
  this->pProvider = new gisl::RasterProvider();
  qDebug("the %s", fileName.c_str());
  pProvider->loadData(fileName);
  if (pProvider->hasError()) {
    Log* log = Log::getLog();
    QMessageBox::warning(
        parent,
        QObject::tr("RasterProvider Warning!"),
        log->getLast());
    return;
  }
  LayerTree* layerTree = gisl::LayerTree::getLayerTree();
  Layer* layer = layerTree->getLayer(pProvider->getFid() * 100 + 1);

  layer->draw(*ui->openGLWidget);
  RasterImgView rv(parent);
  rv.show();
  layer->draw(rv);
}
void gisl::OpenRasterCommand::execute(QWidget* parent) {
  QString openFileName = QFileDialog::getOpenFileName(
      parent,
      QObject::tr("open an raster file."),
      "../",
      QObject::tr("all raster(*.*);;GeoTiff(*.tif)"),
      nullptr,
      QFileDialog::DontUseNativeDialog);
  if (openFileName.isEmpty()) {
    QMessageBox::warning(
        parent,
        QObject::tr("empty file Warning!"),
        QObject::tr("Cancel to open the file!"));
  } else {
    fileName = openFileName.toStdString();
    pProvider = new gisl::RasterProvider();
    pProvider->loadData(fileName);
    if (pProvider->hasError()) {
      Log* log = Log::getLog();
      QMessageBox::warning(
          parent,
          QObject::tr("RasterProvider Warning!"),
          log->getLast());
      return;
    }
    LayerTree* layerTree = gisl::LayerTree::getLayerTree();
    Layer* layer = layerTree->getLayer(pProvider->getFid() * 100 + 1);

    layer->draw(*ui->openGLWidget);
  }
}
const std::string& gisl::OpenRasterCommand::output() {
  return this->mErrorMessage;
}
void gisl::OpenRasterCommand::reverse() {}
gisl::OpenRasterCommand::~OpenRasterCommand() {
  delete pProvider;
  pProvider = nullptr;
}
void gisl::OpenRasterCommand::getUi(Ui_MainWindow& p) { ui = &p; }
