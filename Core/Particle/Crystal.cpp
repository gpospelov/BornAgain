// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Crystal.cpp
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
#include "BornAgainNamespace.h"
#include "FormFactorCrystal.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "Particle.h"
#include "ParticleComposition.h"

Crystal::Crystal(const IParticle& lattice_basis, const Lattice& lattice)
    : m_lattice(lattice), m_dw_factor(0.0)
{
    setName(BornAgain::CrystalType);
    mp_lattice_basis.reset(lattice_basis.clone());
    registerChild(mp_lattice_basis.get());
}

Crystal::~Crystal()
{
}

Crystal* Crystal::clone() const
{
    Crystal* p_new = new Crystal(*mp_lattice_basis, m_lattice);
    p_new->setDWFactor(m_dw_factor);
    return p_new;
}

IFormFactor* Crystal::createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                            const IRotation* p_rotation,
                                            const kvector_t& translation) const
{
    Lattice transformed_lattice = transformedLattice(p_rotation);
    std::unique_ptr<IParticle> P_basis_clone { mp_lattice_basis->clone() };
    if (p_rotation)
        P_basis_clone->applyRotation(*p_rotation);
    P_basis_clone->applyTranslation(translation);
    const std::unique_ptr<IFormFactor> P_basis_ff(P_basis_clone->createFormFactor());
    std::unique_ptr<FormFactorCrystal> P_ff_crystal(
        new FormFactorCrystal(transformed_lattice, *P_basis_ff, meso_crystal_form_factor));
    if (m_dw_factor > 0.0)
        return new FormFactorDecoratorDebyeWaller(*P_ff_crystal, m_dw_factor);
    return P_ff_crystal.release();
}

std::vector<HomogeneousRegion> Crystal::homogeneousRegions() const
{
    std::vector<HomogeneousRegion> result;
    double unit_cell_volume = m_lattice.volume();
    if (unit_cell_volume <= 0)
        return {};
    auto particles = mp_lattice_basis->decompose();
    ZLimits limits;
    for (auto p_particle : particles)
    {
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
        return m_lattice.createTransformedLattice(p_rotation->getTransform3D());
    else
        return m_lattice;
}

std::vector<const INode*> Crystal::getChildren() const
{
    return std::vector<const INode*>() << mp_lattice_basis;
}

Crystal::Crystal(IParticle* p_lattice_basis, const Lattice& lattice)
    : m_lattice(lattice), m_dw_factor(0.0)
{
    setName(BornAgain::CrystalType);
    mp_lattice_basis.reset(p_lattice_basis);
    registerChild(mp_lattice_basis.get());
}
