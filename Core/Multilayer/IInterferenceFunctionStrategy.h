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
class FormFactorCoherentSum;
class IInterferenceFunction;
class IFresnelMap;
class SimulationElement;

//! Base class of all interference function strategy classes.
//! Provides an 'evaluate' function that computes the total scattering intensity
//! from a decorated layer, taking into account a specific inter-particle interference function.
//! This function uses the low-level functions scalarCalculation and polarizedCalculation
//! that are to be overriden in the derived classes.
//! Inheritance is used to support different approximation schemes
//! (DecouplingApproximationStrategy, SSCApproximationStrategy).
//!
//! Instantiation of child classes takes place in LayoutStrategyBuilder::createStrategy,
//! which is called from ParticleLayoutComputation::eval.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>
        matrixFFVector_t;

    IInterferenceFunctionStrategy(const SimulationOptions& sim_params, bool polarized);
    virtual ~IInterferenceFunctionStrategy();

    void init(const SafePointerVector<FormFactorCoherentSum>& weighted_formfactors,
              const IInterferenceFunction* p_iff);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

protected:
    virtual void strategy_specific_post_init() {}
    static std::vector<complex_t> precomputeScalar(const SimulationElement& sim_element,
            const SafePointerVector<FormFactorCoherentSum>& ff_wrappers);
    static matrixFFVector_t precomputePolarized(const SimulationElement& sim_element,
            const SafePointerVector<FormFactorCoherentSum>& ff_wrappers);

    //! Evaluates the intensity in the scalar case
    virtual double scalarCalculation(const SimulationElement& sim_element) const =0;
    //! Evaluates the intensity in the polarized case
    virtual double polarizedCalculation(const SimulationElement& sim_element) const =0;

    SafePointerVector<FormFactorCoherentSum> m_formfactor_wrappers;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    SimulationOptions m_options;

private:
    double evaluateSinglePoint(const SimulationElement& sim_element) const;
    double MCIntegratedEvaluate(const SimulationElement& sim_element) const;
    double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const;
    bool m_polarized;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
#endif
};

#endif // IINTERFERENCEFUNCTIONSTRATEGY_H
