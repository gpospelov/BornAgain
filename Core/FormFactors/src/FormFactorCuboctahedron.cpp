// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCuboctahedron.cpp
//! @brief     Implements class FormFactorCuboctahedron.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCuboctahedron.h"
#include "FormFactorPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"

FormFactorCuboctahedron::FormFactorCuboctahedron(
    double half_side, double height, double height_ratio, double alpha)
{
    setName("FormFactorCuboctahedron");
    m_height = height;
    m_half_side = half_side;
    m_height_ratio = height_ratio;
    m_alpha = alpha;
    init_parameters();
}

void FormFactorCuboctahedron::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("height_ratio", &m_height_ratio);
    registerParameter("half_side", &m_half_side);
    registerParameter("alpha", &m_alpha);
}

FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const
{
    FormFactorCuboctahedron *result =
        new FormFactorCuboctahedron(m_half_side, m_height,
                                    m_height_ratio, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorCuboctahedron::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_half_side;
    double rh = m_height_ratio;
    //double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    FormFactorPyramid fftop(rh*H,R, m_alpha);
    complex_t ffhigh = fftop.evaluate_for_q(q);
    FormFactorPyramid ffbottom(H,R, m_alpha);
    cvector_t downq(qx,qy,-qz);
    complex_t fflow = ffbottom.evaluate_for_q(downq);
    const complex_t im(0,1);

   /* complex_t F;
    if( std::abs(qx) > Numeric::double_epsilon && std::abs(qy) > Numeric::double_epsilon ) {
        complex_t q1t, q2t, q3t, q4t;
        q1t=(rh*H/2.)*((qx-qy)/tga + qz);
        q2t=(rh*H/2.)*((qx-qy)/tga - qz);
        q3t=(rh*H/2.)*((qx+qy)/tga + qz);
        q4t=(rh*H/2.)*((qx+qy)/tga - qz);
        complex_t K1t,K2t,K3t,K4t;

        K1t = MathFunctions::Sinc(q1t)*std::exp(im*q1t)    + MathFunctions::Sinc(q2t)*std::exp(-im*q2t);
        K2t = -MathFunctions::Sinc(q1t)*std::exp(im*q1t)*im + MathFunctions::Sinc(q2t)*std::exp(-im*q2t)*im;
        K3t = MathFunctions::Sinc(q3t)*std::exp(im*q3t)    + MathFunctions::Sinc(q4t)*std::exp(-im*q4t);
        K4t = -MathFunctions::Sinc(q3t)*std::exp(im*q3t)*im + MathFunctions::Sinc(q4t)*std::exp(-im*q4t)*im;

        complex_t q1b, q2b, q3b, q4b;
        q1b=(H/2.)*((qx-qy)/tga - qz);
        q2b=(H/2.)*((qx-qy)/tga + qz);
        q3b=(H/2.)*((qx+qy)/tga - qz);
        q4b=(H/2.)*((qx+qy)/tga + qz);
        complex_t K1b,K2b,K3b,K4b;

        K1b = MathFunctions::Sinc(q1b)*std::exp(im*q1b)    + MathFunctions::Sinc(q2b)*std::exp(-im*q2b);
        K2b = -MathFunctions::Sinc(q1b)*std::exp(im*q1b)*im + MathFunctions::Sinc(q2b)*std::exp(-im*q2b)*im;
        K3b = MathFunctions::Sinc(q3b)*std::exp(im*q3b)    + MathFunctions::Sinc(q4b)*std::exp(-im*q4b);
        K4b = -MathFunctions::Sinc(q3b)*std::exp(im*q3b)*im + MathFunctions::Sinc(q4b)*std::exp(-im*q4b)*im;

        F = (K1t+K1b)*std::cos( (qx-qy)*R ) + (K2t+K2b)*std::sin( (qx-qy)*R )
                - (K3t+K3b)*std::cos( (qx+qy)*R) - (K4t+K4b)*std::sin( (qx+qy)*R );

        F = F*H/(qx*qy);
    } else if(std::abs(qx) <= Numeric::double_epsilon && std::abs(qy) <= Numeric::double_epsilon) {
        if (std::abs(qz) <= Numeric::double_epsilon)
            F = 4./3.*tga*R*R*R*( 2.-
                                 (1. - H/R/tga)*(1. - H/R/tga)*(1. - H/R/tga)
                        - (1. - rh*H/R/tga)*(1. - rh*H/R/tga)*(1. - rh*H/R/tga)
                                  );
        else
             F=4.*im*(
                  + 2.*qz*qz*R*R - std::exp(im*rh*H*qz)
                  * ((-1.+im + rh*H*qz)/tga - qz*R)
                  *((1.+im + rh*H*qz)/tga - qz*R)
                         - std::exp(-im*H*qz)
                          * ((-1.+im - H*qz)/tga + qz*R)
                          *((1.+im - H*qz)/tga + qz*R)
                   )/std::pow(qz,3);
    } else {
        complex_t qxy;
        if(std::abs(qy) <= Numeric::double_epsilon && std::abs(qx) > Numeric::double_epsilon) {
            qxy=qx;
        } else{
            qxy=qy;
        }
        F=(4.*(qxy*tga*(-(qxy*qxy*R) + qz*tga*(-2.0*im + qz*R*tga))*std::cos(qxy*R) -
               std::exp(im*rh*H*qz)*qxy*(rh*H*std::pow(qxy,2) - qxy*qxy*R*tga - qz*(2.0*im + rh*H*qz)*std::pow(tga,2) +
                  std::pow(qz,2)*R*std::pow(tga,3))*std::cos(qxy*(R - rh*H/tga)) +
               tga*(std::pow(qxy,2)*(1. - im*qz*R*tga) + std::pow(qz,2)*std::pow(tga,2)*(1. + im*qz*R*tga))*
                std::sin(qxy*R) + im*std::exp(im*rh*H*qz)*tga*
                (std::pow(qz,2)*std::pow(tga,2)*(im + rh*H*qz - qz*R*tga) +
                  std::pow(qxy,2)*(im - rh*H*qz + qz*R*tga))*std::sin(qxy*(R - rh*H/tga)))

                +4.*(qxy*tga*(-(qxy*qxy*R) + qz*tga*(2.0*im + qz*R*tga))*std::cos(qxy*R) -
                      std::exp(-im*H*qz)*qxy*(H*std::pow(qxy,2) - qxy*qxy*R*tga + qz*(2.0*im - H*qz)*std::pow(tga,2) +
                         std::pow(qz,2)*R*std::pow(tga,3))*std::cos(qxy*(R - H/tga)) +
                      tga*(std::pow(qxy,2)*(1. + im*qz*R*tga) + std::pow(qz,2)*std::pow(tga,2)*(1. - im*qz*R*tga))*
                       std::sin(qxy*R) + im*std::exp(-im*H*qz)*tga*
                       (std::pow(qz,2)*std::pow(tga,2)*(im - H*qz + qz*R*tga) +
                         std::pow(qxy,2)*(im + H*qz - qz*R*tga))*std::sin(qxy*(R - H/tga)))
                  )/(qxy*std::pow(qxy - qz*tga,2)*std::pow(qxy + qz*tga,2));
    }*/
    return std::exp(im*qz*H)*(ffhigh + fflow)/*F*/;
}
