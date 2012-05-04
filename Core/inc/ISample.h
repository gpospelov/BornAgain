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

#include "Exceptions.h"


class ISample
{
public:
    ISample(){}
    virtual ~ISample() {}

    virtual void add(ISample* p_child);

    virtual ISample *clone() const =0;

//    virtual void remove(ISample* p_child);
//    virtual ISample* getChild(size_t index);
};

#endif // ISAMPLE_H
