// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/DocksController.h
//! @brief     Defines class DocksController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DOCKSCONTROLLER_H
#define DOCKSCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>

class QMainWindow;

//! Handles appearing of docked widget in the context of DocksView.

class BA_CORE_API_ DocksController : public QObject
{
    Q_OBJECT

public:
    DocksController(QMainWindow* mainWindow);

private:
    QMainWindow* m_mainWindow;
};

#endif //  DOCKSCONTROLLER_H
