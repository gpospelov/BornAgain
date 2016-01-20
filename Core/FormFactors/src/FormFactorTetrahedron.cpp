// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTetrahedron.h"
#include "MathFunctions.h"
#include "BornAgainNamespace.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

using namespace  BornAgain;

FormFactorTetrahedron::FormFactorTetrahedron(
   double length, double height, double alpha)
{
    setName(FFTetrahedronType);
    m_height = height;
    m_length = length;
    m_alpha = alpha;
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorTetrahedron>::mem_function p_mf =
       & FormFactorTetrahedron::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorTetrahedron>(p_mf, this);
}

FormFactorTetrahedron::~FormFactorTetrahedron()
{
    delete m_integrator;
}

bool FormFactorTetrahedron::check_initialization() const
{
    bool result(true);
    if (2*std::sqrt(3.) * m_height > m_length*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorTetrahedron() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*sqrt(3.) * height <= length*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorTetrahedron::init_parameters()
{
    clearParameterPool();
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Length, &m_length, AttLimits::n_positive());
    registerParameter(Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    return new FormFactorTetrahedron(m_length, m_height, m_alpha);
}

void FormFactorTetrahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorTetrahedron::getRadius() const
{
    return m_length / 2;
}

complex_t FormFactorTetrahedron::Integrand(double Z, void* params) const
{
    (void)params;
    constexpr double root3 = std::sqrt(3.);
    double Rz = m_length/2 -root3*Z/std::tan(m_alpha);

    complex_t xy_part = 0;
    if (m_q.x()==complex_t(0,0) && m_q.y()==complex_t(0,0)) {
        xy_part = root3*Rz*Rz;
    }
    else {
        complex_t r3qyRz = root3*m_q.y()*Rz;
        complex_t expminiqyRdivr3 =
            std::exp(-complex_t(0.0, 1.0)*m_q.y()*Rz/root3);
        if (std::abs(m_q.x()*m_q.x()-3.*m_q.y()*m_q.y()) == 0) {
            xy_part = complex_t(0.0, 1.0)*root3*expminiqyRdivr3*
                   (std::sin(r3qyRz)-r3qyRz*std::exp(complex_t(0.0, 1.0)*r3qyRz))/
                m_q.x()/m_q.x();
        } else {
            complex_t qxRz = m_q.x()*Rz;
            xy_part = 2*root3*expminiqyRdivr3/
                    (m_q.x()*m_q.x()-3.0*m_q.y()*m_q.y())*(
                        std::exp(complex_t(0.0, 1.0)*r3qyRz) -
                std::cos(qxRz)-complex_t(0.0, 1.0)*r3qyRz*
                MathFunctions::Sinc(qxRz));
        }
    }
    return xy_part *std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{
    constexpr double root3 = std::sqrt(3.);
    const complex_t im(0.0,1.0);
    double H = m_height;
    double R = m_length/2;
    double tga = std::tan(m_alpha);
    double L = 2*tga*R/root3-H;

    if (std::abs(q.x()) <=  Numeric::double_epsilon ||
        std::abs(q.y())<=  Numeric::double_epsilon ||
        std::abs(q.z())<=  Numeric::double_epsilon ||
        std::abs(q.x())*std::abs(q.x())
        - 3*std::abs(q.y())*std::abs(q.y()) <=  Numeric::double_epsilon)
    {
        if ( std::abs(q.mag()) < Numeric::double_epsilon) {
            double sqrt3HdivRtga = root3*H/R/tga;
            return tga/3*R*R*R*(1 - (1-sqrt3HdivRtga)
                                 *(1-sqrt3HdivRtga)
                                 *(1-sqrt3HdivRtga));
        } else {
            m_q = q;
            complex_t integral = m_integrator->integrate(0., m_height);
            return integral;
        }
    } else {
        //general case
        const complex_t q1=(1./2.)*((root3*q.x() - q.y())/tga - q.z());
        const complex_t q2=(1./2.)*((root3*q.x() + q.y())/tga + q.z());
        const complex_t q3 = (q.y()/tga - q.z()/2.);

        return H*root3*std::exp(im*q.z()*R*tga/root3)/(q.x()*q.x()-3.*q.y()*q.y())*
            (-(1.+root3*q.y()/q.x())*MathFunctions::Sinc(q1*H)*std::exp(im*q1*L)
             -(1.-root3*q.y()/q.x())*MathFunctions::Sinc(q2*H)*std::exp(-im*q2*L) +
             2.*MathFunctions::Sinc(q3*H)*std::exp(im*q3*L));
    }
}
