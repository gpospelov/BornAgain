// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.h
//! @brief     Defines class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>

class MainWindow;

class TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(MainWindow *window, QWidget *parent = 0);

private:
    void test_MaskEditor();
    void test_AccordionWidget();
    void test_RunFitWidget();
    MainWindow *m_mainWindow;
};

#endif
