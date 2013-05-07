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
        coeff[i].lambda = std::sqrt(rindex*rindex - r2cosalpha2);
    }
}

void SpecularMatrix::calculateTransferMatrices(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    // Layer 0 gets identity matrix:
    coeff[0].l.setIdentity();
    coeff.L.setIdentity();
    for(size_t i=1; i<coeff.size()-1; ++i) {
        complex_t lambda = coeff[i].lambda;
        complex_t kdlambda = k.mag()*sample.getLayer(i)->getThickness()*lambda;
        complex_t cosine_term = std::cos(kdlambda);
        complex_t sine_term =
                ( std::abs(kdlambda) < Numeric::double_epsilon ) ?
                k.mag()*sample.getLayer(i)->getThickness() :
                std::sin(kdlambda)/lambda;
        coeff[i].l(0,0) = cosine_term;
        coeff[i].l(0,1) = -complex_t(0.0, 1.0)*lambda*lambda*sine_term;
        coeff[i].l(1,0) = -complex_t(0.0, 1.0)*sine_term;
        coeff[i].l(1,1) = cosine_term;
        coeff.L = coeff[i].l * coeff.L;
    }
    // Last layer also gets identity matrix:
    size_t N = coeff.size();
    coeff[N-1].l.setIdentity();
}

void SpecularMatrix::calculateBoundaryValues(MultiLayerCoeff_t& coeff) const
{
    complex_t lambda0 = coeff[0].lambda;
    size_t N = coeff.size();
    complex_t lambdaN = coeff[N-1].lambda;
    complex_t denominator = (lambda0*coeff.L(0,0) + coeff.L(0,1) + lambdaN*(lambda0*coeff.L(1,0) + coeff.L(1,1)));
    coeff.R = (lambda0*coeff.L(0,0) - coeff.L(0,1) + lambdaN*(lambda0*coeff.L(1,0) - coeff.L(1,1)))/denominator;
    // Boundary values at bottom of top layer
    // and top of first layer:
    coeff[1].phi_psi(0) = coeff[0].phi_psi(0) = lambda0*(coeff.R - 1.0);
    coeff[1].phi_psi(1) = coeff[0].phi_psi(1) = coeff.R + 1.0;
    for(size_t i=2; i<coeff.size(); ++i) {
        coeff[i].phi_psi = coeff[i-1].l*coeff[i-1].phi_psi;
    }
}
