// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/IFormFactorBorn.cpp
//! @brief     Implements interface class IFormFactorBorn.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFormFactorBorn.h"
#include "MemberFunctionIntegrator.h"
#include "MathFunctions.h"

complex_t IFormFactorBorn::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    (void)alpha_f_bin;
    Bin1DCVector q_bin(k_i - k_f_bin.m_q_lower, k_i - k_f_bin.m_q_upper);
    if (useLargeBinApproximation(q_bin)) {
        return getVolume()*bigZPart(q_bin)*bigRadialPart(q_bin);
    }
    return evaluate_for_q(q_bin.getMidPoint());
}

Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    (void)k_f2_bin;
    (void)alpha_i;
    (void)phi_f_bin;
    Eigen::Matrix2cd unit_matrix = Eigen::Matrix2cd::Identity();
    return evaluate(k_i, k_f1_bin, alpha_f_bin) * unit_matrix;
}

double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}

double IFormFactorBorn::bigRadialPart(const Bin1DCVector& q_bin) const
{
    // modulus of the radial part
    MemberFunctionIntegrator<IFormFactorBorn>::mem_function p_mf =
       & IFormFactorBorn::bigRadialIntegrand;
    MemberFunctionIntegrator<IFormFactorBorn> integrator(p_mf, this);
    double average_intensity = integrator.integrate(0.0, 1.0, (void*)(&q_bin));
    return std::sqrt(average_intensity);
}

complex_t IFormFactorBorn::bigZPart(const Bin1DCVector& q_bin) const
{
    // bin sizes in qz-direction times the height
    complex_t qH2_c = q_bin.getMidPoint().z()*getHeight()/2.0;
    double qH2min = std::abs( q_bin.m_q_lower.z() )*getHeight()/2.0;
    double qH2max = std::abs( q_bin.m_q_upper.z() )*getHeight()/2.0;
    if (qH2min > qH2max) {
        std::swap(qH2min, qH2max);
    }
    double effective_bin_size_h2 = std::abs(qH2max - qH2min);

    // phase from the height of the particle
    complex_t z_phase = std::exp(complex_t(0.0, 1.0)*qH2_c);

    // modulus of the height of the particle
    assert(effective_bin_size_h2);
    double z_average_intensity =
        (bigZPartIntegral(qH2max) - bigZPartIntegral(qH2min)) /
        effective_bin_size_h2;
    assert(z_average_intensity);
    double z_modulus = std::sqrt(z_average_intensity);

    return z_phase*z_modulus;
}

bool IFormFactorBorn::useLargeBinApproximation(const Bin1DCVector& q_bin) const
{
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if (delta_qr == 0 || delta_qz == 0)
        return false;
    if ( delta_qr > M_PI/2/getRadius() )
        return true;
    if ( delta_qz > M_PI/2/getHeight() )
        return true;
    return false;
}

double IFormFactorBorn::bigRadialIntegrand(double t, void* params) const
{
    const Bin1DCVector *p_q_bin = static_cast<const Bin1DCVector*>(params);
    double qR = std::abs( (p_q_bin->m_q_lower +
                           t*p_q_bin->getDelta()).magxy() )*getRadius();
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


