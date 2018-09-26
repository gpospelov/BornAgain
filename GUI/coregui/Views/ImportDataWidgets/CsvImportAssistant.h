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
#include "OutputData.h"
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <memory>

class QBoxLayout;
using namespace std;

//! Dialog to hold ImportAssistant.

class BA_CORE_API_ CsvImportAssistant : public QDialog
{
    Q_OBJECT

public:
    CsvImportAssistant(QString dir = "./", QString file = "", QWidget* parent = nullptr);
    QString filepath() const;
    char separator() const;
    void setHeaders();
    unsigned firstLine() const;
    unsigned lastLine() const;
    void Reload();
    unique_ptr<OutputData<double>> getData();
    QStringList relevantHeaders = {"Intensity","theta","2theta","q"};
    enum relevantColumns {_intensity_,_theta_,_2theta_,_q_};

public slots:
    void onImportButton();
    void onReloadButton();
    void onRejectButton();
    void onIntChanged(int _ = 0);
    void OnColumnClicked(int row, int column);
    void onColumnRightClick(const QPoint position);

private:
    QBoxLayout* createLayout();
    QBoxLayout* createFileDetailsLayout();

    char guessSeparator() const;
    void generate_table();
    void set_table_data(vector<vector<string>> dataArray);
    void removeBlankColumns(vector<vector<string>> &dataArray);
    void extractDesiredColumns(vector<vector<string>> &dataArray);
    bool hasEqualLengthLines(vector<vector<string> > &dataArray);
    void setRowNumbering();



    QString m_dirName;
    QString m_fileName;
    unsigned m_lastDataRow;
    unsigned m_intensityCol;
    unsigned m_coordinateCol;
    QString  m_coordinateName;
    unsigned m_singleCol;

    QTableWidget* m_tableWidget;
    QLineEdit* m_separatorField;
    QSpinBox* m_firstDataRowSpinBox;
    QSpinBox* m_singleDataColSpinBox;

};

#endif // CSVIMPORTASSISTANT_H
