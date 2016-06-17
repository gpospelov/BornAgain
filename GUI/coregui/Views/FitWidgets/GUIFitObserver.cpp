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
#include "FitProgressInfo.h"
#include "GUIHelpers.h"
#include <QVector>
#include <QDebug>


GUIFitObserver::GUIFitObserver(QObject *parent)
    : QObject(parent)
    , IFitObserver(1)
    , m_block_update_plots(false)
    , m_update_interval(1)
{}

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
    emit parameterUpdate(parameters, values);

    emit logInfoUpdate(QString("NCalls: %1 Chi: %2\n%3").
                      arg(QString::number(subject->getNumberOfIterations()),
                          QString::number(subject->getChi2()),
                          QString::fromStdString(text)));

    if (subject->isLastIteration()) {
        std::stringstream buffer;
        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
        subject->printResults();
        std::string text = buffer.str();
        emit logInfoUpdate(QString::fromStdString(text));
        std::cout.rdbuf(old);
    }


    if(canUpdateStatus(subject)) {
        emit statusUpdate(QString::number(subject->getNumberOfIterations()));

        FitProgressInfo info;
        info.m_chi2 = subject->getChi2();
        info.m_iteration_count = subject->getNumberOfIterations();
        info.m_values = GUIHelpers::fromStdVector(subject->getFitParameters()->getValues());
        emit progressInfoUpdate(info);

    }

    if(canUpdatePlots(subject)) {
        m_block_update_plots = true;
        m_simData.reset(subject->getSimulationOutputData()->clone());
        m_chiData.reset(subject->getChiSquaredOutputData()->clone());
        emit plotsUpdate();
    }



}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

//! Returns true if it is time to update plots

bool GUIFitObserver::canUpdatePlots(FitSuite *fitSuite)
{
    if(m_block_update_plots) return false;
    if(fitSuite->getNumberOfIterations() % m_update_interval != 0) return false;
    return true;
}

//! Returns true if it is time to send status message. Follow same rules as for plots update,
//! or in the case of last iteration
bool GUIFitObserver::canUpdateStatus(FitSuite *fitSuite)
{
    if(fitSuite->getNumberOfIterations() == 0) return true;
    if(fitSuite->getNumberOfIterations() % m_update_interval == 0) return true;
    if(fitSuite->isLastIteration()) return true;
    return canUpdatePlots(fitSuite);
}

//! Informs observer that FitSuiteWidget has finished plotting and is ready for next plot
void GUIFitObserver::finishedPlotting()
{
    m_block_update_plots = false;
}

const OutputData<double> *GUIFitObserver::simulationData() const
{
    return m_simData.get();
}

const OutputData<double> *GUIFitObserver::chiSquaredData() const
{
    return m_chiData.get();
}

