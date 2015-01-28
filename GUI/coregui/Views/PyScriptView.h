// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PyScriptView.h
//! @brief     Defines class PyScriptView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSCRIPTVIEW_H
#define PYSCRIPTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>

class SimulationDataModel;
class QPushButton;
class QTextEdit;

class BA_CORE_API_ PyScriptView : public QWidget
{
    Q_OBJECT

public:
    PyScriptView(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    virtual ~PyScriptView() {}

public slots:
    void onOpenScript();
    void onSaveScript();
    void onTextChanged();

private:
    QPushButton *openButton;
    QPushButton *saveButton;
    QTextEdit *scriptEdit;
    SimulationDataModel *mp_simulation_data_model;
    QString oldScript;
    QString oldScriptFilename;
};

#endif // PYSCRIPTVIEW_H
