#include "FormFactorPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"
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

////    double yyy=Numeric::double_epsilon;
    double xxx = 2.2204460492503131e-12;
////    xxx = yyy;

    double Z = Units::deg2rad(45.);

    double qx =  std::cos(Z)*q.x() + std::sin(Z)*q.y();
    double qy = -std::sin(Z)*q.x() + std::cos(Z)*q.y();


//    double qx = q.x() < 0 ? q.x()-xxx : q.x()+xxx;
//    double qy = q.y() < 0 ? q.y()-xxx : q.y()+xxx;
//    qx = qx < 0 ? qx-xxx : qx+xxx;
//    qy = qy < 0 ? qy-xxx : qy+xxx;

    //qx=-qx;
    //qy=-qy;
    //qz=qz;

//    std::cout << qx << " " << qy << " " << qz << std::endl;
//    tga = 1.4139198475210695;
//    qx = 3.827931527975784E-004;
//    qy = 2.220446049250313E-012;
//    qz = complex_t(0.21932409684619383,0);

    //3.520509380266774e-14 + 1.3534220444738035e-14

    complex_t qppH, qmpH, qpmH, qmmH, qpR, qmR, tmp1, tmp2, tmp3, tmp4, F;
    complex_t im(0,1);

    qppH = ( (qx+qy)/tga+qz )*H/2.; //q3
    qmpH = ( (qx-qy)/tga+qz )*H/2.; //q1
    qpmH = ( (qx+qy)/tga-qz )*H/2.; //q4
    qmmH = ( (qx-qy)/tga-qz )*H/2.; //q2

    qpR  = (qx+qy)*R;
    qmR  = (qx-qy)*R;
    tmp1 = MathFunctions::Sinc(qmpH)*std::exp(im*qmpH) +MathFunctions::Sinc(qmmH)*std::exp(-im*qmmH); //K1
    tmp2 = -im*MathFunctions::Sinc(qmpH)*std::exp(im*qmpH) + im*MathFunctions::Sinc(qmmH)*std::exp(-im*qmmH); //K2 ? sign
    tmp3 = MathFunctions::Sinc(qppH)*std::exp(im*qppH)+MathFunctions::Sinc(qpmH)*std::exp(-im*qpmH); //K3
    tmp4 = -im*MathFunctions::Sinc(qppH)*std::exp(im*qppH) + im*MathFunctions::Sinc(qpmH)*std::exp(-im*qpmH);
    F = std::cos(qmR)*tmp1 + std::sin(qmR)*tmp2 - std::cos(qpR)*tmp3 - std::sin(qpR)*tmp4;
    F = F*H/(qx*qy);

//    complex_t F;
//    const complex_t im(0,1);
////    if( std::abs(qx) > Numeric::double_epsilon && std::abs(qx) > Numeric::double_epsilon ) {
//        complex_t q1, q2, q3, q4;
//        q1=(H/2.)*((qx-qy)/tga + qz);
//        q2=(H/2.)*((qx-qy)/tga - qz);
//        q3=(H/2.)*((qx+qy)/tga + qz);
//        q4=(H/2.)*((qx+qy)/tga - qz);
//        complex_t K1,K2,K3,K4;
//        K1 = MathFunctions::Sinc(q1)*std::exp(im*q1)    + MathFunctions::Sinc(q2)*std::exp(-im*q2);
//        K2 = -MathFunctions::Sinc(q1)*std::exp(im*q1)*im + MathFunctions::Sinc(q2)*std::exp(-im*q2)*im;
//        K3 = MathFunctions::Sinc(q3)*std::exp(im*q3)    + MathFunctions::Sinc(q4)*std::exp(-im*q4);
//        K4 = -MathFunctions::Sinc(q3)*std::exp(im*q3)*im + MathFunctions::Sinc(q4)*std::exp(-im*q4)*im;
//        F = K1*cos( (qx-qy)*R ) + K2*sin( (qx-qy)*R ) - K3*cos( (qx+qy)*R ) - K4*sin( (qx+qy)*R );
//        F = F*H/(qx*qy);
////    }

    return F;
}

