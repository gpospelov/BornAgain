//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Fit/Adapter/ResidualFunctionAdapter.h
//! @brief     Defines class ResidualFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_FIT_ADAPTER_RESIDUALFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_ADAPTER_RESIDUALFUNCTIONADAPTER_H

#include "Fit/Adapter/IFunctionAdapter.h"
#include "Fit/Minimizer/Types.h"
#include "Fit/Param/Parameters.h"
#include <functional>
#include <memory>
#include <vector>

class RootResidualFunction;

namespace mumufit {

//! Provides RootResidualFunction which will be minimizer by ROOT.
//! Converts ROOT calls to the call of fcn_residual_t.

class ResidualFunctionAdapter : public IFunctionAdapter {
public:
    ResidualFunctionAdapter(fcn_residual_t func, const Parameters& parameters);

    const RootResidualFunction* rootResidualFunction();

private:
    void calculate_gradients(const std::vector<double>& pars);
    std::vector<double> get_residuals(const std::vector<double>& pars);

    //! evaluate method for gradients and residuals called directly from the minimizer
    double element_residual(const std::vector<double>& pars, unsigned int index,
                            std::vector<double>& gradients);
    //! Evaluate chi2
    double chi2(const std::vector<double>& pars);

    //! Length of vector with residuals, should stay the same during minimization.
    size_t m_datasize;
    fcn_residual_t m_fcn; //!< user function to minimize
    Parameters m_parameters;
    std::vector<double> m_residuals;
    std::vector<std::vector<double>> m_gradients; // [m_npars][m_ndatasize]
    std::unique_ptr<RootResidualFunction> m_root_objective;
};

} //  namespace mumufit

#endif // BORNAGAIN_FIT_ADAPTER_RESIDUALFUNCTIONADAPTER_H
#endif // USER_API
