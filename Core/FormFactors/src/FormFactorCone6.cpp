// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCone6.cpp
//! @brief     Implements class FormFactorCone6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCone6.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

#include <cmath>

using namespace  BornAgain;

FormFactorCone6::FormFactorCone6(double radius, double height, double alpha)
{
    setName(FFCone6Type);
    m_radius = radius;
    m_height = height;
    m_alpha = alpha;
    m_root3 = std::sqrt(3.0);
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorCone6>::mem_function p_mf =
       & FormFactorCone6::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorCone6>(p_mf, this);
}

FormFactorCone6::~FormFactorCone6()
{
    delete m_integrator;
}

bool FormFactorCone6::check_initialization() const
{
    bool result(true);
    if(m_height > m_radius*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorCone6() -> Error in class initialization with parameters";
        ostr << " radius:" << m_radius;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= radius*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorCone6::init_parameters()
{
    clearParameterPool();
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorCone6* FormFactorCone6::clone() const
{
   return new FormFactorCone6(m_radius, m_height, m_alpha);
}

void FormFactorCone6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

//! Integrand for complex formfactor.
complex_t FormFactorCone6::Integrand(double Z, void *) const
{
    double Rz = m_radius - 2. * Z / std::tan(m_alpha) / m_root3;
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    complex_t qz = m_q.z();

    complex_t qxR_half = qx * Rz / 2.0;
    complex_t qyr3R_half = m_root3 * qy * Rz / 2.;

    if (std::abs(3.0 * qy * qy - qx * qx) == 0.0) {
        return Rz * Rz * m_root3 / 2.0 * MathFunctions::sinc(qyr3R_half)
               * (MathFunctions::sinc(qyr3R_half) + 2.0 * std::cos(qyr3R_half));
    } else {
        return (3. / 4. * qy * Rz * qy * Rz * MathFunctions::sinc(qxR_half)
                * MathFunctions::sinc(qyr3R_half) + std::cos(2.0 * qxR_half)
                - std::cos(qyr3R_half) * std::cos(qxR_half))
               * std::exp(complex_t(0.0, 1.0) * qz * Z);
    }
}

//! Complex formfactor.
complex_t FormFactorCone6::evaluate_for_q(const cvector_t& q) const
{
    m_q = q;
    if ( std::abs(q.mag()) < Numeric::double_epsilon) {
        double R = m_radius;
        double H = m_height;
        double tga = std::tan(m_alpha);
        double HdivRtga = 2./m_root3*H/tga/R;

        return  3.0/4.0*tga*R*R*R*
                (1.0 - (1.0 - HdivRtga)*(1.0 - HdivRtga)*(1.0 - HdivRtga));
    } else {
        complex_t integral = m_integrator->integrate(0., m_height);

        return 4.0*m_root3/(3.0*m_q.y()*m_q.y()-m_q.x()*m_q.x())*integral;
    }
}
