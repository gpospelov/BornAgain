// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataInfo.cpp
//! @brief     Implements ImportDataInfo helper struct
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ImportDataInfo.h"
#include "OutputData.h"
#include <vector>

using COORDINATE = ImportDataInfo::COORDINATE;
using UNITS = ImportDataInfo::UNITS;

const std::vector<std::pair<COORDINATE, std::vector<UNITS>>> available_units = {
    {COORDINATE::bins, {UNITS::bins}},
    {COORDINATE::angle, {UNITS::rads, UNITS::degrees}},
    {COORDINATE::double_angle, {UNITS::rads, UNITS::degrees}},
    {COORDINATE::q, {UNITS::inv_angstroms, UNITS::inv_nm}}
};

ImportDataInfo::ImportDataInfo()
    : m_coordinate_type(COORDINATE::bins)
    , m_units(UNITS::bins)
{
}

ImportDataInfo::~ImportDataInfo() = default;

std::vector<UNITS> ImportDataInfo::compatibleUnits(COORDINATE coordinate_type)
{
    for (auto& pair: available_units)
        if (coordinate_type == pair.first)
            return pair.second;
    return {};
}
