//  ************************************************************************************************
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
//  ************************************************************************************************

#include "GUI/coregui/Views/CommonWidgets/DocksController.h"
#include "Base/Utils/Assert.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QAbstractItemView>
#include <QAction>
#include <QDockWidget>
#include <QEvent>
#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QTimer>

namespace {
const char dockWidgetActiveState[] = "DockWidgetActiveState";
const char StateKey[] = "State";
const int settingsVersion = 2;

QString stripAccelerator(const QString& text) {
    QString res = text;
    for (int index = res.indexOf('&'); index != -1; index = res.indexOf('&', index + 1))
        res.remove(index, 1);
    return res;
}

} // namespace

DocksController::DocksController(QMainWindow* mainWindow)
    : QObject(mainWindow), m_mainWindow(mainWindow) {
    m_mainWindow->setDocumentMode(true);
    m_mainWindow->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    m_mainWindow->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    m_mainWindow->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    m_mainWindow->installEventFilter(this);
}

QDockWidget* DocksController::addDockForWidget(QWidget* widget) {
    auto dockWidget = new QDockWidget(m_mainWindow);
    dockWidget->setWidget(widget);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable
                            | QDockWidget::DockWidgetFloatable);
    dockWidget->setObjectName(widget->objectName() + QLatin1String("DockWidget"));

    QString title = widget->windowTitle();
    dockWidget->toggleViewAction()->setProperty("original_title", title);
    title = stripAccelerator(title);
    dockWidget->setWindowTitle(title);

    connect(dockWidget->toggleViewAction(), &QAction::triggered, [=]() {
        if (dockWidget->isVisible())
            dockWidget->raise();
    });

    connect(dockWidget, &QDockWidget::visibilityChanged, [this, dockWidget](bool visible) {
        if (m_handleDockVisibilityChanges)
            dockWidget->setProperty(dockWidgetActiveState, visible);
    });

    dockWidget->setProperty(dockWidgetActiveState, true);

    return dockWidget;
}

void DocksController::addWidget(int id, QWidget* widget, Qt::DockWidgetArea area) {
    if (m_docks.find(id) != m_docks.end())
        throw GUIHelpers::Error("DocksController::addWidget() -> Error. "
                                "Attempt to add widget id twice");

    auto dock = addDockForWidget(widget);
    m_docks[id] = DockWidgetInfo(dock, widget, area);

    QList<QAbstractItemView*> frames = widget->findChildren<QAbstractItemView*>();
    for (int i = 0; i < frames.count(); ++i)
        frames[i]->setFrameStyle(QFrame::NoFrame);
}

void DocksController::resetLayout() {
    setTrackingEnabled(false);
    for (auto dockWidget : dockWidgets()) {
        dockWidget->setFloating(false);
        m_mainWindow->removeDockWidget(dockWidget);
    }

    for (auto& it : m_docks)
        m_mainWindow->addDockWidget(it.second.area(), it.second.dock());

        // Fixes issue: https://bugreports.qt.io/browse/QTBUG-65592
#if QT_VERSION >= 0x050600
    if (dockWidgets().size() > 0)
        m_mainWindow->resizeDocks({dockWidgets().first()}, {10}, Qt::Horizontal);
#endif

    for (auto dockWidget : dockWidgets())
        dockWidget->show();

    setTrackingEnabled(true);
}

void DocksController::toggleDock(int id) {
    auto dock = findDock(id);
    dock->setHidden(!dock->isHidden());
}

QDockWidget* DocksController::findDock(int id) {
    ASSERT(m_docks.find(id) != m_docks.end());
    return m_docks[id].dock();
}

QDockWidget* DocksController::findDock(QWidget* widget) {
    for (auto& it : m_docks)
        if (it.second.widget() == widget)
            return it.second.dock();

    throw GUIHelpers::Error("DocksController::findDock() -> Can't find dock for widget");
}

const QList<QDockWidget*> DocksController::dockWidgets() const {
    return m_mainWindow->findChildren<QDockWidget*>();
}

//! Show docks with id's from the list. Other docks will be hidden.

void DocksController::setVisibleDocks(const std::vector<int>& visibleDocks) {
    for (auto& it : m_docks) {
        if (std::find(visibleDocks.begin(), visibleDocks.end(), it.first) != visibleDocks.end())
            it.second.dock()->show();
        else
            it.second.dock()->hide();
    }
}

