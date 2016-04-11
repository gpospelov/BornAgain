// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/PythonScriptWidget.h
//! @brief     Defines class PythonScriptWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PYTHONSCRIPTWIDGET_H
#define PYTHONSCRIPTWIDGET_H

#include "WinDllMacros.h"
#include <QDialog>

class QToolBar;
class QTextEdit;
class WarningSignWidget;
class ProjectManager;
class SampleModel;
class InstrumentModel;

//! The PythonScriptWidget displays a python script which represents full simulation.
//! Part of SimulationSetupWidget
class BA_CORE_API_ PythonScriptWidget : public QDialog
{
    Q_OBJECT

public:
    PythonScriptWidget(QWidget *parent = 0);

    void generatePythonScript(SampleModel *sampleModel, InstrumentModel *instrumentModel,
                              const QString &outputDir = QString());

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void onExportToFileButton();

private:
    QPoint getPositionForWarningSign();

    QToolBar *m_toolBar;
    QTextEdit *m_textEdit;
    WarningSignWidget *m_warningSign;
    QString m_outputDir;
};

#endif
