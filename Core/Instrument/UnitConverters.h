// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverters.h
//! @brief     Defines interface IUnitConverter and its subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef UNITCONVERTERS_H
#define UNITCONVERTERS_H

#include "ICloneable.h"
#include "WinDllMacros.h"
#include <cstddef>
#include <vector>

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class BA_CORE_API_ IUnitConverter : public ICloneable
{
public:
    virtual ~IUnitConverter() =default;

    virtual IUnitConverter* clone() const=0;

    virtual size_t dimension() const=0;

    virtual double calculateMin(size_t i_axis, AxesUnits units_type) const=0;
    virtual double calculateMax(size_t i_axis, AxesUnits units_type) const=0;
};

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class BA_CORE_API_ UnitConverterSimple : public IUnitConverter
{
public:
    UnitConverterSimple() =default;
    virtual ~UnitConverterSimple() =default;

    virtual size_t dimension() const override;

    double calculateMin(size_t i_axis, AxesUnits units_type) const override;
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;

protected:
    UnitConverterSimple(const UnitConverterSimple& other);
    void addAxisData(double min, double max, AxesUnits default_units, size_t nbins);
    virtual double calculateValue(size_t i_axis, AxesUnits units_type, double value) const=0;
    void checkIndex(size_t i_axis) const;

    struct AxisData {
        double min, max;
        AxesUnits default_units;
        size_t nbins;
    };
    std::vector<AxisData> m_axis_data_table;
};

//! IUnitConverter class that handles the unit translations for spherical detectors
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ SphericalConverter : public UnitConverterSimple
{
public:
    SphericalConverter(size_t n_phi, double phi_min, double phi_max,
                       size_t n_alpha, double alpha_min, double alpha_max);
    virtual ~SphericalConverter();

    SphericalConverter* clone() const override;

private:
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    static const AxesUnits Default_Units = AxesUnits::RADIANS;
};

#endif // UNITCONVERTERS_H
