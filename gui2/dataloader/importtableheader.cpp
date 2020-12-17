//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/importtableheader.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/dataloader/importtableheader.h"
#include "gui2/dataloader/dataloader_constants.h"
#include "gui2/dataloader/dataloader_types.h"
#include "mvvm/model/comboproperty.h"

using ModelView::ComboProperty;

namespace gui2 {

namespace {
const std::vector<std::string> utilityRowNames = {"Type", "Unit", "Multiplier"};

const std::vector<std::string> typeNames = {Constants::AxisType, Constants::IntensityType,
                                            Constants::IgnoreType};

const std::vector<std::string> unitNames = {"a.u.", "counts", "1/nm", "Angstrom"};

//! Returns column type from column index.
std::string suggestColumnTypeFromColumnIndex(int col)
{
    return col < static_cast<int>(typeNames.size()) ? typeNames[col] : Constants::IgnoreType;
}

QVariant CreateTypeVariant(int col = 0)
{
    auto combo = ComboProperty::createFrom(typeNames);
    auto selected_value = suggestColumnTypeFromColumnIndex(col);
    combo.setValue(selected_value);
    return QVariant::fromValue<ComboProperty>(combo);
}

std::vector<QVariant> CreateTypeVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(CreateTypeVariant(i));
    return result;
}

std::vector<QVariant> CreateUnitVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(QVariant::fromValue<ComboProperty>(ComboProperty::createFrom(unitNames)));
    return result;
}

std::vector<QVariant> CreateMultiplierVariants(int maxColumnCount)
{
    std::vector<QVariant> result(maxColumnCount, 1.0);
    return result;
}

} // namespace

ImportTableHeader::ImportTableHeader(int max_column_count) : m_maxColumnCount(max_column_count)
{
    init_data();
}

int ImportTableHeader::rowCount() const
{
    return utilityRowNames.size();
}

int ImportTableHeader::columnCount() const
{
    return m_maxColumnCount;
}

QVariant ImportTableHeader::data(int row, int column) const
{
    return isValid(row, column) ? m_data[row][column] : QVariant();
}

bool ImportTableHeader::setData(int row, int column, const QVariant& variant)
{
    if (isValid(row, column)) {
        m_data[row][column] = variant;
        return true;
    }

    return false;
}

std::string ImportTableHeader::rowName(int row) const
{
    return utilityRowNames[row];
}

std::vector<ColumnInfo> ImportTableHeader::columnInfo() const
{
    std::vector<ColumnInfo> result;
    for (int column = 0; column < columnCount(); ++column) {
        ColumnInfo info;
        info.column = column;
        info.type_name = data(TYPE, column).value<ComboProperty>().value();
        info.units = data(UNITS, column).value<ComboProperty>().value();
        info.multiplier = data(MULTIPLIER, column).value<double>();
        result.push_back(info);
    }

    return result;
}

void ImportTableHeader::init_data()
{
    m_data.resize(MAX);
    m_data[TYPE] = CreateTypeVariants(columnCount());
    m_data[UNITS] = CreateUnitVariants(columnCount());
    m_data[MULTIPLIER] = CreateMultiplierVariants(columnCount());
}

//! Returns true if given pair of indices are valid for data array.

bool ImportTableHeader::isValid(int row, int column) const
{
    return (row >= 0 && row < static_cast<int>(m_data.size()))
           && (column >= 0 && column < static_cast<int>(m_data[row].size()));
}

} // namespace gui2
