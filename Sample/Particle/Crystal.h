// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H
#define BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H

#include "Sample/Scattering/ISample.h"
#include "Sample/Lattice/Lattice.h"

class IFormFactor;
class IRotation;
struct HomogeneousRegion;

//! A crystal structure with a ParticleComposition as a basis.
//! Used in MesoCrystal, where it is given an outer shape.
//! @ingroup samples

class Crystal : public ISample
{
public:
    Crystal(const IParticle& basis, const Lattice& lattice);
    ~Crystal();

    Crystal* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                       const IRotation* p_rotation,
                                       const kvector_t& translation) const;

    std::vector<HomogeneousRegion> homogeneousRegions() const;

    Lattice transformedLattice(const IRotation* p_rotation = nullptr) const;

    void setPositionVariance(double position_variance) { m_position_variance = position_variance; }

    std::vector<const INode*> getChildren() const override final;

private:
    Crystal(IParticle* p_basis, const Lattice& lattice);

    Lattice m_lattice;
    std::unique_ptr<IParticle> m_basis;
    double m_position_variance;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H
