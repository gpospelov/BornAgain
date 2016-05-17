// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/TestFitWidgets.h
//! @brief     Declares class TestFitWidgets
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TESTFITWIDGETS_H
#define TESTFITWIDGETS_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class ParameterTuningWidget;
class FitParametersWidget;
class JobItem;
class QTreeView;

//! TestFitWidgets is a temporary widget (created by mainwindow)
//! for testing fitting related widgets.

class BA_CORE_API_ TestFitWidgets : public QWidget
{
    Q_OBJECT
public:
    TestFitWidgets(MainWindow *mainWindow);

    void showEvent(QShowEvent *);

private:
    MainWindow *m_mainWindow;
    ParameterTuningWidget *m_tuningWidget;
    FitParametersWidget *m_fitParametersWidget;
    QTreeView *m_jobTreeView;
    JobItem *m_jobItem;
};

#endif
