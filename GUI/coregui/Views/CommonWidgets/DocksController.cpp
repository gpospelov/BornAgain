// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/DocksController.cpp
//! @brief     Implements class DocksController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DocksController.h"
#include "GUIHelpers.h"
#include "fancymainwindow.h"
#include <QAbstractItemView>
#include <QDockWidget>

DocksController::DocksController(Manhattan::FancyMainWindow* mainWindow)
    : QObject(mainWindow), m_mainWindow(mainWindow)
{
    m_mainWindow->setDocumentMode(true);
    m_mainWindow->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    m_mainWindow->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    m_mainWindow->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void DocksController::addWidget(int id, QWidget* widget, Qt::DockWidgetArea area)
{
    if (m_docks.find(id) != m_docks.end())
        throw GUIHelpers::Error("DocksController::addWidget() -> Error. "
                                "Attempt to add widget id twice");

    auto dock = m_mainWindow->addDockForWidget(widget);
    m_docks[id] = DockWidgetInfo(dock, widget, area);

    QList<QAbstractItemView*> frames = widget->findChildren<QAbstractItemView*>();
    for (int i = 0; i < frames.count(); ++i)
        frames[i]->setFrameStyle(QFrame::NoFrame);
}

void DocksController::onResetLayout()
{
    m_mainWindow->setTrackingEnabled(false);
    QList<QDockWidget*> dockWidgetList = m_mainWindow->dockWidgets();
    for (QDockWidget* dockWidget : dockWidgetList) {
        dockWidget->setFloating(false);
        m_mainWindow->removeDockWidget(dockWidget);
    }

    for (auto& it : m_docks)
        m_mainWindow->addDockWidget(it.second.area(), it.second.dock());

    for (QDockWidget* dockWidget : dockWidgetList)
        dockWidget->show();

    m_mainWindow->setTrackingEnabled(true);
}

QDockWidget* DocksController::dock(int id)
{
    return get_info(id).dock();
}

QDockWidget* DocksController::findDock(QWidget* widget)
{
    for (auto& it : m_docks)
        if (it.second.widget() == widget)
            return it.second.dock();

    throw GUIHelpers::Error("DocksController::findDock() -> Can't find dock for widget");
}

DockWidgetInfo DocksController::get_info(int id)
{
    if (m_docks.find(id) == m_docks.end())
        throw GUIHelpers::Error("DocksController::addWidget() -> Error. Non existing id.");

    return m_docks[id];
}
