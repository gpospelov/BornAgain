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

//! Enhances ParticleInfo by position in x and y.

//! Used in IsGISAXSMorphologyFileDecoration.
//! Note that position in z ("depth") is inherited from ParticleInfo. 
//!
class PositionParticleInfo : public ParticleInfo
{
 public:
    PositionParticleInfo(
        Particle *p_particle, Geometry::Transform3D *p_transform,
        kvector_t position, double abundance=0);

    PositionParticleInfo(
        const Particle& particle, const Geometry::Transform3D& transform,
        kvector_t position, double abundance=0);

    PositionParticleInfo(
        Particle *p_particle, kvector_t position, double abundance=0);

    PositionParticleInfo(
        const Particle& particle, kvector_t position, double abundance=0);

    virtual ~PositionParticleInfo() {}

    virtual PositionParticleInfo *clone() const;

    //! Returns particle.
    const Particle *getParticle() const { return mp_particle; }

    //! Returns particle position, including depth.
    kvector_t getPosition() const
    { return kvector_t(m_pos_x, m_pos_y, -m_depth); }

    //! Sets particle position, including depth.
    void setPosition(kvector_t position);

 protected:
    PositionParticleInfo& operator=(const PositionParticleInfo& right);
    PositionParticleInfo(const PositionParticleInfo& source);

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    double m_pos_x;
    double m_pos_y;
};

#endif /* POSITIONPARTICLEINFO_H_ */
