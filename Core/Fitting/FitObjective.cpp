// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObjective.cpp
//! @brief     Implements class FitObjective.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjective.h"

//static_assert(std::is_copy_constructible<FitObjective>::value == false,
//              "FitObjective should not be copy constructable");
//static_assert(std::is_copy_assignable<FitObjective>::value == false,
//              "FitObjective should not be copy assignable");


namespace {
void insert_to(std::vector<double>& to, const std::vector<double>& from)
{
    to.insert(to.end(), from.begin(), from.end());
}
}


FitObjective::FitObjective()
    : m_total_weight(0.0)
{}

FitObjective::~FitObjective() = default;

void FitObjective::addSimulationAndData(simulation_builder_t builder,
                                        const OutputData<double>& data, double weight)
{
    m_fit_objects.push_back(new SimDataPair(builder, data, weight));
}

double FitObjective::evaluate(const Fit::Parameters& params)
{
    run_simulations(params);

    return 0.0;
}

std::vector<double> FitObjective::evaluate_residuals(const Fit::Parameters& params)
{
    run_simulations(params);

    return {};
}

size_t FitObjective::numberOfFitElements() const
{
    size_t result(0);
    for (auto obj : m_fit_objects)
        result += obj->numberOfFitElements();

    return result;
}

std::vector<double> FitObjective::experimental_array() const
{
    return m_experimental_array;
}

std::vector<double> FitObjective::simulation_array() const
{
    return m_simulation_array;
}

void FitObjective::run_simulations(const Fit::Parameters& params)
{
    m_simulation_array.clear();
    m_experimental_array.clear();

    for (auto obj : m_fit_objects) {
        obj->runSimulation(params);
        insert_to(m_simulation_array, obj->simulation_array());
        insert_to(m_experimental_array, obj->experimental_array());
    }
}
