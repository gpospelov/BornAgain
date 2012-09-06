#ifndef NANOPARTICLEINFO_H
#define NANOPARTICLEINFO_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleInfo.h
//! @brief  Definition of Layer class
//! @author Scientific Computing Group at FRM II
//! @date   18.07.2012

#include "ICompositeSample.h"
#include "NanoParticle.h"
#include "Transform3D.h"

//- -------------------------------------------------------------------
//! @class NanoParticleInfo
//! @brief holds additional information about nanoparticle (used in NanoParticleDecoration)
//- -------------------------------------------------------------------
class NanoParticleInfo : public ICompositeSample
{
public:
    //! default constructor
    //NanoParticleInfo();
    //! constructor for nano particle having depth and abundance
    //NanoParticleInfo(NanoParticle *p_particle, double depth, double abundance);
    //! constructor for nano particle having transformation property and abundance
    NanoParticleInfo(NanoParticle *p_particle, Geometry::Transform3D *transform=0, double depth=0, double abundance=0);

    virtual ~NanoParticleInfo();

    //! clone nano particle info
    virtual NanoParticleInfo *clone() const;

    //! return nano particle
    const NanoParticle *getNanoParticle() const { return mp_particle; }

    //! return nano particle transformation
    const Geometry::Transform3D *getTransform3D() const { return m_transform; }

    //! return nano particle depth
    double getDepth() const { return m_depth;}

    //! return nano particle abundance
    double getAbundance() const { return m_abundance; }

protected:
    NanoParticleInfo &operator=(const NanoParticleInfo &right);
    NanoParticleInfo(const NanoParticleInfo &source);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    NanoParticle *mp_particle;
    Geometry::Transform3D *m_transform;
    double m_depth;
    double m_abundance;
};


#endif // NANOPARTICLEINFO_H
