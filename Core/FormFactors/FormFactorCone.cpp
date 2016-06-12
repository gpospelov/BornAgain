// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCone.cpp
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
#include "IntegratorComplex.h"

//! @brief Cone constructor
//! @param radius of Cone's base
//! @param height of Cone
//! @param alpha in radians between base and facet
FormFactorCone::FormFactorCone(double radius, double height, double alpha)
{
    setName(BornAgain::FFConeType);
    m_radius = radius;
    m_height = height;
    m_alpha = alpha;
    m_cot_alpha = MathFunctions::cot(m_alpha);
    if( !std::isfinite(m_cot_alpha) || m_cot_alpha<0 )
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    if(m_cot_alpha*m_height > m_radius) {
        std::ostringstream ostr;
        ostr << "FormFactorCone() -> Error in class initialization ";
        ostr << "with parameters radius:" << m_radius;
        ostr << " m_height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= radius*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    clearParameterPool();
    registerParameter(BornAgain::Radius, &m_radius, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, & m_alpha, AttLimits::n_positive());

    mP_integrator = make_integrator_complex(this, &FormFactorCone::Integrand);
}

FormFactorCone::~FormFactorCone() {}

FormFactorCone* FormFactorCone::clone() const
{
   return new FormFactorCone(m_radius, m_height, m_alpha);
}

//! Integrand for complex formfactor.
complex_t FormFactorCone::Integrand(double Z) const
{
    double Rz = m_radius - Z*m_cot_alpha;
    complex_t q_p = std::sqrt(m_q.x()*m_q.x()+m_q.y()*m_q.y()); // sqrt(x*x + y*y)
    return Rz*Rz*MathFunctions::Bessel_J1c(q_p*Rz) * exp_I(m_q.z()*Z);
}

complex_t FormFactorCone::evaluate_for_q(const cvector_t q) const
{
    m_q = q;
    if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {
        double R = m_radius;
        double H = m_height;
        double tga = std::tan(m_alpha);
        double HdivRtga = H/tga/R; // TODO preclude division by zero WAITING fuller refactoring

        return  Units::PI/3.0*tga*R*R*R*
                (1.0 - (1.0 - HdivRtga)*(1.0 - HdivRtga)*(1.0 - HdivRtga));
    } else {
        complex_t integral = mP_integrator->integrate(0., m_height);
        return Units::PI2*integral;
    }
}
