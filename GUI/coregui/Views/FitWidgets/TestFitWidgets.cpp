// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/TestFitWidgets.cpp
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

#include "TestFitWidgets.h"
#include "mainwindow.h"
#include "ModelTuningWidget.h"
#include "FitParametersWidget.h"
#include "item_constants.h"
#include "JobModel.h"
#include "JobItem.h"
#include <QVBoxLayout>

TestFitWidgets::TestFitWidgets(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_tuningWidget(new ModelTuningWidget(mainWindow->jobModel()))
    , m_fitParametersWidget(new FitParametersWidget(this))
    , m_jobItem(0)
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_tuningWidget);
    hlayout->addWidget(m_fitParametersWidget);
    setLayout(hlayout);
}

void TestFitWidgets::showEvent(QShowEvent *)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(m_mainWindow->jobModel()->getTopItem(Constants::JobItemType));
    if(jobItem) {
        m_jobItem = jobItem;
        m_tuningWidget->setItem(jobItem);
        m_fitParametersWidget->setItem(jobItem);
        m_fitParametersWidget->setModelTuningWidget(m_tuningWidget);
    }

}
