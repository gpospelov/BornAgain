// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/TestView.h
//! @brief     Defines class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TESTVIEW_H
#define TESTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;

class BA_CORE_API_ TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(MainWindow *mainWindow = 0);

private:
    void test_MaskEditor();
    void test_AccordionWidget();
    void test_RunFitWidget();
    void test_MaterialEditor();
    void test_MinimizerSettings();
    void test_ColorMapLight();


    MainWindow *m_mainWindow;
};

#endif // TESTVIEW_H
