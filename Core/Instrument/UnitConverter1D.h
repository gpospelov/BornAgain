// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverter1D.h
//! @brief     Defines class UnitConverter1D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef UNITCONVERTER1D_H
#define UNITCONVERTER1D_H

#include <functional>

#include "IUnitConverter.h"

class Beam;

//! Conversion of axis units for the case of 1D simulation result
//! (specular simulation in particular).

class BA_CORE_API_ UnitConverter1D : public IUnitConverter
{
public:
    //! Constructs the object for unit conversion. Input axis
    //! is in radians.
    UnitConverter1D(const Beam& beam, const IAxis& axis, AxesUnits axis_units = AxesUnits::RADIANS);
    ~UnitConverter1D() override;

    UnitConverter1D* clone() const override;

    //! Returns dimensionality of converted canvas.
    size_t dimension() const override;

    //! Calculates minimum on-axis value in given units.
    double calculateMin(size_t i_axis, AxesUnits units_type) const override;

    //! Calculates maximum on-axis value in given units.
    double calculateMax(size_t i_axis, AxesUnits units_type) const override;

    //! Returns the size of underlying axis.
    size_t axisSize(size_t i_axis) const override;

    //! Returns the list of all available units
    std::vector<AxesUnits> availableUnits() const override;

    //! Returns default units to convert to.
    AxesUnits defaultUnits() const override;

    //! Creates axis in converted units.
    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const override;

private:
    UnitConverter1D(const UnitConverter1D& other);

    //! Returns translating functional (input units --> rads)
    std::function<double(double)> getTraslatorFrom(AxesUnits units_type) const;

    //! Returns translating functional (rads --> desired units)
    std::function<double(double)> getTraslatorTo(AxesUnits units_type) const;

    //! Creates name map for axis in various units
    std::vector<std::map<AxesUnits, std::string>> createNameMaps() const override;

    double m_wavelength;           //!< basic wavelength in nm (for translation to q-space).
    std::unique_ptr<IAxis> m_axis; //!< basic inclination angles (in rads).
};

#endif // UNITCONVERTER1D_H
