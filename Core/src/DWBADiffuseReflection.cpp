#include "DWBADiffuseReflection.h"
#include "OpticalFresnel.h"
#include "LayerRoughness.h"



DWBADiffuseReflection::DWBADiffuseReflection() : m_diffuse_autocorr(0), m_diffuse_crosscorr(0)
{

}


void DWBADiffuseReflection::execute(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
{
    setSample(sample);

    m_ki = ki;

    m_kf = kf;

    OpticalFresnel::execute(*m_sample, m_ki, m_fcoeff_i);

    OpticalFresnel::execute(*m_sample, m_kf, m_fcoeff_f);

    diffuse_autocorr();

    if( m_sample->getCrossCorrLength() != 0) diffuse_crosscorr();

}


void DWBADiffuseReflection::diffuse_autocorr()
{
    double autocorr(0);
    kvector_t q = m_ki - m_kf;
    for(size_t i=0; i<m_sample->getNumberOfLayers()-1; i++){
        autocorr += std::norm( get_refractive_term(i)) * std::norm(get_sum4terms(i) ) * m_sample->getLayerBottomInterface(i)->getRoughness().getSpectralFun(q);
    }
    m_diffuse_autocorr = autocorr*m_ki.mag2()/16./M_PI;
}


void DWBADiffuseReflection::diffuse_crosscorr()
{
    double crosscorr(0);
    kvector_t q = m_ki - m_kf;
    for(size_t j=0; j<m_sample->getNumberOfLayers()-1; j++){
        for(size_t k=0; k<m_sample->getNumberOfLayers()-1; k++) {
            if(j==k) continue;
            crosscorr += std::abs(get_refractive_term(j)*get_refractive_term(k))*m_sample->getCrossCorrSpectralFun(q,j,k)*std::abs(get_sum4terms(j)*std::conj(get_sum4terms(k)));
        }
    }
    m_diffuse_crosscorr = std::abs(crosscorr)*m_ki.mag2()/16./M_PI;
}


complex_t DWBADiffuseReflection::get_refractive_term(int ilayer)
{
    complex_t n1 = m_sample->getLayer(ilayer)->getRefractiveIndex();
    complex_t n2 = m_sample->getLayer(ilayer+1)->getRefractiveIndex();
    return (std::pow(n1,2)-std::pow(n2,2));
}


complex_t DWBADiffuseReflection::get_sum4terms(int ilayer)
{
    double sigma = m_sample->getLayerBottomInterface(ilayer)->getRoughness().getSigma();
    double qz1 = m_ki.z() + m_kf.z();
    double qz2 = -m_ki.z() - m_kf.z();
    double qz3 = m_ki.z() - m_kf.z();
    double qz4 = -m_ki.z() + m_kf.z();
    complex_t term1 = m_fcoeff_i[ilayer+1].T * m_fcoeff_f[ilayer+1].T * std::exp( -0.5*std::pow(sigma * qz1 ,2) );
    complex_t term2 = m_fcoeff_i[ilayer+1].R * m_fcoeff_f[ilayer+1].T * std::exp( -0.5*std::pow(sigma * qz2 ,2) );
    complex_t term3 = m_fcoeff_i[ilayer+1].T * m_fcoeff_f[ilayer+1].R * std::exp( -0.5*std::pow(sigma * qz3 ,2) );
    complex_t term4 = m_fcoeff_i[ilayer+1].R * m_fcoeff_f[ilayer+1].R * std::exp( -0.5*std::pow(sigma * qz4 ,2) );
    return term1 + term2 + term3 + term4;
}


//double DWBADiffuseReflection::execute0(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
//{

//    OpticalFresnel::MultiLayerCoeff_t c_f;
//    OpticalFresnel::execute(sample, ki, c_f);

//    OpticalFresnel::MultiLayerCoeff_t c_i;
//    OpticalFresnel::execute(sample, kf, c_i);

//    double autosum(0);
//    for(size_t i=0; i<sample.getNumberOfLayers()-1; i++){
//        complex_t n1 = sample.getLayer(i)->getRefractiveIndex();
//        complex_t n2 = sample.getLayer(i+1)->getRefractiveIndex();
//        const LayerRoughness &rough = sample.getLayerBottomInterface(i)->getRoughness();
//        double sigma = rough.getSigma();

//        kvector_t q = ki - kf;
//        double qz1 = ki.z() + kf.z();
//        double qz2 = -ki.z() - kf.z();
//        double qz3 = ki.z() - kf.z();
//        double qz4 = -ki.z() + kf.z();
//        complex_t term1 = c_i[i+1].T*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz1 ,2) );
//        complex_t term2 = c_i[i+1].R*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz2 ,2) );
//        complex_t term3 = c_i[i+1].T*c_f[i+1].R * std::exp( -0.5*std::pow(sigma * qz3 ,2) );
//        complex_t term4 = c_i[i+1].R*c_f[i+1].R * std::exp( -0.5*std::pow(sigma * qz4 ,2) );
//        double x1 = std::norm( std::pow(n1,2)-std::pow(n2,2) ) * std::norm(term1 + term2 + term3 + term4) * rough.getSpectralFun(q);
//        autosum += x1;
//    }

//    const double S = 1.0;
//    double CS = autosum*S*ki.mag2()/16./M_PI;
//    return CS;
//}
