#include "FormFactorFullSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"

#include <cmath>

FormFactorFullSphere::FormFactorFullSphere(double radius)
{
    mp_radius = new StochasticDiracDelta<double>(radius);
}

FormFactorFullSphere::FormFactorFullSphere(StochasticParameter<double> *p_radius)
    : mp_radius(p_radius)
{
}

FormFactorFullSphere::~FormFactorFullSphere()
{
    delete mp_radius;
}

FormFactorFullSphere* FormFactorFullSphere::clone() const
{
    return new FormFactorFullSphere(mp_radius->clone());
}

complex_t FormFactorFullSphere::evaluate_for_complex_qz(kvector_t q, complex_t qz) const
{
    double R = mp_radius->getCurrent();

    complex_t qzR = complex_t(0.0, 1.0)*qz*R;
    complex_t z_part = std::exp(qzR);

    double qR = std::sqrt( q.x()*q.x()+q.y()*q.y()+std::abs(qz)*std::abs(qz) )*R;
    double volume = 4*M_PI*R*R*R/3;
    double radial;
    if (qR < Numeric::double_epsilon) {
        radial = volume;
    }
    else {
        radial = 3*volume*(std::sin(qR) - qR*std::cos(qR))/(qR*qR*qR);
    }

    return radial*z_part;
}
