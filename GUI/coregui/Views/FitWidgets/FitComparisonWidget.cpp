// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.cpp
//! @brief     Implements class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitComparisonWidget.h"
#include "AxesItems.h"
#include "ColorMapCanvas.h"
#include "ColorMapLabel.h"
#include "FitFlowWidget.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include <QAction>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QVBoxLayout>

namespace {
const double relative_diff_min = 1e-05;
const double relative_diff_max = 1;
}

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_realDataPlot(new ColorMapCanvas)
    , m_simulatedDataPlot(new ColorMapCanvas)
    , m_relativeDiffPlot(new ColorMapCanvas)
    , m_fitFlowWidget(new FitFlowWidget)
    , m_statusLabel(new ColorMapLabel(0, this))
    , m_currentJobItem(0)
    , m_realDataItem(0)
    , m_simulatedDataItem(0)
    , m_relativeDiffItem(0)
    , m_resetViewAction(0)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    setStyleSheet("background-color:white;");

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_relativeDiffPlot, 1, 0);
    gridLayout->addWidget(m_fitFlowWidget, 1, 1);

    vlayout->addLayout(gridLayout);
    vlayout->addWidget(m_statusLabel);
    setLayout(vlayout);

    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SLOT(onResetViewAction()));

}

FitComparisonWidget::~FitComparisonWidget()
{
    if(m_simulatedDataItem)
        m_simulatedDataItem->mapper()->unsubscribe(this);

    if(m_currentJobItem)
        m_currentJobItem->mapper()->unsubscribe(this);
}

void FitComparisonWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    setJobItem(jobItem);
}

QList<QAction *> FitComparisonWidget::actionList()
{
    return QList<QAction *>() << m_resetViewAction;
}

void FitComparisonWidget::setJobItem(JobItem *jobItem)
{
    if(!jobItem->isValidForFitting())
        return;

    processJobItemItem(jobItem);
    setSimulatedDataItem(jobItem->intensityDataItem());


    m_relativeDiffItem = createRelativeDifferenceItem();
    calculateRelativeDifference();

    m_realDataPlot->setItem(m_realDataItem);
    m_simulatedDataPlot->setItem(m_simulatedDataItem);
    m_relativeDiffPlot->setItem(m_relativeDiffItem);
    m_fitFlowWidget->setItem(jobItem->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addColorMap(m_realDataPlot);
    m_statusLabel->addColorMap(m_simulatedDataPlot);
    m_statusLabel->addColorMap(m_relativeDiffPlot);
}

//! When widget is visible, axes labels will be removed intensity data items to free more space.

void FitComparisonWidget::showEvent(QShowEvent *)
{
    if(isVisible()) {
        qDebug() << "!!! visible";
        removeLabels(m_realDataItem);
        removeLabels(m_simulatedDataItem);
    }
}

//! When widget is about to be hidden, axes labels will be restored to not to upset other widgets.

void FitComparisonWidget::hideEvent(QHideEvent *)
{
    if(isHidden()) {
        qDebug() << "!!! hidden";
        restoreLabels(m_realDataItem);
        restoreLabels(m_simulatedDataItem);
    }
}

void FitComparisonWidget::processJobItemItem(JobItem *jobItem)
{

    if(jobItem == m_currentJobItem)
        return;

    if(m_currentJobItem)
        m_currentJobItem->mapper()->unsubscribe(this);

    m_currentJobItem = jobItem;
    if(!m_currentJobItem) return;

    m_currentJobItem->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        if(name == JobItem::P_STATUS) {
            if(m_currentJobItem->isCompleted())
                onResetViewAction();
        }
    }, this);

    m_currentJobItem->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_currentJobItem = 0;
    }, this);

    m_realDataItem = m_currentJobItem->realDataItem()->intensityDataItem();
    backupLabels(m_realDataItem);
}

void FitComparisonWidget::onResetViewAction()
{
    qDebug() << "FitComparisonWidget::onResetViewAction()";
    m_realDataItem->resetView();
    m_simulatedDataItem->resetView();
    m_relativeDiffItem->resetView();
    m_relativeDiffItem->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
}

//! Sets tracking of simulated data item.

void FitComparisonWidget::setSimulatedDataItem(IntensityDataItem *simulatedDataItem)
{
    if(simulatedDataItem == m_simulatedDataItem)
        return;

    if(m_simulatedDataItem)
        m_simulatedDataItem->mapper()->unsubscribe(this);

    m_simulatedDataItem = simulatedDataItem;
    if(!m_simulatedDataItem) return;

    m_simulatedDataItem->mapper()->setOnValueChange(
        [this]()
    {
        calculateRelativeDifference();
    }, this);

    m_simulatedDataItem->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_simulatedDataItem = 0;
    }, this);

    backupLabels(simulatedDataItem);

}

//! Creates an IntensityDataItem which will hold relative difference map between simulation
//! and real data.

IntensityDataItem *FitComparisonWidget::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    IntensityDataItem *result = dynamic_cast<IntensityDataItem *>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));

    return result;
}

void FitComparisonWidget::calculateRelativeDifference()
{
    Q_ASSERT(m_realDataItem);
    Q_ASSERT(m_simulatedDataItem);
    Q_ASSERT(m_relativeDiffItem);

    m_relativeDiffItem->setOutputData(
        IntensityDataFunctions::createRelativeDifferenceData(*m_simulatedDataItem->getOutputData(),
                *m_realDataItem->getOutputData()));

    m_relativeDiffItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
    m_relativeDiffItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
    m_relativeDiffItem->setLowerAndUpperZ(relative_diff_min, relative_diff_max);

}

//! Backup axes labels for given item. Labels will be returned back when FitComparisonWidget
//! is hidden.

void FitComparisonWidget::backupLabels(IntensityDataItem *intensityItem)
{
    LabelBackup data;
    data.xlabel = intensityItem->xAxisItem()->getItemValue(BasicAxisItem::P_TITLE).toString();
    data.ylabel = intensityItem->yAxisItem()->getItemValue(BasicAxisItem::P_TITLE).toString();
    m_labelBackup[intensityItem] = data;
}

//! Restores item labels from the backup.

void FitComparisonWidget::restoreLabels(IntensityDataItem *intensityItem)
{
    QMap<IntensityDataItem *, LabelBackup>::iterator it = m_labelBackup.find(intensityItem);
    if(it != m_labelBackup.end()) {
        LabelBackup lb = it.value();
        intensityItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, lb.xlabel);
        intensityItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, lb.ylabel);
    }
}

//! Removes axes label from item. This is because they occupy too much space on this dense widget.

void FitComparisonWidget::removeLabels(IntensityDataItem *intensityItem)
{
    if(!intensityItem)
        return;

    intensityItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
    intensityItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
}
