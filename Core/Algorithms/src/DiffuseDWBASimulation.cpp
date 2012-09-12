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
    m_dwba_intensity.resetIndex();
    complex_t k_iz = -mp_kz_function->evaluate(-m_alpha_i);
    size_t number_of_nps = m_np_infos.size();
    std::vector<IFormFactor *> form_factors;
    // collect all particle formfactors and create dwba formfactors for these
    for (size_t np_index=0; np_index<number_of_nps; ++np_index) {
        ParticleInfo *p_np_info = m_np_infos[np_index];
        Particle *p_np = p_np_info->getParticle()->clone();
        double depth = p_np_info->getDepth();

        p_np->setAmbientRefractiveIndex(m_refractive_index);
        IFormFactor *ff_particle = p_np->createFormFactor();
        // TODO: include geometric transformation?
//        IFormFactor  *ff_transformed(0);
//        if(transform) {
//            ff_transformed = new FormFactorDecoratorTransformation(ff_particle, new Geometry::Transform3D(*transform));
//        } else{
//            ff_transformed = ff_particle;
//        }

        FormFactorDWBAConstZ *p_dwba_z = new FormFactorDWBAConstZ(ff_particle, depth);
        p_dwba_z->setReflectionFunction(*mp_R_function);
        p_dwba_z->setTransmissionFunction(*mp_T_function);

        form_factors.push_back(p_dwba_z);
    }

    double wavevector_scattering_factor = M_PI/getWaveLength()/getWaveLength();
    while (m_dwba_intensity.hasNext()) {
        complex_t amplitude(0.0, 0.0);
        double intensity = 0.0;
        for (size_t i=0; i<form_factors.size(); ++i) {
            double phi_f = m_dwba_intensity.getCurrentValueOfAxis<double>("phi_f");
            double alpha_f = m_dwba_intensity.getCurrentValueOfAxis<double>("alpha_f");
            double weight = m_np_infos[i]->getAbundance();
            if (alpha_f<0) {
                m_dwba_intensity.next() = 0.0;
                continue;
            }
            cvector_t k_f;
            k_f.setLambdaAlphaPhi(getWaveLength(), alpha_f, phi_f);
            k_f.setZ(mp_kz_function->evaluate(alpha_f));
            complex_t amp = form_factors[i]->evaluate(m_ki, k_f, -m_alpha_i, alpha_f);
            amplitude += weight*amp;
            intensity += weight*std::norm(amp);
        }
        m_dwba_intensity.next() = m_surface_density*wavevector_scattering_factor*wavevector_scattering_factor
                *(intensity - std::norm(amplitude));
    }

    for (size_t i=0; i<form_factors.size(); ++i) delete form_factors[i];

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
