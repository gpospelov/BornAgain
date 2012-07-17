#include "FormFactorPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"
#include "Exceptions.h"
#include <iostream>


FormFactorPyramid::FormFactorPyramid(double height, double half_side, double alpha)
{
    mp_height = new StochasticDiracDelta<double>(height);
    mp_half_side = new StochasticDiracDelta<double>(half_side);
    mp_alpha = new StochasticDiracDelta<double>(alpha);
}

FormFactorPyramid::FormFactorPyramid(StochasticParameter<double> *p_height, StochasticParameter<double> *p_half_side, StochasticParameter<double> *p_alpha)
    : mp_height(p_height)
    , mp_half_side(p_half_side)
    , mp_alpha(p_alpha)
{
}

FormFactorPyramid::~FormFactorPyramid()
{
    delete mp_height;
    delete mp_half_side;
    delete mp_alpha;
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
    return new FormFactorPyramid(mp_height->clone(), mp_half_side->clone(), mp_alpha->clone());
}

complex_t FormFactorPyramid::evaluate_for_complex_qz(kvector_t q, complex_t qz) const
{
    double H = mp_height->getCurrent();
    double R = mp_half_side->getCurrent();
    double tga = std::tan(mp_alpha->getCurrent());

    double qx = q.x();
    double qy = q.y();

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
        F = K1*cos( (qx-qy)*R ) + K2*sin( (qx-qy)*R ) - K3*cos( (qx+qy)*R ) - K4*sin( (qx+qy)*R );
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
        F=(4.*(qxy*tga*(-(qxy*qxy*R) + qz*tga*(complex_t(0,-2) + qz*R*tga))*std::cos(qxy*R) -
               std::exp(im*H*qz)*qxy*(H*std::pow(qxy,2) - qxy*qxy*R*tga - qz*(complex_t(0,2) + H*qz)*std::pow(tga,2) +
                  std::pow(qz,2)*R*std::pow(tga,3))*std::cos(qxy*(R - H/tga)) +
               tga*(std::pow(qxy,2)*(1. - complex_t(0,1)*qz*R*tga) + std::pow(qz,2)*std::pow(tga,2)*(1. + complex_t(0,1)*qz*R*tga))*
                std::sin(qxy*R) + complex_t(0,1)*std::exp(im*H*qz)*tga*
                (std::pow(qz,2)*std::pow(tga,2)*(complex_t(0,1) + H*qz - qz*R*tga) +
                  std::pow(qxy,2)*(complex_t(0,1) - H*qz + qz*R*tga))*std::sin(qxy*(R - H/tga))))/
           (qxy*std::pow(qxy - qz*tga,2)*std::pow(qxy + qz*tga,2));
    }
    return F;
}

