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


/*
If a file contains only the decimal bytes 9–13, 32–126, it's probably a pure ASCII text file.
Otherwise, it's not. However, it may still be text in another encoding.

If, in addition to the above bytes, the file contains only the decimal bytes 128–255,
it's probably a text file in an 8-bit or variable-length ASCII-based encoding such as ISO-8859-1,
UTF-8 or ASCII+Big5. If not, for some purposes you may be able to stop here and consider the
file to be binary. However, it may still be text in a 16- or 32-bit encoding.

If a file doesn't meet the above constraints, examine the first 2–4 bytes of the file for a
byte-order mark:

    If the first two bytes are hex FE FF, the file is tentatively UTF-16 BE.
    If the first two bytes are hex FF FE, and the following two bytes are not hex 00 00,
    the file is tentatively UTF-16 LE.
    If the first four bytes are hex 00 00 FE FF, the file is tentatively UTF-32 BE.
    If the first four bytes are hex FF FE 00 00, the file is tentatively UTF-32 LE.

If, through the above checks, you have determined a tentative encoding, then check only for the
corresponding encoding below, to ensure that the file is not a binary file which happens to match
a byte-order mark.

If you have not determined a tentative encoding, the file might still be a text file in one of these
encodings, since the byte-order mark is not mandatory, so check for all encodings in the following
list:

    If the file contains only big-endian two-byte words with the decimal values 9–13, 32–126, and 128 or above, the file is probably UTF-16 BE.
    If the file contains only little-endian two-byte words with the decimal values 9–13, 32–126, and 128 or above, the file is probably UTF-16 LE.
    If the file contains only big-endian four-byte words with the decimal values 9–13, 32–126, and 128 or above, the file is probably UTF-32 BE.
    If the file contains only little-endian four-byte words with the decimal values 9–13, 32–126, and 128 or above, the file is probably UTF-32 LE.

If, after all these checks, you still haven't determined an encoding, the file isn't a text file
in any ASCII-based encoding I know about, so for most purposes you can probably consider it to be binary
(it might still be a text file in a non-ASCII encoding such as EBCDIC,but I suspect that's
well outside the scope of your concern).
*/
bool isAscii(QString filename);

}

//! Logic for importing intensity data from csv files

class BA_CORE_API_ CsvImportAssistant: public QObject
{
    Q_OBJECT
public:
    CsvImportAssistant(const QString& file, const bool useGUI = false, QWidget* parent = nullptr);
    ImportDataInfo getData(){return m_dataAvailable ? fillData() : ImportDataInfo();}
    static void showErrorMessage(std::string message);
    static double stringToDouble(std::string string_to_parse);
    void setIntensityColumn(unsigned iCol){m_intensityCol = iCol;}
    void setCoordinateColumn(unsigned iCol, AxesUnits units){m_coordinateCol = iCol; m_units = units;}
    void setFirstRow(unsigned iRow){m_firstRow = iRow;}
    void setLastRow(unsigned iRow){m_lastRow = iRow;}
    unsigned columnCount(){return unsigned(m_csvArray[0].size());}
    char separator(){return m_separator;}

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
