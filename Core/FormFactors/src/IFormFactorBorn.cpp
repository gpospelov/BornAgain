#include "IFormFactorBorn.h"

void IFormFactorBorn::setBinSizes(double delta_qy, double delta_qz)
{
    m_bin_qy = delta_qy;
    m_bin_qz = delta_qz;
    if (m_bin_qy > M_PI/2.0/getRadius()) {
        m_use_large_bin_approximation_radial = true;
    }
    else {
        m_use_large_bin_approximation_radial = false;
    }
    if (m_bin_qz > M_PI/2.0/getHeight()) {
        m_use_large_bin_approximation_z = true;
    }
    else {
        m_use_large_bin_approximation_z = false;
    }
}

double IFormFactorBorn::bigRadialPart(double qR, void *params) const
{
    (void)params;
    static double a = 1.0;
    static double b = std::sqrt(M_PI/3.0/std::sqrt(3.0));

    return a/(1.0 + std::pow(std::abs(b*qR),3.0));
}

IFormFactorBorn::IFormFactorBorn()
: m_use_large_bin_approximation_radial(false)
, m_use_large_bin_approximation_z(false)
, m_bin_qy(0.0)
, m_bin_qz(0.0)
{
}

double IFormFactorBorn::bigZPart(double qH2) const
{
    if (qH2<Numeric::double_epsilon) return qH2;
    double qH = 2.0*qH2;
    return (qH*MathFunctions::Si(qH) + std::cos(qH) - 1.0)/qH;
}
