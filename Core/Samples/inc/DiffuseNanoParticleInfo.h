#ifndef DIFFUSENANOPARTICLEINFO_H_
#define DIFFUSENANOPARTICLEINFO_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DiffuseNanoParticleInfo.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Sep 4, 2012

#include "NanoParticleInfo.h"

class DiffuseNanoParticleInfo: public NanoParticleInfo
{
public:
    DiffuseNanoParticleInfo(Particle *p_particle, Geometry::Transform3D *transform=0, double depth=0, double abundance=0);
    virtual ~DiffuseNanoParticleInfo();

    //! scale abundance
    void scaleAbundance(double factor) { m_abundance *= factor; }

    //! scale abundance
    void scaleNumberPerMeso(double factor) { m_number_per_meso *= factor; }

    //! set number of nanoparticles per containing mesocrystal
    void setNumberPerMeso(double n) { m_number_per_meso = n; }

    //! get number of nanoparticles per containing mesocrystal
    double getNumberPerMeso() const { return m_number_per_meso; }
protected:
    double m_number_per_meso;

};

#endif /* DIFFUSENANOPARTICLEINFO_H_ */
