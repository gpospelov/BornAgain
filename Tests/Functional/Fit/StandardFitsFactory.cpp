// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandardFitsFactory.cpp
//! @brief     Implements class StandardFitsFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardFitsFactory.h"
#include "MinimizerTests.h"
#include "RectDetectorFitTest.h"
#include "AdjustMinimizerStrategyTest.h"
#include "StandaloneFitTest.h"
#include <boost/format.hpp>

StandardFitsFactory::StandardFitsFactory()
{
    registerItem(
        "Minuit2_Migrad",
        create_new<Minuit2MigradTest>,
        "Functional test of Minuit2/Migrad minimizer");

    registerItem(
        "Minuit2_Fumili",
        create_new<Minuit2FumiliTest>,
        "Functional test of Minuit2/Fumili minimizer");

    registerItem(
        "GSLLevenbergMarquardt",
        create_new<GSLLevenbergMarquardtTest>,
        "Functional test of GSL's LevenbergMarquardt minimizer");

    registerItem(
        "GSLMultiMinBFGS",
        create_new<GSLMultiMinBFGSTest>,
        "Functional test of GSL's MultiMin/BFGS minimizer");

    registerItem(
        "GSLMultiMinSteepestDescent",
        create_new<GSLMultiMinSteepestDescentTest>,
        "Functional test of GSL's MultiMin/SteepestDescent minimizer");

    registerItem(
        "GSLSimulatedAnnealing",
        create_new<GSLSimulatedAnnealingTest>,
        "Functional test of GSL's Simulated Annealing minimizer");

    registerItem(
        "GeneticMinimizer",
        create_new<GeneticTest>,
        "Functional test of TMVA's Genetic minimizer");

    registerItem(
        "RectDetectorFit",
        create_new<RectDetectorFitTest>,
        "Fit of rectangular detector, with crop and masks applied");

    registerItem(
        "AdjustMinimizerStrategy",
        create_new<AdjustMinimizerStrategyTest>,
        "Test of minimizer chain: genetic -> minuit2");

    registerItem(
        "StandaloneFit",
        create_new<StandaloneFitTest>,
        "Test of standalone fit of arbitrary functions");

}

IFunctionalTest* StandardFitsFactory::createTest(const std::string& test_name)
{
    IFunctionalTest* result = createItem(test_name);
    result->setDescription(m_descriptions[test_name]);
    return result;
}

bool StandardFitsFactory::isValidTest(const std::string& test_name)
{
    return m_callbacks.find(test_name) != m_callbacks.end();
}

void StandardFitsFactory::printCatalogue(std::ostream& ostr)
{
    for(DescriptionMap_t::iterator it=m_descriptions.begin(); it!=m_descriptions.end(); ++it) {
        ostr << boost::format("%-35s | %-50s\n") % it->first % it->second;
    }
}
