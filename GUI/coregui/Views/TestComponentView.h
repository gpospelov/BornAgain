// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestComponentView.h
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TECTCOMPONENTVIEW_H
#define TECTCOMPONENTVIEW_H

#include <QWidget>

class MainWindow;

class TestComponentView : public QWidget
{
    Q_OBJECT
public:
    TestComponentView(MainWindow *mainWindow = 0);

private:
    void test_ComponentEditor();
    MainWindow *m_mainWindow;
};

#endif
