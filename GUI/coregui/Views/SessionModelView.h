// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SessionModelView.h
//! @brief     Declares class SessionModelView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODELVIEW_H
#define SESSIONMODELVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;

//! The SessionModelView is a technical view which shows the content all current application
//! models. It appears as an additional view in the main navigation bar on the left, right
//! after the jobView (if corresponding setting of MainWindow is On).

class BA_CORE_API_ SessionModelView : public QWidget
{
    Q_OBJECT

public:
    SessionModelView(MainWindow *mainWindow = 0);

private:
    MainWindow *m_mainWindow;
};

#endif
