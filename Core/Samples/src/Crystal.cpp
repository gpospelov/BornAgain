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

Crystal::Crystal(const LatticeBasis& lattice_basis,
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
    if (mP_transform.get()) {
        p_new->mP_transform.reset(mP_transform->clone());
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
    if (mP_transform.get()) {
        return m_lattice.createTransformedLattice(*mP_transform);
    } else {
        return m_lattice;
    }
}

void Crystal::applyTransformation(const Geometry::Transform3D& transform)
{
    Geometry::Transform3D total_transformation;
    if (mP_transform.get()) {
        total_transformation = transform * (*mP_transform);
    }
    else {
        total_transformation = transform;
    }
    mP_transform.reset(total_transformation.clone());
    applyTransformationToSubParticles(transform);
}

Crystal::Crystal(LatticeBasis* p_lattice_basis, const Lattice& lattice)
: m_lattice(lattice)
, m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = p_lattice_basis;
    registerChild(mp_lattice_basis);
}

void Crystal::applyTransformationToSubParticles(
        const Geometry::Transform3D& transform)
{
    mp_lattice_basis->applyTransformation(transform);
}
