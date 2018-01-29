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
#include "Vectors3D.h"
#include "WinDllMacros.h"
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Beam;
class IAxis;
class IDetector;
class IDetector2D;
class RectangularDetector;
class RectangularPixel;
class SphericalDetector;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE };
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
    virtual size_t axisSize(size_t i_axis) const=0;
    virtual std::string axisName(size_t i_axis, AxesUnits units_type = AxesUnits::DEFAULT) const=0;
};

//! Interface for objects that provide axis translations to different units for IDetector objects
//! @ingroup simulation_internal

class BA_CORE_API_ UnitConverterSimple : public IUnitConverter
{
public:
    UnitConverterSimple(const Beam& beam);
    virtual ~UnitConverterSimple() =default;

    virtual size_t dimension() const override;

    double calculateMin(size_t i_axis, AxesUnits units_type) const override;
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;
    size_t axisSize(size_t i_axis) const override;

    std::string axisName(size_t i_axis, AxesUnits units_type = AxesUnits::DEFAULT) const override;

protected:
    UnitConverterSimple(const UnitConverterSimple& other);
    void addDetectorAxis(const IDetector& detector, size_t i_axis);

    void addAxisData(std::string name, double min, double max,
                     AxesUnits default_units, size_t nbins);
    void checkIndex(size_t i_axis) const;
    void checkDimension(size_t dim) const;

#ifndef SWIG
    struct AxisData {
        std::string name;
        double min, max;
        AxesUnits default_units;
        size_t nbins;
    };
    std::vector<AxisData> m_axis_data_table;
#endif
    double m_wavelength;
    double m_alpha_i;
    double m_phi_i;

private:
    virtual double calculateValue(size_t i_axis, AxesUnits units_type, double value) const=0;
    virtual AxesUnits defaultUnits() const=0;
    virtual std::vector<std::map<AxesUnits, std::string>> createNameMaps() const=0;
};

//! IUnitConverter class that handles the unit translations for spherical detectors
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ SphericalConverter : public UnitConverterSimple
{
public:
    SphericalConverter(const SphericalDetector& detector, const Beam& beam);

    virtual ~SphericalConverter();

    SphericalConverter* clone() const override;

private:
    SphericalConverter(const SphericalConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    AxesUnits defaultUnits() const override { return AxesUnits::RADIANS; }
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
};

//! IUnitConverter class that handles the unit translations for rectangular detectors
//! Its default units are mm for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ RectangularConverter : public UnitConverterSimple
{
public:
    RectangularConverter(const RectangularDetector& detector, const Beam& beam);
    virtual ~RectangularConverter();

    RectangularConverter* clone() const override;

private:
    RectangularConverter(const RectangularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    AxesUnits defaultUnits() const override { return AxesUnits::MM; }
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
    kvector_t normalizeToWavelength(kvector_t vector) const;
    double axisAngle(size_t i_axis, kvector_t k_f) const;
    std::unique_ptr<RectangularPixel> mP_detector_pixel;
};

//! IUnitConverter class that handles the unit translations for off-specular simulations
//! with a spherical detector
//! Its default units are radians for both axes
//! @ingroup simulation_internal

class BA_CORE_API_ OffSpecularConverter : public UnitConverterSimple
{
public:
    OffSpecularConverter(const IDetector2D& detector, const Beam& beam, const IAxis& alpha_axis);
    virtual ~OffSpecularConverter();

    OffSpecularConverter* clone() const override;

private:
    OffSpecularConverter(const OffSpecularConverter& other);
    double calculateValue(size_t i_axis, AxesUnits units_type, double value) const override;
    AxesUnits defaultUnits() const override { return AxesUnits::RADIANS; }
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;
    void addDetectorYAxis(const IDetector2D& detector);
};

#endif // UNITCONVERTERS_H
