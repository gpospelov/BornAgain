#ifndef DIFFUSEPARTICLEINFO_H_
#define DIFFUSEPARTICLEINFO_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DiffuseParticleInfo.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Sep 4, 2012

#include "ParticleInfo.h"

class DiffuseParticleInfo: public ParticleInfo
{
public:
    DiffuseParticleInfo(Particle *p_particle, Geometry::Transform3D *transform=0, double depth=0, double abundance=0);
    virtual ~DiffuseParticleInfo();

    //! scale abundance
    void scaleAbundance(double factor) { m_abundance *= factor; }

    //! scale abundance
    void scaleNumberPerMeso(double factor) { m_number_per_meso *= factor; }

    //! set number of particles per containing mesocrystal
    void setNumberPerMeso(double n) { m_number_per_meso = n; }

    //! get number of particles per containing mesocrystal
    double getNumberPerMeso() const { return m_number_per_meso; }

    //! set the range of height
    void setHeightRange(double height_range) { m_height_range = height_range; }

    //! get the range of height
    double getHeightRange() const { return m_height_range; }
protected:
    DiffuseParticleInfo &operator=(const DiffuseParticleInfo &right);
    DiffuseParticleInfo(const DiffuseParticleInfo &source);

    double m_number_per_meso;
    double m_height_range;

};

#endif /* DIFFUSEPARTICLEINFO_H_ */
