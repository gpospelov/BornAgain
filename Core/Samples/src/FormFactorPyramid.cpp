#include "FormFactorPyramid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"


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
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
    return new FormFactorPyramid(mp_height->clone(), mp_half_side->clone());
}

complex_t FormFactorPyramid::evaluate_for_complex_qz(kvector_t q, complex_t qz) const
{
//    complex_t qzH_half = qz*H/2.0;
//    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*std::exp(complex_t(0.0, 1.0)*qzH_half);

//    double qrR = q.magxy()*R;
//    double J1_qrR_div_qrR = qrR > Numeric::double_epsilon ? MathFunctions::Bessel_J1(qrR)/qrR : 0.5;
//    double radial_part = 2*M_PI*R*R*J1_qrR_div_qrR;
//    return radial_part*z_part;



    return 0;
}


/*
! Fourier transform of a in plane square
! truncated pyramid with angle atand(tga) between the (001) plane
! and the facets : analytic expression
! To prevent divide by zero
qc(1:2)	= q(1:2) + SIGN(x$EPSILON,q(1:2))
qc(3)	= qz

qppH	= ((qc(1)+qc(2))/tga + qc(3))*H/2._wp
qmpH	= ((qc(1)-qc(2))/tga + qc(3))*H/2._wp
qpmH	= ((qc(1)+qc(2))/tga - qc(3))*H/2._wp
qmmH	= ((qc(1)-qc(2))/tga - qc(3))*H/2._wp
qpR		= (qc(1)+qc(2))*R
qmR		= (qc(1)-qc(2))*R
tmp(1)	=     sinc(qmpH)*Exp(im*qmpH) +    sinc(qmmH)*Exp(-im*qmmH)
tmp(2)	= -im*sinc(qmpH)*Exp(im*qmpH) + im*sinc(qmmH)*Exp(-im*qmmH)
tmp(3)	=     sinc(qppH)*Exp(im*qppH) +    sinc(qpmH)*Exp(-im*qpmH)
tmp(4)	= -im*sinc(qppH)*Exp(im*qppH) + im*sinc(qpmH)*Exp(-im*qpmH)
FF		= Cos(qmR)*tmp(1) + Sin(qmR)*tmp(2) - Cos(qpR)*tmp(3) - Sin(qpR)*tmp(4)
FF		= FF*H/(qc(1)*qc(2))

*/
