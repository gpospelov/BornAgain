// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant.h
//! @brief     Defines class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CSVIMPORTASSISTANT_H
#define CSVIMPORTASSISTANT_H

#include "WinDllMacros.h"
#include "CsvReader.h"
#include "ImportDataInfo.h"
#include "DataFormatUtils.h"
#include <QStringList>
#include <QWidget>
#include <memory>

namespace csv{
typedef std::vector<std::vector<std::string>> DataArray ;
typedef std::vector<std::string> DataRow;
}

//! Logic for importing intensity data from csv files

class BA_CORE_API_ CsvImportAssistant: public QObject
{
    Q_OBJECT
public:
    CsvImportAssistant(const QString& file, QWidget* parent = nullptr);
    ImportDataInfo getData(){return m_dataAvailable ? fillData() : ImportDataInfo();}
    static void showErrorMessage(std::string message);
    static double stringToDouble(std::string string_to_parse);

private:
    bool loadCsvFile();
    ImportDataInfo fillData();
    bool hasEqualLengthLines(csv::DataArray &dataArray);




    char guessSeparator() const;
    void removeBlankColumns();
    void runDataSelector(QWidget* parent);
    std::vector<double> getValuesFromColumn(size_t jcol);
    void resetSelection();
    void resetAssistant();

    //Helpers:

    QString m_fileName;
    std::unique_ptr<CSVFile> m_csvFile;
    csv::DataArray m_csvArray;
    char m_separator;
    unsigned m_intensityCol;
    unsigned m_coordinateCol;
    unsigned m_firstRow;
    unsigned m_lastRow;
    AxesUnits m_units;
    bool m_dataAvailable;
};
#endif // CSVIMPORTASSISTANT_H
