// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/OpticalFresnel.cpp
//! @brief     Implements class OpticalFresnel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include <algorithm>
#include "OpticalFresnel.h"
#include "Numeric.h"
#include <cassert>

void OpticalFresnel::execute(const MultiLayer& sample, const kvector_t& kvec,
                             MultiLayerCoeff_t& coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());

    calculateKZ(sample, kvec, coeff);

    // check if there is a roughness
    for (size_t i=0; i<sample.getNumberOfInterfaces(); ++i) {
        if(sample.getLayerInterface(i)->getRoughness() ) {
            m_use_roughness = true;
            break;
        }
    }

    calculateFresnelCoefficients(sample, coeff);

    calculateX(sample, coeff);
    calculateRT(sample, coeff);

#ifdef DEBUG_FPE
    // checking coeff
    for(size_t i=0; i<coeff.size(); ++i) {
        assert(!std::isnan(coeff[i].kz.real()));
        assert(!std::isinf(coeff[i].kz.real()));
        assert(!std::isnan(coeff[i].kz.imag()));
        assert(!std::isinf(coeff[i].kz.imag()));
        //
        assert(!std::isnan(coeff[i].R.real()));
        assert(!std::isinf(coeff[i].R.real()));
        assert(!std::isnan(coeff[i].R.imag()));
        assert(!std::isinf(coeff[i].R.imag()));
        //
        assert(!std::isnan(coeff[i].T.real()));
        assert(!std::isinf(coeff[i].T.real()));
        assert(!std::isnan(coeff[i].T.imag()));
        assert(!std::isinf(coeff[i].T.imag()));
    }
#endif

}

void OpticalFresnel::calculateKZ(const MultiLayer& sample, const kvector_t& kvec, MultiLayerCoeff_t& coeff) const
{
    // z-component of reflected wave vector inside each layer
    // k is the vacuum wave number
    // Q_{z,j}& = 2k_{z,j} = 2\cdot \sqrt{ k^2 n_j^2 - k_x^2 n_0^2 }
    // top layer refractive index:
    complex_t rindex0 = sample.getLayer(0)->getRefractiveIndex();
    complex_t rindex0_squared = rindex0*rindex0;
    for(size_t i=0; i<coeff.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        coeff[i].kz = std::sqrt( kvec.mag2()*rindex*rindex - kvec.magxy2()*rindex0_squared );
    }
}

void OpticalFresnel::calculateFresnelCoefficients(const MultiLayer& sample, MultiLayerCoeff_t& coeff) const
{
    static const double picoeff = std::pow(M_PI/2., 1.5);

    // calculation of reflection/transmission Fresnel coefficients
    for(size_t i=0; i<coeff.size() - 1; i++) {
        complex_t kzi = coeff[i].kz;
        complex_t kziplus1 = coeff[i+1].kz;
        if (kzi == complex_t(0, 0) && kziplus1 == complex_t(0, 0)) {
            coeff[i].r = complex_t(0, 0);
            coeff[i].t = complex_t(1, 0);
            coeff[i].rb = complex_t(0, 0);
            coeff[i].tb = complex_t(1, 0);
        } else {
            double sigma = 0.0;
            if (sample.getLayerBottomInterface(i)->getRoughness()) {
                sigma = sample.getLayerBottomInterface(i)->getRoughness()->getSigma();
            }
            if(sigma == 0.0) {
                coeff[i].r = (coeff[i].kz - coeff[i + 1].kz)
                        / (coeff[i].kz + coeff[i + 1].kz);
                coeff[i].t = 2. * coeff[i].kz / (coeff[i].kz + coeff[i + 1].kz);
            } else {
                complex_t a = picoeff * sigma * coeff[i].kz;
                complex_t b = picoeff * sigma * coeff[i + 1].kz;
                coeff[i].r = std::sinh(a-b)/std::sinh(a+b);
                coeff[i].t = std::sqrt(a*std::sinh(2.*a)*std::sinh(2.*b)/b)
                             / std::sinh(a+b);
            }
            coeff[i].rb = -coeff[i].r;
            coeff[i].tb = coeff[i].t*coeff[i+1].kz/coeff[i].kz;
        }
    }
}

