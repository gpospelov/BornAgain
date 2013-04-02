// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ICompositeSample.h
//! @brief     Defines interface class ICompositeSample.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPOSITESAMPLE_H
#define ICOMPOSITESAMPLE_H

#include "ISample.h"
#include <list>

//! Interface to equip ISample with a tree structure.

//! As of March 2013, this is the base class for
//! - IClustered Particle
//!   - Crystal
//! - IDecoration
//!   - ParticleDecoration
//! - Layer
//!   - LayerDecorator
//! - LayerInterface
//! - MultiLayer
//! - Particle
//!   - LatticeBasis
//!   - MesoCrystal
//!   - ParticleCoreShell
//! - ParticleInfo
//!   - DiffuseParticleInfo
//!   - PositionParticleInfo
//!
class ICompositeSample : public ISample
{
 public:
    ICompositeSample() {}
    virtual ~ICompositeSample() {}

    ICompositeSample *clone() const;

    //! to confirm compound nature of given class
    virtual ICompositeSample *getCompositeSample() { return this; }
    virtual const ICompositeSample *getCompositeSample() const { return this; }

    //! Registers child in the container.
    virtual void registerChild(ISample *sample);

    //! Removes registered child from the container
    virtual void deregisterChild(ISample *sample);

    //! Begins iteration over local registered children.
    std::list<ISample*>::iterator begin_shallow()
    { return m_samples.begin(); }

    //! Ends iteration over local registered children.
    std::list<ISample*>::iterator end_shallow()
    { return m_samples.end(); }

    //! Begins read-only iteration over local registered children.
    std::list<ISample*>::const_iterator begin_shallow() const
    { return m_samples.begin(); }

    //! Ends read-only iteration over local registered children.
    std::list<ISample*>::const_iterator end_shallow() const
    { return m_samples.end(); }

    //! Returns number of children.
    virtual size_t size() const { return m_samples.size(); }

    //! Creates general iterator to walk through tree of composite children.
    class ICompositeIterator createIterator();

 private:
    //! List of registered children.
    std::list<ISample*> m_samples;
};

#endif // ICOMPOSITESAMPLE_H


