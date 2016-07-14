// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/PythonScriptWidget.h
//! @brief     Declares class PythonScriptWidget
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

#include <QDialog>
#include "WinDllMacros.h"

class QToolBar;
class QTextEdit;
class WarningSignWidget;
class ProjectManager;
class SampleModel;
class InstrumentModel;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;

//! The PythonScriptWidget displays a python script which represents full simulation.
//! Part of SimulationSetupWidget
class BA_CORE_API_ PythonScriptWidget : public QDialog
{
    Q_OBJECT

public:
    PythonScriptWidget(QWidget *parent = 0);

    void generatePythonScript(const MultiLayerItem *sampleItem,
                              const InstrumentItem *instrumentItem,
                              const SimulationOptionsItem *optionItem = 0,
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

#endif // PYTHONSCRIPTWIDGET_H
