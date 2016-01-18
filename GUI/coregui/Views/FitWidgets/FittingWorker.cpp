// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.cpp
//! @brief     Implements class FittingWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FittingWorker.h"
#include "FitSuite.h"

void FittingWorker::startFit()
{
    m_fitsuite->resetInterrupt();
    emit started();
    m_fitsuite->runFit();
    emit finished();
}

void FittingWorker::interruptFitting()
{
    if (m_fitsuite) {
        m_fitsuite->interruptFitting();
    }
}


/*void FittingWorker::update(FitSuite *subject)
{
    QString msg = QString("Iteration: %1\nChi: %2").arg(QString::number(subject->getNumberOfIterations()));
    msg = msg.arg(subject->getChi2(), 10, 'f', 1, QChar(' '));

    std::stringstream ss;
    FitSuite *m_fit_suite = subject;

    ss << "FitPrintObserver::update() -> Info."
              << " NCall:" << m_fit_suite->getNumberOfIterations()
              << " NStrategy:" << m_fit_suite->getCurrentStrategyIndex()
              << " Chi2:" << std::scientific << std::setprecision(8)
              << m_fit_suite->getChi2() << std::endl;

    emit addLog(QString::fromStdString(ss.str()));

    if (!isdrawing)
    {
        isdrawing = true;
        emit statusUpdate(msg, subject->getSimulationData(), subject->getChiSquaredMap());
    }


}*/
