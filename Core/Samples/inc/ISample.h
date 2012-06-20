#ifndef ISAMPLE_H
#define ISAMPLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISample.h
//! @brief  Definition of ISample class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "INamed.h"
#include "Exceptions.h"


class ICompositeSample;

class ISample : public INamed
{
public:
    ISample();
    virtual ~ISample() {}

    virtual ICompositeSample *getCompositeSample() { return 0; }
    virtual ISample *clone();

//    virtual void add(ISample* p_child);
//    virtual void remove(ISample* p_child);
//    virtual ISample* getChild(size_t index);

    long getId() const {return m_id; }

protected:
    long m_id; //! temporary debug variable to track id of instance
    static long m_id_last; //! temporary debug variable to track id of instance
};

#endif // ISAMPLE_H
