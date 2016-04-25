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
class ModelTuningWidget;
class FitParametersWidget;

//! TestFitWidgets is a temporary widget (created by mainwindow)
//! for testing fitting related widgets.

class BA_CORE_API_ TestFitWidgets : public QWidget
{
    Q_OBJECT
public:
    TestFitWidgets(MainWindow *mainWindow);

private:
    MainWindow *m_mainWindow;
    ModelTuningWidget *m_tuningWidget;
    FitParametersWidget *m_fitParametersWidget;
};

#endif
