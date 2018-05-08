// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootResidualFunction.cpp
//! @brief     Implements class RootResidualFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RootResidualFunction.h"

RootResidualFunction::RootResidualFunction(gradient_function_t fun_gradient, size_t npars,
                                           size_t ndatasize)
    : ROOT::Math::FitMethodFunction(static_cast<int>(npars), static_cast<int>(ndatasize)),
      m_npars(npars), m_datasize(ndatasize), m_fun_gradient(fun_gradient)
{
}

RootResidualFunction::Type_t RootResidualFunction::Type() const
{
    return ROOT::Math::FitMethodFunction::kLeastSquare;
}

ROOT::Math::IMultiGenFunction* RootResidualFunction::Clone() const
{
    return new RootResidualFunction(m_fun_gradient, m_npars, m_datasize);
}

//! Returns residual value for given data element index. Transform call of ancient
//! pointer based function to safer gradient_function_t.
//! @param pars: array of fit parameter values from the minimizer
//! @param index: index of residual element
//! @param gradients: if not zero, then array where we have to put gradients
//! @return value of residual for given data element index

double RootResidualFunction::DataElement(const double* pars, unsigned int index,
                                         double* gradients) const
{
    std::vector<double> par_values;
    par_values.resize(m_npars, 0.0);
    std::copy(pars, pars + m_npars, par_values.begin());

    std::vector<double> par_gradients;

    if (gradients)
        par_gradients.resize(m_npars);

    // retrieving result from user function
    double result = m_fun_gradient(par_values, index, par_gradients);

    // packing result back to minimizer's array
    if (gradients)
        for (size_t i = 0; i < m_npars; ++i)
            gradients[i] = par_gradients[i];

    return result;
}

double RootResidualFunction::DoEval(const double* pars) const
{
    double chi2 = 0.0;
    for (size_t i_data = 0; i_data < NPoints(); ++i_data) {
        double res = DataElement(pars, static_cast<unsigned int>(i_data));
        chi2 += res * res;
    }
    return chi2 / double(NPoints());
}
