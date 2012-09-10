#ifndef CRYSTAL_H_
#define CRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Crystal.h
//! @brief  Definition of Crystal class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "IClusteredParticles.h"
#include "Particle.h"
#include "Lattice.h"
#include "LatticeBasis.h"

//- -------------------------------------------------------------------
//! @class Crystal
//! @brief Definition of a crystal structure with a form factor as a basis
//- -------------------------------------------------------------------
class Crystal : public IClusteredParticles
{
public:
     //! @brief constructor
     //! @param lattice_basis  the basis which is repeated in the lattice structure
     //! @param lattice  the crystal lattice, described by its basis vectors
    Crystal(const LatticeBasis &lattice_basis, const Lattice &lattice);
    ~Crystal();

    virtual Crystal *clone() const;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        mp_lattice_basis->setAmbientRefractiveIndex(refractive_index);
    }

    virtual IFormFactor *createTotalFormFactor(const IFormFactor &meso_crystal_form_factor
            , complex_t ambient_refractive_index) const;

    Lattice getLattice() const { return m_lattice; }
    Particle *createBasis() const { return mp_lattice_basis->clone(); }

    const LatticeBasis *getLatticeBasis() const { return mp_lattice_basis; }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

     virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(double depth, double weight,
                const Geometry::Transform3D &transform, double meso_volume) const;

private:
    Lattice m_lattice;
    LatticeBasis *mp_lattice_basis;
    double m_dw_factor;
};


#endif /* CRYSTAL_H_ */
