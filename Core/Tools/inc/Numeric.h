#ifndef NUMERIC_H_
#define NUMERIC_H_

// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Numeric.h
//! @brief  Definition of constants for numeric calculations
//! @author Scientific Computing Group at FRM II
//! @date   10.05.2012

#include <limits>
#include <cmath>

namespace Numeric {

static const double required_precision = 1.e-4;

static double double_epsilon = std::numeric_limits<double>::epsilon();
static double double_min = std::numeric_limits<double>::min();

static const double probthreshold = 0.0000000001; //!< threshold on probability value during calculation of weighted form factor

//! compare two doubles
inline bool areAlmostEqual(double a, double b, double tolerance_factor=1.0) { return std::abs(a-b) < tolerance_factor*Numeric::double_epsilon; }

}

#endif /* NUMERIC_H_ */
