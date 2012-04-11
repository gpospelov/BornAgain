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

    // wave vector inside each layer
    // Q_{z,j} &= 2k_{z,j} = 2\cdot \sqrt{ k^2 n_j^2 - k_x^2 }
    for(size_t i=0; i<fC.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        fC[i].kz = std::sqrt( kvec.mag2()*std::pow( rindex, 2) - kvec.x()*kvec.x() );
    }

    // calculation of reflection/transmission Fresnel coefficients
    for(size_t i=0; i<fC.size() - 1; i++) {
        fC[i].r = ( fC[i].kz - fC[i+1].kz ) / (fC[i].kz + fC[i+1].kz );
        fC[i].t = 2.*fC[i].kz / (fC[i].kz + fC[i+1].kz );
        fC[i].rb = ( fC[i+1].kz - fC[i].kz ) / (fC[i].kz + fC[i+1].kz );
        fC[i].tb = 2.*fC[i+1].kz / (fC[i].kz + fC[i+1].kz );
    }

    // ratio of amplitudes of outgoing and incoming waves
    for(int i=fC.size()-2; i>=0; --i) {
        double z = sample.getLayerZ(i);
        fC[i].X = std::exp(complex_t(0,-2)*fC[i].kz*z) *
            (fC[i].r + fC[i+1].X*std::exp(complex_t(0,2)*fC[i+1].kz*z) ) /
            ( complex_t(1,0)+fC[i].r*fC[i+1].X*std::exp(complex_t(0,2)*fC[i+1].kz*z) );
    }

    fC[0].R = fC[0].X;
    fC[0].T = 1;
    for(size_t i=0; i<fC.size()-1; ++i) {
        double z = sample.getLayerZ(i);
        fC[i+1].R = complex_t(1,0)/fC[i].tb * (fC[i].T*fC[i].rb*std::exp( complex_t(0,-1)*(fC[i+1].kz+fC[i].kz)*z ) +
                                        fC[i].R*std::exp(complex_t(0,-1)*(fC[i+1].kz-fC[i].kz)*z) );

        fC[i+1].T = complex_t(1,0)/fC[i].tb * (fC[i].T*std::exp( complex_t(0,1)*(fC[i+1].kz-fC[i].kz)*z ) +
                                        fC[i].R*fC[i].rb*std::exp(complex_t(0,1)*(fC[i+1].kz+fC[i].kz)*z) );
    }

    return 0;
}

