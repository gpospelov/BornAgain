
#include "StandardFitsFactory.h"
#include "MinimizerFunctionalTests.h"
#include "RectDetectorFitTest.h"
#include <boost/format.hpp>

//! build<C> is a function void -> IFunctionalTest*. C must be a child of IFunctionalTest.
template<class Builder> IFunctionalTest* build() { return new Builder(); }

StandardFitsFactory::StandardFitsFactory()
{
    registerItem(
        "Minuit2_Migrad",
        build<Minuit2MigradTest>,
        "Functional test of Minuit2/Migrad minimizer");

    registerItem(
        "Minuit2_Fumili",
        build<Minuit2FumiliTest>,
        "Functional test of Minuit2/Fumili minimizer");

    registerItem(
        "GSLLevenbergMarquardt",
        build<GSLLevenbergMarquardtTest>,
        "Functional test of GSL's LevenbergMarquardt minimizer");

    registerItem(
        "GSLMultiMinBFGS",
        build<GSLMultiMinBFGSTest>,
        "Functional test of GSL's MultiMin/BFGS minimizer");

    registerItem(
        "GSLMultiMinSteepestDescent",
        build<GSLMultiMinSteepestDescentTest>,
        "Functional test of GSL's MultiMin/SteepestDescent minimizer");

    registerItem(
        "GSLSimulatedAnnealing",
        build<GSLSimulatedAnnealingTest>,
        "Functional test of GSL's Simulated Annealing minimizer");

    registerItem(
        "GeneticMinimizer",
        build<GeneticTest>,
        "Functional test of TMVA's Genetic minimizer");

    registerItem(
        "RectDetectorFit",
        build<RectDetectorFitTest>,
        "Fit of rectangular detector, with crop and masks applied");
}

IFunctionalTest* StandardFitsFactory::createTest(const std::string& test_name)
{
    IFunctionalTest* result = createItem(test_name);
    result->setName(test_name);
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
