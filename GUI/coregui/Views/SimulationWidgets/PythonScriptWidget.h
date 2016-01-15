// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/PythonScriptWidget.h
//! @brief     Defines class PythonScriptWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONSCRIPTWIDGET_H
#define PYTHONSCRIPTWIDGET_H

#include "WinDllMacros.h"
#include <QDialog>

class QToolBar;
class QTextEdit;
class SampleModel;
class InstrumentModel;
class WarningSignWidget;
class ProjectManager;

//! The PythonScriptWidget displays a python script which represents full simulation.
//! Part of SimulationSetupWidget
class BA_CORE_API_ PythonScriptWidget : public QDialog
{
    Q_OBJECT

public:
    PythonScriptWidget(QWidget *parent = 0, ProjectManager *projectManager = 0);
    virtual ~PythonScriptWidget();

    void generatePythonScript(SampleModel *sampleModel, InstrumentModel *instrumentModel);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void onExportToFileButton();

private:
    QPoint getPositionForWarningSign();
    QToolBar *m_toolBar;
    QTextEdit *m_textEdit;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    WarningSignWidget *m_warningSign;
    ProjectManager *m_projectManager;
};

#endif
