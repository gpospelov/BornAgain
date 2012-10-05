#ifndef MINIMIZER_H
#define MINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Minimizer.h
//! @brief  Definition of Minimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012


//- -------------------------------------------------------------------
//! @class Minimizer
//! @brief Common wrapper for all kind minimizer's
//- -------------------------------------------------------------------
class Minimizer
{
public:
    Minimizer();
    virtual ~Minimizer(){}
};

#endif // MINIMIZER_H
