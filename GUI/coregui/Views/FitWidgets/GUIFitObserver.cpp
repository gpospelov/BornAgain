// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.cpp
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUIFitObserver.h"
#include "FitParameterSet.h"
#include "FitProgressInfo.h"
#include "FitSuite.h"
#include "GUIHelpers.h"
#include "MinimizerUtils.h"
#include <QDebug>

GUIFitObserver::GUIFitObserver(QObject* parent)
    : QObject(parent)
    , IFitObserver(1)
    , m_block_update_plots(false)
    , m_update_interval(1)
{
}

GUIFitObserver::~GUIFitObserver()
{
}

void GUIFitObserver::update(FitSuite* subject)
{
    // discard data after interruption
    if (subject->isInterrupted())
        return;

    if (subject->numberOfIterations() % m_update_interval == 0) {
        if (m_block_update_plots) {
            qDebug() << "GUI is busy with plotting, skipping iteration "
                     << subject->numberOfIterations();
        }
    }

    if (subject->numberOfIterations() == 0)
        emit logInfoUpdate(QString::fromStdString(subject->setupToString()));

    if (!canUpdatePlots(subject))
        return;

    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    if (m_block_update_plots)
        m_on_finish_notifier.wait(lock, [this]() { return m_block_update_plots; });
    m_block_update_plots = true;

    FitProgressInfo info;
    info.m_chi2 = subject->getChi2();
    info.m_iteration_count = (int)subject->numberOfIterations();
    info.m_values = GUIHelpers::fromStdVector(subject->fitParameters()->values());

    emit progressInfoUpdate(info);

    m_simData.reset(subject->simulationResult().data());
    emit plotsUpdate();

    if (subject->isLastIteration())
        emit logInfoUpdate(reportToString(subject));
}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

//! Returns true if it is time to update plots.

bool GUIFitObserver::canUpdatePlots(FitSuite* fitSuite)
{
    if (fitSuite->isLastIteration())
        return true;
    return !m_block_update_plots && fitSuite->numberOfIterations() % m_update_interval == 0;
}

//! Return string representing results of the minimization.

QString GUIFitObserver::reportToString(FitSuite* fitSuite)
{
    QString result = QString::fromStdString(MinimizerUtils::sectionString("Fit parameter setup"));
    result += QString::fromStdString(fitSuite->setupToString());
    result += QString::fromStdString(fitSuite->reportResults());
    return result;
}

//! Informs observer that FitSuiteWidget has finished plotting and is ready for next plot
void GUIFitObserver::finishedPlotting()
{
    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    m_block_update_plots = false;
    lock.unlock();
    m_on_finish_notifier.notify_one();
}

const OutputData<double>* GUIFitObserver::simulationData() const
{
    return m_simData.get();
}
