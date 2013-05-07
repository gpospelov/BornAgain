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

    calculateTransferAndBoundary(sample, k, coeff);
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

void SpecularMatrix::calculateTransferAndBoundary(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    // Last layer boundary ensures no reflection
    coeff[N-1].phi_psi(0) = -coeff[N-1].lambda;
    coeff[N-1].phi_psi(1) = 1.0;
    coeff[N-1].l.setIdentity();
    for(size_t i=N-2; i>0; --i) {
        complex_t lambda = coeff[i].lambda;
        complex_t kdlambda = k.mag()*sample.getLayer(i)->getThickness()*lambda;
        complex_t cosine_term = std::cos(kdlambda);
        complex_t sine_term =
                ( std::abs(kdlambda) < Numeric::double_epsilon ) ?
                k.mag()*sample.getLayer(i)->getThickness() :
                std::sin(kdlambda)/lambda;
        coeff[i].l(0,0) = cosine_term;
        coeff[i].l(0,1) = complex_t(0.0, 1.0)*lambda*lambda*sine_term;
        coeff[i].l(1,0) = complex_t(0.0, 1.0)*sine_term;
        coeff[i].l(1,1) = cosine_term;
        coeff[i].phi_psi = coeff[i].l * coeff[i+1].phi_psi;
    }
    // First layer boundary is also top layer boundary:
    coeff[0].l.setIdentity();
    coeff[0].phi_psi = coeff[1].phi_psi;
    // Normalize all boundary values with top layer transmitted wave:
    complex_t T0 = coeff[0].T();
    for (size_t i=0; i<N; ++i) {
        coeff[i].phi_psi = coeff[i].phi_psi/T0;
    }
}
