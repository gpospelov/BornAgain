//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Base/Math/IntegratorGK.h
//! @brief     Defines classes RealIntegrator, ComplexIntegrator.
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
#ifndef BORNAGAIN_BASE_MATH_INTEGRATORGK_H
#define BORNAGAIN_BASE_MATH_INTEGRATORGK_H

#include "Base/Types/Complex.h"
#include <functional>
#include <gsl/gsl_integration.h>

//! To integrate a real function of a real variable.
class RealIntegrator {
public:
    RealIntegrator();
    ~RealIntegrator();
    double integrate(const std::function<double(double)>& f, double lmin, double lmax);

private:
    static double m_Cfunction(double x, void* p)
    {
        return (*(const std::function<double(double)>*)(p))(x);
    };
    gsl_function m_gsl_f;
    gsl_integration_workspace* m_workspace;
};

//! To integrate a complex function of a real variable.
class ComplexIntegrator {
public:
    complex_t integrate(const std::function<complex_t(double)>& f, double lmin, double lmax);

private:
    RealIntegrator realPart;
    RealIntegrator imagPart;
};

#endif // BORNAGAIN_BASE_MATH_INTEGRATORGK_H
#endif // USER_API
