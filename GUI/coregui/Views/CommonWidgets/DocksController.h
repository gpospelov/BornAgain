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
#include "DockWidgetInfo.h"
#include <QObject>
#include <map>

namespace Manhattan { class FancyMainWindow; }

//! Handles appearing of docked widget in the context of DocksView.

class BA_CORE_API_ DocksController : public QObject
{
    Q_OBJECT

public:
    DocksController(Manhattan::FancyMainWindow* mainWindow);

    void addWidget(int id, QWidget* widget, Qt::DockWidgetArea area);

    virtual void onResetLayout();

    QDockWidget* dock(int id);

    QDockWidget* findDock(QWidget* widget);

private:
    DockWidgetInfo get_info(int id);

    Manhattan::FancyMainWindow* m_mainWindow;
    std::map<int, DockWidgetInfo> m_docks;
};

#endif //  DOCKSCONTROLLER_H
