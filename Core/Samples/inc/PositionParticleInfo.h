// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/PositionParticleInfo.h
//! @brief     Defines class PositionParticleInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef POSITIONPARTICLEINFO_H_
#define POSITIONPARTICLEINFO_H_

#include "ParticleInfo.h"

//! Holds additional information about particle and position
//! (used in IsGISAXSMorphologyFileDecoration)

class PositionParticleInfo : public ParticleInfo
{
public:
    //! constructor for positioned particle info having transformation property, position and abundance
    PositionParticleInfo(Particle *p_particle,
            Geometry::Transform3D *p_transform, kvector_t position,
            double abundance=0);

    PositionParticleInfo(const Particle &particle,
            const Geometry::Transform3D &transform, kvector_t position,
            double abundance=0);

    PositionParticleInfo(Particle *p_particle, kvector_t position,
            double abundance=0);

    PositionParticleInfo(const Particle &particle, kvector_t position,
            double abundance=0);


    virtual ~PositionParticleInfo();

    //! clone particle info
    virtual PositionParticleInfo *clone() const;

    //! return particle
    const Particle *getParticle() const { return mp_particle; }

    //! return particle position
    kvector_t getPosition() const { return kvector_t(m_pos_x, m_pos_y, -m_depth); }

    //! set particle position
    void setPosition(kvector_t position);

protected:
    PositionParticleInfo &operator=(const PositionParticleInfo &right);
    PositionParticleInfo(const PositionParticleInfo &source);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
    double m_pos_x;
    double m_pos_y;
};

#endif /* POSITIONPARTICLEINFO_H_ */
