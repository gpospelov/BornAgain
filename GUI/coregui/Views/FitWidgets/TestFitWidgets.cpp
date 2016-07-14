// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/TestFitWidgets.cpp
//! @brief     Implements class TestFitWidgets
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterItems.h"
#include "FitParameterWidget.h"
#include "FitSuiteItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "ParameterTuningWidget.h"
#include "item_constants.h"
#include "mainwindow.h"
#include "TestFitWidgets.h"
#include <QHBoxLayout>
#include <QTreeView>
#include <QVBoxLayout>

TestFitWidgets::TestFitWidgets(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_tuningWidget(new ParameterTuningWidget)
    , m_fitParametersWidget(new FitParameterWidget(this))
    , m_jobTreeView(new QTreeView)
    , m_jobItem(0)
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_tuningWidget);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(m_fitParametersWidget);
    vlayout->addWidget(m_jobTreeView);

    hlayout->addLayout(vlayout);
    setLayout(hlayout);
}

void TestFitWidgets::showEvent(QShowEvent *)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(m_mainWindow->jobModel()->topItem(Constants::JobItemType));
    if(jobItem) {
        m_jobItem = jobItem;
        m_tuningWidget->setItem(jobItem);
        m_fitParametersWidget->setItem(jobItem);
        m_fitParametersWidget->setParameterTuningWidget(m_tuningWidget);
        m_jobTreeView->setModel(m_mainWindow->jobModel());
        m_jobTreeView->setRootIndex(jobItem->fitSuiteItem()->index());
    }

}
