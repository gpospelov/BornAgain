// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DiffuseDWBASimulation.cpp
//! @brief     Implements class DiffuseDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DiffuseDWBASimulation.h"
#include "FormFactorDWBAConstZ.h"
#include "MessageService.h"
#include "FormFactorTools.h"
#include "MathFunctions.h"
#include "BornAgainNamespace.h"
#include "Layer.h"

//! Carry out one simulation thread.

void DiffuseDWBASimulation::run()
{
    setStatus(Running);
    try {
        runProtected();
        setStatus(Completed);
    }
    catch(const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(Failed);
    }
}

void DiffuseDWBASimulation::runProtected()
{
    msglog(MSG::DEBUG2) << "DiffuseDWBASimulation::run()";
    // Set diffuse terms.
    SafePointerVector<DiffuseFormFactorTerm> diffuse_terms;
    size_t nbr_heights = 50;
    size_t samples_per_particle = 9;
    double wavevector_scattering_factor = M_PI/getWaveLength()/getWaveLength();
    initDiffuseFormFactorTerms(diffuse_terms, nbr_heights, samples_per_particle,
            wavevector_scattering_factor);

    if (checkPolarizationPresent()) {
        // matrix dwba calculation
        OutputData<Eigen::Matrix2d>::iterator it_intensity =
                mp_polarization_output->begin(m_thread_info);
        while ( it_intensity != mp_polarization_output->end(m_thread_info) )
        {
            if( !m_progress.update()) break;

            Bin1D phi_bin = mp_polarization_output->getBinOfAxis(
                BornAgain::PHI_AXIS_NAME, it_intensity.getIndex());
            Bin1D alpha_bin = mp_polarization_output->getBinOfAxis(
                BornAgain::ALPHA_AXIS_NAME, it_intensity.getIndex());
            double alpha_f = alpha_bin.getMidPoint();
            size_t n_layers = mp_layer->getNumberOfLayers();
            if (n_layers>1 && alpha_f<0) {
                ++it_intensity;
                continue;
            }
            Bin1DCVector k_f_bin = getKfBin(getWaveLength(), alpha_bin,
                    phi_bin);

            const ILayerRTCoefficients *p_in_coeffs =
                    mp_specular_info->getInCoefficients();
            boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
                    mp_specular_info->getOutCoefficients(
                            alpha_f, phi_bin.getMidPoint()) );

            Eigen::Matrix2d total_intensity = Eigen::Matrix2d::Zero();
            for (size_t i=0; i<diffuse_terms.size(); ++i) {
                DiffuseFormFactorTerm *p_diffuse_term = diffuse_terms[i];
                Eigen::Matrix2cd amplitude = Eigen::Matrix2cd::Zero();
                Eigen::Matrix2d intensity = Eigen::Matrix2d::Zero();
                for (size_t j=0; j<p_diffuse_term->m_form_factors.size(); ++j) {
                    p_diffuse_term->m_form_factors[j]
                            ->setSpecularInfo(p_in_coeffs, P_out_coeffs.get());
                    Eigen::Matrix2cd amp =
                        p_diffuse_term->m_form_factors[j]->evaluatePol(
                            m_ki, k_f_bin, alpha_bin, phi_bin);
                    amplitude += p_diffuse_term->m_probabilities[j] * amp;
                    intensity += p_diffuse_term->m_probabilities[j]
                                 * MathFunctions::Norm(amp);
                }
                total_intensity += p_diffuse_term->m_factor
                        * (intensity - MathFunctions::Norm(amplitude));
            }
            *it_intensity = total_intensity;
            ++it_intensity;
        }
    }
    else {
        // scalar dwba calculation
        cvector_t k_ij = m_ki;
        k_ij.setZ(-(complex_t)mp_specular_info->getInCoefficients()->getScalarKz());

        DWBASimulation::iterator it_intensity = begin();
        while ( it_intensity != end() )
        {
            if( !m_progress.update()) break;

            Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(
                BornAgain::PHI_AXIS_NAME, it_intensity.getIndex());
            Bin1D alpha_bin = getDWBAIntensity().getBinOfAxis(
                BornAgain::ALPHA_AXIS_NAME, it_intensity.getIndex());
            double alpha_f = alpha_bin.getMidPoint();
            if (alpha_f<0) {
                ++it_intensity;
                continue;
            }
            Bin1DCVector k_f_bin = getKfBin(getWaveLength(), alpha_bin, phi_bin);

            const ILayerRTCoefficients *p_in_coeffs =
                    mp_specular_info->getInCoefficients();
            boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
                    mp_specular_info->getOutCoefficients(alpha_f, 0.0) );

            double total_intensity = 0;
            for (size_t i=0; i<diffuse_terms.size(); ++i) {
                DiffuseFormFactorTerm *p_diffuse_term = diffuse_terms[i];
                complex_t amplitude(0., 0.);
                double intensity = 0;
                for (size_t j=0; j<p_diffuse_term->m_form_factors.size(); ++j) {
                    p_diffuse_term->m_form_factors[j]
                            ->setSpecularInfo(p_in_coeffs, P_out_coeffs.get());
                    complex_t amp =
                        p_diffuse_term->m_form_factors[j]->evaluate(
                            k_ij, k_f_bin, alpha_bin);
                    amplitude += p_diffuse_term->m_probabilities[j]*amp;
                    intensity += p_diffuse_term->m_probabilities[j]*std::norm(amp);
                }
                total_intensity +=
                    p_diffuse_term->m_factor * (intensity - std::norm(amplitude));
            }
            *it_intensity = total_intensity;
            ++it_intensity;
        }
    }
    m_progress.finished();
}


