#ifndef UNITS_H
#define UNITS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Units.h
//! @brief  Definition of units
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "Types.h"

namespace Units {  // BornAgain namespace

// Length
static const double nanometer   = 1;
static const double angstrom    = 1.e-1*nanometer;
static const double micrometer  = 1.e+3*nanometer;
static const double millimeter  = 1.e+6*nanometer;
static const double meter       = 1.e+9*nanometer;

// symbols
static const double nm  = nanometer;

// Angle
static const double radian      = 1.;
static const double milliradian = 1.e-3*radian;
static const double degree = (3.14159265358979323846/180.0)*radian;
static const double steradian = 1.;

inline double rad2deg(double angle) {return angle/degree; }
inline double deg2rad(double angle) {return angle*degree; }

// symbols
static const double rad  = radian;
static const double mrad = milliradian;
static const double sr   = steradian;
static const double deg  = degree;


}


#endif // UNITS_H
