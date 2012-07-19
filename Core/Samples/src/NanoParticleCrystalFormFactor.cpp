#include "NanoParticleCrystalFormFactor.h"
#include "Units.h"

NanoParticleCrystalFormFactor::NanoParticleCrystalFormFactor(
        const NanoParticleCrystal* p_crystal,
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index)
: m_ambient_refractive_index(ambient_refractive_index)
, m_max_rec_length(0.0)
{
    m_lattice = p_crystal->getLattice();
    mp_nano_particle = p_crystal->createNanoParticle();
    mp_meso_form_factor = meso_crystal_form_factor.clone();
    setAmbientRefractiveIndex(ambient_refractive_index);
    calculateLargestReciprocalDistance();
}

NanoParticleCrystalFormFactor::~NanoParticleCrystalFormFactor()
{
    delete mp_nano_particle;
    delete mp_meso_form_factor;
}

NanoParticleCrystalFormFactor* NanoParticleCrystalFormFactor::clone() const
{
    NanoParticleCrystal np_crystal(*mp_nano_particle, m_lattice);
    NanoParticleCrystalFormFactor *p_new = new NanoParticleCrystalFormFactor(&np_crystal,
            *mp_meso_form_factor, m_ambient_refractive_index);
    return p_new;
}

void NanoParticleCrystalFormFactor::setAmbientRefractiveIndex(
        complex_t refractive_index)
{
    mp_nano_particle->setAmbientRefractiveIndex(refractive_index);
}

complex_t NanoParticleCrystalFormFactor::evaluate_for_complex_qz(kvector_t q,
        complex_t qz) const
{
    // construct a real reciprocal vector
    kvector_t q_real(q.x(), q.y(), qz.real());
    kvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 2*m_max_rec_length;
    // retrieve nearest reciprocal lattice vectors
    std::vector<kvector_t> rec_vectors =
            m_lattice.getReciprocalLatticeVectorsWithinRadius(q_real, radius);
    // perform convolution on these lattice vectors
    std::cout << "Number of reciprocal vectors used for convolution: " << rec_vectors.size() << std::endl;
    complex_t result(0.0, 0.0);
    IFormFactor *p_basis_form_factor = mp_nano_particle->createFormFactor();
    for (std::vector<kvector_t>::const_iterator it = rec_vectors.begin(); it != rec_vectors.end(); ++it) {
        kvector_t q_i = *it;
        kvector_t q_min_q_i = q_real - q_i;
        complex_t q_min_q_i_z = qz - q_i.z();
        result += p_basis_form_factor->evaluate(q_i, k_zero)
                *mp_meso_form_factor->evaluateForComplexkz(q_min_q_i, k_zero, q_min_q_i_z, complex_t(0.0, 0.0));
    }
    delete p_basis_form_factor;
    // the transformed delta train gets a factor of (2pi)^3 :
    double pi3 = M_PI*M_PI*M_PI;
    return 8.0*pi3*result;
}

void NanoParticleCrystalFormFactor::calculateLargestReciprocalDistance()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI/a1.mag(), M_PI/a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI/a3.mag());
}
