// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTetrahedron.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"

// Integration
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorTetrahedron::FormFactorTetrahedron(
   double length, double height, double alpha)
{
    setName("FormFactorTetrahedron");
    m_height = height;
    m_length = length;
    m_alpha = alpha;
    m_root3 = std::sqrt(3.0);
    assert(2.*m_root3 * m_height <= m_length*std::tan(m_alpha) );
    init_parameters();

    // addition integration

    MemberComplexFunctionIntegrator<FormFactorTetrahedron>::mem_function p_mf =
       & FormFactorTetrahedron::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorTetrahedron>(p_mf, this);

}

void FormFactorTetrahedron::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("length", &m_length);
    registerParameter("alpha", &m_alpha);
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    FormFactorTetrahedron *result =
        new FormFactorTetrahedron(m_length, m_height, m_alpha);
    result->setName(getName());
    return result;
}

// addition integration
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
                    (m_q.x()*m_q.x()-3.0*m_q.y()*m_q.y())*(std::exp(complex_t(0.0, 1.0)*r3qyRz) -
                std::cos(qxRz)-complex_t(0.0, 1.0)*r3qyRz*
                MathFunctions::Sinc(qxRz));

        }
    }

    return xy_part *std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{   m_q = q;

  if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {

        double R = m_length/2.;
        double H = m_height;
        double tga = std::tan(m_alpha);
        double sqrt3HdivRtga = m_root3*H/R/tga;
        return tga/3.*R*R*R*(1. -
                    (1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga));

    } else {

        complex_t integral = m_integrator->integrate(0., m_height);

        return integral;
    }
}

