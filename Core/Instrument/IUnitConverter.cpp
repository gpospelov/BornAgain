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
#include "OutputData.h"
#include "UnitConverterUtils.h"

IUnitConverter::~IUnitConverter() =default;

std::string IUnitConverter::axisName(size_t i_axis, AxesUnits units_type) const
{
    const auto& name_maps = createNameMaps();
    if (name_maps.size() <= i_axis)
        throw std::runtime_error("Error in IUnitConverter::axisName: the size of name map vector "
                                 "is smaller or equal to the axis index"
                                 + std::to_string(static_cast<int>(i_axis)));
    const auto& name_map = name_maps[i_axis];
    units_type = UnitConverterUtils::substituteDefaultUnits(*this, units_type);
    const auto& it = name_map.find(units_type);
    if (it == name_map.cend())
        throw std::runtime_error("Error in IUnitConverter::axisName: "
                                 "unknown or unsupported unit type");
    return it->second;
}

std::unique_ptr<OutputData<double>>
IUnitConverter::createConvertedData(const OutputData<double>& data, AxesUnits units) const
{
    const size_t dim = data.getRank();
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        result->addAxis(*createConvertedAxis(i, units));
    result->setRawDataVector(data.getRawDataVector());
    return result;
}

void IUnitConverter::checkIndex(size_t i_axis) const
{
    if (i_axis < dimension()) return;
    throw std::runtime_error("Error in IUnitConverter::checkIndex: passed axis index too big: "
                             + std::to_string(static_cast<int>(i_axis)));
}
