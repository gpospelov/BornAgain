// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularMatrix.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathFunctions.h"
#include "MultiLayer.h"
#include "MathConstants.h"
#include <stdexcept>

namespace {
    const complex_t imag_unit = complex_t(0.0, 1.0);
}

void setZeroBelow(SpecularMatrix::MultiLayerCoeff_t& coeff, size_t current_layer);

bool calculateUpFromLayer(SpecularMatrix::MultiLayerCoeff_t& coeff, const MultiLayer& sample,
                          const double kmag, size_t layer_index);

size_t bisectRTcomputation(SpecularMatrix::MultiLayerCoeff_t& coeff, const MultiLayer& sample,
                           const double kmag,
                           const size_t lgood, const size_t lbad, const size_t l);

//! Computes refraction angles and transmission/reflection coefficients
//! for given coherent wave propagation in a multilayer.
//! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
//! k : length: wavenumber in vacuum, direction: defined in layer 0.

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t k, MultiLayerCoeff_t& coeff)
{
    size_t N = sample.getNumberOfLayers();
    assert(N>0);
    assert(N-1 == sample.getNumberOfInterfaces());
    coeff.clear();
    coeff.resize(N);

    // Calculate refraction angle, expressed as lambda or k_z, for each layer.
    double sign_kz_out = k.z() > 0.0 ? -1.0 : 1.0;
    complex_t r2ref = sample.getLayer(0)->getRefractiveIndex2() * k.sin2Theta();
    for(size_t i=0; i<N; ++i) {
        complex_t rad = sample.getLayer(i)->getRefractiveIndex2() - r2ref;
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
    complex_t T0 = coeff[0].getScalarT();
    // This trick is used to avoid overflows in the intermediate steps of
    // complex division:
    double tmax = std::max(std::abs(T0.real()), std::abs(T0.imag()));
    for (size_t i=0; i<N; ++i) {
        coeff[i].t_r(0) /= tmax;
        coeff[i].t_r(1) /= tmax;
    }
    // Now the real normalization to T_0 proceeds
    T0 = coeff[0].getScalarT();
    for (size_t i=0; i<N; ++i) {
        coeff[i].t_r = coeff[i].t_r/T0;
    }
}

void setZeroBelow(SpecularMatrix::MultiLayerCoeff_t& coeff, size_t current_layer)
{
    size_t N = coeff.size();
    for (size_t i=current_layer+1; i<N; ++i) {
        coeff[i].t_r.setZero();
    }
}

bool calculateUpFromLayer(SpecularMatrix::MultiLayerCoeff_t& coeff, const MultiLayer& sample,
                          const double kmag, size_t layer_index)
{
    coeff[layer_index+1].t_r(0) = 1.0;
    coeff[layer_index+1].t_r(1) = 0.0;
    double kfactor = std::pow(M_PI_2, 1.5)*kmag;
    for (int i=layer_index; i>=0; --i) {
        complex_t roughness_factor = 1;
        if (sample.getLayerInterface(i)->getRoughness()) {
            double sigma = sample.getLayerBottomInterface(i)->getRoughness()->getSigma();
            if(sigma > 0.0) {
                // since there is a roughness, compute one diagonal matrix element p00;
                // the other element is p11 = 1/p00.
                double sigeff = kfactor*sigma;
                roughness_factor = sqrt(
                            MathFunctions::tanhc(sigeff*coeff[i+1].lambda) /
                            MathFunctions::tanhc(sigeff*coeff[i  ].lambda) );
            }
        }
        complex_t lambda = coeff[i].lambda;

        complex_t lambda_rough = coeff[i  ].lambda / roughness_factor;
        complex_t lambda_below = coeff[i+1].lambda * roughness_factor;
        complex_t exp_fac = exp_I(kmag * sample.getLayer(i)->getThickness() * lambda);
        coeff[i].t_r(0) = (
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda/exp_fac;
        coeff[i].t_r(1) = (
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda*exp_fac;
        // If T overflowed, return false, so the calculation can restart from a layer higher
        if (std::isinf(std::abs(coeff[i].getScalarT()))) {
            return false;
        }
    }
    return true;
}

size_t bisectRTcomputation(SpecularMatrix::MultiLayerCoeff_t& coeff, const MultiLayer& sample,
                           const double kmag,
                           const size_t lgood, const size_t lbad, const size_t l)
{
    if (calculateUpFromLayer(coeff, sample, kmag, l)) {
        // success => highest valid l must be in l..lbad-1
        if (l+1==lbad)
            return l;
        return bisectRTcomputation(coeff, sample, kmag, l, lbad, (l+lbad)/2);
    } else {
        // failure => highest valid l must be in lgood..l-1
        if (l-1==lgood)
            return l-1;
        return bisectRTcomputation(coeff, sample, kmag, lgood, l, (lgood+l)/2);
    }
}
