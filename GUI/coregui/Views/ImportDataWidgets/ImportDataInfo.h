// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataInfo.h
//! @brief     Defines ImportDataInfo helper struct
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMPORTDATAINFO_H
#define IMPORTDATAINFO_H

#include <memory>
#include <vector>

template<class T> class OutputData;

//! Carries information about loaded data.

struct ImportDataInfo
{
    enum class COORDINATE {bins, angle, double_angle, q};
    enum class UNITS {bins, rads, degrees, inv_nm, inv_angstroms};

    ImportDataInfo();
    ~ImportDataInfo();
    static std::vector<UNITS> compatibleUnits(COORDINATE coordinate_type);

    std::unique_ptr<OutputData<double>> m_data;
    COORDINATE m_coordinate_type;
    UNITS m_units;
};

#endif // IMPORTDATAINFO_H
