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
        std::cout << "k_z: " << coeff[i].kz << std::endl;
    }
}

void OpticalFresnel::calculateFresnelCoefficients(MultiLayerCoeff_t &coeff)
{
    // calculation of reflection/transmission Fresnel coefficients
    for(size_t i=0; i<coeff.size() - 1; i++) {
        coeff[i].r = ( coeff[i].kz - coeff[i+1].kz ) / (coeff[i].kz + coeff[i+1].kz );
        coeff[i].t = 2.*coeff[i].kz / (coeff[i].kz + coeff[i+1].kz );
        coeff[i].rb = ( coeff[i+1].kz - coeff[i].kz ) / (coeff[i].kz + coeff[i+1].kz );
        coeff[i].tb = 2.*coeff[i+1].kz / (coeff[i].kz + coeff[i+1].kz );
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
    // Calculate coefficients for layer 1 seperately, since d_0 = 0
    if(coeff.size()>1) {
        complex_t small_factor_approx = coeff[1].X*(complex_t(1,0)-coeff[0].r);
        if(std::abs(small_factor_approx) < Numeric::double_epsilon / Numeric::required_precision * std::abs(coeff[0].r)) {
            coeff[1].R = complex_t(1,0)/coeff[0].tb * small_factor_approx;
        }
        else {
            coeff[1].R = complex_t(1,0)/coeff[0].tb * (coeff[0].rb + coeff[0].R);
        }
        if(std::abs(coeff[0].r*coeff[0].r - complex_t(1,0)) <
                Numeric::double_epsilon / Numeric::required_precision * std::abs(coeff[1].X * coeff[0].r)) {
            coeff[1].T = complex_t(1,0)/coeff[0].tb * (complex_t(1,0) / coeff[0].r / coeff[1].X - coeff[0].r / coeff[1].X );
        }
        else {
            coeff[1].T = complex_t(1,0)/coeff[0].tb * (coeff[0].R * coeff[0].rb + complex_t(1,0));
        }
        std::cout << "Calculated R: "<< coeff[1].R << " Calculated T: " << coeff[1].T << std::endl;
        std::cout << "Calculated X: "<< coeff[1].R / coeff[1].T << " Real X: " << coeff[1].X << std::endl;
    }
    // Calculate the other coefficients
    for(size_t i=1; i<coeff.size()-1; ++i) {
        double d = sample.getLayerThickness(i);
        complex_t exp_pos, exp_neg;
        if((coeff[i].kz*d).imag() >= -std::log(Numeric::double_min)) {
            exp_pos = complex_t(0,0);
            exp_neg = complex_t(0,0);
        }
        else {
            exp_pos = std::exp( complex_t(0,1)*coeff[i].kz*d );
            exp_neg = std::exp( complex_t(0,-1)*coeff[i].kz*d );
        }
        // Calculate the largest coefficient first and then the other from X
        if(std::abs(coeff[i+1].X) < 1.0) {
            coeff[i+1].T = complex_t(1,0)/coeff[i].tb * (coeff[i].T*exp_pos + coeff[i].R*coeff[i].rb*exp_neg );
            coeff[i+1].R = coeff[i+1].T * coeff[i+1].X;
        }
        else {
            coeff[i+1].R = complex_t(1,0)/coeff[i].tb * (coeff[i].T*coeff[i].rb*exp_pos + coeff[i].R*exp_neg );
            coeff[i+1].T = coeff[i+1].R / coeff[i+1].X;
        }
//        complex_t r_term1 = coeff[i].T*coeff[i].rb*std::exp( complex_t(0,1)*coeff[i].kz*d );
//        complex_t r_term2 = coeff[i].R*std::exp( complex_t(0,-1)*coeff[i].kz*d );
//        double r_max_norm = std::max(std::abs(r_term1), std::abs(r_term2));
//        r_max_norm = std::max(r_max_norm, Numeric::double_min / Numeric::required_precision);
//        complex_t r_sum = r_term1 + r_term2;
//        if (std::abs(r_sum) / r_max_norm < Numeric::double_epsilon / Numeric::required_precision) {
//            complex_t epsilon_exponent = complex_t(0,1)*coeff[i].kz*d - (std::log(-coeff[i].R) - std::log(coeff[i].T*coeff[i].rb))/complex_t(2,0);
//            complex_t d2 = std::log(std::sqrt(-coeff[i].R/(coeff[i].T*coeff[i].rb)));
//            coeff[i+1].R = epsilon_exponent * (r_term1 - r_term2);
//        }
//        else {
//            coeff[i+1].R = complex_t(1,0)/coeff[i].tb * r_sum;
//        }
//        complex_t t_term1 = coeff[i].T*std::exp( complex_t(0,1)*coeff[i].kz*d );
//        complex_t t_term2 = coeff[i].R*coeff[i].rb*std::exp( complex_t(0,-1)*coeff[i].kz*d );
//        double t_max_norm = std::max(std::abs(t_term1), std::abs(t_term2));
//        t_max_norm = std::max(t_max_norm, Numeric::double_min / Numeric::required_precision);
//        complex_t t_sum = t_term1 + t_term2;
//        if (std::abs(t_sum) / t_max_norm < Numeric::double_epsilon / Numeric::required_precision) {
//            complex_t epsilon_exponent = complex_t(0,1)*coeff[i].kz*d - (std::log(-coeff[i].R*coeff[i].rb) - std::log(coeff[i].T))/complex_t(2,0);
//            coeff[i+1].T = epsilon_exponent * (t_term1 - t_term2);
//        }
//        else {
//            coeff[i+1].T = complex_t(1,0)/coeff[i].tb * t_sum;
//        }

//        coeff[i+1].T = complex_t(1,0)/coeff[i].tb * (coeff[i].T*std::exp( complex_t(0,1)*coeff[i].kz*d ) +
//                                        coeff[i].R*coeff[i].rb*std::exp( complex_t(0,-1)*coeff[i].kz*d ) );
//        coeff[i+1].R = coeff[i+1].T*coeff[i+1].X;
        complex_t x_ratio = coeff[i+1].R / coeff[i+1].T;
        std::cout << "Calculated R: "<< coeff[i+1].R << " Calculated T: " << coeff[i+1].T << std::endl;
        std::cout << "Calculated X: "<< x_ratio << " Real X: " << coeff[i+1].X << std::endl;
    }
}
