// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/Crystal.cpp
//! @brief     Implements class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/FormFactorCrystal.h"
#include "Sample/Particle/HomogeneousRegion.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Particle/SlicedParticle.h"

Crystal::Crystal(const IParticle& basis, const Lattice& lattice)
    : m_lattice(lattice), m_position_variance(0.0)
{
    setName("Crystal");
    m_basis.reset(basis.clone());
    m_basis->registerAbundance(false);
    registerChild(m_basis.get());
    registerChild(&m_lattice);
}

Crystal::~Crystal() = default;

Crystal* Crystal::clone() const
{
    Crystal* p_new = new Crystal(*m_basis, m_lattice);
    p_new->setPositionVariance(m_position_variance);
    return p_new;
}

IFormFactor* Crystal::createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                            const IRotation* p_rotation,
                                            const kvector_t& translation) const
{
    Lattice transformed_lattice = transformedLattice(p_rotation);
    std::unique_ptr<IParticle> P_basis_clone{m_basis->clone()};
    if (p_rotation)
        P_basis_clone->rotate(*p_rotation);
    P_basis_clone->translate(translation);
    const std::unique_ptr<IFormFactor> P_basis_ff(P_basis_clone->createFormFactor());
    return new FormFactorCrystal(transformed_lattice, *P_basis_ff, meso_crystal_form_factor,
                                 m_position_variance);
}

std::vector<HomogeneousRegion> Crystal::homogeneousRegions() const
{
    std::vector<HomogeneousRegion> result;
    double unit_cell_volume = m_lattice.unitCellVolume();
    if (unit_cell_volume <= 0)
        return {};
    auto particles = m_basis->decompose();
    ZLimits limits;
    for (auto p_particle : particles) {
        auto sliced_particle = p_particle->createSlicedParticle(limits);
        result.insert(result.end(), sliced_particle.m_regions.begin(),
                      sliced_particle.m_regions.end());
    }
    for (auto& region : result)
        region.m_volume /= unit_cell_volume;
    return result;
}

Lattice Crystal::transformedLattice(const IRotation* p_rotation) const
{
    if (p_rotation)
        return m_lattice.transformed(p_rotation->getTransform3D());
    else
        return m_lattice;
}

std::vector<const INode*> Crystal::getChildren() const
{
    return std::vector<const INode*>() << m_basis << &m_lattice;
}

Crystal::Crystal(IParticle* p_basis, const Lattice& lattice)
    : m_lattice(lattice), m_position_variance(0.0)
{
    setName("Crystal");
    m_basis.reset(p_basis);
    registerChild(m_basis.get());
    registerChild(&m_lattice);
}
