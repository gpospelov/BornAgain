// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/IFormFactorBorn.cpp
//! @brief     Implements interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFormFactorBorn.h"
#include "MemberFunctionIntegrator.h"
#include "MathFunctions.h"

complex_t IFormFactorBorn::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    (void)alpha_f_bin;
    Bin1DCVector q_bin(k_i - k_f_bin.m_q_lower, k_i - k_f_bin.m_q_upper);
    return evaluate_for_q(q_bin.getMidPoint());
}

Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin, const Bin1D &phi_f_bin) const
{
    (void)phi_f_bin;
    Eigen::Matrix2cd unit_matrix = Eigen::Matrix2cd::Identity();
    return evaluate(k_i, k_f_bin, alpha_f_bin) * unit_matrix;
}

double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}

double IFormFactorBorn::bigRadialPart(const Bin1DCVector& q_bin) const
{
    // the analytical average intensity for a circle form factor
    double qpar_max = q_bin.m_q_upper.magxy().real();
    double qpar_min = q_bin.m_q_lower.magxy().real();
    double R = getRadius();
    double J0max = MathFunctions::Bessel_J0(qpar_max*R);
    double J0min = MathFunctions::Bessel_J0(qpar_min*R);
    double J1max = MathFunctions::Bessel_J1(qpar_max*R);
    double J1min = MathFunctions::Bessel_J1(qpar_min*R);
    double intensity_tot = -2.0*(J0max*J0max + J1max*J1max
            - J0min*J0min - J1min*J1min);
    double radial_size = R*R*(qpar_max*qpar_max - qpar_min*qpar_min)/2.0;

    return std::sqrt(intensity_tot/radial_size);
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
    double z_modulus = std::sqrt(z_average_intensity);

    return z_phase*z_modulus;
}

bool IFormFactorBorn::useLargeBinApproximation(const Bin1DCVector& q_bin) const
{
    double delta_qr = std::abs( q_bin.getDelta().magxy() );
    double delta_qz = std::abs( q_bin.getDelta().z() );
    if (delta_qr == 0 || delta_qz == 0)
        return false;
    if ( delta_qr > Units::PID2/getRadius() )
        return true;
    if ( delta_qz > Units::PID2/getHeight() )
        return true;
    return false;
}

bool IFormFactorBorn::check_initialization() const
{
    return true;
}

double IFormFactorBorn::bigZPartIntegral(double qH2) const
{
    if (qH2<Numeric::double_epsilon) return qH2;
    double qH = 2.0*qH2;
    return MathFunctions::Si(qH) - std::sin(qH2)*std::sin(qH2)/qH2;
}


