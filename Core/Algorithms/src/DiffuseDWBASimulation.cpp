#include "DiffuseDWBASimulation.h"
#include "FormFactorDWBAConstZ.h"

DiffuseDWBASimulation::DiffuseDWBASimulation()
: m_refractive_index(1.0, 0.0)
, m_surface_density(1.0)
{
}

DiffuseDWBASimulation::~DiffuseDWBASimulation()
{
    for (size_t i=0; i<m_np_infos.size(); ++i) {
        delete m_np_infos[i];
    }
}

void DiffuseDWBASimulation::run()
{
    std::vector<DiffuseFormFactorTerm *> diffuse_terms;
    size_t nbr_heights = 50;
    size_t samples_per_particle = 9;
    initDiffuseFormFactorTerms(diffuse_terms, nbr_heights, samples_per_particle);
    double wavevector_scattering_factor = M_PI/getWaveLength()/getWaveLength();

    resetIndex();
    while ( hasNext() ) {
        if( !m_output_data_mask.currentValue() ) {
            next();
            continue;
        }

        double phi_f = getDWBAIntensity().getCurrentValueOfAxis<double>("phi_f");
        double alpha_f = getDWBAIntensity().getCurrentValueOfAxis<double>("alpha_f");
        if (alpha_f<0) {
            next();
            continue;
        }
        cvector_t k_f;
        k_f.setLambdaAlphaPhi(getWaveLength(), alpha_f, phi_f);
        k_f.setZ(mp_kz_function->evaluate(alpha_f));

        double total_intensity = 0.0;
        for (size_t i=0; i<diffuse_terms.size(); ++i) {
            DiffuseFormFactorTerm *p_diffuse_term = diffuse_terms[i];
            complex_t amplitude(0.0, 0.0);
            double intensity = 0.0;
            for (size_t j=0; j<p_diffuse_term->m_form_factors.size(); ++j) {
                complex_t amp = p_diffuse_term->m_form_factors[j]->evaluate(m_ki, k_f, -m_alpha_i, alpha_f);
                amplitude += p_diffuse_term->m_probabilities[j]*amp;
                intensity += p_diffuse_term->m_probabilities[j]*std::norm(amp);
            }
            total_intensity += p_diffuse_term->m_factor*(intensity - std::norm(amplitude));
        }
        next() = total_intensity*wavevector_scattering_factor*wavevector_scattering_factor;
    }

    for (size_t i=0; i<diffuse_terms.size(); ++i) delete diffuse_terms[i];
}

void DiffuseDWBASimulation::addParticleInfo(DiffuseParticleInfo *p_info)
{
    m_np_infos.push_back(p_info);
}

void DiffuseDWBASimulation::rescaleAbundances(double factor)
{
    size_t number_of_nps = m_np_infos.size();
    for (size_t np_index=0; np_index<number_of_nps; ++np_index) {
        m_np_infos[np_index]->scaleAbundance(factor);
    }
}

void DiffuseDWBASimulation::initDiffuseFormFactorTerms(
        std::vector<DiffuseFormFactorTerm*>& terms, size_t nbr_heights,
        size_t samples_per_particle)
{
    size_t number_of_nps = m_np_infos.size();
    for (size_t i=0; i<number_of_nps; ++i) {
        DiffuseParticleInfo *p_diff_info = m_np_infos[i];
        Particle *p_particle = p_diff_info->getParticle()->clone();
        double total_particle_density = p_diff_info->getNumberPerMeso();
        double density_per_height_per_particle = total_particle_density/nbr_heights;
        for (size_t j=0; j<nbr_heights; ++j) {
            DiffuseFormFactorTerm *p_diffuse_term = new DiffuseFormFactorTerm;
            p_diffuse_term->m_factor = density_per_height_per_particle;
            double depth = p_diff_info->getDepth() - (double)j*p_diff_info->getHeightRange()/(nbr_heights-1.0);
            std::vector<IFormFactor *> form_factors;
            p_diff_info->getParticle()->getSimpleFormFactor()->createDistributedFormFactors(
                    form_factors, p_diffuse_term->m_probabilities, samples_per_particle);
            for (size_t ff_index=0; ff_index<form_factors.size(); ++ff_index) {
                p_particle->setSimpleFormFactor(form_factors[ff_index]);
                IFormFactor *ff_particle = p_particle->createFormFactor();
                FormFactorDWBAConstZ *p_dwba_z = new FormFactorDWBAConstZ(ff_particle, depth);
//                p_dwba_z->setReflectionFunction(*mp_R_function);
//                p_dwba_z->setTransmissionFunction(*mp_T_function);
                p_dwba_z->setReflectionTransmissionFunction(*mp_RT_function);

                p_diffuse_term->m_form_factors.push_back(p_dwba_z);
            }
            terms.push_back(p_diffuse_term);
        }
        delete p_particle;
    }
}

DiffuseDWBASimulation::DiffuseFormFactorTerm::~DiffuseFormFactorTerm()
{
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        delete m_form_factors[i];
    }
}
