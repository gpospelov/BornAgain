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
#include "KzComputation.h"
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
Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                                  const Eigen::Vector2cd& t_r1);
std::vector<ScalarRTCoefficients> computeTR(const MultiLayer& sample,
                                            const std::vector<complex_t>& kz);
void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer);
bool calculateUpFromLayer(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const std::vector<complex_t>& kz, size_t layer_index);
size_t bisectRTcomputation(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const std::vector<complex_t> &kz, const size_t lgood, const size_t lbad, const size_t l);

const double pi2_15 = std::pow(M_PI_2, 1.5);
}

std::vector<ScalarRTCoefficients> SpecularMatrix::execute(const MultiLayer& sample, kvector_t k)
{
    std::vector<complex_t> kz = KzComputation::computeReducedKz(sample, k);
    return computeTR(sample, kz);
}

std::vector<ScalarRTCoefficients> SpecularMatrix::execute(const MultiLayer& sample,
                                                          const std::vector<complex_t>& kz)
{
    assert(sample.numberOfLayers() == kz.size());
    return computeTR(sample, kz);
}

namespace {
std::vector<ScalarRTCoefficients> computeTR(const MultiLayer& sample,
                                            const std::vector<complex_t>& kz)
{
    const size_t N = sample.numberOfLayers();
    std::vector<ScalarRTCoefficients> coeff(N);

    for (size_t i = 0; i < N; ++i)
        coeff[i].kz = kz[i];

    if (N == 1) { // If only one layer present, there's nothing left to calculate
        coeff[0].t_r = {1.0, 0.0};
        return coeff;
    } else if (kz[0] == 0.0) { // If kz in layer 0 is zero, R0 = -T0 and all others equal to 0
        coeff[0].t_r = {1.0, -1.0};
        for (size_t i = 1; i < N; ++i)
            coeff[i].t_r.setZero();
        return coeff;
    }

    // Calculate transmission/refraction coefficients t_r for each layer, from bottom to top.
    size_t start_layer_index = N-2;
    if (!calculateUpFromLayer(coeff, sample, kz, start_layer_index)) {
        // If excessive damping leads to infinite amplitudes, then use bisection to determine
        // the maximum number of layers for which results remain finite.
        start_layer_index = bisectRTcomputation(coeff, sample, kz, 0, N-2, (N-2)/2);
    }
    setZeroBelow(coeff, start_layer_index+1);

    // Normalize to incoming downward travelling amplitude = 1.
    complex_t T0 = coeff[0].t_r(0);
    // This trick is used to avoid overflows in the intermediate steps of
    // complex division:
    double tmax = std::max(std::abs(T0.real()), std::abs(T0.imag()));
    if (std::isinf(tmax))
        throw std::runtime_error("Unexpected tmax=infty");
    for (size_t i=0; i<N; ++i) {
        coeff[i].t_r(0) /= tmax;
        coeff[i].t_r(1) /= tmax;
    }

    // Now the real normalization to T_0 proceeds
    T0 = coeff[0].t_r(0);
    if (std::isinf(abs(T0)))
        throw std::runtime_error("Unexpected tmax=infty");
    for (size_t i=0; i<N; ++i)
        coeff[i].t_r = coeff[i].t_r/T0;

    return coeff;
}
}

namespace {
//! Recursive bisection to determine the number of the deepest layer where RT computation
//! can be started without running into overflow.
//! Computes coeff, and returns largest possible start layer index.
size_t bisectRTcomputation(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const std::vector<complex_t> &kz, const size_t lgood, const size_t lbad, const size_t l)
{
    if (calculateUpFromLayer(coeff, sample, kz, l)) {
        // success => highest valid l must be in l..lbad-1
        if (l+1==lbad)
            return l;
        return bisectRTcomputation(coeff, sample, kz, l, lbad, (l+lbad)/2);
    } else {
        // failure => highest valid l must be in lgood..l-1
        if (l-1==lgood) {
            if (!calculateUpFromLayer(coeff, sample, kz, l-1))
                throw std::runtime_error(
                    "Bisection failed: Unexpected non-monotonicity in RT computation");
            return l-1;
        }
        return bisectRTcomputation(coeff, sample, kz, lgood, l, (lgood+l)/2);
    }
}

//! Computes RT coefficients coeff, starting from layer number layer_index.
//! Returns true if no overflow happens.
bool calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
                          const std::vector<complex_t> &kz, size_t layer_index)
{
    coeff[layer_index+1].t_r(0) = 1.0;
    coeff[layer_index+1].t_r(1) = 0.0;
    for (size_t j=0; j<=layer_index; ++j) {
        size_t i = layer_index - j;  // start from bottom
        double sigma = 0.0;
        if (const auto roughness = sample.layerBottomInterface(i)->getRoughness())
            sigma = roughness->getSigma();

        coeff[i].t_r =
            transition(kz[i], kz[i + 1], sigma, sample.layer(i)->thickness(), coeff[i + 1].t_r);
        if (std::isinf(std::norm(coeff[i].t_r(0))))
            return false; // overflow => retry calulation starting from a higher layer
    }
    return true; // no overflow => result is definitive
}

Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                            const Eigen::Vector2cd& t_r1)
{
    complex_t roughness = 1;
    if (sigma > 0.0) {
        const double sigeff = pi2_15 * sigma;
        roughness =
            std::sqrt(MathFunctions::tanhc(sigeff * kzi1) / MathFunctions::tanhc(sigeff * kzi));
    }
    const complex_t inv_roughness = 1.0 / roughness;
    const complex_t phase_shift = exp_I(kzi * thickness);
    const complex_t kz_ratio = kzi1 / kzi * roughness;

    const complex_t a00 = 0.5 * (inv_roughness + kz_ratio);
    const complex_t a01 = 0.5 * (inv_roughness - kz_ratio);

    Eigen::Vector2cd result;
    result << (a00 * t_r1(0) + a01 * t_r1(1)) / phase_shift,
              (a01 * t_r1(0) + a00 * t_r1(1)) * phase_shift;
    return result;
}

void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer)
{
    size_t N = coeff.size();
    for (size_t i = current_layer + 1; i < N; ++i) {
        coeff[i].t_r.setZero();
    }
}
}
