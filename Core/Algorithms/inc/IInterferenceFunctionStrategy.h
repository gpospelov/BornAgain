// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IInterferenceFunctionStrategy.h
//! @brief     Defines class IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H_
#define IINTERFERENCEFUNCTIONSTRATEGY_H_

#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "Bin.h"
#include "SafePointerVector.h"
#include "LayerStrategyBuilder.h"
#include "FormFactorDWBAPol.h"

#include <vector>
#include <boost/scoped_ptr.hpp>
#include <Eigen/StdVector>

//! @class IInterferenceFunctionStrategy
//! @ingroup algorithms_internal
//! @brief Algorithm to apply one of interference function strategies (LMA, SCCA etc)

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd> >
        MatrixFFVector;
    IInterferenceFunctionStrategy(SimulationParameters sim_params);
    virtual ~IInterferenceFunctionStrategy()
    {
    }

    //! Initializes the object with form factors and interference functions
    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
                      const SafePointerVector<IInterferenceFunction> &ifs);

    //! Provides the R,T coefficients information
    void setSpecularInfo(const LayerSpecularInfo &specular_info);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin, Bin1D alpha_f_bin,
                    Bin1D phi_f_bin) const;

    //! Calculates the intensity in the presence of polarization of beam and detector
    double evaluate(const cvector_t &k_i, const Eigen::Matrix2cd &beam_density,
                    const Bin1DCVector &k_f_bin, const Eigen::Matrix2cd &detector_density,
                    Bin1D alpha_f_bin, Bin1D phi_f_bin) const;

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
                                   const std::vector<complex_t> &ff_list) const = 0;

    //! Evaluates the intensity for given list of evaluated form factors
    //! in the presence of polarization of beam and detector
    virtual double evaluateForMatrixList(const cvector_t &k_i, const Eigen::Matrix2cd &beam_density,
                                         const Bin1DCVector &k_f_bin,
                                         const Eigen::Matrix2cd &detector_density,
                                         const MatrixFFVector &ff_list) const = 0;

    //! Returns q-vector from k_i and the bin of k_f
    cvector_t getQ(const cvector_t &k_i, const Bin1DCVector &k_f_bin) const;

    SafePointerVector<FormFactorInfo> m_ff_infos;          //!< form factor info
    SafePointerVector<IInterferenceFunction> m_ifs;        //!< interference functions
    SimulationParameters m_sim_params;                     //!< simulation parameters
    boost::scoped_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA

private:
    struct IntegrationParamsAlpha
    {
        cvector_t k_i;
        double wavelength;
        Bin1D alpha_bin;
        Bin1D phi_bin;
        Eigen::Matrix2cd beam_density;
        Eigen::Matrix2cd detector_density;
    };

    //! Constructs one list of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorList(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
                                 Bin1D alpha_f_bin) const;

    //! Constructs lists of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorLists(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
                                  Bin1D alpha_f_bin, Bin1D phi_f_bin) const;

    //! Clears the cached form factor lists
    void clearFormFactorLists() const;

    //! Perform a Monte Carlo integration over the bin for the evaluation of the
    //! intensity
    double MCIntegratedEvaluate(const cvector_t &k_i, Bin1D alpha_f_bin, Bin1D phi_f_bin) const;

    //! Perform a Monte Carlo integration over the bin for the evaluation of the
    //! polarized intensity
    double MCIntegratedEvaluatePol(const cvector_t &k_i, const Eigen::Matrix2cd &beam_density,
                                   const Eigen::Matrix2cd &detector_density, Bin1D alpha_f_bin,
                                   Bin1D phi_f_bin) const;

    //! Get the reciprocal integration region
    IntegrationParamsAlpha getIntegrationParams(const cvector_t &k_i, Bin1D alpha_f_bin,
                                                Bin1D phi_f_bin) const;

    //! Evaluate for fixed angles
    double evaluate_for_fixed_angles(double *fractions, size_t dim, void *params) const;

    //! Evaluate polarized for fixed angles
    double evaluate_for_fixed_angles_pol(double *fractions, size_t dim, void *params) const;

    //! cached form factor evaluations
    mutable std::vector<complex_t> m_ff;

    //! cached polarized form factors
    mutable MatrixFFVector m_ff_pol;
};

inline cvector_t IInterferenceFunctionStrategy::getQ(const cvector_t &k_i,
                                                     const Bin1DCVector &k_f_bin) const
{
    return k_i - k_f_bin.getMidPoint();
}

#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */
