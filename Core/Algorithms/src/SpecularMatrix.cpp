// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SpecularMatrix.cpp
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
#include "Numeric.h"
#include "MathFunctions.h"

using std::sqrt;

namespace {
    const complex_t imag_unit = complex_t(0.0, 1.0);
}

// Computes refraction angles and transmission/reflection coefficients
// for given coherent wave propagation in a multilayer.
// k : length: wavenumber in vacuum, direction: defined in layer 0
// roughness is modelled by tanh profile (see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993) )

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t& k,
        MultiLayerCoeff_t& coeff)
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
        coeff[i].lambda = sqrt(sample.getLayer(i)->getRefractiveIndex2() - r2ref);
        if( std::abs(coeff[i].lambda)<1e-20) // UNTESTED FEATURE
            coeff[i].lambda = 0; // ensure uniform treatment of limiting case lambda->0
        coeff[i].kz = sign_kz_out * k.mag()*coeff[i].lambda;
    }

    // In the bottom layer, there is no upward travelling wave.
    coeff[N-1].t_r(0) = 1.0;
    coeff[N-1].t_r(1) = 0.0;

    // If only one layer present, there's nothing left to calculate
    if( N==1) return;

    // Calculate transmission/refraction coefficients t_r for each layer,
    // from bottom to top.
    for (int i=N-2; i>=0; --i) {
        if( coeff[i+1].lambda == 0.0 ) {
            // total reflection by layer with k_perp=0
            coeff[i].t_r(0) = +1;
            coeff[i].t_r(1) = -1;
            continue;
        }
        complex_t roughness_factor = 1;
        if (sample.getLayerInterface(i)->getRoughness()) {
            double sigma = sample.getLayerBottomInterface(i)->getRoughness()->getSigma();
            if(sigma > 0.0) {
                // since there is a roughness, compute one diagonal matrix element p00;
                // the other element is p11 = 1/p00.
                double sigeff = std::pow(Units::PID2, 1.5)*sigma*k.mag();
                roughness_factor = sqrt(
                            MathFunctions::tanhc(sigeff*coeff[i+1].lambda) /
                            MathFunctions::tanhc(sigeff*coeff[i  ].lambda) );
            }
        }

        complex_t lambda = coeff[i].lambda;
        if (lambda == 0.0) {
            if (i==0) {
                // standing vertical wave in top layer with k_perp=0
                coeff[i].t_r(0) = +1;
                coeff[i].t_r(1) = -1;
            }
            else {
                // no intensity in inner layer with k_perp=0
                coeff[i].t_r.setZero();
            }
            // no intensity in layers below
            for (size_t ii=i+1; ii<N; ++ii) {
                coeff[ii].t_r.setZero();
            }
            continue;
        }
        complex_t lambda_rough = coeff[i  ].lambda / roughness_factor;
        complex_t lambda_below = coeff[i+1].lambda * roughness_factor;
        complex_t ikd = imag_unit * k.mag() * sample.getLayer(i)->getThickness();
        coeff[i].t_r(0) = (
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda *
                    std::exp(-ikd*lambda);
        coeff[i].t_r(1) = (
                    (lambda_rough-lambda_below)*coeff[i+1].t_r(0) +
                    (lambda_rough+lambda_below)*coeff[i+1].t_r(1) )/2.0/lambda *
                    std::exp( ikd*lambda);
    }

    // Normalize to incoming downward travelling amplitude = 1.
    complex_t T0 = coeff[0].getScalarT();
    for (size_t i=0; i<N; ++i) {
        coeff[i].t_r = coeff[i].t_r/T0;
    }
}