void OpticalFresnel::calculateX(const MultiLayer& sample, MultiLayerCoeff_t& coeff) const
{
    // ratio of amplitudes of outgoing and incoming waves in alternative conventions
    coeff[coeff.size()-1].X = complex_t(0, 0);
    for(int i=(int)coeff.size()-2; i>=0; --i) {
        // first check for infinity
        if(std::abs(coeff[i].r*coeff[i+1].X + complex_t(1,0)) < Numeric::double_epsilon) {
            throw DivisionByZeroException("Division by zero during calculation of X_i");
        }
        double d = i==0 ? 0.0 : sample.getLayerThickness(i);
        complex_t exp_factor;
        if((coeff[i].kz*d*2.0).imag() >=
           -std::log(std::numeric_limits<double>::min())) {
            exp_factor = complex_t(0,0);
        }
        else {
            exp_factor = std::exp(complex_t(0,2)*coeff[i].kz*d);
        }
        coeff[i].X = exp_factor * (coeff[i].r + coeff[i+1].X ) /
            ( complex_t(1,0)+coeff[i].r*coeff[i+1].X );
    }
}

void OpticalFresnel::calculateRT(const MultiLayer& sample, MultiLayerCoeff_t& coeff) const
{
    //complex_t ct0(0,0);

    coeff[0].R = coeff[0].X;
    coeff[0].T = 1;

    for(size_t i=0; i<coeff.size()-1; ++i) {
        // First check for adjacent identical layers with k_z = 0
        if(coeff[i+1].kz == complex_t(0,0) && coeff[i].kz == complex_t(0,0)) {
            coeff[i+1].R = coeff[i].R;
            coeff[i+1].T = coeff[i].T;
            continue;
        }

        // Then check for exact critical angle ( k_{z,i+1} = 0 )
        if(coeff[i+1].kz == complex_t(0,0)) {
            coeff[i+1].R = complex_t(0,0);
            coeff[i+1].T = complex_t(2,0)*coeff[i].T;
            continue;
        }

        double d = i==0 ? 0.0 : sample.getLayerThickness(i);
        // Logarithm of common prefactor:
        // \log(T_i) + i k_{z,i}d_i - \log(t_{i+1,i})
        if(std::abs(coeff[i].T) == 0) {
            coeff[i+1].R = complex_t(0,0);
            coeff[i+1].T = complex_t(0,0);
            continue;
        }
        complex_t log_prefactor = std::log(coeff[i].T)
            + complex_t(0,1)*coeff[i].kz*d - std::log(coeff[i].tb);

        // Calculate R
        complex_t numerator_R = coeff[i+1].X*(complex_t(1,0)-coeff[i].r*coeff[i].r);
        if(numerator_R == complex_t(0,0)) {
            coeff[i+1].R = complex_t(0,0);
        } else {
            complex_t log_R = std::log(numerator_R)
                - std::log(complex_t(1,0)+coeff[i].r*coeff[i+1].X)
                + log_prefactor;
            if(log_R.real() < std::log(std::numeric_limits<double>::min())) {
                coeff[i+1].R = complex_t(0,0);
            } else {
                coeff[i+1].R = std::exp(log_R);
            }
        }

        // Calculate T
        complex_t numerator_T = (complex_t(1,0)-coeff[i].r*coeff[i].r);
        if(numerator_T == complex_t(0,0)) {
            coeff[i+1].T = complex_t(0,0);
        } else {
            complex_t log_T = std::log(numerator_T) - std::log(complex_t(1,0)
                    +coeff[i].r*coeff[i+1].X) + log_prefactor;
            if(log_T.real() < std::log(std::numeric_limits<double>::min())) {
                coeff[i+1].T = complex_t(0,0);
            } else {
                coeff[i+1].T = std::exp(log_T);
            }
        }
    }
}
