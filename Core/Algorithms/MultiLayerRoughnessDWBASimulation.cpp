// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/MultiLayerRoughnessDWBASimulation.cpp
//! @brief     Implements class MultiLayerRoughnessDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerRoughnessDWBASimulation.h"
#include "MultiLayer.h"
#include "DWBADiffuseReflection.h"
#include "BornAgainNamespace.h"

#include <memory>

// Diffuse scattering from rough interfaces is modelled after
// Phys. Rev. B, vol. 51 (4), p. 2311 (1995)

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
    setStatus(RUNNING);
    try {
        runProtected();
        setStatus(COMPLETED);
    }
    catch(const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(FAILED);
    }
}

void MultiLayerRoughnessDWBASimulation::runProtected()
{
    std::vector<SimulationElement>::iterator it = m_begin_it;
    while ( it != m_end_it )
    {
        if( !m_progress.update()) break;
        it->setIntensity(evaluate(*it));
        ++it;
    }
    m_progress.finished();
}

double MultiLayerRoughnessDWBASimulation::evaluate(const SimulationElement& sim_element)
{
    kvector_t q = sim_element.getMeanQ();
    double wavelength = sim_element.getWavelength();
    double autocorr(0.0);
    complex_t crosscorr(0.0, 0.0);

    std::vector<complex_t > rterm;
    rterm.resize( mp_multi_layer->getNumberOfLayers()-1 );
    std::vector<complex_t > sterm;
    sterm.resize( mp_multi_layer->getNumberOfLayers()-1 );

    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers()-1; i++){
        rterm[i] = get_refractive_term(i);
        sterm[i] = get_sum4terms(i, sim_element);
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
                crosscorr += rterm[j]*sterm[j]*
                    mp_multi_layer->getCrossCorrSpectralFun(q,j,k)*
                    std::conj(rterm[k])*std::conj(sterm[k]);
            }
        }
    }

    //! @TODO clarify complex vs double
    return (autocorr+crosscorr.real())*Units::PI/4./wavelength/wavelength;
}

complex_t MultiLayerRoughnessDWBASimulation::get_refractive_term(size_t ilayer) const
{
    return mp_multi_layer->getLayer(ilayer  )->getRefractiveIndex2() -
           mp_multi_layer->getLayer(ilayer+1)->getRefractiveIndex2();
}

complex_t MultiLayerRoughnessDWBASimulation::get_sum4terms(size_t ilayer,
                                                           const SimulationElement& sim_element)
{
    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double alpha_f = sim_element.getAlphaMean();

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeff(
        mp_specular_info_vector[ilayer + 1]->getInCoefficients(alpha_i, 0.0, wavelength));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeff(
        mp_specular_info_vector[ilayer + 1]->getOutCoefficients(alpha_f, 0.0, wavelength));

    complex_t kiz = P_in_coeff->getScalarKz();
    complex_t kfz = P_out_coeff->getScalarKz();
    complex_t qz1 = kiz + kfz;
    complex_t qz2 = kiz - kfz;
    complex_t qz3 = -qz2;
    complex_t qz4 = -qz1;

    double sigma(0.0);
    if (const LayerRoughness *roughness
        = mp_multi_layer->getLayerBottomInterface(ilayer)->getRoughness()) {
        sigma = roughness->getSigma();
    }
    double sigma2 = -0.5 * sigma * sigma;
    complex_t term1 = P_in_coeff->getScalarT() * P_out_coeff->getScalarT()
                      * std::exp(sigma2 * qz1 * qz1);
    complex_t term2 = P_in_coeff->getScalarT() * P_out_coeff->getScalarR()
                      * std::exp(sigma2 * qz2 * qz2);
    complex_t term3 = P_in_coeff->getScalarR() * P_out_coeff->getScalarT()
                      * std::exp(sigma2 * qz3 * qz3);
    complex_t term4 = P_in_coeff->getScalarR() * P_out_coeff->getScalarR()
                      * std::exp(sigma2 * qz4 * qz4);

    return term1 + term2 + term3 + term4;
}
