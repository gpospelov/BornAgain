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

class BA_CORE_API_ ICompositeSample : public ISample
{
public:
    typedef std::list<ISample*>::iterator iterator_t;
    typedef std::list<ISample*>::const_iterator const_iterator_t;

    ICompositeSample() {}
    virtual ~ICompositeSample() {}

    ICompositeSample *clone() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! to confirm compound nature of given class
    virtual ICompositeSample *getCompositeSample() { return this; }
    virtual const ICompositeSample *getCompositeSample() const { return this; }

    //! Registers child in the container.
    virtual void registerChild(ISample *sample);

    //! Removes registered child from the container
    virtual void deregisterChild(ISample *sample);

    //! Begins iteration over local registered children.
    iterator_t begin_shallow() { return m_samples.begin(); }

    //! Ends iteration over local registered children.
    iterator_t end_shallow() { return m_samples.end(); }

    //! Begins read-only iteration over local registered children.
    const_iterator_t begin_shallow() const { return m_samples.begin(); }

    //! Ends read-only iteration over local registered children.
    const_iterator_t end_shallow() const { return m_samples.end(); }

    //! Returns number of children.
    virtual size_t size() const { return m_samples.size(); }

    //! Creates general iterator to walk through tree of composite children.
    class ICompositeIterator createIterator() const;

private:
    //! List of registered children.
    std::list<ISample*> m_samples;
};

#endif // ICOMPOSITESAMPLE_H


