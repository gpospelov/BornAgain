// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IUnitConverter.cpp
//! @brief     Implements IUnitConverter class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IUnitConverter.h"

IUnitConverter::~IUnitConverter() =default;

std::string IUnitConverter::axisName(size_t i_axis, AxesUnits units_type) const
{
    const std::vector<std::map<AxesUnits, std::string>> name_maps = createNameMaps();
    auto& name_map = name_maps[i_axis];
    // Replace DEFAULT by the converter's default units:
    if (units_type==AxesUnits::DEFAULT) units_type = defaultUnits();
    auto it = name_map.find(units_type);
    if (it==name_map.end())
        throw std::runtime_error("Error in IUnitConverter::axisName: "
                                 "unknown or unsupported unit type");
    return it->second;
}
