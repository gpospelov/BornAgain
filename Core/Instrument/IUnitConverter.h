// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IUnitConverter.h
//! @brief     Defines interface IUnitConverter and possible axis units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef UNITCONVERTERS_H
#define UNITCONVERTERS_H

#include <cstddef>
#include <string>
#include "ICloneable.h"
#include "WinDllMacros.h"

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

//! Interface to provide axis translations to different units for simulation output
//! @ingroup simulation_internal

class BA_CORE_API_ IUnitConverter : public ICloneable
{
public:
    virtual ~IUnitConverter();

    virtual IUnitConverter* clone() const=0;

    virtual size_t dimension() const=0;

    virtual double calculateMin(size_t i_axis, AxesUnits units_type) const=0;
    virtual double calculateMax(size_t i_axis, AxesUnits units_type) const=0;
    virtual size_t axisSize(size_t i_axis) const=0;
    virtual std::string axisName(size_t i_axis, AxesUnits units_type = AxesUnits::DEFAULT) const=0;

    virtual AxesUnits defaultUnits() const=0;
};

#endif // UNITCONVERTERS_H
