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
#include "IParticle.h"

//! @class ParticleInfo
//! @ingroup samples
//! @brief Holds additional information about particle.
//!
//! Used in ParticleLayout

class BA_CORE_API_ ParticleInfo : public ICompositeSample
{
public:
    ParticleInfo(IParticle *p_particle,
                 double depth=0, double abundance=0);
    ParticleInfo(const IParticle& p_particle,
                 double depth=0, double abundance=0);

    virtual ~ParticleInfo() {}

    virtual ParticleInfo *clone() const
    {
        return new ParticleInfo(
            mP_particle->clone(), m_depth, m_abundance);
    }

    //! Returns a clone with inverted magnetic fields
    virtual ParticleInfo *cloneInvertB() const
    {
        return new ParticleInfo(
            mP_particle->cloneInvertB(), m_depth, m_abundance);
    }

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Returns particle.
    const IParticle *getParticle() const { return mP_particle.get(); }

    //! Returns depth.
    double getDepth() const { return m_depth; }

    //! Sets depth.
    void setDepth(double depth) { m_depth = depth; }

    //! Returns abundance.
    double getAbundance() const { return m_abundance; }

    //! Sets abundance.
    void setAbundance(double abundance) { m_abundance = abundance; }

    //! Sets the ambient material
    void setAmbientMaterial(const IMaterial *p_material) {
        mP_particle->setAmbientMaterial(p_material);
    }

protected:
    virtual void init_parameters();

    virtual void print(std::ostream& ostr) const;

    std::auto_ptr<IParticle> mP_particle;
    double m_depth;
    double m_abundance;
};

#endif /* PARTICLEINFO_H */


