#include <iostream>
#include <algorithm>
#include "OpticalFresnel.h"
#include "Numeric.h"

OpticalFresnel::OpticalFresnel()
{
}


int OpticalFresnel::execute(const MultiLayer &sample, const kvector_t &kvec, MultiLayerCoeff_t &coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());

    calculateKZ(sample, kvec, coeff);

    calculateFresnelCoefficients(coeff);

    calculateX2(sample, coeff);

    calculateRT2(sample, coeff);

    return 0;
}

void OpticalFresnel::calculateKZ(const MultiLayer &sample, const kvector_t &kvec, MultiLayerCoeff_t &coeff)
{
    // wave vector inside each layer
    // Q_{z,j} &= 2k_{z,j} = 2\cdot \sqrt{ k^2 n_j^2 - k_x^2 }
    for(size_t i=0; i<coeff.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        coeff[i].kz = std::sqrt( kvec.mag2()*std::pow( rindex, 2) - kvec.magxy()*kvec.magxy() );
        //std::cout << "k_z: " << coeff[i].kz << std::endl;
    }
}

void OpticalFresnel::calculateFresnelCoefficients(MultiLayerCoeff_t &coeff)
{
    // calculation of reflection/transmission Fresnel coefficients
    for(size_t i=0; i<coeff.size() - 1; i++) {
        complex_t kzi = coeff[i].kz;
        complex_t kziplus1 = coeff[i+1].kz;
        if (kzi == complex_t(0, 0) && kziplus1 == complex_t(0, 0))
        {
            coeff[i].r = complex_t(0, 0);
            coeff[i].t = complex_t(1, 0);
            coeff[i].rb = complex_t(0, 0);
            coeff[i].tb = complex_t(1, 0);
        } else
        {
            coeff[i].r = (coeff[i].kz - coeff[i + 1].kz)
                    / (coeff[i].kz + coeff[i + 1].kz);
            coeff[i].t = 2. * coeff[i].kz / (coeff[i].kz + coeff[i + 1].kz);
            coeff[i].rb = (coeff[i + 1].kz - coeff[i].kz)
                    / (coeff[i].kz + coeff[i + 1].kz);
            coeff[i].tb = 2. * coeff[i + 1].kz
                    / (coeff[i].kz + coeff[i + 1].kz);
        }
    }
}

void OpticalFresnel::calculateX(const MultiLayer &sample, MultiLayerCoeff_t &coeff)
{
    // ratio of amplitudes of outgoing and incoming waves
    coeff[coeff.size()-1].X = complex_t(0, 0);
    for(int i=coeff.size()-2; i>=0; --i) {
        double z = sample.getLayerBottomZ(i);
        coeff[i].X = std::exp(complex_t(0,-2)*coeff[i].kz*z) *
            (coeff[i].r + coeff[i+1].X*std::exp(complex_t(0,2)*coeff[i+1].kz*z) ) /
            ( complex_t(1,0)+coeff[i].r*coeff[i+1].X*std::exp(complex_t(0,2)*coeff[i+1].kz*z) );
    }
}

void OpticalFresnel::calculateX2(const MultiLayer &sample, MultiLayerCoeff_t &coeff)
{
    // ratio of amplitudes of outgoing and incoming waves in alternative conventions
    coeff[coeff.size()-1].X = complex_t(0, 0);
    for(int i=coeff.size()-2; i>=0; --i) {
        // first check for infinity
        if(std::abs(coeff[i].r*coeff[i+1].X + complex_t(1,0)) < Numeric::double_epsilon) {
            throw DivisionByZeroException("Division by zer during calculation of X_i");
        }
        double d = i==0 ? 0.0 : sample.getLayerThickness(i);
        complex_t exp_factor;
        if((coeff[i].kz*d*2.0).imag() >= -std::log(Numeric::double_min)) {
            exp_factor = complex_t(0,0);
        }
        else {
            exp_factor = std::exp(complex_t(0,2)*coeff[i].kz*d);
        }
        coeff[i].X = exp_factor * (coeff[i].r + coeff[i+1].X ) /
            ( complex_t(1,0)+coeff[i].r*coeff[i+1].X );
    }
}

void OpticalFresnel::calculateRT(const MultiLayer &sample, MultiLayerCoeff_t &coeff)
{
    coeff[0].R = coeff[0].X;
    coeff[0].T = 1;
    for(size_t i=0; i<coeff.size()-1; ++i) {
        double z = sample.getLayerBottomZ(i);
        coeff[i+1].R = complex_t(1,0)/coeff[i].tb * (coeff[i].T*coeff[i].rb*std::exp( complex_t(0,-1)*(coeff[i+1].kz+coeff[i].kz)*z ) +
                                        coeff[i].R*std::exp( complex_t(0,-1)*(coeff[i+1].kz-coeff[i].kz)*z) );

        coeff[i+1].T = complex_t(1,0)/coeff[i].tb * (coeff[i].T*std::exp( complex_t(0,1)*(coeff[i+1].kz-coeff[i].kz)*z ) +
                                        coeff[i].R*coeff[i].rb*std::exp( complex_t(0,1)*(coeff[i+1].kz+coeff[i].kz)*z) );
    }
}

void OpticalFresnel::calculateRT2(const MultiLayer &sample, MultiLayerCoeff_t &coeff)
{
    coeff[0].R = coeff[0].X;
    coeff[0].T = 1;

    for(size_t i=0; i<coeff.size()-1; ++i) {
        // First check for adjecant identical layers with k_z = 0
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
        complex_t log_prefactor = std::log(coeff[i].T) + complex_t(0,1)*coeff[i].kz*d - std::log(coeff[i].tb);

        // Calculate R
        complex_t numerator_R = coeff[i+1].X*(complex_t(1,0)-coeff[i].r*coeff[i].r);
        if(numerator_R == complex_t(0,0)) {
            coeff[i+1].R = complex_t(0,0);
        }
        else {
            complex_t log_R = std::log(numerator_R) - std::log(complex_t(1,0)+coeff[i].r*coeff[i+1].X) + log_prefactor;
            if(log_R.real() < std::log(Numeric::double_min)) {
                coeff[i+1].R = complex_t(0,0);
            }
            else {
                coeff[i+1].R = std::exp(log_R);
            }
        }

        // Calculate T
        complex_t numerator_T = (complex_t(1,0)-coeff[i].r*coeff[i].r);
        if(numerator_T == complex_t(0,0)) {
            coeff[i+1].T = complex_t(0,0);
        }
        else {
            complex_t log_T = std::log(numerator_T) - std::log(complex_t(1,0)+coeff[i].r*coeff[i+1].X) + log_prefactor;
            if(log_T.real() < std::log(Numeric::double_min)) {
                coeff[i+1].T = complex_t(0,0);
            }
            else {
                coeff[i+1].T = std::exp(log_T);
            }
        }

        //complex_t x_ratio = coeff[i+1].R / coeff[i+1].T;
        //std::cout << "Calculated R: "<< coeff[i+1].R << " Calculated T: " << coeff[i+1].T << std::endl;
        //std::cout << "Calculated X: "<< x_ratio << " Real X: " << coeff[i+1].X << std::endl;
    }
}
