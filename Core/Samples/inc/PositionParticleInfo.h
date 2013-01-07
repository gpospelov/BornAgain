#ifndef POSITIONPARTICLEINFO_H_
#define POSITIONPARTICLEINFO_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   PositionParticleInfo.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jan 7, 2013

#include "ParticleInfo.h"

//- -------------------------------------------------------------------
//! @class PositionParticleInfo
//! @brief holds additional information about particle and position
//! (used in IsGISAXSMorphologyFileDecoration)
//- -------------------------------------------------------------------
class PositionParticleInfo : public ParticleInfo
{
public:
    //! constructor for positioned particle info having transformation property, position and abundance
    PositionParticleInfo(Particle *p_particle, Geometry::Transform3D *p_transform, kvector_t position, double abundance=0);
    PositionParticleInfo(Particle *p_particle, kvector_t position, double abundance=0);

    virtual ~PositionParticleInfo();

    //! clone particle info
    virtual PositionParticleInfo *clone() const;

    //! return particle
    const Particle *getParticle() const { return mp_particle; }

    //! return particle position
    kvector_t getPosition() { return m_position; }

    //! set particle position
    void setPosition(kvector_t position) { m_position = position; }

    //! set particle depth
    virtual void setDepth(double depth);

protected:
    PositionParticleInfo &operator=(const PositionParticleInfo &right);
    PositionParticleInfo(const PositionParticleInfo &source);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    kvector_t m_position;
};


#endif /* POSITIONPARTICLEINFO_H_ */
