#ifndef SAMPLEFACTORY_H
#define SAMPLEFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SampleFactory.h
//! @brief  Definition of SampleFactory class
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <map>
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class SampleFactory
//! @brief Factory to create standard pre-defined samples
//! See StandardSamples.{h,cpp} with sample definition
//- -------------------------------------------------------------------
class SampleFactory
{
public:
    //! access to SampleFactory
    static SampleFactory &instance();

    //! create sample described by given sampleId
    ISample *createItem(int sampleId);

    typedef ISample* (*CreateItemCallback) ();

    //! save pointer to the function which will be used for object creation
    bool registerItem(int itemId, CreateItemCallback CreateFn);

    //! return number of register standard samples
    size_t getNumberOfSamples() const { return m_callbacks.size(); }

private:
    //! prevents client from creating a copy of singleton
    SampleFactory();
    SampleFactory(const SampleFactory &);
    SampleFactory &operator=(const SampleFactory &);

    //! reaction on too early destroyed object
    static void onDeadReference();

    //! create single copy of manager
    static void create();

    virtual ~SampleFactory();

    static SampleFactory *m_instance;
    static bool m_destroyed;

    //! holds pointers to function which create sample of given type (which is int)
    typedef std::map<int, CreateItemCallback > CallbackMap_t;

    //! holds pointers to function which create sample of given type (which is int)
    CallbackMap_t m_callbacks;
};

#endif // SAMPLEFACTORY_H

