// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.cpp
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIFitObserver.h"
#include "FitSuite.h"
#include "IntensityDataItem.h"
#include "FitParameter.h"
#include "FitSuiteParameters.h"
#include "QDebug"


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

    // pass parameter name and values to gui
    auto container = subject->getFitParameters();
    FitSuiteParameters::iterator it;
    QStringList parameters;
    QVector<double> values;
    for (it = container->begin(); it != container->end(); it++) {
        parameters.push_back(QString::fromStdString((*it)->getName()));
        values.push_back((*it)->getValue());
        if ((*it)->getValue() < 0.0) {
            qDebug() << (*it)->getValue();
        }
    }
    emit updateParameters(parameters, values);

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


//    if (curIteration % m_update_interval == 0 && !m_block_update_plots) {
//        m_block_update_plots = true;

////        emit updateStatus(QString("Iteration: %1").arg(subject->getNumberOfIterations()));
//        emit updateStatus(QString::number(subject->getNumberOfIterations()));

//        emit updatePlots(subject->getSimulationOutputData()->clone(),
//                         subject->getChiSquaredOutputData()->clone());
//    }

    if(isToUpdateStatus(subject)) {
        emit updateStatus(QString::number(subject->getNumberOfIterations()));
    }

    if(isToUpdatePlots(subject)) {
        m_block_update_plots = true;
        emit updatePlots(subject->getSimulationOutputData()->clone(),
                         subject->getChiSquaredOutputData()->clone());
    }

}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

//! Returns true if it is time to update plots
bool GUIFitObserver::isToUpdatePlots(FitSuite *fitSuite)
{
    if(m_block_update_plots) return false;
    if(fitSuite->getNumberOfIterations() % m_update_interval != 0) return false;
    return true;
}

//! Returns true if it is time to send status message. Follow same rules as for plots update,
//! or in the case of last iteration
bool GUIFitObserver::isToUpdateStatus(FitSuite *fitSuite)
{
    if(fitSuite->getNumberOfIterations() == 0) return true;
    if(fitSuite->getNumberOfIterations() % m_update_interval == 0) return true;
    if(fitSuite->isLastIteration()) return true;
    return isToUpdatePlots(fitSuite);
}

//! Informs observer that FitSuiteWidget has finished plotting and is ready for next plot
void GUIFitObserver::finishedPlotting()
{
    m_block_update_plots = false;
}
