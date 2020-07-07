// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Units.h
//! @brief     Defines some unit conversion factors and other constants in namespace Units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_UNITS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_UNITS_H

//! Constants and functions for physical unit conversions.

namespace Units
{

// Length
static const double nanometer = 1.;
static const double angstrom = 1.e-1 * nanometer;
static const double micrometer = 1.e+3 * nanometer;
static const double millimeter = 1.e+6 * nanometer;
static const double meter = 1.e+9 * nanometer;

// Symbols for length
static const double nm = nanometer;

// Area (cross-section)
static const double nm2 = nanometer * nanometer;
static const double barn = nanometer * nanometer * 1e-10;

// Angle
static const double radian = 1.;
static const double milliradian = 1.e-3 * radian;
static const double degree = (3.1415926535897932 / 180.0) * radian;
static const double steradian = 1.;

inline double rad2deg(double angle)
{
    return angle / degree;
}
inline double deg2rad(double angle)
{
    return angle * degree;
}

// Symbols for (solid) angle
static const double rad = radian;
static const double mrad = milliradian;
static const double sr = steradian;
static const double deg = degree;

// Magnetic field
static const double tesla = 1.;
static const double gauss = 1e-4;

} // namespace Units

#endif // BORNAGAIN_CORE_PARAMETRIZATION_UNITS_H
