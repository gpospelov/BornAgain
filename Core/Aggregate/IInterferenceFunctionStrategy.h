// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IInterferenceFunctionStrategy.h
//! @brief     Declares class IInterferenceFunctionStrategy.
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
class FormFactorInfo;
class IInterferenceFunction;
class LayerSpecularInfo;
class SimulationElement;

//! @class IInterferenceFunctionStrategy
//! @ingroup algorithms_internal
//! @brief Algorithm to apply one of interference function strategies (LMA, SCCA etc)
class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd> >
        MatrixFFVector;
    IInterferenceFunctionStrategy(const SimulationOptions& sim_params);
    virtual ~IInterferenceFunctionStrategy();

    //! Initializes the object with form factors and interference functions
    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
                      const IInterferenceFunction& iff);

    //! Provides the R,T coefficients information
    void setSpecularInfo(const LayerSpecularInfo& specular_info);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

    //! Calculates the intensity in the presence of polarization of beam and detector
    double evaluatePol(const SimulationElement& sim_element) const;

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const SimulationElement& sim_element,
                                   const std::vector<complex_t>& ff_list) const = 0;

    //! Evaluates the intensity for given list of evaluated form factors
    //! in the presence of polarization of beam and detector
    virtual double evaluateForMatrixList(const SimulationElement& sim_element,
                                         const MatrixFFVector& ff_list) const = 0;

    SafePointerVector<FormFactorInfo> m_ff_infos;          //!< form factor info
    std::unique_ptr<IInterferenceFunction> mP_iff;       //!< interference function
    SimulationOptions m_options;                     //!< simulation options
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA

private:
    //! Constructs one list of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorList(const SimulationElement& sim_element) const;

    //! Constructs lists of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorLists(const SimulationElement& sim_element) const;

    //! Clears the cached form factor lists
    void clearFormFactorLists() const;

    //! Perform a Monte Carlo integration over the bin for the evaluation of the
    //! intensity
    double MCIntegratedEvaluate(const SimulationElement& sim_element) const;

    //! Perform a Monte Carlo integration over the bin for the evaluation of the
    //! polarized intensity
    double MCIntegratedEvaluatePol(const SimulationElement& sim_element) const;

    //! Evaluate for fixed angles
    double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const;

    //! Evaluate polarized for fixed angles
    double evaluate_for_fixed_angles_pol(double* fractions, size_t dim, void* params) const;

    //! cached form factor evaluations
    mutable std::vector<complex_t> m_ff;

    //! cached polarized form factors
    mutable MatrixFFVector m_ff_pol;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator_pol;
#endif
};

#endif // IINTERFERENCEFUNCTIONSTRATEGY_H
