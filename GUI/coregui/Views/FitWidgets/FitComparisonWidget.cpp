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
#include "ColorMapPlot.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "IntensityDataFunctions.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_realDataPlot(new ColorMapPlot)
    , m_simulatedDataPlot(new ColorMapPlot)
    , m_relativeDiffPlot(new ColorMapPlot)
    , m_realDataItem(0)
    , m_simulatedDataItem(0)
    , m_relativeDiffItem(0)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
{

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_relativeDiffPlot, 1, 0);

    setLayout(gridLayout);
}

FitComparisonWidget::~FitComparisonWidget()
{
    if(m_simulatedDataItem)
        m_simulatedDataItem->mapper()->unsubscribe(this);
}

void FitComparisonWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    setJobItem(jobItem);
}

void FitComparisonWidget::setJobItem(JobItem *jobItem)
{
    m_realDataItem = jobItem->realDataItem()->intensityDataItem();

    setSimulatedDataItem(jobItem->getIntensityDataItem());


    m_relativeDiffItem = createRelativeDifferenceItem();

    calculateRelativeDifference();

    m_realDataPlot->setItem(m_realDataItem);
    m_simulatedDataPlot->setItem(m_simulatedDataItem);
    m_relativeDiffPlot->setItem(m_relativeDiffItem);
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

}
