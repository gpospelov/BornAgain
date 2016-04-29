// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitSuiteWidget.cpp
//! @brief     Implements class FitSuiteWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSuiteWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "FitParametersWidget.h"
#include <QVBoxLayout>
#include <QTabWidget>

FitSuiteWidget::FitSuiteWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParametersWidget(this))
    , m_jobModel(jobModel)
    , m_currentItem(0)
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");

    layout->addWidget(m_tabWidget);

    setLayout(layout);
}

void FitSuiteWidget::setItem(JobItem *jobItem)
{
    m_currentItem = jobItem;

}

