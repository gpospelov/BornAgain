// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/GUIFitObserver.h
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIFitObserver.h"
#include "FitSuite.h"
#include "IntensityDataItem.h"
 

void GUIFitObserver::update(FitSuite *subject)
{
    // discard data after interruption
    if (subject->isInterrupted())
        return;

    // update log every time
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    subject->getFitParameters()->printParameters();
    std::string text = buffer.str();
    std::cout.rdbuf(old);

    emit updateLog(QString("NCalls: %1 Chi: %2\n%3").
                      arg(QString::number(subject->getNumberOfIterations()),
                          QString::number(subject->getChi2()),
                          QString::fromStdString(text)));

    if (subject->isLastIteration()) {
        std::stringstream buffer;
        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
        subject->printResults();
        std::string text = buffer.str();
        emit updateLog(QString::fromStdString(text));
        std::cout.rdbuf(old);
    }

    int curIteration = subject->getNumberOfIterations();

    if (curIteration == 0) {
        emit startFitting(subject->getRealOutputData()->clone());
    }
    if (curIteration % m_update_interval == 0 && !m_block_update_plots) {
        m_block_update_plots = true;

        emit updateStatus(QString("Iteration: %1").arg(subject->getNumberOfIterations()));

        emit updatePlots(subject->getSimulationOutputData()->clone(),
                         subject->getChiSquaredOutputData()->clone());
    }
}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

void GUIFitObserver::finishedPlotting()
{
    m_block_update_plots = false;
}
