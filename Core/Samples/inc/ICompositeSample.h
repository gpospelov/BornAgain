// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ICompositeSample.h
//! @brief     Defines class ICompositeSample.
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

class ICompositeIterator;

//! Interface to equip ISample with a tree structure.

class ICompositeSample : public ISample
{
 public:
    //! definition of container for registered children
    typedef std::list<ISample *> samples_t;
    typedef samples_t::iterator iterator_t;
    typedef samples_t::const_iterator const_iterator_t;

    ICompositeSample() { }
    virtual ~ICompositeSample() { }

    ICompositeSample *clone() const;

    //! to confirm compound nature of given class
    virtual ICompositeSample *getCompositeSample() { return this; }
    virtual const ICompositeSample *getCompositeSample() const { return this; }

    //! Registers child in the container
    virtual void registerChild(ISample *sample);

    //! remove registered child from the container
    virtual void deregisterChild(ISample *sample);

    //! iteration over local registered children
    iterator_t begin_shallow() { return m_samples.begin(); }
    iterator_t end_shallow() { return m_samples.end(); }
    const_iterator_t begin_shallow() const { return m_samples.begin(); }
    const_iterator_t end_shallow() const { return m_samples.end(); }

    //! size of children
    virtual size_t size() const { return m_samples.size(); }

    //! Creates general iterator to walk through the tree of registered composite children
    ICompositeIterator createIterator();

 private:
//    ICompositeSample& operator=(const ICompositeSample& other);

    //! Checks index of child
    //inline size_t check_index(size_t index) const { return index < m_samples.size() ? index : throw OutOfBoundsException("ICompositeSample::check_index() -> Error! Index is out of bounds"); }

    samples_t m_samples; //! list of registered children
};

#endif // ICOMPOSITESAMPLE_H
