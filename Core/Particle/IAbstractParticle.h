// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IAbstractParticle.h
//! @brief     Defines interface IAParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IABSTRACTPARTICLE_H
#define IABSTRACTPARTICLE_H

#include "ISample.h"
#include "Vectors3D.h"
#include "BornAgainNamespace.h"
#include <memory>

class IMaterial;

//! Interface for a generic particle.
//!
//! Inherited by IParticle and ParticleDistribution.

//! @ingroup samples

class BA_CORE_API_ IAbstractParticle : public ISample
{
public:
    IAbstractParticle() : m_abundance(1.0) {}
    virtual ~IAbstractParticle() {}

    virtual IAbstractParticle* clone() const =0;
    virtual IAbstractParticle* cloneInvertB() const =0;

    virtual void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double abundance() const { return m_abundance; }
    void setAbundance(double abundance) { m_abundance = abundance; }

protected:
    double m_abundance;
};

#endif // IABSTRACTPARTICLE_H
