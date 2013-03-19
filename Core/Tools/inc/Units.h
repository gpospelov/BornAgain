// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/Units.h
//! @brief     Defines some unit conversion factors and other constants in namespace Units.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef UNITS_H
#define UNITS_H

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

// definitions of Pi for fast sine calculations
static const double PI          = 3.14159265358979323846264338327950288f;
static const double PI2         = 6.28318530717958647692528676655900577f;
static const double PID2        = 1.57079632679489661923132169163975144f;
static const double PI_SQR      = 9.86960440108935861883449099987615114f;

}


#endif // UNITS_H
