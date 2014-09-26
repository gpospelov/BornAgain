#include "ModelTuningWidget.h"
#include "JobItem.h"
#include "SliderSettingsWidget.h"
#include "ParameterModelBuilder.h"
#include "GUIHelpers.h"
#include "ModelTuningDelegate.h"
#include "JobQueueData.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>


ModelTuningWidget::ModelTuningWidget(JobQueueData *jobQueueData, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueData(jobQueueData)
    , m_currentJobItem(0)
    , m_sliderSettingsWidget(0)
    , m_parameterModel(0)
    , m_delegate(new ModelTuningDelegate)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QColor bgColor(0,0,255,255);
//    QPalette palette;
//    palette.setColor(QPalette::Background, bgColor);
//    setAutoFillBackground(true);

    m_sliderSettingsWidget = new SliderSettingsWidget();
    connect(m_sliderSettingsWidget, SIGNAL(sliderRangeFactorChanged(double)), this, SLOT(onSliderValueChanged(double)));

    m_treeView = new QTreeView();
    m_treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/treeview-branch-open.png);}");
    m_treeView->setItemDelegate(m_delegate);
    connect(m_delegate, SIGNAL(currentLinkChanged(ItemLink)), this, SLOT(onCurrentLinkChanged(ItemLink)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_sliderSettingsWidget);
    mainLayout->addWidget(m_treeView);

    setLayout(mainLayout);

}


ModelTuningWidget::~ModelTuningWidget()
{
    delete m_parameterModel;
}


void ModelTuningWidget::setCurrentItem(JobItem *item)
{
    qDebug() << "AdvModelTuningWidget::setCurrentItem" << item;
    if(m_currentJobItem != item) {
        m_currentJobItem = item;
        updateParameterModel();
    }
}


void ModelTuningWidget::onCurrentLinkChanged(ItemLink link)
{
    qDebug() << "AdvModelTuningWidget::onCurrentLinkChanged";
    Q_ASSERT(m_currentJobItem);

    if(m_currentJobItem->isRunning())
        return;

    if(link.getItem()) {
        qDebug() << "AdvModelTuningWidget::onCurrentLinkChanged() -> Starting to tune model" << link.getItem()->modelType() << link.getPropertyName() << link.getValue();

        link.getItem()->setRegisteredProperty(link.getPropertyName(), link.getValue());

        m_jobQueueData->runJob(m_jobQueueData->getIdentifierForJobItem(m_currentJobItem));
    }
}


void ModelTuningWidget::onSliderValueChanged(double value)
{
    m_delegate->setSliderRangeFactor(value);
}


void ModelTuningWidget::updateParameterModel()
{
    qDebug() << "AdvModelTuningWidget::updateParameterModel()";
    if(m_parameterModel) {
        m_treeView->setModel(0);
        delete m_parameterModel;
        m_parameterModel = 0;
    }

    if(!m_currentJobItem) return;

    if(!m_currentJobItem->getSampleModel() || !m_currentJobItem->getInstrumentModel())
        throw GUIHelpers::Error("AdvModelTuningWidget::updateParameterModel() -> Error. JobItem doesn't have sample or instrument model.");

    m_parameterModel = ParameterModelBuilder::createParameterModel(m_currentJobItem->getSampleModel(), m_currentJobItem->getInstrumentModel());

    m_treeView->setModel(m_parameterModel);
//    m_treeView->setFixedHeight(height);
    m_treeView->setColumnWidth(0, 170);
    m_treeView->expandAll();
}
