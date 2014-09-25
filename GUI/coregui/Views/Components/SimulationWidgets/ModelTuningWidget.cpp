#include "ModelTuningWidget.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "PropertyAttribute.h"
#include "ModelTuningDelegate.h"
#include "GUIHelpers.h"
#include "ItemLink.h"
#include "QuickSimulationRunner.h"
#include "QuickSimulationHelper.h"
#include "Simulation.h"
#include "BeamItem.h"
#include <QItemSelectionModel>
#include <QDebug>
#include <QVBoxLayout>



ModelTuningWidget::ModelTuningWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent)
    : QWidget(parent)
    , m_parameterModel(0)
    , m_treeView(0)
    , m_delegate(new ModelTuningDelegate)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_simulationRunner(0)
    , m_update_in_progress(false)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    setSampleModel(sampleModel);
    setInstrumentModel(instrumentModel);

    //generate Tree View
    m_treeView = new QTreeView();
    //treeView->setModel(model);
    //m_itemModel = getItemModelFromSessionModel();
    //treeView->setModel(getTestItemModel());

    m_treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/treeview-branch-open.png);}");
    //treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {background: cyan;}QTreeView::branch:has-siblings:adjoins-item {background: red;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {background: blue;}QTreeView::branch:closed:has-children:has-siblings {background: pink;}QTreeView::branch:has-children:!has-siblings:closed {background: gray;}QTreeView::branch:open:has-children:has-siblings {background: magenta;}QTreeView::branch:open:has-children:!has-siblings {background: green;}");

    //m_treeView->setFixedWidth(350);
    //m_treeView->setFixedHeight(600);
    //m_treeView->setColumnWidth(0,200);
    //m_treeView->expandAll();



    m_treeView->setItemDelegate(m_delegate);
    connect(m_delegate, SIGNAL(currentLinkChanged(ItemLink)), this, SLOT(onCurrentLinkChanged(ItemLink)));

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_treeView);
    vlayout->addStretch();
    this->setLayout(vlayout);


}



void ModelTuningWidget::updateTreeView(const QString &instrument, const QString &sample)
{
    if(instrument != m_instrument_name || sample != m_sample_name) {
        m_instrument_name = instrument;
        m_sample_name = sample;

        m_treeView->setModel(0);

        delete m_parameterModel;
        m_parameterModel = QuickSimulationHelper::createParameterModel(m_sampleModel, m_instrumentModel);
        //connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));


        int height = this->height();
        m_treeView->setModel(m_parameterModel);
        m_treeView->setFixedHeight(height);
        m_treeView->setColumnWidth(0,170);
        m_treeView->expandAll();

        onCurrentLinkChanged(ItemLink());

    }
}


void ModelTuningWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(sampleModel);
    if(m_sampleModel != sampleModel) {

        //        if(m_sampleModel)
        //            disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));

        m_sampleModel = sampleModel;
        //        connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));
    }
}


void ModelTuningWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    Q_ASSERT(instrumentModel);
    if(m_instrumentModel != instrumentModel) {

        //        if(m_instrumentModel)
        //            disconnect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));

        m_instrumentModel = instrumentModel;
        //        connect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));
    }

}

void ModelTuningWidget::setQuickSimulationRunner(QuickSimulationRunner *simulationRunner)
{
    m_simulationRunner = simulationRunner;

}


void ModelTuningWidget::onModelChanged(const QModelIndex & /* first */, const QModelIndex & /* second */)
{
    qDebug() << "SampleTuningWidget::onModelChanged()";

}

void ModelTuningWidget::onCurrentLinkChanged(ItemLink link)
{
    Q_ASSERT(m_simulationRunner);
    qDebug() << "SampleTuningWidget::onCurrentLinkChanged() -> ";
    if(m_simulationRunner->isSimulationInProgress())
        return;

    if(m_update_in_progress)
        return;

    m_update_in_progress = true;

    if(link.getItem())
    {
        qDebug() << "SampleTuningWidget::onCurrentLinkChanged() -> Starting to tune model" << link.getItem()->modelType() << link.getPropertyName() << link.getValue();

        link.getItem()->setRegisteredProperty(link.getPropertyName(), link.getValue());
    }


    Simulation *simulation = QuickSimulationHelper::getSimulation(m_sampleModel, m_sample_name, m_instrumentModel, m_instrument_name);

    qDebug() << "SampleTuningWidget::onCurrentLinkChanged() -> Ready to run simulation";
    m_simulationRunner->runSimulation(simulation);


    m_update_in_progress = false;
}



//! returns parent index of MultiLayer with given name
QModelIndex ModelTuningWidget::getMultiLayerIndex(const QString &name)
{
    Q_ASSERT(m_sampleModel);

    QModelIndex result;
    for( int i_row = 0; i_row < m_sampleModel->rowCount( QModelIndex()); ++i_row) {
        QModelIndex itemIndex = m_sampleModel->index( i_row, 0, QModelIndex() );

        if (ParameterizedItem *item = m_sampleModel->itemForIndex(itemIndex)){
            if(item->modelType() == Constants::MultiLayerType && item->itemName() == name) {
                result = itemIndex;
            }
        }
    }

    if(!result.isValid()) {
        throw GUIHelpers::Error("SampleTuningWidget::getParentSampleIndex() -> Can't find the sample with given name" + name);
    }

    return result;
}

void ModelTuningWidget::setSliderRangeFactor(double value)
{
    m_delegate->setSliderRangeFactor(value);
}






