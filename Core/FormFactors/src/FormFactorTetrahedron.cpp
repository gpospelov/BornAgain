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
    m_root3 = std::sqrt(3.0);
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
    if(2.*m_root3 * m_height > m_length*std::tan(m_alpha)) {
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
    return m_length / 2.0;
}

complex_t FormFactorTetrahedron::Integrand(double Z, void* params) const
{
    (void)params;
    double Rz = m_length/2. -m_root3*Z/std::tan(m_alpha);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (std::abs(m_q.x())==0.0 && std::abs(m_q.y())==0.0) {
        xy_part = m_root3*Rz*Rz;
    }
    else {
        complex_t r3qyRz = m_root3*m_q.y()*Rz;
        complex_t expminiqyRdivr3 =
            std::exp(-complex_t(0.0, 1.0)*m_q.y()*Rz/m_root3);
        if (std::abs(m_q.x()*m_q.x()-3.0*m_q.y()*m_q.y())==0.0) {
            xy_part = complex_t(0.0, 1.0)*m_root3*expminiqyRdivr3*
                   (std::sin(r3qyRz)-r3qyRz*std::exp(complex_t(0.0, 1.0)*r3qyRz))/
                m_q.x()/m_q.x();
        } else {
            complex_t qxRz = m_q.x()*Rz;
            xy_part = 2.0*m_root3*expminiqyRdivr3/
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
    m_q =q ;
    double H = m_height;
    double R = m_length/2.0;
    double tga = std::tan(m_alpha);
    double L = 2.*tga*R/m_root3-H;
    const complex_t im(0.0,1.0);

    if (std::abs(m_q.x()) <=  Numeric::double_epsilon ||
        std::abs(m_q.y())<=  Numeric::double_epsilon ||
        std::abs(m_q.z())<=  Numeric::double_epsilon ||
        std::abs(m_q.x())*std::abs(m_q.x())
        - 3.*std::abs(m_q.y())*std::abs(m_q.y()) <=  Numeric::double_epsilon)
     {
        if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {
          double sqrt3HdivRtga = m_root3*H/R/tga;
          return tga/3.*R*R*R*(1. - (1.-sqrt3HdivRtga)
                              *(1.-sqrt3HdivRtga)
                              *(1.-sqrt3HdivRtga));
     } else {
          complex_t integral = m_integrator->integrate(0., m_height);
          return integral;}
 } else {
        //general case
       complex_t qx = m_q.x();
       complex_t qy = m_q.y();
       complex_t qz = m_q.z();
       complex_t q1, q2, q3;
       q1=(1./2.)*((m_root3*qx - qy)/tga - qz);
       q2=(1./2.)*((m_root3*qx + qy)/tga + qz);
       q3 = (qy/tga - qz/2.);

       return H*m_root3*std::exp(im*qz*R*tga/m_root3)/(qx*qx-3.*qy*qy)*
            (-(1.+m_root3*qy/qx)*MathFunctions::Sinc(q1*H)*std::exp(im*q1*L)
            -(1.-m_root3*qy/qx)*MathFunctions::Sinc(q2*H)*std::exp(-im*q2*L) +
             2.*MathFunctions::Sinc(q3*H)*std::exp(im*q3*L));
    }
}


