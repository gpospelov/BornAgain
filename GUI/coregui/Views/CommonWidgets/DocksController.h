//  ************************************************************************************************
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
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H

#include "GUI/coregui/Views/CommonWidgets/DockWidgetInfo.h"
#include <QObject>
#include <QSize>
#include <map>

class QMainWindow;
class QMenu;
class QSettings;

//! Handles creation and appearance of docked widgets in the context of QMainWindow. It is used for
//! SampleView and JobView which are based on QMainWindow.

class DocksController : public QObject {
    Q_OBJECT

public:
    DocksController(QMainWindow* mainWindow);

    void addWidget(int id, QWidget* widget, Qt::DockWidgetArea area);

    virtual void onResetLayout(); // #TODO: better name
    void toggleDock(int id);
    void setVisibleDocks(const std::vector<int>& visibleDocks);

    QDockWidget* findDock(int id);
    QDockWidget* findDock(QWidget* widget);
    const QList<QDockWidget*> dockWidgets() const;

    void addDockActionsToMenu(QMenu* menu);

    QHash<QString, QVariant> saveSettings() const;
    void saveSettings(QSettings* settings) const;
    void restoreSettings(const QHash<QString, QVariant>& settings);
    void restoreSettings(const QSettings* settings);

public slots:
    void setDockHeightForWidget(int height);
    void dockToMinMaxSizes();
    void onWidgetCloseRequest();

private:
    struct DockSizeInfo {
        QDockWidget* m_dock = nullptr;
        QSize m_min_size;
        QSize m_max_size;
    };

    QDockWidget* addDockForWidget(QWidget* widget);
    void setTrackingEnabled(bool enabled);
    void handleWindowVisibilityChanged(bool visible);
    virtual bool eventFilter(QObject*, QEvent* event);

    QMainWindow* m_mainWindow;
    std::map<int, DockWidgetInfo> m_docks;
    DockSizeInfo m_dock_info;
    bool m_handleDockVisibilityChanges;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_DOCKSCONTROLLER_H
