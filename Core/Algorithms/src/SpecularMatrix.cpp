// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "SpecularMatrix.h"

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t& k,
        MultiLayerCoeff_t& coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());

    calculateEigenvalues(sample, k, coeff);

    calculateTransferMatrices(sample, k, coeff);

    calculateBoundaryValues(coeff);
}

void SpecularMatrix::calculateEigenvalues(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    double sinalpha = std::abs( k.cosTheta() );
    double cosalpha2 = 1.0 - sinalpha*sinalpha;
    complex_t rindex0 = sample.getLayer(0)->getRefractiveIndex();
    complex_t r2cosalpha2 = rindex0*rindex0*cosalpha2;
    for(size_t i=0; i<coeff.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        coeff[i].lambda = std::sqrt(rindex*rindex - r2cosalpha2)/sinalpha;
    }
}

void SpecularMatrix::calculateTransferMatrices(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    double ksinalpha = k.mag()*std::abs( k.cosTheta() );
    // Layer 0 gets identity matrix:
    coeff[0].l11 = complex_t(1.0, 0.0);
    coeff[0].l12 = complex_t(0.0, 0.0);
    coeff[0].l21 = complex_t(0.0, 0.0);
    coeff[0].l22 = complex_t(1.0, 0.0);
    coeff.L11 = complex_t(1.0, 0.0);
    coeff.L12 = complex_t(0.0, 0.0);
    coeff.L21 = complex_t(0.0, 0.0);
    coeff.L22 = complex_t(1.0, 0.0);
    for(size_t i=1; i<coeff.size()-1; ++i) {
        complex_t lambda = coeff[i].lambda;
        complex_t coskdsinlambda = std::cos(ksinalpha*sample.getLayer(i)->getThickness()*lambda);
        complex_t sinkdsinlambda = std::sin(ksinalpha*sample.getLayer(i)->getThickness()*lambda);
        coeff[i].l11 = coskdsinlambda;
        coeff[i].l12 = -complex_t(0.0, 1.0)*lambda*sinkdsinlambda;
        coeff[i].l21 = -complex_t(0.0, 1.0)*sinkdsinlambda/lambda;
        coeff[i].l22 = coskdsinlambda;
        complex_t ltemp11 = coeff[i].l11*coeff.L11 + coeff[i].l12*coeff.L21;
        complex_t ltemp12 = coeff[i].l11*coeff.L12 + coeff[i].l12*coeff.L22;
        complex_t ltemp21 = coeff[i].l21*coeff.L11 + coeff[i].l22*coeff.L21;
        complex_t ltemp22 = coeff[i].l21*coeff.L12 + coeff[i].l22*coeff.L22;
        coeff.L11 = ltemp11;
        coeff.L12 = ltemp12;
        coeff.L21 = ltemp21;
        coeff.L22 = ltemp22;
    }
    // Last layer also gets identity matrix:
    size_t N = coeff.size();
    coeff[N-1].l11 = complex_t(1.0, 0.0);
    coeff[N-1].l12 = complex_t(0.0, 0.0);
    coeff[N-1].l21 = complex_t(0.0, 0.0);
    coeff[N-1].l22 = complex_t(1.0, 0.0);
}

void SpecularMatrix::calculateBoundaryValues(MultiLayerCoeff_t& coeff) const
{
    complex_t lambda0 = coeff[0].lambda;
    size_t N = coeff.size();
    complex_t lambdaN = coeff[N-1].lambda;
    complex_t denominator = (lambda0*coeff.L11 + coeff.L12 + lambdaN*(lambda0*coeff.L21 + coeff.L22));
    coeff.R = (lambda0*coeff.L11 - coeff.L12 + lambdaN*(lambda0*coeff.L21 - coeff.L22))/denominator;
    // Boundary values at bottom of top layer
    // and top of first layer:
    coeff[1].phi = coeff[0].phi = lambda0*(coeff.R - 1.0);
    coeff[1].psi = coeff[0].psi = coeff.R + 1.0;
    for(size_t i=2; i<coeff.size(); ++i) {
        coeff[i].phi = coeff[i-1].l11*coeff[i-1].phi + coeff[i-1].l12*coeff[i-1].psi;
        coeff[i].psi = coeff[i-1].l21*coeff[i-1].phi + coeff[i-1].l22*coeff[i-1].psi;
    }
}
