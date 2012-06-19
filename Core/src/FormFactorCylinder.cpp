#include "FormFactorCylinder.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorCylinder::FormFactorCylinder(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius)
    : mp_height(p_height)
    , mp_radius(p_radius)
{
}

FormFactorCylinder::FormFactorCylinder(double height, double radius)
{
    mp_height = new StochasticDiracDelta<double>(height);
    mp_radius = new StochasticDiracDelta<double>(radius);
}

FormFactorCylinder::~FormFactorCylinder()
{
    delete mp_height;
    delete mp_radius;
}

complex_t FormFactorCylinder::evaluate_for_q(kvector_t q) const
{
    double R = mp_radius->getCurrent();
    double H = mp_height->getCurrent();
    double qrR = q.magxy()*R;
    double qzH_half = q.z()*H/2.0;
    double J1_qrR_div_qrR = qrR > Numeric::double_epsilon ? MathFunctions::Bessel_J1(qrR)/qrR : 0.5;
    double modulus = 2*M_PI*R*R*H*MathFunctions::Sinc(qzH_half)*J1_qrR_div_qrR;
    complex_t phase_factor = std::exp(complex_t(0.0, qzH_half));
    return phase_factor*modulus;
}

complex_t FormFactorCylinder::evaluate_for_complex_qz(kvector_t q, complex_t qz) const
{
    double R = mp_radius->getCurrent();
    double H = mp_height->getCurrent();
    double qrR = q.magxy()*R;
    complex_t qzH_half = qz*H/2.0;
    double J1_qrR_div_qrR = qrR > Numeric::double_epsilon ? MathFunctions::Bessel_J1(qrR)/qrR : 0.5;
    double radial_part = 2*M_PI*R*R*H*J1_qrR_div_qrR;
    complex_t z_part = MathFunctions::Sinc(qzH_half)*std::exp(complex_t(0.0, 1.0)*qzH_half);
    return radial_part*z_part;
}
