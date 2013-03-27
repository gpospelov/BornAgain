// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleInfo.h
//! @brief     Defines class ParticleInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H

#include "ICompositeSample.h"
#include "Particle.h"
#include "Transform3D.h"

//! Holds additional information about particle (used in ParticleDecoration).

class ParticleInfo : public ICompositeSample
{
 public:
    ParticleInfo(Particle *p_particle,
                 Geometry::Transform3D *transform=0,
                 double depth=0, double abundance=0);
    ParticleInfo(const Particle& p_particle,
                 const Geometry::Transform3D& transform,
                 double depth=0, double abundance=0);
    virtual ~ParticleInfo();

    virtual ParticleInfo *clone() const;

    //! Returns particle.
    const Particle *getParticle() const { return mp_particle; }

    //! Returns transformation.
    const Geometry::Transform3D *getTransform3D() const { return mp_transform; }

    //! Sets transformation.
    void setTransform(const Geometry::Transform3D &transform) {
        delete mp_transform;
        mp_transform = new Geometry::Transform3D(transform);
    }

    //! Returns depth.
    double getDepth() const { return m_depth; }

    //! Sets depth.
    void setDepth(double depth) { m_depth = depth; }

    //! Returns abundance.
    double getAbundance() const { return m_abundance; }

    //! Sets abundance.
    void setAbundance(double abundance) { m_abundance = abundance; }

 protected:
    virtual void init_parameters();

    Particle *mp_particle;
    Geometry::Transform3D *mp_transform;
    double m_depth;
    double m_abundance;
};

#endif /* PARTICLEINFO_H */
