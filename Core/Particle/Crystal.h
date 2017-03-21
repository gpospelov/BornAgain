// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "IClusteredParticles.h"
#include "Lattice.h"
#include "Vectors3D.h"

class Particle;
class ParticleComposition;

//! A crystal structure with a ParticleComposition as a basis.
//! Used in MesoCrystal, where it is given an outer shape.
//! @ingroup samples

class BA_CORE_API_ Crystal : public IClusteredParticles
{
public:
    Crystal(const ParticleComposition& lattice_basis, const Lattice& lattice);
    ~Crystal();

    Crystal* clone() const override final;
    Crystal* cloneInvertB() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        const IRotation* p_rotation, const kvector_t& translation) const override final;

    std::vector<HomogeneousRegion> homogeneousRegions() const override final;

    Lattice transformedLattice(const IRotation* p_rotation) const;

    const ParticleComposition* latticeBasis() const { return mp_lattice_basis.get(); }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

    std::vector<const INode*> getChildren() const override final;

private:
    Crystal(ParticleComposition* p_lattice_basis, const Lattice& lattice);

    Lattice m_lattice;
    std::unique_ptr<ParticleComposition> mp_lattice_basis;
    double m_dw_factor;
};

#endif // CRYSTAL_H
