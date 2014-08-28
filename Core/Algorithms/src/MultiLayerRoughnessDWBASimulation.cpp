// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/MultiLayerRoughnessDWBASimulation.cpp
//! @brief     Implements class MultiLayerRoughnessDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerRoughnessDWBASimulation.h"
#include "MultiLayer.h"
#include "DWBADiffuseReflection.h"
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>

MultiLayerRoughnessDWBASimulation::MultiLayerRoughnessDWBASimulation(
    const MultiLayer *p_multi_layer)
{
    mp_multi_layer = p_multi_layer->clone();
    mp_specular_info_vector.resize(mp_multi_layer->getNumberOfLayers(), 0);
}

MultiLayerRoughnessDWBASimulation::~MultiLayerRoughnessDWBASimulation()
{
    for(size_t i=0; i<mp_specular_info_vector.size(); ++i)
        delete mp_specular_info_vector[i];

    delete mp_multi_layer;
}

void MultiLayerRoughnessDWBASimulation::run()
{
    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    double lambda = 2*M_PI/m_ki_real.mag();

    DWBASimulation::iterator it_intensity = m_dwba_intensity.begin(m_thread_info);
    while ( it_intensity != m_dwba_intensity.end(m_thread_info) )
    {
        if( !m_progress.update()) break;

        double phi_f = getDWBAIntensity().getValueOfAxis(
            BornAgain::PHI_AXIS_NAME, it_intensity.getIndex());
        double alpha_f = getDWBAIntensity().getValueOfAxis(
            BornAgain::ALPHA_AXIS_NAME, it_intensity.getIndex());
        cvector_t k_f;
        k_f.setLambdaAlphaPhi(lambda, alpha_f, phi_f);
        *it_intensity = evaluate(m_ki, k_f, -m_alpha_i, alpha_f);
        ++it_intensity;
    }
    m_progress.finished();
}

double MultiLayerRoughnessDWBASimulation::evaluate(
    const cvector_t& k_i, const cvector_t& k_f,
    double alpha_i, double alpha_f)
{
    (void)alpha_i;
    kvector_t ki_real(k_i.x().real(), k_i.y().real(), k_i.z().real());
    kvector_t kf_real(k_f.x().real(), k_f.y().real(), k_f.z().real());
    kvector_t q = kf_real - ki_real;
    double autocorr(0.0);
    complex_t crosscorr(0.0, 0.0);

    std::vector<complex_t > rterm;
    rterm.resize( mp_multi_layer->getNumberOfLayers() );
    std::vector<complex_t > sterm;
    sterm.resize( mp_multi_layer->getNumberOfLayers() );

    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers()-1; i++){
        rterm[i] = get_refractive_term(i);
        sterm[i] = get_sum4terms(i, k_i, k_f, alpha_f);
    }

    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers()-1; i++){
        const LayerRoughness *rough =
            mp_multi_layer->getLayerBottomInterface(i)->getRoughness();
        if(rough) {
            autocorr += std::norm( rterm[i] ) * std::norm( sterm[i] ) *
                rough->getSpectralFun(q);
        }
    }

    // cross correlation between layers
    if( mp_multi_layer->getCrossCorrLength() != 0.0 ) {
        for(size_t j=0; j<mp_multi_layer->getNumberOfLayers()-1; j++){
            for(size_t k=0; k<mp_multi_layer->getNumberOfLayers()-1; k++) {
                if(j==k) continue;
                crosscorr += rterm[j]*sterm[j]*rterm[k]*
                    mp_multi_layer->getCrossCorrSpectralFun(q,j,k)*
                    std::conj(sterm[k]);
            }
        }
    }

    //! @TODO clarify complex vs double
    return (autocorr+crosscorr.real())*k_i.mag2().real()/16./M_PI;
}

complex_t MultiLayerRoughnessDWBASimulation::get_refractive_term(
    size_t ilayer) const
{
    complex_t n1 = mp_multi_layer->getLayer(ilayer)  ->getRefractiveIndex();
    complex_t n2 = mp_multi_layer->getLayer(ilayer+1)->getRefractiveIndex();
    return n1*n1-n2*n2;
}

complex_t MultiLayerRoughnessDWBASimulation::get_sum4terms(
    size_t ilayer, const cvector_t& k_i, const cvector_t& k_f, double alpha_f)
{
    complex_t qz1 =  k_i.z() + k_f.z();
    complex_t qz2 =  k_i.z() - k_f.z();
    complex_t qz3 = -k_i.z() + k_f.z();
    complex_t qz4 = -k_i.z() - k_f.z();

    const ILayerRTCoefficients *p_in_coeff =
            mp_specular_info_vector[ilayer+1]->getInCoefficients();
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeff(
        mp_specular_info_vector[ilayer+1]->getOutCoefficients(alpha_f, 0.0) );


    double sigma = mp_multi_layer->getLayerBottomInterface(ilayer)->
        getRoughness()->getSigma();
    double sigma2 = -0.5*sigma*sigma;
    complex_t term1 = p_in_coeff->getScalarT() * P_out_coeff->getScalarT()
            * std::exp( sigma2*qz1*qz1 );
    complex_t term2 = p_in_coeff->getScalarT() * P_out_coeff->getScalarR()
            * std::exp( sigma2*qz2*qz2 );
    complex_t term3 = p_in_coeff->getScalarR()  * P_out_coeff->getScalarT()
            * std::exp( sigma2*qz3*qz3 );
    complex_t term4 = p_in_coeff->getScalarR()  * P_out_coeff->getScalarR()
            * std::exp( sigma2*qz4*qz4 );

    return term1 + term2 + term3 + term4;
}