///////////////////
/*complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{
   double H = m_height;
    double R = m_length/2.0;
    double tga = std::tan(m_alpha);
    double L = 2.*tga*R/m_root3-H;

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    complex_t q1, q2, q3;
    q1=(1./2.)*((m_root3*qx - qy)/tga - qz);
    q2=(1./2.)*((m_root3*qx + qy)/tga + qz);
    q3 = (qy/tga - qz/2.);

    complex_t F;
    const complex_t im(0.0,1.0);


    if (std::abs(qx*qx-3.0*qy*qy) <= Numeric::double_epsilon) {
        if (std::abs(qx) <= Numeric::double_epsilon) {
            if (std::abs(qz) <= Numeric::double_epsilon) {*/
    //            //volume
              /*  double sqrt3HdivRtga = m_root3*H/R/tga;
                F = tga/3.*R*R*R*(1. -
                   (1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga));
            } else {*/
             // qx=qy=0 qz!=0
               /* complex_t qzH_half = qz*H/2.0;
                F = m_root3*H*std::exp(im*qzH_half)*(
                            MathFunctions::Sinc(qzH_half)*
                           (R*R-im*2.*m_root3*R/(qz*tga)-6./(qz*qz*tga*tga))
                           + m_root3*std::exp(im*qzH_half)/(qz*tga)*(
                            2.*im*R - im*m_root3*H/tga + 2.*m_root3/(qz*tga)));
            }

        } else {*/
            // qx**2-3qy**2
            /*complex_t qa = 2.0*qy/tga + qz/2.0;
            F = H*m_root3*std::exp(im*2.0*qy*R/m_root3)*(
                MathFunctions::Sinc(q3*H)
                  *(1.0 +m_root3*qy*(-im*2.0*R + m_root3/(q3*tga)))
              - 3.0*qy*std::exp(-im*2.0*q3*H)/(q3*tga)
              - std::exp(im*qa*H-im*2.0*m_root3*qy*R)*MathFunctions::Sinc(qa*H)
                )/(2.0*qx*qx);

        }
    } else {
        if (std::abs(qx) <= Numeric::double_epsilon) {*/
            //qx=0 qy!=0 case with pb
           // F =  m_integrator->integrate(0., m_height);

         /*   complex_t q2x0  =(1./2.)*(qy/tga + qz);

            if (std::abs(q2x0) >= Numeric::double_epsilon)
               F=  2.*H/(m_root3)*std::exp(im*qz*(L+H)/2.)*(
                               std::exp(-im*q2x0*L)*(
                                   MathFunctions::Sinc(q2x0*H)
                               *(1./qy/qy+im*m_root3*R/qy+3./(qy*q2x0*tga))-
                                   3./(qy*q2x0*tga)*std::exp(im*q2x0*H)
                                   )
                         -std::exp(im*q3*L)*MathFunctions::Sinc(q3*H)/qy/qy
                         );*/
  //2./3.*im *(-6.*im * std::exp((1./3.*im) * (-qy*R*m_root3*tga +3.*qz*H*tga + 3.*qy*H)/tga) *R*(qy*qy*qy)* tga-3.*im *std::exp((1./3.*im)*(-qy*R*m_root3*tga+3.*qz*H*tga + 3.*qy*H)/tga)*R*(qy*qy)*qz*(tga*tga)
  //+ (6.*im)*H* std::exp((1./3.*im)* (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga)* (2. / 3.*im)* ((-6.*im) * std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * R * (qy*qy*qy) * tga + (-3.*im) * std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * R * (qy*qy) * qz * (tga*tga) + (6.*im) * H * std::exp((1./3.*im)* (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * (qy*qy*qy) + (6.*im) * std::exp((-1./3.*im) * qy * R * m_root3) * R * (qy*qy*qy) * tga + (-3.*im) * H* std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * qy * (qz*qz) * (tga*tga) + (3.*im) * std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * R * qy * (qz*qz) * (tga*tga*tga)+ (3.*im) * H * std::exp((1./ 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * (qy*qy) * qz * tga + (-3.*im) * std::exp((-1. / 3.*im) * qy * R * m_root3) * R * qy * (qz*qz) * (tga*tga*tga) + std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * (qz*qz) * (tga*tga*tga)- std::exp((-1. / 3.*im) * (-2. * qy * R * m_root3 * tga - 3. * qz * H * tga + 6. * qy * H) / tga) * m_root3 * (qz*qz)) * (tga*tga*tga) + (3.*im) * std::exp((-1. / 3.*im) * qy * R * m_root3) * R * (qy*qy) * qz * (tga*tga) - std::exp((-1. / 3.*im) * qy * R * m_root3) * m_root3 * (qz*qz) * (tga*tga*tga) + m_root3 * std::exp((2. / 3.*im) * qy * R * m_root3) * (qz*qz) * (tga*tga*tga) + 2. * std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * qy * qz * (tga*tga) - 2. * std::exp((-1. / 3.*im) * (-2. * qy * R * m_root3 * tga - 3. * qz * H * tga + 6. * qy * H) / tga) * m_root3 * qy * qz * (tga*tga) - 2. * std::exp((-1. / 3.*im) * qy * R * m_root3) * m_root3 * qy * qz * (tga*tga) + 2.*m_root3 * std::exp((2. / 3.*im) * qy * R * m_root3) * qy * qz * (tga*tga) - 8. * std::exp((1. / 3.*im) * (-qy * R * m_root3 * tga + 3. * qz * H * tga + 3. * qy * H) / tga) * m_root3 * (qy*qy) * tga - std::exp((-1. / 3.*im) * (-2. * qy * R * m_root3* tga - 3. * qz * H * tga + 6. * qy * H) / tga) * m_root3 * (qy*qy) * tga + 8. * std::exp((-1./3.*im) * qy * R * m_root3) * m_root3 * (qy*qy) * tga + m_root3*std::exp((2./3.*im) * qy * R * m_root3)*(qy*qy) * tga)/((qz * tga +qy)*(qz*tga+qy))/(-qz*tga+2.*qy)/(qy*qy);

           //  else {
         //        // q2==0
          /*      F = 2.*H/(m_root3*qy*qy)*(
                            -std::exp(im*2.*qy*R/m_root3)*MathFunctions::Sinc(qz*3.*H/2.)
                            +std::exp(-im*qy*R/m_root3)*(1.0+im*3.*qy*L/(2.*tga))
                            );
}
        } else {*/
            //general case
           /* F =-(1.+m_root3*qy/qx)*MathFunctions::Sinc(q1*H)*std::exp(im*q1*L)
               -(1.-m_root3*qy/qx)*MathFunctions::Sinc(q2*H)*std::exp(-im*q2*L)
               +2.*MathFunctions::Sinc(q3*H)*std::exp(im*q3*L);
            F = H*m_root3*std::exp(im*qz*R*tga/m_root3)/(qx*qx-3.*qy*qy)*F;
        }
    }
    return F;
}*/



