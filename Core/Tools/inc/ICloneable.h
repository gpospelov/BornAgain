#ifndef ICLONEABLE_H
#define ICLONEABLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ICloneable.h
//! @brief  Definition of ICloneable class
//! @author Scientific Computing Group at FRM II
//! @date   10.01.2013

#include "Exceptions.h"


//- -------------------------------------------------------------------
//! @class ICloneable
//! @brief Cloneable interface for objects with clone method defined
//! and with disabled copy constructor and assignment operators
//- -------------------------------------------------------------------
class ICloneable
{
public:
    ICloneable(){}
    virtual ~ICloneable() {}
    virtual ICloneable *clone() const = 0;

private:
    ICloneable(const ICloneable &) { throw NotImplementedException("ICloneable(const ICloneable &) -> Error: not implemented."); }
    ICloneable &operator=(const ICloneable &) { throw NotImplementedException("ICloneable &operator=(const ICloneable &) -> Error: not implemented."); }
};

#endif // ICLONEABLE_H
