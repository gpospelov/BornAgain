//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvNamespace.h
//! @brief     Defines namespace csv
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVNAMESPACE_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVNAMESPACE_H

#include <QString>
#include <QStringList>
#include <vector>

namespace csv {
enum ColumnType { _intensity_, _theta_, _q_ };
const QStringList HeaderLabels{"Intensity", "theta", "q"};
const QStringList UnitsLabels{"default", "bin", "rad", "deg", "mm", "1/nm"};
typedef std::vector<std::vector<std::string>> DataArray;
typedef std::vector<std::string> DataRow;
typedef std::vector<std::string> DataColumn;
bool isAscii(QString filename);
} // namespace csv

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_CSVIMPORTASSISTANT_CSVNAMESPACE_H
