// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitSuite/MultipleSpecFitTest.cpp
//! @brief     Implements class MultipleSpecFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultipleSpecFitTest.h"
#include "FitParameterSet.h"
#include "FitSuite.h"
#include "MultiLayer.h"
#include "Simulation.h"

const size_t n_datasets = 2;

MultipleSpecFitTest::MultipleSpecFitTest() : SpecularFitTest()
{
}

MultipleSpecFitTest::~MultipleSpecFitTest() = default;

bool MultipleSpecFitTest::runTest()
{
    initParameterPlan();

    std::unique_ptr<MultiLayer> sample(createSample());
    std::unique_ptr<FitSuite> fitSuite(createFitSuite());

    std::unique_ptr<Simulation> simulation(createSimulation());
    simulation->setSample(*sample.get());
    simulation->runSimulation();
    std::unique_ptr<OutputData<double>> real_data(createOutputData(simulation.get()));

    // adding identical datasets
    for (size_t i = 0; i < n_datasets; ++i)
        fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    std::cout << fitSuite->treeToString() << std::endl;
    std::cout << fitSuite->parametersToString() << std::endl;
    std::cout << fitSuite->setupToString() << std::endl;
    fitSuite->runFit();

    std::vector<double> valuesAtMinimum = fitSuite->fitParameters()->values();

    const bool success = analyzeResults(*fitSuite);
    return success;
}
