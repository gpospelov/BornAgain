// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.h
//! @brief     Defines class DWBAComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MAINCOMPUTATION_H
#define MAINCOMPUTATION_H

#include "IComputation.h"
#include "Complex.h"
#include "SimulationOptions.h"

class IComputationTerm;
class IFresnelMap;
struct HomogeneousRegion;
class MultiLayer;
class SimulationElement;

//! Performs a single-threaded DWBA computation with given sample and simulation parameters.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class DWBAComputation : public IComputation
{
public:
    DWBAComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                    ProgressHandler& progress,
                    std::vector<SimulationElement>::iterator begin_it,
                    std::vector<SimulationElement>::iterator end_it);
    ~DWBAComputation() override;

private:
    void runProtected() override;
    // creates a multilayer that contains averaged materials, for use in Fresnel calculations
    std::unique_ptr<MultiLayer> getAveragedMultilayer() const;
    // creates a multilayer for use in Fresnel calculations; if needed, it calculates average
    // materials and precalculates the magnetic B fields
    std::unique_ptr<MultiLayer> getMultilayerForFresnel() const;
    // sets the correct layer materials for the Fresnel map to use
    void initFresnelMap();
    bool checkRegions(const std::vector<HomogeneousRegion>& regions) const;

    std::vector<SimulationElement>::iterator m_begin_it, m_end_it; //!< these iterators define the span of detector bins this simulation will work on
    std::unique_ptr<IFresnelMap> mP_fresnel_map; //!< Contains the information, necessary to calculate the Fresnel coefficients.
    std::vector<std::unique_ptr<IComputationTerm>> m_computation_terms;
};

#endif // MAINCOMPUTATION_H
