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

bool calculateUpFromLayer(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const double kmag, size_t layer_index);
size_t bisectRTcomputation(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const double kmag, const size_t lgood, const size_t lbad, const size_t l);

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t k,
                             std::vector<ScalarRTCoefficients>& coeff)
{
    size_t N = sample.numberOfLayers();
    assert(N>0);
    assert(N-1 == sample.numberOfInterfaces());
    coeff.clear();
    coeff.resize(N);

    double n_ref = sample.layer(0)->material()->refractiveIndex(2 * M_PI / k.mag()).real();

    // Calculate refraction angle, expressed as lambda or k_z, for each layer.
    double sign_kz_out = k.z() > 0.0 ? -1.0 : 1.0;
    for(size_t i=0; i<N; ++i) {
        complex_t rad = sample.layer(i)->scalarReducedPotential(k, n_ref);
        // use small absorptive component for layers with i>0 if radicand becomes very small:
        if (i>0 && std::abs(rad)<1e-40) rad = imag_unit*1e-40;
        coeff[i].lambda = sqrt(rad);
        coeff[i].kz = sign_kz_out * k.mag()*coeff[i].lambda;
    }
    // If only one layer present, there's nothing left to calculate
    if( N==1) {
        coeff[N-1].t_r(0) = 1.0;
        coeff[N-1].t_r(1) = 0.0;
        return;
    }

    // If lambda in layer 0 is zero, R0 = -T0 and all other R, T coefficients become zero
    if (coeff[0].lambda == 0.0) {
        coeff[0].t_r(0) = 1.0;
        coeff[0].t_r(1) = -1.0;
        setZeroBelow(coeff, 0);
        return;
    }
    // Calculate transmission/refraction coefficients t_r for each layer, from bottom to top.
    size_t start_layer_index = N-2;
    if (!calculateUpFromLayer(coeff, sample, k.mag(), start_layer_index)) {
        // If excessive damping leads to infinite amplitudes, then use bisection to determine
        // the maximum number of layers for which results remain finite.
        start_layer_index = bisectRTcomputation(coeff, sample, k.mag(), 0, N-2, (N-2)/2);
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
    for (size_t i=0; i<N; ++i) {
        coeff[i].t_r = coeff[i].t_r/T0;
    }
}

void SpecularMatrix::execute_(const MultiLayer& sample, kvector_t k,
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

//! Computes RT coefficients coeff, starting from layer number layer_index.
//! Returns true if no overflow happens.

bool calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
                          const double kmag, size_t layer_index)
{
    coeff[layer_index+1].t_r(0) = 1.0;
    coeff[layer_index+1].t_r(1) = 0.0;
    double kfactor = std::pow(M_PI_2, 1.5)*kmag;
    for (size_t j=0; j<=layer_index; ++j) {
        size_t i = layer_index - j;  // start from bottom
        complex_t roughness_factor = 1;
        if (sample.layerInterface(i)->getRoughness()) {
            double sigma = sample.layerBottomInterface(i)->getRoughness()->getSigma();
            if(sigma > 0.0) {
                // since there is a roughness, compute one diagonal matrix element p00;
                // the other non-zero element is p11 = 1/p00.
                double sigeff = kfactor*sigma;
                roughness_factor = sqrt(
                            MathFunctions::tanhc(sigeff*coeff[i+1].lambda) /
                            MathFunctions::tanhc(sigeff*coeff[i  ].lambda) );
            }
        }
        complex_t lambda = coeff[i].lambda;

        complex_t lambda_rough = coeff[i  ].lambda / roughness_factor;
        complex_t lambda_below = coeff[i+1].lambda * roughness_factor;
        complex_t exp_fac = exp_I(kmag * sample.layer(i)->thickness() * lambda);
        coeff[i].t_r(0) = (
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda/exp_fac;
        coeff[i].t_r(1) = (
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda*exp_fac;
        if (std::isinf(abs(coeff[i].t_r(0))))
            return false; // overflow => retry calulation starting from a higher layer
    }
    return true; // no overflow => result is definitive
}

//! Recursive bisection to determine the number of the deepest layer where RT computation
//! can be started without running into overflow.
//! Computes coeff, and returns largest possible start layer index.

size_t bisectRTcomputation(
    std::vector<ScalarRTCoefficients>& coeff, const MultiLayer& sample,
    const double kmag, const size_t lgood, const size_t lbad, const size_t l)
{
    if (calculateUpFromLayer(coeff, sample, kmag, l)) {
        // success => highest valid l must be in l..lbad-1
        if (l+1==lbad)
            return l;
        return bisectRTcomputation(coeff, sample, kmag, l, lbad, (l+lbad)/2);
    } else {
        // failure => highest valid l must be in lgood..l-1
        if (l-1==lgood) {
            if (!calculateUpFromLayer(coeff, sample, kmag, l-1))
                throw std::runtime_error(
                    "Bisection failed: Unexpected non-monotonicity in RT computation");
            return l-1;
        }
        return bisectRTcomputation(coeff, sample, kmag, lgood, l, (lgood+l)/2);
    }
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
