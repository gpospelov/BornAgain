// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CRYSTAL_H_
#define CRYSTAL_H_

#include "IClusteredParticles.h"
#include "Particle.h"
#include "Lattice.h"
#include "LatticeBasis.h"

//! A crystal structure with a form factor as a basis.

class Crystal : public IClusteredParticles
{
 public:
    Crystal(const LatticeBasis& lattice_basis, const Lattice& lattice);
    ~Crystal();

    virtual Crystal *clone() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const { p_visitor->visit(this); }

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    { mp_lattice_basis->setAmbientRefractiveIndex(refractive_index); }

    virtual IFormFactor *createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index) const;

    Lattice getLattice() const { return m_lattice; }
    Particle *createBasis() const { return mp_lattice_basis->clone(); }

    const LatticeBasis *getLatticeBasis() const { return mp_lattice_basis; }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(
            const ParticleInfo& parent_info) const;

 private:
    Lattice m_lattice;
    LatticeBasis *mp_lattice_basis;
    double m_dw_factor;
};

#endif /* CRYSTAL_H_ */


