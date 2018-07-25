// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlan.h
//! @brief     Defines class FitPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlan.h"
#include "SimulationFactory.h"
#include "SampleBuilderFactory.h"
#include "Parameters.h"
#include "MultiLayer.h"

FitPlan::FitPlan(const std::string& name)
    : MinimizerTestPlan(name)
{

}

FitPlan::~FitPlan() = default;

bool FitPlan::checkMinimizer(Fit::Minimizer& minimizer)
{
    (void)minimizer;
    return true;
}

//! Creates simulation for given set of fit parameters.

std::unique_ptr<Simulation> FitPlan::createSimulation(const Fit::Parameters& params) const
{
    SimulationFactory factory;
    auto simulation = factory.create(m_simulation_name);
    auto sample = createMultiLayer(params);
    simulation->setSample(*sample);
    return simulation;
}

//! Creates sample for given set of fit parameters.

std::unique_ptr<MultiLayer> FitPlan::createMultiLayer(const Fit::Parameters& params) const
{
    SampleBuilderFactory factory;
    auto sample_builder = factory.create(m_sample_builder_name);

    // propagating current values of fit parameters to sample builder before building the sample
    for(const auto& par : params)
        sample_builder->setParameterValue(par.name(), par.value());

    return std::unique_ptr<MultiLayer>(sample_builder->buildSample());
}

//! Creates "experimental" data for fitting.

std::unique_ptr<OutputData<double> > FitPlan::createOutputData() const
{
    // use expected values of fit parameters to construct simulation
    auto params = parameters();
    params.setValues(expectedValues());
    auto simulation = createSimulation(params);
    simulation->runSimulation();
    return std::unique_ptr<OutputData<double>>(simulation->result().data());
}