//! A hack to request update of QDockWidget size if its child (e.g. InfoWidget) wants it.
//! The problem bypassed here is that there is no direct method to QMainWindow to recalculate
//! position of splitters surrounding given QDockWidget. So our child QWidget requests here
//! the change of Min/Max size of QDockWidget, this will trigger recalculation of QDockWidget
//! layout and will force QDockWidget to respect sizeHints provided by ChildWidget. Later (in one
//! single timer shot) we return min/max sizes of QDockWidget back to re-enable splitters
//! functionality.

void DocksController::setDockHeightForWidget(int height) {
    QWidget* widget = qobject_cast<QWidget*>(sender());
    ASSERT(widget);
    QDockWidget* dock = findDock(widget);
    ASSERT(dock);

    m_dock_info.m_dock = dock;
    m_dock_info.m_min_size = dock->minimumSize();
    m_dock_info.m_max_size = dock->maximumSize();

    if (height > 0) {
        if (dock->height() < height)
            dock->setMinimumHeight(height);
        else
            dock->setMaximumHeight(height);
    }

    QTimer::singleShot(1, this, &DocksController::dockToMinMaxSizes);
}

void DocksController::dockToMinMaxSizes() {
    ASSERT(m_dock_info.m_dock);
    m_dock_info.m_dock->setMinimumSize(m_dock_info.m_min_size);
    m_dock_info.m_dock->setMaximumSize(m_dock_info.m_max_size);
    m_dock_info.m_dock = nullptr;
}

void DocksController::setTrackingEnabled(bool enabled) {
    if (enabled) {
        m_handleDockVisibilityChanges = true;
        for (auto dockWidget : dockWidgets())
            dockWidget->setProperty(dockWidgetActiveState, dockWidget->isVisible());
    } else {
        m_handleDockVisibilityChanges = false;
    }
}

void DocksController::handleWindowVisibilityChanged(bool visible) {
    m_handleDockVisibilityChanges = false;
    for (auto dockWidget : dockWidgets()) {
        if (dockWidget->isFloating()) {
            dockWidget->setVisible(visible && dockWidget->property(dockWidgetActiveState).toBool());
        }
    }
    if (visible)
        m_handleDockVisibilityChanges = true;
}

bool DocksController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Show)
        handleWindowVisibilityChanged(true);
    else if (event->type() == QEvent::Hide)
        handleWindowVisibilityChanged(false);

    return QObject::eventFilter(obj, event);
}

void DocksController::addDockActionsToMenu(QMenu* menu) {
    QList<QAction*> actions;
    for (auto dockWidget : dockWidgets()) {
        if (dockWidget->property("managed_dockwidget").isNull()
            && dockWidget->parentWidget() == m_mainWindow) {
            QAction* action = dockWidget->toggleViewAction();
            action->setText(action->property("original_title").toString());
            actions.append(action);
        }
    }
    std::sort(actions.begin(), actions.end(), [](const QAction* action1, const QAction* action2) {
        return stripAccelerator(action1->text()).toLower()
               < stripAccelerator(action2->text()).toLower();
    });

    foreach (QAction* action, actions)
        menu->addAction(action);
}

void DocksController::saveSettings(QSettings* settings) const {
    QHash<QString, QVariant> hash = saveSettings();
    QHashIterator<QString, QVariant> it(hash);
    while (it.hasNext()) {
        it.next();
        settings->setValue(it.key(), it.value());
    }
}

void DocksController::restoreSettings(const QSettings* settings) {
    QHash<QString, QVariant> hash;
    foreach (const QString& key, settings->childKeys()) { hash.insert(key, settings->value(key)); }
    restoreSettings(hash);
}

QHash<QString, QVariant> DocksController::saveSettings() const {
    QHash<QString, QVariant> settings;
    settings.insert(QLatin1String(StateKey), m_mainWindow->saveState(settingsVersion));
    for (auto dockWidget : dockWidgets()) {
        settings.insert(dockWidget->objectName(), dockWidget->property(dockWidgetActiveState));
    }
    return settings;
}

void DocksController::restoreSettings(const QHash<QString, QVariant>& settings) {
    QByteArray ba = settings.value(QLatin1String(StateKey), QByteArray()).toByteArray();
    if (!ba.isEmpty())
        m_mainWindow->restoreState(ba, settingsVersion);
    for (auto widget : dockWidgets()) {
        widget->setProperty(dockWidgetActiveState, settings.value(widget->objectName(), false));
    }
}
