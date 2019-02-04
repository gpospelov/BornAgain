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
void computeTR(std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample);
bool zeroTransmission(const Eigen::Matrix2cd& m);
void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer);

const complex_t imag_unit = complex_t(0.0, 1.0);
const double pi2_15 = std::pow(M_PI_2, 1.5);
}

void SpecularMatrix::execute(const MultiLayer& sample, kvector_t k,
                             std::vector<ScalarRTCoefficients>& coeff)
{
    size_t N = sample.numberOfLayers();
    coeff.clear();
    coeff.resize(N);

    double n_ref = sample.layer(0)->material()->refractiveIndex(2 * M_PI / k.mag()).real();

    // Calculate refraction angle, expressed as lambda or k_z, for each layer.
    double sign_kz_out = k.z() > 0.0 ? -1.0 : 1.0;
    for (size_t i = 0; i < N; ++i) {
        complex_t rad = sample.layer(i)->scalarReducedPotential(k, n_ref);
        // use small absorptive component for layers with i>0 if radicand becomes very small:
        if (i > 0 && std::norm(rad) < 1e-40)
            rad = imag_unit * 1e-40;
        coeff[i].lambda = sqrt(rad);
        coeff[i].kz = sign_kz_out * k.mag() * coeff[i].lambda;
    }

    coeff[0].t_r(0) = 1.0;
    coeff[0].t_r(1) = 0.0;

    if (N == 1) // If only one layer present, there's nothing left to calculate
        return;
    else if (coeff[0].kz == 0.0) { // If kz in layer 0 is zero, R0 = -T0 and all others equal to 0
        coeff[0].t_r(1) = -1.0;
        setZeroBelow(coeff, 0);
        return;
    }

    // Calculate transmission/refraction coefficients t_r for each layer, from top to bottom.
    computeTR(coeff, sample);
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

void computeTR(std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample)
{
    const size_t coeff_size = coeff.size();
    std::valarray<Eigen::Vector2cd> m_tr_l({0, 0}, coeff_size);
    std::valarray<Eigen::Vector2cd> m_tr_r({0, 0}, coeff_size);
    Eigen::Matrix2cd acc = Eigen::Matrix2cd::Identity();
    m_tr_l[0] = {1, 0};
    m_tr_r[0] = {0, 1};

    complex_t kz_previous = coeff[0].getScalarKz();
    size_t i = 1;
    for (; i < coeff_size; ++i) {
        const size_t im1 = i - 1;
        double sigma = 0.0;
        if (const LayerRoughness* roughness = sample.layerInterface(im1)->getRoughness())
            sigma = roughness->getSigma();
        const complex_t kz = coeff[i].getScalarKz();
        acc = transitionMatrix(kz_previous, kz, sigma, sample.layer(im1)->thickness()) * acc;
        if (zeroTransmission(acc))
            break;

        kz_previous = kz;
        m_tr_l[i] = acc.col(0);
        m_tr_r[i] = acc.col(1);
    }
    const complex_t r_0 = -m_tr_l[i - 1](1) / m_tr_r[i - 1](1);

    for (size_t i = 0, size = coeff.size(); i < size; ++i)
        coeff[i].t_r = m_tr_l[i] + r_0 * m_tr_r[i];
}

bool zeroTransmission(const Eigen::Matrix2cd& m)
{
    const double norm = std::norm(m(1, 1));
    return std::norm(m.determinant()) < norm * norm * 1e-40;
}

void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer)
{
    size_t N = coeff.size();
    for (size_t i = current_layer + 1; i < N; ++i) {
        coeff[i].t_r.setZero();
    }
}
}
