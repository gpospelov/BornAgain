// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitSuite.cpp
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
#include "IHistogram.h"
#include "MinimizerFactory.h"

FitSuite::FitSuite()
    : m_kernel(new FitKernel(this))
{
}

FitSuite::~FitSuite()
{
}

void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation,
                                        const OutputData<double> &real_data, double weight)
{
    m_kernel->addSimulationAndRealData(simulation, real_data, weight);
}

void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation,
                                        const IHistogram &real_data, double weight)
{
    const std::unique_ptr<OutputData<double> > data(real_data.createOutputData());
    m_kernel->addSimulationAndRealData(simulation, *data, weight);
}

void FitSuite::addFitParameter(const std::string &name, double value, const AttLimits &attlim,
                               double step)
{
    m_kernel->addFitParameter(name, value, attlim, step);
}

void FitSuite::setMinimizer(const std::string &minimizer_name, const std::string &algorithm_name,
                            const std::string &minimizer_options)
{
    IMinimizer *minimizer = MinimizerFactory::createMinimizer(minimizer_name, algorithm_name,
                                                              minimizer_options);
    m_kernel->setMinimizer(minimizer);
}

void FitSuite::setChiSquaredModule(const IChiSquaredModule &chi2_module)
{
    m_kernel->getFitObjects()->setChiSquaredModule(chi2_module);
}

void FitSuite::addFitStrategy(const IFitStrategy &strategy)
{
    m_kernel->addFitStrategy(strategy);
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
    std::shared_ptr<FitSuitePrintObserver > observer(new FitSuitePrintObserver(print_every_nth));
    attachObserver(observer);
}

void FitSuite::fixAllParameters()
{
    getFitParameters()->fixAll();
}

void FitSuite::releaseAllParameters()
{
    getFitParameters()->releaseAll();
}

void FitSuite::setParametersFixed(const std::vector<std::string> &pars, bool is_fixed)
{
    getFitParameters()->setParametersFixed(pars, is_fixed);
}

void FitSuite::runFit()
{
    m_kernel->runFit();
}

int FitSuite::getNumberOfFitObjects() const
{
    return m_kernel->getFitObjects()->getNumberOfFitObjects();
}

IHistogram *FitSuite::getRealData(size_t i_item) const
{
    return IHistogram::createHistogram(*m_kernel->getFitObjects()->getRealData(i_item));
}

IHistogram *FitSuite::getSimulationData(size_t i_item) const
{
    return IHistogram::createHistogram(*m_kernel->getFitObjects()->getSimulationData(i_item));
}

IHistogram *FitSuite::getChiSquaredMap(size_t i_item) const
{
    return IHistogram::createHistogram(*m_kernel->getFitObjects()->getChiSquaredMap(i_item));
}

const OutputData<double> *FitSuite::getRealOutputData(size_t i_item) const
{
    return m_kernel->getFitObjects()->getRealData(i_item);
}

const OutputData<double> *FitSuite::getSimulationOutputData(size_t i_item) const
{
    return m_kernel->getFitObjects()->getSimulationData(i_item);
}

const OutputData<double> *FitSuite::getChiSquaredOutputData(size_t i_item) const
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

size_t FitSuite::getNumberOfIterations() const
{
    return m_kernel->getNCalls();
}

size_t FitSuite::getCurrentStrategyIndex() const
{
    return m_kernel->getCurrentStrategyIndex();
}

void FitSuite::printResults() const
{
    m_kernel->printResults();
}

double FitSuite::getChi2() const
{
    return m_kernel->getFitObjects()->getChiSquaredValue();
}

FitOptions &FitSuite::getOptions()
{
    return m_kernel->getOptions();
}

void FitSuite::interruptFitting()
{
    m_kernel->interruptFitting();
}

void FitSuite::resetInterrupt()
{
    m_kernel->resetInterrupt();
}

bool FitSuite::isInterrupted()
{
    return m_kernel->isInterrupted();
}
