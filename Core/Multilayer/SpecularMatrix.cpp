// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularMatrix.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathFunctions.h"
#include "MultiLayer.h"
#include "MathConstants.h"
#include <Eigen/Dense>
#include <stdexcept>
#include <valarray>

namespace {
Eigen::Matrix2cd transitionMatrix(complex_t kzi, complex_t kzi1, double sigma, double thickness);
std::vector<ScalarRTCoefficients> computeTR(const MultiLayer& sample,
                                            const std::vector<complex_t>& kz);
bool zeroTransmission(const Eigen::Matrix2cd& m);

const complex_t imag_unit = complex_t(0.0, 1.0);
const double pi2_15 = std::pow(M_PI_2, 1.5);
}

std::vector<ScalarRTCoefficients> SpecularMatrix::execute(const MultiLayer& sample, kvector_t k)
{
    const size_t N = sample.numberOfLayers();
    const double n_ref = sample.layer(0)->material()->refractiveIndex(2 * M_PI / k.mag()).real();
    const double k_base_out = k.mag() * (k.z() > 0.0 ? -1 : 1);

    std::vector<complex_t> kz(N);
    // Calculate refraction angle, expressed as k_z, for each layer.
    complex_t rad = sample.layer(0)->scalarReducedPotential(k, n_ref);
    kz[0] = k_base_out * sqrt(rad);
    for (size_t i = 1; i < N; ++i) {
        rad = sample.layer(i)->scalarReducedPotential(k, n_ref);
        // use small absorptive component for layers with i>0 if radicand becomes very small:
        if (std::norm(rad) < 1e-40)
            rad = imag_unit * 1e-40;
        kz[i] = k_base_out * sqrt(rad);
    }

    return computeTR(sample, kz);
}

std::vector<ScalarRTCoefficients> SpecularMatrix::execute(const MultiLayer& sample,
                                                          const std::vector<complex_t>& kz)
{
    assert(sample.numberOfLayers() == kz.size());
    return computeTR(sample, kz);
}

namespace  {
Eigen::Matrix2cd transitionMatrix(complex_t kzi, complex_t kzi1, double sigma, double thickness)
{
    complex_t roughness = 1;
    if (sigma > 0.0) {
        const double sigeff = pi2_15 * sigma;
        roughness =
            std::sqrt(MathFunctions::tanhc(sigeff * kzi1) / MathFunctions::tanhc(sigeff * kzi));
    }
    const complex_t phase_shift = exp_I(kzi * thickness);
    const complex_t kz_r_by_rough = kzi / kzi1 / roughness;

    const complex_t a00 = 0.5 * (roughness + kz_r_by_rough);
    const complex_t a01 = 0.5 * (roughness - kz_r_by_rough);
    // a10 = a01, a11 = a00

    Eigen::Matrix2cd result;
    result << a00 * phase_shift, a01 / phase_shift, a01 * phase_shift, a00 / phase_shift;
    return result;
}

std::vector<ScalarRTCoefficients> computeTR(const MultiLayer& sample,
                                            const std::vector<complex_t>& kz)
{
    const size_t N = sample.numberOfLayers();
    std::vector<ScalarRTCoefficients> coeff(N);

    if (N == 1) { // If only one layer present, there's nothing left to calculate
        coeff[0].t_r = {1.0, 0.0};
        coeff[0].kz = kz[0];
        return coeff;
    } else if (kz[0] == 0.0) { // If kz in layer 0 is zero, R0 = -T0 and all others equal to 0
        coeff[0].t_r = {1.0, -1.0};
        for (size_t i = 1; i < N; ++i)
            coeff[i].t_r.setZero();
        return coeff;
    }

    std::valarray<Eigen::Vector2cd> m_tr_l({0, 0}, N);
    std::valarray<Eigen::Vector2cd> m_tr_r({0, 0}, N);
    Eigen::Matrix2cd acc = Eigen::Matrix2cd::Identity();

    complex_t kz_previous = kz[0];
    size_t im1 = 0;
    for (size_t i = im1 + 1; i < N && !zeroTransmission(acc); ++i, ++im1) {
        m_tr_l[im1] = acc.col(0);
        m_tr_r[im1] = acc.col(1);
        double sigma = 0.0;
        if (const LayerRoughness* roughness = sample.layerInterface(im1)->getRoughness())
            sigma = roughness->getSigma();
        const complex_t kz_cur = kz[i];
        acc = transitionMatrix(kz_previous, kz_cur, sigma, sample.layer(im1)->thickness()) * acc;

        kz_previous = kz_cur;
    }
    m_tr_l[im1] = acc.col(0);
    m_tr_r[im1] = acc.col(1);
    const complex_t r_0 = -m_tr_l[im1](1) / m_tr_r[im1](1);

    for (size_t i = 0, size = coeff.size(); i < size; ++i) {
        coeff[i].kz = kz[i];
        coeff[i].t_r = m_tr_l[i] + r_0 * m_tr_r[i];
    }
    return coeff;
}

bool zeroTransmission(const Eigen::Matrix2cd& m)
{
    const double norm = std::norm(m(1, 1));
    return std::norm(m.determinant()) < norm * norm * 1e-40;
}
}
