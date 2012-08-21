#ifndef ICOMPOSITESAMPLE_H
#define ICOMPOSITESAMPLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ICompositeSample
//! @brief  Definition of ICompositeSample class
//! @author Scientific Computing Group at FRM II
//! @date   16.06.2012

#include "ISample.h"
#include <list>


class ICompositeIterator;

//- -------------------------------------------------------------------
//! @class ICompositeSample
//! @brief Definition of ICompositeSample which compose ISample objects
//! into tree structure
//- -------------------------------------------------------------------
class ICompositeSample : public ISample
{
public:
    //! definition of container for registered children
    typedef std::list<ISample *> samples_t;
    typedef samples_t::iterator iterator_t;

    ICompositeSample();

    //! to confirm compound nature of given class
    virtual ICompositeSample *getCompositeSample() { return this; }

    //! register child in the container
    virtual void registerChild(ISample *sample);

    //! remove registered child from the container
    virtual void deregisterChild(ISample *sample);

    //! iteration over local registered children
    iterator_t begin_shallow() { return m_samples.begin(); }
    iterator_t end_shallow() { return m_samples.end(); }

    //! size of children
    virtual size_t size() const { return m_samples.size(); }

    //! create general iterator to walk through the tree of registered composite children
    ICompositeIterator createIterator();

protected:
    ICompositeSample(const ICompositeSample &other);

private:
    ICompositeSample &operator=(const ICompositeSample &other);

    //! check index of child
    //inline size_t check_index(size_t index) const { return index < m_samples.size() ? index : throw OutOfBoundsException("ICompositeSample::check_index() -> Error! Index is out of bounds"); }

    samples_t m_samples; //! list of registered children
};

#endif // ICOMPOSITESAMPLE_H
