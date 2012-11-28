#include "IFormFactorBorn.h"

IFormFactorBorn::IFormFactorBorn()
: m_use_large_bin_approximation_radial(false)
, m_use_large_bin_approximation_z(false)
, m_bin_qy(0.0)
, m_bin_qz(0.0)
{
}

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

double IFormFactorBorn::bigRadialPart(const cvector_t& q) const
{
    // radial part
    double qR = std::abs(q.magxy()*getRadius());

    // radial parameters
    double effective_bin_size_r = m_bin_qy*getRadius();
    double qRmin = qR - effective_bin_size_r/2.0;
    double qRmax = qR + effective_bin_size_r/2.0;

    // modulus of the radial part
    MemberFunctionIntegrator<IFormFactorBorn>::mem_function p_mf = &IFormFactorBorn::bigRadialIntegrand;
    MemberFunctionIntegrator<IFormFactorBorn> integrator(p_mf, this);
    double average_intensity = integrator.integrate(qRmin, qRmax, (void*)0)/effective_bin_size_r;
    return std::sqrt(average_intensity);
}

complex_t IFormFactorBorn::bigZPart(const cvector_t& q) const
{
    // bin sizes in qz-direction times the height
    complex_t qH2_c = q.z()*getHeight()/2.0;
    double qH2 = std::abs(qH2_c);
    double effective_bin_size_h2 = m_bin_qz*getHeight()/2.0; // qH2 is only half qz*H !
    double qH2min = qH2 - effective_bin_size_h2/2.0;
    double qH2max = qH2 + effective_bin_size_h2/2.0;

    // phase from the height of the particle
    complex_t z_phase = std::exp(complex_t(0.0, 1.0)*qH2_c);

    // modulus of the height of the particle
    double z_average_intensity = (bigZPartIntegral(qH2max) - bigZPartIntegral(qH2min))/effective_bin_size_h2;
    double z_modulus = std::sqrt(z_average_intensity);

    return z_phase*z_modulus;
}

double IFormFactorBorn::bigRadialIntegrand(double qR, void* params) const
{
    (void)params;
    static double a = 1.0;
    static double b = std::sqrt(M_PI/3.0/std::sqrt(3.0));

    return a/(1.0 + std::pow(std::abs(b*qR),3.0));
}

double IFormFactorBorn::bigZPartIntegral(double qH2) const
{
    if (qH2<Numeric::double_epsilon) return qH2;
    double qH = 2.0*qH2;
    return (qH*MathFunctions::Si(qH) + std::cos(qH) - 1.0)/qH;
}
