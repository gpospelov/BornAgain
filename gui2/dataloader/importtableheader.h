//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/dataloader/importtableheader.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEHEADER_H
#define BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEHEADER_H

#include "darefl_export.h"
#include <QVariant>
#include <vector>

namespace gui2 {

struct ColumnInfo;

//! Holds all data related to the content of utility rows in ImportTableModel.

class DAREFLCORE_EXPORT ImportTableHeader {
public:
    enum RowTypes { TYPE, UNITS, MULTIPLIER, MAX };
    using header_data_t = std::vector<std::vector<QVariant>>;

    ImportTableHeader(int max_column_count);

    int rowCount() const;

    int columnCount() const;

    QVariant data(int row, int column) const;

    bool setData(int row, int column, const QVariant& variant);

    std::string rowName(int row) const;

    std::vector<ColumnInfo> columnInfo() const;

private:
    void init_data();
    bool isValid(int row, int column) const;

    header_data_t m_data;
    int m_maxColumnCount;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEHEADER_H
