// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/DataSelector.h
//! @brief     Defines class DataSelector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATASELECTOR_H
#define DATASELECTOR_H

#include "WinDllMacros.h"
#include "ImportDataInfo.h"
#include "CsvImportAssistant.h"
#include <QAction>
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <memory>

class QBoxLayout;

enum  RelevantColumns {_intensity_,_theta_,_2theta_,_q_};
const QStringList HeaderLabels{"Intensity","theta","2theta","q"};
const QStringList UnitsLabels{"default", "bin", "rad", "deg", "mm", "1/nm"};

//! Dialog to hold ImportAssistant.

class DataSelector : public QDialog
{
    Q_OBJECT
public:
    DataSelector(csv::DataArray csvArray, QWidget* parent = nullptr);
    unsigned firstLine() const;
    unsigned lastLine() const;
    unsigned intensityColumn() const {return m_intensityCol;}
    unsigned coordinateColumn() const {return m_coordinateCol;}
    unsigned maxLines() const;
    AxesUnits units() const;
    char separator() const;
    void setHeaders();
    void setColumnAsCoordinate(int coord);
    void setColumnAsIntensity();
    void setCoordinateUnits();
    void setFirstRow();
    void setLastRow();
    void setDataArray(csv::DataArray csvArray){m_data = csvArray; updateData();}
    void resetSelection();
    void updateSelection();

public slots:
    void onImportButton();
    void onCancelButton();
    void onColumnRightClick(QPoint position);

signals:
    void separatorChanged(char newSeparator);

private:
    bool updateData();
    QBoxLayout* createLayout();
    void setTableData();
    void populateUnitsComboBox(int coordinate);
    void greyoutTableRegions();
    bool dataLooksGood();

    bool needsGreyout(int iRow, int jCol);
    void greyoutCell(int i, int j, bool yes);

    csv::DataArray m_data;

    unsigned m_intensityCol;
    unsigned m_coordinateCol;
    QString m_coordinateName;

    QTableWidget* m_tableWidget;
    QLineEdit* m_separatorField;
    QSpinBox* m_firstDataRowSpinBox;
    QSpinBox* m_lastDataRowSpinBox;
    QPushButton* m_importButton;
    QPushButton* m_cancelButton;
    QComboBox* m_coordinateUnitsSelector;
    QAction* m_setAsTheta;
    QAction* m_setAs2Theta;
    QAction* m_setAsQ;
    QAction* m_setAsIntensity;
};

#endif // DATASELECTOR_H
