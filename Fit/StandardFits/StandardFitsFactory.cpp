#include "StandardFitsFactory.h"
#include "MinimizerFunctionalTests.h"
#include "RectDetectorFitTest.h"
#include <boost/format.hpp>


StandardFitsFactory::StandardFitsFactory()
{
    registerItem(
        "Minuit2_Migrad",
        IFactoryCreateFunction<Minuit2MigradTest, IFunctionalTest>,
        "Functional test of Minuit2/Migrad minimizer");

    registerItem(
        "Minuit2_Fumili",
        IFactoryCreateFunction<Minuit2FumiliTest, IFunctionalTest>,
        "Functional test of Minuit2/Fumili minimizer");

    registerItem(
        "GSLLevenbergMarquardt",
        IFactoryCreateFunction<GSLLevenbergMarquardtTest, IFunctionalTest>,
        "Functional test of GSL's LevenbergMarquardt minimizer");

    registerItem(
        "GSLMultiMinBFGS",
        IFactoryCreateFunction<GSLMultiMinBFGSTest, IFunctionalTest>,
        "Functional test of GSL's MultiMin/BFGS minimizer");

    registerItem(
        "GSLMultiMinSteepestDescent",
        IFactoryCreateFunction<GSLMultiMinSteepestDescentTest, IFunctionalTest>,
        "Functional test of GSL's MultiMin/SteepestDescent minimizer");

    registerItem(
        "GSLSimulatedAnnealing",
        IFactoryCreateFunction<GSLSimulatedAnnealingTest, IFunctionalTest>,
        "Functional test of GSL's Simulated Annealing minimizer");

    registerItem(
        "GeneticMinimizer",
        IFactoryCreateFunction<GeneticTest, IFunctionalTest>,
        "Functional test of TMVA's Genetic minimizer");

    registerItem(
        "RectDetectorFit",
        IFactoryCreateFunction<RectDetectorFitTest, IFunctionalTest>,
        "Fit of rectangular detector, with crop and masks applied");

}

IFunctionalTest *StandardFitsFactory::createTest(const std::string &test_name)
{
    IFunctionalTest *result = createItem(test_name);
    result->setName(test_name);
    result->setDescription(m_descriptions[test_name]);
    return result;
}

bool StandardFitsFactory::isValidTest(const std::string &test_name)
{
    CallbackMap_t::const_iterator it = m_callbacks.find(test_name);
    if( it != m_callbacks.end() ) {
        return true;
    } else {
        return false;
    }
}

void StandardFitsFactory::printCatalogue(std::ostream &ostr)
{
    for(DescriptionMap_t::iterator it=m_descriptions.begin(); it!=m_descriptions.end(); ++it) {
        ostr << boost::format("%-35s | %-50s\n") % it->first % it->second;
    }
}
