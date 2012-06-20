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
    typedef std::list<ISample *> samples_t;
    typedef samples_t::iterator iterator_t;

    ICompositeSample();


    virtual ICompositeSample *getCompositeSample() { return this; }

    virtual void registerChild(ISample *sample) { m_samples.push_back(sample); }
    virtual void deregisterChild(ISample *sample) { m_samples.remove(sample); }

    //virtual ISample* getChild(size_t index) { return m_samples[ check_index(index) ]; }

    iterator_t begin_shallow() { return m_samples.begin(); }
    iterator_t end_shallow() { return m_samples.end(); }

    ICompositeIterator createIterator();


protected:
    ICompositeSample(const ICompositeSample &other);
    ICompositeSample &operator=(const ICompositeSample &other);

    //! check index of child
    //inline size_t check_index(size_t index) const { return index < m_samples.size() ? index : throw OutOfBoundsException("ICompositeSample::check_index() -> Error! Index is out of bounds"); }

    samples_t m_samples; //! list of registered children
};

#endif // ICOMPOSITESAMPLE_H
