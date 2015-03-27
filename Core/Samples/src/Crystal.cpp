// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Crystal.cpp
//! @brief     Implements class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Crystal.h"
#include "FormFactors.h"
#include "Units.h"
#include "MathFunctions.h"

#include <boost/scoped_ptr.hpp>

Crystal::Crystal(const ParticleComposition& lattice_basis,
        const Lattice& lattice)
: m_lattice(lattice)
, m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = lattice_basis.clone();
    registerChild(mp_lattice_basis);
}

Crystal::~Crystal()
{
    delete mp_lattice_basis;
}

Crystal* Crystal::clone() const
{
    Crystal *p_new = new Crystal(*mp_lattice_basis, m_lattice);
    p_new->setDWFactor(m_dw_factor);
    if (mP_rotation.get()) {
        p_new->mP_rotation.reset(mP_rotation->clone());
    }
    return p_new;
}

Crystal* Crystal::cloneInvertB() const
{
    Crystal *p_new = new Crystal(mp_lattice_basis->cloneInvertB(), m_lattice);
    p_new->setDWFactor(m_dw_factor);
    p_new->setName(getName() + "_inv");
    return p_new;
}

IFormFactor* Crystal::createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        const IMaterial &p_ambient_material,
        complex_t wavevector_scattering_factor) const
{
    FormFactorCrystal *p_ff_crystal =
        new FormFactorCrystal(*this, meso_crystal_form_factor,
                p_ambient_material, wavevector_scattering_factor);
    if (m_dw_factor>0.0) {
        return new FormFactorDecoratorDebyeWaller(p_ff_crystal, m_dw_factor);
    }
    return p_ff_crystal;
}

Lattice Crystal::getTransformedLattice() const
{
    if (mP_rotation.get()) {
        return m_lattice.createTransformedLattice(*mP_rotation);
    } else {
        return m_lattice;
    }
}

void Crystal::applyTransformation(const IRotation& rotation)
{
    if (mP_rotation.get()) {
        IRotation *total_rotation = CreateProduct(rotation, *mP_rotation);
        mP_rotation.reset(total_rotation);
    }
    else {
        mP_rotation.reset(rotation.clone());
    }
    applyTransformationToSubParticles(rotation);
}

Crystal::Crystal(ParticleComposition* p_lattice_basis, const Lattice& lattice)
: m_lattice(lattice)
, m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = p_lattice_basis;
    registerChild(mp_lattice_basis);
}

void Crystal::applyTransformationToSubParticles(const IRotation& rotation)
{
    mp_lattice_basis->applyTransformation(rotation);
}
