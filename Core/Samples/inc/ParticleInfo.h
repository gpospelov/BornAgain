// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleInfo.h
//! @brief     Defines class ParticleInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H

#include "ICompositeSample.h"
#include "IParticle.h"

#include <boost/scoped_ptr.hpp>

//! @class ParticleInfo
//! @ingroup samples
//! @brief Holds additional information about particle.
//!
//! Used in ParticleLayout

class BA_CORE_API_ ParticleInfo : public ICompositeSample
{
public:
    ParticleInfo(const IAbstractParticle &p_particle, double abundance = 1.0);

    virtual ParticleInfo *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleInfo *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Returns particle.
    const IAbstractParticle *getParticle() const;

    //! Returns abundance.
    double getAbundance() const;

    //! Sets abundance.
    void setAbundance(double abundance);

    //! Sets the ambient material
    void setAmbientMaterial(const IMaterial &material);

protected:
    virtual void init_parameters();

    virtual void print(std::ostream &ostr) const;

    boost::scoped_ptr<IAbstractParticle> mP_particle;
    double m_abundance;
};

#endif /* PARTICLEINFO_H */
