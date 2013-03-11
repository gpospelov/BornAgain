#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ParticleInfo.h
//! @brief  Definition of Layer class
//! @author Scientific Computing Group at FRM II
//! @date   18.07.2012

#include "ICompositeSample.h"
#include "Particle.h"
#include "Transform3D.h"

//- -------------------------------------------------------------------
//! @class ParticleInfo
//! @brief holds additional information about particle (used in ParticleDecoration)
//- -------------------------------------------------------------------
class ParticleInfo : public ICompositeSample
{
public:
    //! constructor for particle info having transformation property and abundance
    ParticleInfo(Particle *p_particle, Geometry::Transform3D *transform=0, double depth=0, double abundance=0);
    ParticleInfo(const Particle &p_particle, const Geometry::Transform3D &transform, double depth=0, double abundance=0);

    virtual ~ParticleInfo();

    //! clone particle info
    virtual ParticleInfo *clone() const;

    //! return particle
    const Particle *getParticle() const { return mp_particle; }

    //! return particle transformation
    const Geometry::Transform3D *getTransform3D() const { return mp_transform; }

    //! set particle transformation
    void setTransform(const Geometry::Transform3D &transform) {
        delete mp_transform;
        mp_transform = new Geometry::Transform3D(transform);
    }

    //! return particle depth
    double getDepth() const { return m_depth;}

    //! set particle depth
    void setDepth(double depth) { m_depth = depth; }

    //! return particle abundance
    double getAbundance() const { return m_abundance; }

    //! set particle abundance
    void setAbundance(double abundance) { m_abundance = abundance; }

protected:
//    ParticleInfo &operator=(const ParticleInfo &right);
//    ParticleInfo(const ParticleInfo &source);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    Particle *mp_particle;
    Geometry::Transform3D *mp_transform;
    double m_depth;
    double m_abundance;
};


#endif // PARTICLEINFO_H
