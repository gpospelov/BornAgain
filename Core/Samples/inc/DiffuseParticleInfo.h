// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/DiffuseParticleInfo.h
//! @brief     Defines class DiffuseParticleInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DIFFUSEPARTICLEINFO_H_
#define DIFFUSEPARTICLEINFO_H_

#include "ParticleInfo.h"

//! ?

class DiffuseParticleInfo: public ParticleInfo
{
 public:
    DiffuseParticleInfo(
        Particle *p_particle, Geometry::Transform3D *transform=0,
        double depth=0, double abundance=0);
    virtual ~DiffuseParticleInfo();

    //! scale abundance
    void scaleAbundance(double factor) { m_abundance *= factor; }

    //! scale number of particles per containing mesocrystal
    void scaleNumberPerMeso(double factor) { m_number_per_meso *= factor; }

    //! Sets number of particles per containing mesocrystal
    void setNumberPerMeso(double n) { m_number_per_meso = n; }

    //! Returns number of particles per containing mesocrystal
    double getNumberPerMeso() const { return m_number_per_meso; }

    DiffuseParticleInfo *clone() const
    { throw NotImplementedException(
            "DiffuseParticleInfo::clone() -> Error: not implemented");
    }

    //! Sets the range of height
    void setHeightRange(double height_range) { m_height_range = height_range; }

    //! Returns the range of height
    double getHeightRange() const { return m_height_range; }
 protected:
    double m_number_per_meso;
    double m_height_range;
};

#endif /* DIFFUSEPARTICLEINFO_H_ */
