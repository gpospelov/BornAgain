#include <iostream>
#include "OpticalFresnel.h"

OpticalFresnel::OpticalFresnel()
{
}


int OpticalFresnel::execute(const MultiLayer &sample, const kvector_t &kvec, MultiLayerCoeff_t &coeff)
{
    MultiLayerCoeff_t &fC = coeff;
    fC.clear();
    fC.resize(sample.getNumberOfLayers());

    calculateKZ(sample, kvec, fC);

    calculateFresnelCoefficients(fC);

    calculateX(sample, fC);

    calculateRT(sample, fC);

    return 0;
}

void OpticalFresnel::calculateKZ(const MultiLayer &sample, const kvector_t &kvec, MultiLayerCoeff_t &coeff)
{
    // wave vector inside each layer
    // Q_{z,j} &= 2k_{z,j} = 2\cdot \sqrt{ k^2 n_j^2 - k_x^2 }
    for(size_t i=0; i<coeff.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        coeff[i].kz = std::sqrt( kvec.mag2()*std::pow( rindex, 2) - kvec.magxy()*kvec.magxy() );
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
    // ratio of amplitudes of outgoing and incoming waves in alternative conventions
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
    // ratio of amplitudes of outgoing and incoming waves
    coeff[coeff.size()-1].X = complex_t(0, 0);
    for(int i=coeff.size()-2; i>=0; --i) {
        double d = i==0 ? 0.0 : sample.getLayerThickness(i);
        coeff[i].X = std::exp(complex_t(0,2)*coeff[i].kz*d) *
            (coeff[i].r + coeff[i+1].X ) /
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
        double d = i==0 ? 0.0 : sample.getLayerThickness(i);
        coeff[i+1].R = complex_t(1,0)/coeff[i].tb * (coeff[i].T*coeff[i].rb*std::exp( complex_t(0,1)*coeff[i].kz*d ) +
                                        coeff[i].R*std::exp( complex_t(0,-1)*coeff[i].kz*d ) );

        coeff[i+1].T = complex_t(1,0)/coeff[i].tb * (coeff[i].T*std::exp( complex_t(0,1)*coeff[i].kz*d ) +
                                        coeff[i].R*coeff[i].rb*std::exp( complex_t(0,-1)*coeff[i].kz*d ) );
    }
}
