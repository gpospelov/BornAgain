// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorAnisoPyramid.cpp
//! @brief     Implements class FormFactorAnisoPyramid.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorAnisoPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"

FormFactorAnisoPyramid::FormFactorAnisoPyramid(
    double length, double width, double height, double alpha)
{
    setName("FormFactorAnisoPyramid");
    m_length = length;
    m_width = width;
    m_height = height;
    m_alpha = alpha;
    init_parameters();
}

void FormFactorAnisoPyramid::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter("width", &m_width);
    registerParameter("height", &m_height);
    registerParameter("alpha", &m_alpha);
}

FormFactorAnisoPyramid* FormFactorAnisoPyramid::clone() const
{
    FormFactorAnisoPyramid *result =
        new FormFactorAnisoPyramid(m_length, m_width, m_height, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorAnisoPyramid::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double L = m_length;
    double W = m_width;
    double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    complex_t F;
    const complex_t im(0,1);

    if( std::abs(qx) > Numeric::double_epsilon
            && std::abs(qy) > Numeric::double_epsilon ) {
        // General case
        complex_t q1, q2, q3, q4;
        q1=(H/2.)*((qx-qy)/tga + qz);
        q2=(H/2.)*((qx-qy)/tga - qz);
        q3=(H/2.)*((qx+qy)/tga + qz);
        q4=(H/2.)*((qx+qy)/tga - qz);
        complex_t K1,K2,K3,K4;
        K1 = MathFunctions::Sinc(q1)*std::exp(im*q1)
                + MathFunctions::Sinc(q2)*std::exp(-im*q2);
        K2 = -MathFunctions::Sinc(q1)*std::exp(im*q1)*im
                + MathFunctions::Sinc(q2)*std::exp(-im*q2)*im;
        K3 = MathFunctions::Sinc(q3)*std::exp(im*q3)
                + MathFunctions::Sinc(q4)*std::exp(-im*q4);
        K4 = -MathFunctions::Sinc(q3)*std::exp(im*q3)*im
                + MathFunctions::Sinc(q4)*std::exp(-im*q4)*im;
        F = K1*std::cos( (qx*L-qy*W)/2. ) + K2*std::sin( (qx*L-qy*W)/2.  )
                - K3*std::cos( (qx*L+qy*W)/2. ) - K4*std::sin( (qx*L+qy*W)/2. );
        F = F*H/(qx*qy);
    } else if(std::abs(qx) <= Numeric::double_epsilon
              && std::abs(qy) <= Numeric::double_epsilon) {

        if (std::abs(qz) <= Numeric::double_epsilon)
        //Volume qx=qy=qz=0
        F = L*W*H - (L + W)*H*H/tga + 4.0/3.0*H*H*H/(tga*tga);
        else
            //qx=0 qy=0 qz!=0
             F=im*(
                - 8.0/std::pow(tga,2) - 2.0*im*qz*(L+W)/tga + std::pow(qz,2)*L*W
                - std::exp(im*H*qz)*(L*W*qz*qz - 2.0*(L+W)*qz/tga*(H*qz+im)
                + 4.0*(std::pow(qz*H,2)+2.0*im*qz*H-2.0)/std::pow(tga,2))
                   )/std::pow(qz,3);

    } else {
        complex_t qxy, q5, q6;
         double R0, Rxy;
        if(std::abs(qy) <= Numeric::double_epsilon
                && std::abs(qx) > Numeric::double_epsilon) {
            // qx!=0 qy=0
            qxy=qx;
            Rxy = L/2.0;
            R0 = W/2.0;
        } else {
            // qy!=0 qx=0
            qxy=qy;
            R0 = L/2.0;
            Rxy = W/2.0;
        }
        q5 = (qz - qxy/tga)/2.;
        q6 = (qz + qxy/tga)/2.;

        if (std::abs(q5) <= Numeric::double_epsilon) {
            //q5 = 0, q6!=0
        F= -2.0*H*im/qxy*(
                    (R0 - H/(2.0*tga))*std::exp(im*qxy*Rxy)
                    - std::exp(im*q6*H-im*qxy*Rxy)*
                    ( R0*MathFunctions::Sinc(q6*H)
                    + im*( std::exp(im*q6*H)
                           - MathFunctions::Sinc(q6*H) )/(2.0*q6*tga))
                    );
        } else {
            if (std::abs(q6) <= Numeric::double_epsilon) {
                //q5!= 0, q6=0
                F=-2.0*H*im/qxy*(
                            std::exp(im*q5*H+im*qxy*Rxy)*
                            ( R0*MathFunctions::Sinc(q5*H)
                            + im*( std::exp(im*q5*H)
                                   - MathFunctions::Sinc(q5*H) )/(2.0*q5*tga))
                            +(H/(2.0*tga)-R0)*std::exp(-im*qxy*Rxy)
                            );
            } else {
                F=-2.0*H*im/qxy*(
                            std::exp(im*q5*H+im*qxy*Rxy)*
                            (R0*MathFunctions::Sinc(q5*H)
                            + im*( std::exp(im*q5*H)
                                   - MathFunctions::Sinc(q5*H) )/(2.0*q5*tga))
                            - std::exp(im*q6*H-im*qxy*Rxy)
                            *(R0*MathFunctions::Sinc(q6*H)
                            + im*( std::exp(im*q6*H)
                                   - MathFunctions::Sinc(q6*H))/(2.0*q6*tga))
                            );
            }
}
}
    return F;
}



