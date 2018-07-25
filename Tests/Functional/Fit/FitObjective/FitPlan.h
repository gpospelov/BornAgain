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

#ifndef FITPLAN_H
#define FITPLAN_H

#include "MinimizerTestPlan.h"
#include <memory>

namespace Fit { class Parameters; }
class Simulation;
class MultiLayer;
template<class T> class OutputData;

//! Contains all logic to construct FitObjective, setup Minimizer and check minimization results.

class FitPlan : public MinimizerTestPlan
{
public:
    FitPlan(const std::string& name);
    ~FitPlan();

    virtual bool checkMinimizer(Fit::Minimizer& minimizer);

private:
    virtual std::unique_ptr<Simulation> createSimulation(const Fit::Parameters& params) const;
    virtual std::unique_ptr<MultiLayer> createMultiLayer(const Fit::Parameters& params) const;
    virtual std::unique_ptr<OutputData<double>> createOutputData() const;

    std::string m_simulation_name;
    std::string m_sample_builder_name;
};

#endif // FITPLAN_H
