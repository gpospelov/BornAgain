#include "FormFactorCrystal.h"
#include "Units.h"

FormFactorCrystal::FormFactorCrystal(
        const Crystal* p_crystal,
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index)
: m_lattice(p_crystal->getLattice())
, m_ambient_refractive_index(ambient_refractive_index)
, m_max_rec_length(0.0)
{
    mp_particle = p_crystal->createBasis();
    mp_basis_form_factor = mp_particle->createFormFactor();
    mp_meso_form_factor = meso_crystal_form_factor.clone();
    setAmbientRefractiveIndex(ambient_refractive_index);
    calculateLargestReciprocalDistance();
}

FormFactorCrystal::~FormFactorCrystal()
{
    delete mp_particle;
    delete mp_basis_form_factor;
    delete mp_meso_form_factor;
}

FormFactorCrystal* FormFactorCrystal::clone() const
{
    Crystal np_crystal(*mp_particle, m_lattice);
    FormFactorCrystal *p_new = new FormFactorCrystal(&np_crystal,
            *mp_meso_form_factor, m_ambient_refractive_index);
    return p_new;
}

void FormFactorCrystal::setAmbientRefractiveIndex(
        complex_t refractive_index)
{
    mp_particle->setAmbientRefractiveIndex(refractive_index);
    mp_basis_form_factor->setAmbientRefractiveIndex(refractive_index);
}

complex_t FormFactorCrystal::evaluate_for_q(const cvector_t &q) const
{
    // construct a real reciprocal vector
    kvector_t q_real(q.x().real(), q.y().real(), q.z().real());
    cvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 1.1*m_max_rec_length;
    // retrieve nearest reciprocal lattice vectors
    std::vector<kvector_t> rec_vectors =
            m_lattice.getReciprocalLatticeVectorsWithinRadius(q_real, radius);
    // perform convolution on these lattice vectors
    complex_t result(0.0, 0.0);
    for (std::vector<kvector_t>::const_iterator it = rec_vectors.begin(); it != rec_vectors.end(); ++it) {
        cvector_t q_i((*it).x(), (*it).y(), (*it).z());
        cvector_t q_min_q_i = q - q_i;
        complex_t basis_factor = mp_basis_form_factor->evaluate(q_i, k_zero, 0.0, 0.0);
        complex_t meso_factor = mp_meso_form_factor->evaluate(q_min_q_i, k_zero, 0.0, 0.0);
        result += basis_factor*meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V :
    double pi3 = M_PI*M_PI*M_PI;
    double volume = m_lattice.getVolume();
    return 8.0*pi3*result/volume;
}

void FormFactorCrystal::calculateLargestReciprocalDistance()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI/a1.mag(), M_PI/a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI/a3.mag());
}
