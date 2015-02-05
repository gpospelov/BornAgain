// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCrystal.cpp
//! @brief     Implements class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCrystal.h"

FormFactorCrystal::FormFactorCrystal(
        const Crystal& p_crystal,
        const IFormFactor& meso_crystal_form_factor,
        const IMaterial &material, complex_t wavevector_scattering_factor)
: m_lattice(p_crystal.getTransformedLattice())
, m_wavevector_scattering_factor(wavevector_scattering_factor)
, mp_ambient_material(material.clone())
, m_max_rec_length(0.0)
{
    setName("FormFactorCrystal");
    mp_lattice_basis = p_crystal.getLatticeBasis()->clone();
    mp_basis_form_factor = mp_lattice_basis->createFormFactor(
            m_wavevector_scattering_factor);
    if (p_crystal.getTransform()) {
        mp_meso_form_factor = new FormFactorDecoratorTransformation(
                meso_crystal_form_factor.clone(),
                *p_crystal.getTransform() );
    } else {
        mp_meso_form_factor = meso_crystal_form_factor.clone();
    }
    setAmbientMaterial(material);
    calculateLargestReciprocalDistance();
}

FormFactorCrystal::~FormFactorCrystal()
{
    delete mp_lattice_basis;
    delete mp_basis_form_factor;
    delete mp_meso_form_factor;
    delete mp_ambient_material;
}

FormFactorCrystal* FormFactorCrystal::clone() const
{
    Crystal np_crystal(*mp_lattice_basis, m_lattice);
    FormFactorCrystal *result = new FormFactorCrystal(np_crystal,
            *mp_meso_form_factor, *mp_ambient_material,
            m_wavevector_scattering_factor);
    result->setName(getName());
    return result;
}

void FormFactorCrystal::setAmbientMaterial(const IMaterial& material)
{
    mp_lattice_basis->setAmbientMaterial(material);
    mp_basis_form_factor->setAmbientMaterial(material);
}

complex_t FormFactorCrystal::evaluate_for_q(const cvector_t& q) const
{
    (void)q;
    throw LogicErrorException("evaluate_for_q() should never be called"
            " explicitly for FormFactorCrystal");
}

complex_t FormFactorCrystal::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    // construct a real reciprocal vector
    cvector_t q_bin_lower = k_i - k_f_bin.m_q_lower;
    cvector_t q_bin_upper = k_i - k_f_bin.m_q_upper;
    Bin1DCVector q_bin = Bin1DCVector(q_bin_lower, q_bin_upper);

    cvector_t q = q_bin.getMidPoint();
    kvector_t q_real(q.x().real(), q.y().real(), q.z().real());
    cvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 2.1*m_max_rec_length;

    // retrieve nearest reciprocal lattice vectors
    m_lattice.computeReciprocalLatticeVectorsWithinRadius(q_real, radius);
    const KVectorContainer& rec_vectors = m_lattice.getKVectorContainer();

    // perform convolution on these lattice vectors
    complex_t result(0.0, 0.0);
    for (KVectorContainer::const_iterator it = rec_vectors.begin();
            it != rec_vectors.end(); ++it) {
        cvector_t q_i((*it).x(), (*it).y(), (*it).z());
        Bin1DCVector min_q_i_zero_bin(-q_i, -q_i);
        Bin1DCVector q_i_min_q(q_i - q_bin.m_q_lower, q_i - q_bin.m_q_upper);
        complex_t basis_factor = mp_basis_form_factor->evaluate(
                k_zero, min_q_i_zero_bin, alpha_f_bin);
        complex_t meso_factor = mp_meso_form_factor->evaluate(
                k_zero, q_i_min_q, alpha_f_bin);
        result += basis_factor*meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result/volume;
}

Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin, const Bin1D &phi_f_bin) const
{
    // construct a real reciprocal vector
    cvector_t q_bin_lower = k_i - k_f_bin.m_q_lower;
    cvector_t q_bin_upper = k_i - k_f_bin.m_q_upper;
    Bin1DCVector q_bin =  Bin1DCVector(q_bin_lower, q_bin_upper);

    cvector_t q = q_bin.getMidPoint();
    kvector_t q_real(q.x().real(), q.y().real(), q.z().real());
    cvector_t k_zero;
    // calculate the used radius in function of the reciprocal lattice scale
    double radius = 2.1*m_max_rec_length;

    // retrieve nearest reciprocal lattice vectors
    m_lattice.computeReciprocalLatticeVectorsWithinRadius(q_real, radius);
    const KVectorContainer& rec_vectors = m_lattice.getKVectorContainer();

    // perform convolution on these lattice vectors
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (KVectorContainer::const_iterator it = rec_vectors.begin();
            it != rec_vectors.end(); ++it) {
        cvector_t q_i((*it).x(), (*it).y(), (*it).z());
        Bin1DCVector min_q_i_zero_bin(-q_i, -q_i);
        Bin1DCVector q_i_min_q(q_i - q_bin.m_q_lower, q_i - q_bin.m_q_upper);
        Eigen::Matrix2cd basis_factor = mp_basis_form_factor->
                evaluatePol(k_zero, min_q_i_zero_bin, alpha_f_bin, phi_f_bin);
        complex_t meso_factor = mp_meso_form_factor->evaluate(
                k_zero, q_i_min_q, alpha_f_bin);
        result += basis_factor*meso_factor;
    }
    // the transformed delta train gets a factor of (2pi)^3/V, but the (2pi)^3
    // is canceled by the convolution of Fourier transforms :
    double volume = m_lattice.getVolume();
    return result/volume;
}

double FormFactorCrystal::getVolume() const
{
    return mp_meso_form_factor->getVolume();
}

void FormFactorCrystal::calculateLargestReciprocalDistance()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_max_rec_length = std::max(M_PI/a1.mag(), M_PI/a2.mag());
    m_max_rec_length = std::max(m_max_rec_length, M_PI/a3.mag());
}


