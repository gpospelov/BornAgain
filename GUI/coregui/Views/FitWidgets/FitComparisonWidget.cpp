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
#include "FitSuiteItem.h"
#include "PropertyRepeater.h"
#include "IntensityDataPropertyWidget.h"
#include "AxesItems.h"
#include "FitComparisonController.h"
#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

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
    , m_propertyWidget(new IntensityDataPropertyWidget)
    , m_repeater(new PropertyRepeater(this))
    , m_relativeDiffItem(0)
    , m_resetViewAction(0)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel"))
    , m_comparisonController(new FitComparisonController(this))
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_relativeDiffPlot, 1, 0);
    gridLayout->addWidget(m_fitFlowWidget, 1, 1);

    vlayout->addLayout(gridLayout);
    vlayout->addWidget(m_statusLabel);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addLayout(vlayout);
    hlayout->addWidget(m_propertyWidget);
    setLayout(hlayout);

    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SLOT(onResetViewAction()));

    m_relativeDiffItem = createRelativeDifferenceItem();
    m_relativeDiffPlot->setItem(diffItem());

    m_propertyWidget->setVisible(false);
}

FitComparisonWidget::~FitComparisonWidget() { delete m_tempIntensityDataModel; }

QList<QAction*> FitComparisonWidget::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_propertyWidget->actionList();
}

void FitComparisonWidget::subscribeToItem()
{
    if (!jobItem()->isValidForFitting())
        return;

    jobItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_STATUS) {
                if (jobItem()->isCompleted())
                    onResetViewAction();
            }
        },
        this);

    if (auto simItem = simulatedDataItem()) {
        simItem->mapper()->setOnValueChange([this]() { calculateRelativeDifference(); }, this);
//        simItem->mapper()->setOnPropertyChange([this](const QString& name)
//        {
//            if (name == IntensityDataItem::P_AXES_UNITS) {
//                calculateRelativeDifference();
//            }
//        }, this);
    }

    calculateRelativeDifference();

    m_realDataPlot->setItem(realDataItem());
    m_simulatedDataPlot->setItem(simulatedDataItem());
    m_fitFlowWidget->setItem(jobItem()->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addColorMap(m_realDataPlot);
    m_statusLabel->addColorMap(m_simulatedDataPlot);
    m_statusLabel->addColorMap(m_relativeDiffPlot);

    m_repeater->addItem(realDataItem());
    m_repeater->addItem(simulatedDataItem());

    QStringList activeProperties = QStringList() << BasicAxisItem::P_MIN << BasicAxisItem::P_MAX;
    m_repeater->addItem(diffItem(), activeProperties);

    m_propertyWidget->setItem(simulatedDataItem());
}

void FitComparisonWidget::unsubscribeFromItem()
{
    if (!currentItem())
        return;

    if (simulatedDataItem())
        simulatedDataItem()->mapper()->unsubscribe(this);

    m_repeater->clear();
}

void FitComparisonWidget::onResetViewAction()
{
//    m_repeater->setActive(false);

    if (auto item = realDataItem())
        item->resetView();

    if (auto item = simulatedDataItem())
        item->resetView();

    if (diffItem()) {
        diffItem()->resetView();
        diffItem()->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
    }

//    m_repeater->setActive(true);
}

//! Creates an IntensityDataItem which will hold relative difference map between simulation
//! and real data.

IntensityDataItem* FitComparisonWidget::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));

    return result;
}

void FitComparisonWidget::calculateRelativeDifference()
{
    if (!simulatedDataItem()->getOutputData()) // job failed
        return;

    Q_ASSERT(realDataItem());
    Q_ASSERT(simulatedDataItem());
    Q_ASSERT(diffItem());

    diffItem()->setOutputData(IntensityDataFunctions::createRelativeDifferenceData(
        *simulatedDataItem()->getOutputData(), *realDataItem()->getOutputData()));

    diffItem()->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, simulatedDataItem()->getXaxisTitle());
    diffItem()->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, simulatedDataItem()->getYaxisTitle());
    diffItem()->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
}

JobItem* FitComparisonWidget::jobItem()
{
    JobItem* jobItem = dynamic_cast<JobItem*>(currentItem());
    Q_ASSERT(jobItem);
    return jobItem;
}

IntensityDataItem* FitComparisonWidget::realDataItem()
{
    return jobItem()->realDataItem()->intensityDataItem();
}

IntensityDataItem* FitComparisonWidget::simulatedDataItem()
{
    return jobItem()->intensityDataItem();
}

IntensityDataItem* FitComparisonWidget::diffItem()
{
    return m_relativeDiffItem;
}
