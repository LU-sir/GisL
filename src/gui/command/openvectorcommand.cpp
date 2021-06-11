/*!
 * @author tau
 * @date 12/30/20
 */

#include "openvectorcommand.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "../../utils/ptroperate.h"
#include "src/core/layer/layertree.h"
#include "src/core/provider/vectorprovider.h"

void gisl::OpenVectorCommand::execute(QWidget* parent) {

    //    auto openFileName = QString(
    //    "../resource/mydata/hubei_hospital_voronoi_extract.shp" ); auto
    //    openFileName = QString( "../resource/practise_6/qu.geojson" );
    QString openFileName = QFileDialog::getOpenFileName(
                               parent,
                               QObject::tr("open an vector file."),
                               "../",
                               QObject::tr("GeoJSON(*.geojson);;ESRI Shapefile(*.shp);;All files(*.*)"),
                               nullptr,
                               QFileDialog::DontUseNativeDialog);
    if (openFileName.isEmpty()) {
        QMessageBox::warning(
            parent,
            QObject::tr("VectorProvider Warning!"),
            QObject::tr("Cancel to open the file!"));
    } else {
        vectorName = openFileName.toStdString();
        pProvider = new gisl::VectorProvider();
        pProvider->loadData(vectorName);
        if (pProvider->hasError()) {
            Log* log = Log::getLog();
            QMessageBox::warning(
                parent,
                QObject::tr("VectorProvider Warning!"),
                log->getLast());
            return;
        }
        LayerTree* layerTree = LayerTree::getLayerTree();
        VectorLayer* layer = layerTree->getLayer("qu");

        ui->openGLWidget->getLayerName("qu");
        ui->openGLWidget->getEnvelope(*layer->getEnvelope());

        //    qDebug((openFileName.split(".")[0] + "-style.sld"));
        QFileInfo info1(openFileName);
        //    QFileInfo::exists(info1.absolutePath() + info1.baseName() +
        //    "-style.sld"); QString q = openFileName.split(".")[0] + "-style.sld";
        //    qDebug("%s", q.toStdString().c_str());
        //    qDebug("%s", (info1.absolutePath() + info1.baseName() +
        //    "-style.sld").toStdString().c_str());
        if (QFileInfo::exists(
                    info1.absolutePath() + "/" + info1.baseName() + "-style.sld")) {
            ui->openGLWidget->setSld(
                new Sld((info1.absolutePath() + "/" + info1.baseName() + "-style.sld")
                        .toStdString()));
        } else {
            ui->openGLWidget->setRandSld();
        }
        ui->openGLWidget->getLayer(*layer);
        layer->draw(*ui->openGLWidget);
    }
}

void gisl::OpenVectorCommand::getUi(Ui_MainWindow& p) {
    ui = &p;
}

void gisl::OpenVectorCommand::reverse() {
    // todo dont draw vector

    PtrOperate::clear(pProvider);
    vectorName = "";
}

const std::string& gisl::OpenVectorCommand::output() {
    return vectorName;
}

gisl::OpenVectorCommand::~OpenVectorCommand() {
    PtrOperate::clear(pProvider);
}
