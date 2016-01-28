// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCone.cpp
//! @brief     Implements class FormFactorCone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCone.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

#include <cmath>

using namespace  BornAgain;

FormFactorCone::FormFactorCone(double radius, double height, double alpha)
{
    setName(FFConeType);
    m_radius = radius;
    m_height = height;
    m_alpha = alpha;
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorCone>::mem_function p_mf =
       & FormFactorCone::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorCone>(p_mf, this);
}

FormFactorCone::~FormFactorCone()
{
    delete m_integrator;
}

bool FormFactorCone::check_initialization() const
{
    bool result(true);
    if(m_height > m_radius*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorCone() -> Error in class initialization ";
        ostr << "with parameters radius:" << m_radius;
        ostr << " m_height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= radius*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorCone::init_parameters()
{
    clearParameterPool();
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Alpha, & m_alpha, AttLimits::n_positive());
}

FormFactorCone* FormFactorCone::clone() const
{
   return new FormFactorCone(m_radius, m_height, m_alpha);
}

//! Integrand for complex formfactor.
complex_t FormFactorCone::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    double Rz = m_radius -Z/std::tan(m_alpha);
    complex_t q_p = std::sqrt(m_q.x()*m_q.x()+m_q.y()*m_q.y()); // sqrt(x*x + y*y)

    return Rz*Rz*MathFunctions::Bessel_J1c(q_p*Rz) *
            std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

complex_t FormFactorCone::evaluate_for_q(const cvector_t& q) const
{   m_q = q;

  if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {
        double R = m_radius;
        double H = m_height;
        double tga = std::tan(m_alpha);
        double HdivRtga = H/tga/R;

        return  Units::PI/3.0*tga*R*R*R*
                (1.0 - (1.0 - HdivRtga)*(1.0 - HdivRtga)*(1.0 - HdivRtga));
    } else {
        complex_t integral = m_integrator->integrate(0., m_height);

        return Units::PI2*integral;
    }
}