void DiffuseDWBASimulation::setMaterial(const IMaterial* p_material)
{
    if(!p_material) return;
    SafePointerVector<DiffuseParticleInfo>::iterator it =
            m_np_infos.begin();
    while (it != m_np_infos.end()) {
        (*it)->setAmbientMaterial(p_material);
        ++it;
    }
}


//! Initializes vector<DiffuseFormFactorTerm*> term.
//!
//! Called near beginning of this->run().
//! Collect one entry (p_diffuse_term) per particle type and layer[?].
//! For each entry, set
//! - m_factor
//! - m_form_factors <- vector<FormFactorDWBAConstZ*>
//!
void DiffuseDWBASimulation::initDiffuseFormFactorTerms(
        SafePointerVector<DiffuseFormFactorTerm>& terms,
        size_t nbr_heights,
        size_t samples_per_particle, complex_t wavevector_scattering_factor)
{
    msglog(MSG::DEBUG2) << "DiffuseDWBASimulation::init...()";
    for (size_t i=0; i<m_np_infos.size(); ++i) {
        DiffuseParticleInfo *p_diff_info = m_np_infos[i];
        IParticle *p_particle = p_diff_info->getParticle()->clone();
        double total_particle_density = p_diff_info->getNumberPerMeso();
        double density_per_height_per_particle =
            total_particle_density/nbr_heights;
        for (size_t j=0; j<nbr_heights; ++j) {
            DiffuseFormFactorTerm *p_diffuse_term = new DiffuseFormFactorTerm;
            p_diffuse_term->m_factor = density_per_height_per_particle;
            double depth = p_diff_info->getDepth() -
                j*p_diff_info->getHeightRange()/(nbr_heights-1.0);
            std::vector<IFormFactor*> form_factors;
            p_diff_info->getParticle()->getSimpleFormFactor()
                ->createDistributedFormFactors(
                    form_factors, p_diffuse_term->m_probabilities,
                    samples_per_particle);
            for (size_t ff_index=0; ff_index<form_factors.size(); ++ff_index) {
                p_particle->setSimpleFormFactor(form_factors[ff_index]);
                IFormFactor *p_ff_particle = p_particle->createFormFactor(
                        wavevector_scattering_factor);
                IFormFactor *p_dwba_ff(p_ff_particle);
                if (checkPolarizationPresent()) {
                    p_dwba_ff = FormFactorTools::createDWBAMatrixFormFactor(
                            p_ff_particle, depth);
                }
                else {
                    p_dwba_ff = FormFactorTools::createDWBAScalarFormFactor(
                            p_ff_particle, depth);
                }
                p_diffuse_term->m_form_factors.push_back(p_dwba_ff);
            }
            terms.push_back(p_diffuse_term);
        }
        delete p_particle;
    }
}

DiffuseDWBASimulation::DiffuseFormFactorTerm::~DiffuseFormFactorTerm()
{
    for (size_t i=0; i<m_form_factors.size(); ++i)
        delete m_form_factors[i];
}
