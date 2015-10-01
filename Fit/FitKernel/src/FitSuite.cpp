// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitSuite.cpp
//! @brief     Implements class FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuite.h"
#include "FitKernel.h"
#include "FitSuitePrintObserver.h"


FitSuite::FitSuite()
    : m_kernel(new FitKernel(this))
{

}

void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation,
                                        const OutputData<double> &real_data)
{
    m_kernel->addSimulationAndRealData(simulation, real_data);
}

void FitSuite::addFitParameter(const std::string &name, double value, const AttLimits &attlim,
                               double step)
{
    m_kernel->addFitParameter(name, value, step, attlim);
}

void FitSuite::setMinimizer(const std::string &minimizer, const std::string &algorithm,
                            const std::string &options)
{
    m_kernel->setMinimizer(minimizer, algorithm, options);
}

void FitSuite::setMinimizer(IMinimizer *minimizer)
{
    m_kernel->setMinimizer(minimizer);
}

IMinimizer *FitSuite::getMinimizer()
{
    return m_kernel->getMinimizer();
}

void FitSuite::initPrint(int print_every_nth)
{
    boost::shared_ptr<FitSuitePrintObserver > observer(new FitSuitePrintObserver(print_every_nth));
    attachObserver(observer);
}

void FitSuite::runFit()
{
    m_kernel->runFit();
}

const OutputData<double> *FitSuite::getRealData(size_t i_item) const
{
    return m_kernel->getFitObjects()->getRealData(i_item);
}

const OutputData<double> *FitSuite::getSimulationData(size_t i_item) const
{
    return m_kernel->getFitObjects()->getSimulationData(i_item);
}

const OutputData<double> *FitSuite::getChiSquaredMap(size_t i_item) const
{
    return m_kernel->getFitObjects()->getChiSquaredMap(i_item);
}




FitSuiteObjects *FitSuite::getFitObjects()
{
    return m_kernel->getFitObjects();
}

FitSuiteParameters *FitSuite::getFitParameters()
{
    return m_kernel->getFitParameters();
}

FitSuiteStrategies *FitSuite::getFitStrategies()
{
    return m_kernel->getFitStrategies();
}

bool FitSuite::isLastIteration() const
{
    return m_kernel->isLastIteration();
}

size_t FitSuite::getNCalls() const
{
    return m_kernel->getNCalls();
}

size_t FitSuite::getNStrategy() const
{
    return m_kernel->getNStrategy();
}

void FitSuite::printResults() const
{
    m_kernel->printResults();
}


