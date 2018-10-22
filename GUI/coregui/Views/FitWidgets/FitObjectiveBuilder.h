// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitObjectiveBuilder.h
//! @brief     Defines class FitObjectiveBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVEBUILDER_H
#define FITOBJECTIVEBUILDER_H

#include "WinDllMacros.h"
#include <memory>

class JobItem;
class FitObjective;
class Simulation;
namespace Fit { class Parameters; }
template<class T> class OutputData;
class IMinimizer;

class BA_CORE_API_ FitObjectiveBuilder
{
public:
    FitObjectiveBuilder(JobItem* jobItem);

    void runFit();

    std::unique_ptr<FitObjective> createFitObjective() const;
    std::unique_ptr<IMinimizer> createMinimizer() const;

    Fit::Parameters createParameters() const;

private:
    JobItem* m_jobItem;

    std::unique_ptr<Simulation> buildSimulation(const Fit::Parameters& params) const;
    std::unique_ptr<OutputData<double>> createOutputData() const;

    void update_fit_parameters(const Fit::Parameters& params) const;
};

#endif
