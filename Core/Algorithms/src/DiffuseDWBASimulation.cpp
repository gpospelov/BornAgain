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

#define SQR(x) ((x)*(x))

//! Carry out one simulation thread.

void DiffuseDWBASimulation::run()
{
    msglog(MSG::DEBUG) << "DiffuseDWBASimulation::run()";
    // Set diffuse terms.
    std::vector<DiffuseFormFactorTerm*> diffuse_terms;
    size_t nbr_heights = 50;
    size_t samples_per_particle = 9;
    initDiffuseFormFactorTerms(
        diffuse_terms, nbr_heights, samples_per_particle);

    double wavevector_scattering_factor = M_PI/SQR(getWaveLength());
    cvector_t k_ij = m_ki;
    k_ij.setZ(-mp_kz_function->evaluate(-m_alpha_i));

    for (DWBASimulation::iterator it_intensity =
             begin(); it_intensity != end(); ++it_intensity ) {
        Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(
            "phi_f", it_intensity.getIndex());
        Bin1D alpha_bin = getDWBAIntensity().getBinOfAxis(
            "alpha_f", it_intensity.getIndex());
        double alpha_f = alpha_bin.getMidPoint();
        if (alpha_f<0)
            continue;
        Bin1DCVector k_f_bin = getKfBin(getWaveLength(), alpha_bin, phi_bin);

        double total_intensity = 0;
        for (size_t i=0; i<diffuse_terms.size(); ++i) {
            DiffuseFormFactorTerm *p_diffuse_term = diffuse_terms[i];
            complex_t amplitude(0., 0.);
            double intensity = 0;
            for (size_t j=0; j<p_diffuse_term->m_form_factors.size(); ++j) {
                complex_t amp =
                    p_diffuse_term->m_form_factors[j]->evaluate(
                        k_ij, k_f_bin, -m_alpha_i, alpha_f);
                amplitude += p_diffuse_term->m_probabilities[j]*amp;
                intensity += p_diffuse_term->m_probabilities[j]*std::norm(amp);
            }
            total_intensity +=
                p_diffuse_term->m_factor * (intensity - std::norm(amplitude));
        }
        *it_intensity = total_intensity * SQR(wavevector_scattering_factor);
    }

    for (size_t i=0; i<diffuse_terms.size(); ++i)
        delete diffuse_terms[i];
}

//! Initializes vector<DiffuseFormFactorTerm*> term.

//! Called near beginning of this->run().
//! Collect one entry (p_diffuse_term) per particle type and layer[?].
//! For each entry, set
//! - m_factor
//! - m_form_factors <- vector<FormFactorDWBAConstZ*>
//!
void DiffuseDWBASimulation::initDiffuseFormFactorTerms(
        std::vector<DiffuseFormFactorTerm*>& terms,
        size_t nbr_heights,
        size_t samples_per_particle)
{
    msglog(MSG::DEBUG) << "DiffuseDWBASimulation::init...()";
    for (size_t i=0; i<m_np_infos.size(); ++i) {
        DiffuseParticleInfo *p_diff_info = m_np_infos[i];
        Particle *p_particle = p_diff_info->getParticle()->clone();
        double total_particle_density = p_diff_info->getNumberPerMeso();
        double density_per_height_per_particle =
            total_particle_density/nbr_heights;
        for (size_t j=0; j<nbr_heights; ++j) {
            DiffuseFormFactorTerm *p_diffuse_term = new DiffuseFormFactorTerm;
            p_diffuse_term->m_factor = density_per_height_per_particle;
            double depth = p_diff_info->getDepth() -
                j*p_diff_info->getHeightRange()/(nbr_heights-1.0);
            std::vector<IFormFactor*> form_factors;
            p_diff_info->getParticle()->getSimpleFormFactor()->createDistributedFormFactors(
                form_factors, p_diffuse_term->m_probabilities,
                samples_per_particle);
            for (size_t ff_index=0; ff_index<form_factors.size(); ++ff_index) {
                p_particle->setSimpleFormFactor(form_factors[ff_index]);
                IFormFactor *ff_particle = p_particle->createFormFactor();
                FormFactorDWBAConstZ *p_dwba_z =
                    new FormFactorDWBAConstZ(ff_particle, depth);
                p_dwba_z->setReflectionTransmissionFunction(*mp_RT_function);

                p_diffuse_term->m_form_factors.push_back(p_dwba_z);
            }
            terms.push_back(p_diffuse_term);
        }
        delete p_particle;
    }
}

