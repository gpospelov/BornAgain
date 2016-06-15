// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerLibrary.cpp
//! @brief     Implements namespace MinimizerLibrary.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerLibrary.h"
#include "Exceptions.h"
#include "BornAgainNamespace.h"

using namespace MinimizerLibrary;

AlgorithmInfo::AlgorithmInfo(const std::string &algType, const std::string &algDescription)
    : InfoItem(algType, algDescription)
{
}

MinimizerInfo::MinimizerInfo(const std::string &minimizerType,
                             const std::string &minimizerDescription)
    : InfoItem(minimizerType, minimizerDescription)
{

}

void MinimizerInfo::addAlgorithm(const MinimizerLibrary::AlgorithmInfo &algorithm)
{
    m_algorithms.push_back(algorithm);
}

void MinimizerInfo::addAlgorithm(const std::string &algorithmName,
                                               const std::string &algorithmDescription)
{
    addAlgorithm(AlgorithmInfo(algorithmName, algorithmDescription));
}

//! Return list of algorithm types.

std::list<std::string> MinimizerInfo::algorithmTypes() const
{
    std::list<std::string> result;
    for(AlgorithmInfo algo : m_algorithms) {
        result.push_back(algo.getType());
    }
    return result;
}

//! Returns list of string with description of all available algorithms.

std::list<std::string> MinimizerInfo::algorithmDescriptions() const
{
    std::list<std::string> result;
    for(AlgorithmInfo algo : m_algorithms) {
        result.push_back(algo.getDescription());
    }
    return result;
}

//! Catalogue constructor fills in all information related to available minimizers/algorithms.

Catalogue::Catalogue()
{
    MinimizerInfo minuit(BornAgain::MinuitMinimizerType, "Minuit2 minimizer from ROOT library");
    minuit.addAlgorithm(
        BornAgain::MigradAlgorithmType,
        "Variable-metric method with inexact line search, best minimizer according to ROOT.");
    minuit.addAlgorithm(BornAgain::SimplexAlgorithmType, "Simplex method of Nelder and Meadh, "
                                                         "robust against big fluctuations in "
                                                         "objective function.");
    minuit.addAlgorithm(BornAgain::CombinedAlgorithmType,
                        "Combination of Migrad and Simplex (if Migrad fails).");
    minuit.addAlgorithm(BornAgain::ScanAlgorithmType,
                        "Simple objective function scan, one parameter at a time.");
    minuit.addAlgorithm(BornAgain::FumiliAlgorithmType, "Gradient descent minimizer similar to "
                                                        "Levenberg-Margquardt, sometimes can be "
                                                        "better than all others.");
    addMinimizer(minuit);

    MinimizerInfo gsl(BornAgain::GSLMinimizerType, "Set of minimizers from GNU Scientific Library");
    gsl.addAlgorithm(BornAgain::ConjugateFRAlgorithmType, "Fletcher-Reeves conjugate gradient");
    gsl.addAlgorithm(BornAgain::ConjugatePRAlgorithmType, "Polak-Ribiere conjugate gradient");
    gsl.addAlgorithm(BornAgain::BFGSAlgorithmType, "BFGS conjugate gradient");
    gsl.addAlgorithm(BornAgain::BFGS2AlgorithmType, "BFGS conjugate gradient (Version 2)");
    gsl.addAlgorithm(BornAgain::LMAAlgorithmType, "Levenberg-Marquardt, often works quite well.");
//    gsl.addAlgorithm(BornAgain::SimAnAlgorithmType, "Simulated Annealing");
    addMinimizer(gsl);

    MinimizerInfo genetic(BornAgain::GeneticMinimizerType, "TMVA Genetic Algorithm");
    genetic.addAlgorithm(BornAgain::GeneticAlgorithmType, "TMVA Genetic Algorithm");
    addMinimizer(genetic);
}

//! Adds minimizer info to the catalogue.

void Catalogue::addMinimizer(const MinimizerInfo &minimizer)
{
    auto it = m_minimizers.find(minimizer.getType());
    if(it==m_minimizers.end()) {
        m_minimizers[minimizer.getType()] = minimizer;
    } else {
        throw LogicErrorException("Catalogue::addMinimizer() -> Error. Attempt to add twice "
                                  " minimizer " + minimizer.getType());
    }
}

//! Returns list of algorithm types for given minimizer type.

std::list<std::string> Catalogue::algorithmTypes(const std::string &minimizerType)
{
    MinimizerInfo minimizer = minimizerInfo(minimizerType);
    return  minimizer.algorithmTypes();
}

//! Returns list of algorithm descriptions for given minimizer type.

std::list<std::string> Catalogue::algorithmDescriptions(const std::string &minimizerType)
{
    MinimizerInfo minimizer = minimizerInfo(minimizerType);
    return  minimizer.algorithmDescriptions();
}

//! Returns minimizer info for given minimizer type.

MinimizerLibrary::MinimizerInfo Catalogue::minimizerInfo(const std::string &minimizerType)
{
    auto it = m_minimizers.find(minimizerType);
    if(it == m_minimizers.end()) {
        throw LogicErrorException("Catalogue::addMinimizer() -> Error. Non existing minimizer "
                                  + minimizerType);
    }
    return m_minimizers[minimizerType];
}
