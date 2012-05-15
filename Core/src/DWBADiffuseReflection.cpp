#include "DWBADiffuseReflection.h"
#include "OpticalFresnel.h"
#include "LayerRoughness.h"



DWBADiffuseReflection::DWBADiffuseReflection()
{

}



double DWBADiffuseReflection::execute(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
{

    OpticalFresnel::MultiLayerCoeff_t c_f;
    OpticalFresnel::execute(sample, ki, c_f);

    OpticalFresnel::MultiLayerCoeff_t c_i;
    OpticalFresnel::execute(sample, kf, c_i);

    double sum(0);
    for(size_t i=0; i<sample.getNumberOfLayers()-1; i++){
        complex_t n1 = sample.getLayer(i)->getRefractiveIndex();
        complex_t n2 = sample.getLayer(i+1)->getRefractiveIndex();
        const LayerRoughness &rough = sample.getLayerBottomInterface(i)->getRoughness();
        double sigma = rough.getSigma();

        kvector_t q = ki - kf;
        double qz1 = ki.z() + kf.z();
        double qz2 = -ki.z() - kf.z();
        double qz3 = ki.z() - kf.z();
        double qz4 = -ki.z() + kf.z();
        complex_t term1 = c_i[i+1].T*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz1 ,2) );
        complex_t term2 = c_i[i+1].R*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz2 ,2) );
        complex_t term3 = c_i[i+1].T*c_f[i+1].R * std::exp( -0.5*std::pow(sigma * qz3 ,2) );
        complex_t term4 = c_i[i+1].R*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz4 ,2) );

        sum += std::norm( std::pow(n1,2)-std::pow(n2,2) ) * std::norm(term1 + term2 + term3 + term4) * rough.getSpectralFun(q);
    }

    const double S = 1.0;
    double CS = sum*S*ki.mag2()/16./M_PI;
    return CS;
}
