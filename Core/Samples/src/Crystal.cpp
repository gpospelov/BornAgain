// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Crystal.cpp
//! @brief     Implements class Crystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Crystal.h"
#include "FormFactors.h"
#include "Units.h"
#include "MathFunctions.h"
#include "DiffuseParticleInfo.h"

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

std::vector<DiffuseParticleInfo*>* Crystal::createDiffuseParticleInfo(
        const ParticleInfo& parent_info) const
{
    std::vector<DiffuseParticleInfo *> *p_result =
            new std::vector<DiffuseParticleInfo *>(
            mp_lattice_basis->createDiffuseParticleInfos());
    if (p_result->empty()) return p_result;

    double parent_volume =
        parent_info.getParticle()->getSimpleFormFactor()->getVolume();
    double parent_height =
        parent_info.getParticle()->getSimpleFormFactor()->getHeight();
    double parent_depth =
        parent_info.getDepth();

    double primitive_cell_volume = m_lattice.getVolume();
    double nbr_unit_cells = parent_volume/primitive_cell_volume;

    for (size_t i=0; i<p_result->size(); ++i) {
        DiffuseParticleInfo *p_info = (*p_result)[i];
        p_info->setDepth(parent_depth);
        p_info->setNumberPerMeso(nbr_unit_cells*p_info->getNumberPerMeso());
        p_info->setHeightRange(parent_height);
    }

    return p_result;
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
