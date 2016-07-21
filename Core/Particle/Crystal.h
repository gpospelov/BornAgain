// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particles/Crystal.h
//! @brief     Declares class Crystal.
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

#include "IClusteredParticles.h" // inheriting from
#include "Lattice.h"
#include "Particle.h"
#include "ParticleComposition.h"


//! @class Crystal
//! @ingroup samples
//! @brief A crystal structure with a form factor as a basis.

class BA_CORE_API_ Crystal : public IClusteredParticles
{
public:
    Crystal(const ParticleComposition& lattice_basis, const Lattice& lattice);
    virtual ~Crystal();

    virtual Crystal* clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual Crystal* cloneInvertB() const;

    virtual void accept(ISampleVisitor* visitor) const;

    virtual void setAmbientMaterial(const IMaterial& material) {
        mp_lattice_basis->setAmbientMaterial(material); }

    virtual const IMaterial* getAmbientMaterial() const {
        return mp_lattice_basis->getAmbientMaterial(); }

    virtual IFormFactor* createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        const IRotation* p_rotation, kvector_t translation) const;

    Lattice getTransformedLattice(const IRotation* p_rotation) const;

    const ParticleComposition* getLatticeBasis() const { return mp_lattice_basis; }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

private:
    //! Private constructor
    Crystal(ParticleComposition* p_lattice_basis, const Lattice& lattice);

    Lattice m_lattice;
    ParticleComposition* mp_lattice_basis;
    double m_dw_factor;
};

#endif // CRYSTAL_H
