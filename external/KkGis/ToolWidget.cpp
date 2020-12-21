#include "ToolWidget.h"
#include "ui_ToolWidget.h"
#include <QVBoxLayout>
#include <qtreewidget.h>
#include <EnumType.h>
#include <qheaderview.h>
#include "kernalDensity.h"
#include "AccessibilityAnalysisTool.h"
#include "AccessAnalysisWidget.h"
#include"CGeoKernalDensTool.h"
#include"COption.h"
#include"kernalDensity.h"
#include "util.h"

ToolWidget::ToolWidget(GeoMap* map, QWidget *parent)
	: QWidget(parent), toolTree(NULL),map(map), aaw(NULL)
{
	ui = new Ui::ToolWidget();
	ui->setupUi(this);
	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	toolTree = new QTreeWidget();
	mainLayout->addWidget(toolTree);
	initToolTree();
}

ToolWidget::~ToolWidget()
{
	delete ui;
}

void ToolWidget::initToolTree()
{
	toolTree->header()->hide();
	QTreeWidgetItem* spatialToolBox = new QTreeWidgetItem(QStringList() << QStringLiteral("空间分析") << "(spatial analysis)");
	toolTree->addTopLevelItem(spatialToolBox);

	QTreeWidgetItem* nda = new QTreeWidgetItem(QStringList() << QStringLiteral("核密度分析") << "(Nuclear density analysis)");
	QTreeWidgetItem* aa = new QTreeWidgetItem(QStringList() << QStringLiteral("可达性分析") << "(Accessibility analysis)");
	spatialToolBox->addChild(nda);
	spatialToolBox->addChild(aa);
	nda->setData(0, Qt::WhatsThisRole, QVariant(EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS));
	aa->setData(0, Qt::WhatsThisRole, QVariant(EnumType::sparitalAnalysisTool::ACCESSIBILITY_ANALYSIS));
	connect(toolTree, &QTreeWidget::itemDoubleClicked, this, &ToolWidget::on_item_clicked);

	toolTree->expandAll();  //必须在之后调用
}


void ToolWidget::on_item_clicked(QTreeWidgetItem* item)
{
	int toolType = item->data(0, Qt::WhatsThisRole).toInt();
	if (toolType == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) { //核密度
		execKDEDiolog();
	}
	else if (toolType == EnumType::sparitalAnalysisTool::ACCESSIBILITY_ANALYSIS) { //可达性
		initAccessibilityAnalysisWidget();
	}
}

void ToolWidget::initAccessibilityAnalysisWidget()
{
	if (!aaw) {
		aaw = new AccessAnalysisWidget(map);
	}
	else {
		aaw->initWidget();
	}
	aaw->show();
}

void ToolWidget::execKDEDiolog()
{
	KernalDensity *kdDialog = new KernalDensity();
	Qt::WindowFlags flags = kdDialog->windowFlags();
	kdDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
	kdDialog->setMap(map);
	int ret = kdDialog->exec();//以模态方式显示对话框

	if (ret == QDialog::Accepted)
	{
		COption *opt = new COption();
		opt->input_file = kdDialog->getInputFile();
		opt->population_field = kdDialog->getPopulation();
		opt->output_file = kdDialog->getOutputFile();
		opt->output_cell_size = kdDialog->getRasterSize().toFloat();
		opt->search_radius = kdDialog->getSearchR().toFloat();
		opt->area_unit = kdDialog->getAreaUnits();
		opt->output_value_type = kdDialog->getOutValues();
		opt->method_type = kdDialog->getMethod();

		if (map->size() != 0)
		{
			CGeoKernalDensTool * kdTool = new CGeoKernalDensTool();
			kdTool->setOption(opt);
			kdTool->setLayer(map->getLayerAt(opt->input_file));
			int status = kdTool->run_tool();
			//对工具的使用状态进行判断
			if (status == 0)//成功运行
			{
				QString fullPath = kdTool->getFullPath();
				GeoLayer* gridLayer = util::grid2FeatureLayer(kdTool->getKDResult(), kdTool->getLayer()->getRect(),
					kdTool->getWidthCellNum(), kdTool->getHeightCellNum(), kdTool->getCellSize(), fullPath,
					fullPath.mid(fullPath.lastIndexOf("/") + 1, fullPath.lastIndexOf(".") - fullPath.lastIndexOf("/") - 1)
					, "cellValue");
				emit on_addNewLayerSignal(gridLayer);
				QMessageBox::about(NULL, "Kernal Dense", "Execute Successfully");
			}
			else if (status == 1)//输入的population不符合要求
				QMessageBox::critical(NULL, "Input Error", "Population Field Input Error", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			else if (status == 3)//输入的要素类型不符合要求
				QMessageBox::critical(NULL, "Input Error", "Data Type Input Error", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			else if (status == 2)//输入的数据size=0，无效
				QMessageBox::critical(NULL, "Input Error", "Invalid Data", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}
		else
			QMessageBox::critical(NULL, "Input Error", "No Input", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);//未加载任何数据
	}

}


