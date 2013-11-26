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

FormFactorTetrahedron::FormFactorTetrahedron(
   double half_side, double height, double alpha)
{
    setName("FormFactorTetrahedron");
    m_height = height;
    m_half_side = half_side;
    m_alpha = alpha;
    m_root3 = std::sqrt(3.0);
    init_parameters();

  /*  MemberComplexFunctionIntegrator<FormFactorTetrahedron>::mem_function p_mf =
       & FormFactorTetrahedron::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorTetrahedron>(p_mf, this);*/
}

void FormFactorTetrahedron::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("half_side", &m_half_side);
    registerParameter("alpha", &m_alpha);
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    FormFactorTetrahedron *result =
        new FormFactorTetrahedron(m_half_side, m_height, m_alpha);
    result->setName(getName());
    return result;
}


//! Integrand for complex formfactor.
/*complex_t FormFactorTetrahedron::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    double Rz = m_half_side -Z*m_root3/std::tan(m_alpha);
    complex_t r3qyR = m_root3*m_q.y()*Rz;
    complex_t qxR = m_q.x()*Rz;

    return (std::exp(complex_t(0.0, 1.0)*r3qyR) -
            std::cos(qxR)-complex_t(0.0, 1.0)*r3qyR*
            MathFunctions::Sinc(qxR))
            *std::exp(complex_t(0.0, 1.0)*(m_q.z()*Z-m_q.y()*Rz/m_root3));

}*/

//! Complex formfactor.

/*complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{   m_q = q;
    double H = m_height;
    double R = m_half_side;
    double tga = std::tan(m_alpha);

  if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {
      double sqrt3HdivRtga = m_root3*H/R/tga;
       return tga/3.*R*R*R*(1. -
          (1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga));
    }
    else {
    complex_t integral = m_integrator->integrate(0., H);
    return    2.0*m_root3/(q.x()*q.x()-3.0*q.y()*q.y())*integral;
    }
}*/


complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_half_side;
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
    const complex_t im(0,1);

    if (std::abs(qx) <= Numeric::double_epsilon) {

        if (std::abs(qy) <= Numeric::double_epsilon) {

            if (std::abs(qz) <= Numeric::double_epsilon) {
                // qx=qy=qz=0
                double sqrt3HdivRtga = m_root3*H/R/tga;
                F = tga/3.*R*R*R*(1. -
                   (1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga)*(1.-sqrt3HdivRtga));
            }
            else {
                //qx=qy=0 qz!=0
                complex_t qzH_half = qz*H/2.0;
                F = m_root3*H*std::exp(im*qzH_half)*(
                            MathFunctions::Sinc(qzH_half)*
                            (R*R-im*2.*m_root3*R/(qz*tga)-6./(qz*qz*tga*tga))
                            + m_root3*std::exp(im*qzH_half)/(qz*tga)*(
                            2.*im*R - im*m_root3*H/tga + 2.*m_root3/(qz*tga)));
            }
        }
        else {
            // qx=0 qy!=0
            F = 2.*H/(m_root3*qy*qy)*
                    std::exp(im*R*qz*tga/m_root3 + im*q3*L)*(
                    std::exp(-im*q2*L)*MathFunctions::Sinc(q2*H)
                  - std::exp(im*q3*L)*MathFunctions::Sinc(q3*H)) ;
        }
    }
    else {
        // qx!=0
         if (std::abs(qx*qx-3.0*qy*qy)==0.0) {
            // qx**2= 3qy**2
             complex_t qa = 2.0*qy/tga + qz/2.0;
             F = H*m_root3*std::exp(im*2.0*qy*R/m_root3)*(
                 MathFunctions::Sinc(q3*H)
                   *(1.0 +m_root3*qy*(-im*2.0*R + m_root3/(q3*tga)))
               - 3.0*qy*std::exp(-im*2.0*q3*H)/(q3*tga)
               - std::exp(im*qa*H-im*2.0*m_root3*qy*R)*MathFunctions::Sinc(qa*H)
                 )/(2.0*qx*qx);
        }
        else {
        //Formula Isgisaxs
         /*    complex_t qc1      = 2./m_root3*qx;
             complex_t qc2      = qx/m_root3 + qy;

             complex_t qq1  = 2.*qc1 -  qc2 - tga*qz;
             complex_t qq2  = qc1 +  qc2 + tga*qz;
             complex_t qq3  =-qc1 +2.*qc2 - tga*qz;
             complex_t Rt  =  R/m_root3;
             complex_t Ht  =  H/(2.*tga);

             F = -qc2*MathFunctions::Sinc(qq1*Ht)*std::exp(im*(Rt-Ht)*qq1) +
        (qc2-qc1)*MathFunctions::Sinc(qq2*Ht)*std::exp(-im*(Rt-Ht)*qq2) +
                qc1*MathFunctions::Sinc(qq3*Ht)*std::exp(im*(Rt-Ht)*qq3);
             F = F*2.*H/m_root3/qc1/qc2/(qc1-qc2)*std::exp(im*Rt*tga*qz);*/

             F =-(1.+m_root3*qy/qx)*MathFunctions::Sinc(q1*H)*std::exp(im*q1*L)
                -(1.-m_root3*qy/qx)*MathFunctions::Sinc(q2*H)*std::exp(-im*q2*L)
                +2.*MathFunctions::Sinc(q3*H)*std::exp(im*q3*L);

             F = H*m_root3*std::exp(im*qz*R*tga/m_root3)/(qx*qx-3.*qy*qy)*F;
}
}
    return F;
}



