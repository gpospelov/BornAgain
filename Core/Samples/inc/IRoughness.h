#ifndef IROUGHNESS_H
#define IROUGHNESS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IRoughness.h
//! @brief  Definition of IRoughness class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ISample.h"


//- -------------------------------------------------------------------
//! @class IRoughness
//! @brief Definition of Roughness interface
//- -------------------------------------------------------------------
class IRoughness : public ISample
{
public:
    IRoughness();
    virtual ~IRoughness(){}
};

#endif // IROUGHNESS_H
