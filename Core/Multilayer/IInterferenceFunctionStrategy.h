// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.h
//! @brief     Defines class IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H
#define IINTERFERENCEFUNCTIONSTRATEGY_H

#include "Complex.h"
#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include "Vectors3D.h"
#include <Eigen/StdVector>
#include <memory>
#include <vector>

template <class T> class IntegratorMCMiser;
class Bin1DCVector;
class WeightedFormFactor;
class IInterferenceFunction;
class LayerSpecularInfo;
class SimulationElement;

//! Virtual base class of the interference function strategy classes
//! DecouplingApproximationStrategy, SizeSpacingCorrelationApproximationStrategy.
//! These classes provide 'evaluate' functions that compute the scattering intensity
//! from a decorated layer, taking into account a specific inter-particle interference function.
//!
//! Child classes are instantiated in LayerStrategyBuilder::createStrategy,
//! which is called from DecoratedLayerComputation::eval.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>
        matrixFFVector_t;

    IInterferenceFunctionStrategy(const SimulationOptions& sim_params);
    virtual ~IInterferenceFunctionStrategy();

    void init(const SafePointerVector<WeightedFormFactor>& weighted_formfactors,
              const IInterferenceFunction& iff, const LayerSpecularInfo& specular_info);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

    //! Calculates the intensity in the presence of polarization of beam and detector
    double evaluatePol(const SimulationElement& sim_element) const;

protected:
    virtual void strategy_specific_post_init() {}

    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const SimulationElement& sim_element) const = 0;

    //! Evaluates the intensity for given list of evaluated form factors
    //! in the presence of polarization of beam and detector
    virtual double evaluateForMatrixList(const SimulationElement& sim_element) const = 0;

    double m_total_abundance; //!< cached sum of particle abundances, computed by init()
    SafePointerVector<WeightedFormFactor> m_weighted_ffs;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    SimulationOptions m_options;
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
    mutable std::vector<complex_t> m_ff; //!< cached form factor evaluations
    mutable matrixFFVector_t m_ff_pol; //!< cached polarized form factors

private:
    void precomputeParticleFormfactors   (const SimulationElement& sim_element) const;
    void precomputeParticleFormfactorsPol(const SimulationElement& sim_element) const;

    //! Perform a Monte Carlo integration over the bin for the evaluation of the intensity
    double MCIntegratedEvaluate   (const SimulationElement& sim_element) const;
    double MCIntegratedEvaluatePol(const SimulationElement& sim_element) const;

    double evaluate_for_fixed_angles    (double* fractions, size_t dim, void* params) const;
    double evaluate_for_fixed_angles_pol(double* fractions, size_t dim, void* params) const;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator_pol;
#endif
};

#endif // IINTERFERENCEFUNCTIONSTRATEGY_H
