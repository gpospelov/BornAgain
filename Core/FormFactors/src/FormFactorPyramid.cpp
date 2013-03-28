// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPyramid.cpp
//! @brief     Implements class FormFactorPyramid.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"

FormFactorPyramid::FormFactorPyramid(
    double height, double half_side, double alpha)
{
    setName("FormFactorPyramid");
    m_height = height;
    m_half_side = half_side;
    m_alpha = alpha;
    init_parameters();
}

void FormFactorPyramid::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("half_side", &m_half_side);
    getParameterPool()->registerParameter("alpha", &m_alpha);
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
    FormFactorPyramid *p_clone =
        new FormFactorPyramid(m_height, m_half_side, m_alpha);
    return p_clone;
}

complex_t FormFactorPyramid::evaluate_for_q(const cvector_t& q) const
{

    double H = m_height;
    double R = m_half_side;
    double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

//    // comparison with isgisaxs trick
//        double gisaxs_epsilon = 2.2204460492503131e-12;
//        qx < 0 ? qx -= gisaxs_epsilon : qx += gisaxs_epsilon;
//        qy < 0 ? qy -= gisaxs_epsilon : qy += gisaxs_epsilon;
//        //double Z = 45.*Units::deg;
//        //double qx =  std::cos(Z)*q.x() + std::sin(Z)*q.y();
//        //double qy = -std::sin(Z)*q.x() + std::cos(Z)*q.y();

    complex_t F;
    const complex_t im(0,1);
    if( std::abs(qx) > Numeric::double_epsilon && std::abs(qy) > Numeric::double_epsilon ) {
        complex_t q1, q2, q3, q4;
        q1=(H/2.)*((qx-qy)/tga + qz);
        q2=(H/2.)*((qx-qy)/tga - qz);
        q3=(H/2.)*((qx+qy)/tga + qz);
        q4=(H/2.)*((qx+qy)/tga - qz);
        complex_t K1,K2,K3,K4;
        K1 = MathFunctions::Sinc(q1)*std::exp(im*q1)    + MathFunctions::Sinc(q2)*std::exp(-im*q2);
        K2 = -MathFunctions::Sinc(q1)*std::exp(im*q1)*im + MathFunctions::Sinc(q2)*std::exp(-im*q2)*im;
        K3 = MathFunctions::Sinc(q3)*std::exp(im*q3)    + MathFunctions::Sinc(q4)*std::exp(-im*q4);
        K4 = -MathFunctions::Sinc(q3)*std::exp(im*q3)*im + MathFunctions::Sinc(q4)*std::exp(-im*q4)*im;
        F = K1*std::cos( (qx-qy)*R ) + K2*std::sin( (qx-qy)*R ) - K3*std::cos( (qx+qy)*R ) - K4*std::sin( (qx+qy)*R );
        F = F*H/(qx*qy);
    } else if(std::abs(qx) <= Numeric::double_epsilon && std::abs(qy) <= Numeric::double_epsilon) {
        F=(4.*im*(-2./tga/tga - 2.*im*qz*R/tga + qz*qz*R*R - std::exp(im*H*qz) * ((-1.+im + H*qz)/tga - qz*R)*((1.+im + H*qz)/tga - qz*R)  ))/std::pow(qz,3);
    } else {
        complex_t qxy;
        if(std::abs(qy) <= Numeric::double_epsilon && std::abs(qx) > Numeric::double_epsilon) {
            qxy=qx;
        } else{
            qxy=qy;
        }
        F=(4.*(qxy*tga*(-(qxy*qxy*R) + qz*tga*(complex_t(0.0,-2.0) + qz*R*tga))*std::cos(qxy*R) -
               std::exp(im*H*qz)*qxy*(H*std::pow(qxy,2) - qxy*qxy*R*tga - qz*(complex_t(0.0,2.0) + H*qz)*std::pow(tga,2) +
                  std::pow(qz,2)*R*std::pow(tga,3))*std::cos(qxy*(R - H/tga)) +
               tga*(std::pow(qxy,2)*(1. - complex_t(0.0,1.0)*qz*R*tga) + std::pow(qz,2)*std::pow(tga,2)*(1. + complex_t(0.0,1.0)*qz*R*tga))*
                std::sin(qxy*R) + complex_t(0.0,1.0)*std::exp(im*H*qz)*tga*
                (std::pow(qz,2)*std::pow(tga,2)*(complex_t(0.0,1.0) + H*qz - qz*R*tga) +
                  std::pow(qxy,2)*(complex_t(0.0,1.0) - H*qz + qz*R*tga))*std::sin(qxy*(R - H/tga))))/
           (qxy*std::pow(qxy - qz*tga,2)*std::pow(qxy + qz*tga,2));
    }
    return F;
}
