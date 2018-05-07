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

double RootResidualFunction::DataElement(const double* pars, unsigned int i_data,
                                         double* gradient) const
{
    std::vector<double> vec;
    vec.resize(m_npars, 0.0);
    std::copy(pars, pars + m_npars, vec.begin());

    std::vector<double> vec_gradients;

    if (gradient)
        vec_gradients.resize(m_npars);

    double result = m_fun_gradient(vec, i_data, vec_gradients);

    if (gradient)
        for (size_t i = 0; i < m_npars; ++i)
            gradient[i] = vec_gradients[i];

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
