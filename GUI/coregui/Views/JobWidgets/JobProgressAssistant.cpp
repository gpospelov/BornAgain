// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobProgressAssistant.cpp
//! @brief     Implements class JobProgressAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobProgressAssistant.h"
#include "mainwindow.h"
#include "JobModel.h"
#include "JobQueueData.h"
#include "progressbar.h"

JobProgressAssistant::JobProgressAssistant(MainWindow *mainWindow)
    : QObject(mainWindow)
    , m_mainWindow(mainWindow)
{
    connect(m_mainWindow->jobModel(), SIGNAL(globalProgress(int)),
            this, SLOT(onGlobalProgress(int)));

    connect(m_mainWindow->progressBar(), SIGNAL(clicked()),
            m_mainWindow->jobModel(), SLOT(onCancelAllJobs()));
}

void JobProgressAssistant::onGlobalProgress(int progress)
{
    Q_ASSERT(m_mainWindow->progressBar());
    if(progress<0 || progress >= 100) {
        m_mainWindow->progressBar()->setFinished(true);
        m_mainWindow->progressBar()->hide();
    } else {
        m_mainWindow->progressBar()->show();
        m_mainWindow->progressBar()->setFinished(false);
        m_mainWindow->progressBar()->setValue(progress);
    }
}
