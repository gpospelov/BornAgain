// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file     Core/RT/MatrixRTCoefficients_v3.cpp
//! @brief    Implements class MatrixRTCoefficients_v3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/RT/MatrixRTCoefficients_v3.h"
#include "Core/Basics/Assert.h"
#include <iostream>

namespace
{
complex_t GetImExponential(complex_t exponent);
const auto eps = std::numeric_limits<double>::epsilon() * 10.;
} // namespace

MatrixRTCoefficients_v3::MatrixRTCoefficients_v3(double kz_sign, Eigen::Vector2cd eigenvalues,
                                                 kvector_t b, double magnetic_SLD)
    : m_kz_sign(kz_sign), m_lambda(std::move(eigenvalues)), m_b(std::move(b)),
      m_magnetic_SLD(magnetic_SLD)
{
    ASSERT(std::abs(m_b.mag() - 1) < eps || (m_b.mag() < eps && magnetic_SLD < eps));

    m_T << 1, 0, 0, 1;
    m_R << -1, 0, 0, -1;
}

MatrixRTCoefficients_v3::MatrixRTCoefficients_v3(const MatrixRTCoefficients_v3& other) = default;

MatrixRTCoefficients_v3::~MatrixRTCoefficients_v3() = default;

MatrixRTCoefficients_v3* MatrixRTCoefficients_v3::clone() const
{
    return new MatrixRTCoefficients_v3(*this);
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::TransformationMatrix(complex_t eigenvalue,
                                                               Eigen::Vector2d selection) const
{
    Eigen::Matrix2cd result;

    auto exp2 = Eigen::Matrix2cd(Eigen::DiagonalMatrix<complex_t, 2>(selection));

    if (std::abs(m_b.mag() - 1.) < eps) {
        Eigen::Matrix2cd Q;
        auto factor1 = 2. * (1. + m_b.z());
        Q << (1. + m_b.z()), (I * m_b.y() - m_b.x()), (m_b.x() + I * m_b.y()), (m_b.z() + 1.);
        result = Q * exp2 * Q.adjoint() / factor1;

    } else if (m_b.mag() < eps && eigenvalue != 0.)
        result = exp2;
    //        result = Eigen::Matrix2cd(Eigen::DiagonalMatrix<complex_t, 2>({0.5, 0.5}));
    else if (m_b.mag() < eps && eigenvalue == 0.)
        result = Eigen::Matrix2cd(Eigen::DiagonalMatrix<complex_t, 2>({0.5, 0.5}));
    else
        throw std::runtime_error("Broken magnetic field vector");

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::T1Matrix() const
{
    return TransformationMatrix(m_lambda(1), {0., 1.});
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::T2Matrix() const
{
    return TransformationMatrix(m_lambda(0), {1., 0.});
}

Eigen::Vector2cd MatrixRTCoefficients_v3::T1plus() const
{
    auto mat = T1Matrix();
    return mat * m_T.col(0);
    ;
}

Eigen::Vector2cd MatrixRTCoefficients_v3::R1plus() const
{
    auto mat = T1Matrix();
    return mat * m_R.col(0);
    ;
}

Eigen::Vector2cd MatrixRTCoefficients_v3::T2plus() const
{
    auto mat = T2Matrix();
    return mat * m_T.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::R2plus() const
{
    auto mat = T2Matrix();
    return mat * m_R.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::T1min() const
{
    auto mat = T1Matrix();
    return mat * m_T.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::R1min() const
{
    auto mat = T1Matrix();
    return mat * m_R.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::T2min() const
{
    auto mat = T2Matrix();
    return mat * m_T.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::R2min() const
{
    auto mat = T2Matrix();
    return mat * m_R.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients_v3::getKz() const
{
    return m_kz_sign * m_lambda;
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::pMatrixHelper(double sign) const
{
    const complex_t alpha = m_lambda(1) + m_lambda(0);
    const complex_t beta = m_lambda(1) - m_lambda(0);

    Eigen::Matrix2cd result;

    kvector_t b = m_b;

    result << alpha + sign * beta * b.z(), sign * beta * (b.x() - I * b.y()),
        sign * beta * (b.x() + I * b.y()), alpha - sign * beta * b.z();

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::computeP() const
{
    Eigen::Matrix2cd result = pMatrixHelper(1.);
    result *= 0.5;

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::computeInverseP() const
{
    const complex_t alpha = m_lambda(1) + m_lambda(0);
    const complex_t beta = m_lambda(1) - m_lambda(0);

    if (std::abs(alpha * alpha - beta * beta) < eps)
        throw std::runtime_error("Singular p_m");

    Eigen::Matrix2cd result = pMatrixHelper(-1.);
    result *= 2. / (alpha * alpha - beta * beta);

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients_v3::computeDeltaMatrix(double thickness)
{
    Eigen::Matrix2cd result;
    const auto alpha = 0.5 * thickness * (m_lambda(1) + m_lambda(0));

    const auto exp2 = Eigen::Matrix2cd(Eigen::DiagonalMatrix<complex_t, 2>(
        {GetImExponential(thickness * m_lambda(1)), GetImExponential(thickness * m_lambda(0))}));

    // Compute resulting phase matrix according to exp(i p_m d_m) = exp1 * Q * exp2 * Q.adjoint();
    if (std::abs(m_b.mag() - 1.) < eps) {
        Eigen::Matrix2cd Q;
        const double factor1 = 2. * (1. + m_b.z());
        Q << (1. + m_b.z()), (I * m_b.y() - m_b.x()), (m_b.x() + I * m_b.y()), (m_b.z() + 1.);

        result = Q * exp2 * Q.adjoint() / factor1;

    } else if (m_b.mag() < eps) {
        result = Eigen::Matrix2cd::Identity() * GetImExponential(alpha);

    } else
        throw std::runtime_error("Broken magnetic field vector");

    return result;
}

namespace
{
complex_t GetImExponential(complex_t exponent)
{
    if (exponent.imag() > -std::log(std::numeric_limits<double>::min()))
        return 0.0;
    return std::exp(I * exponent);
}
} // namespace
