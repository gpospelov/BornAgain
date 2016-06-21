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
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_realDataPlot(new ColorMapPlot)
    , m_simulatedDataPlot(new ColorMapPlot)
    , m_chi2DataPlot(new ColorMapPlot)
{

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_chi2DataPlot, 1, 0);


    setLayout(gridLayout);
}

void FitComparisonWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    setJobItem(jobItem);
}

void FitComparisonWidget::setJobItem(JobItem *jobItem)
{

    m_realDataPlot->setItem(jobItem->realDataItem()->intensityDataItem());
    m_simulatedDataPlot->setItem(jobItem->getIntensityDataItem());
}
