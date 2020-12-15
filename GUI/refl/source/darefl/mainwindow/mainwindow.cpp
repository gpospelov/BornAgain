// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <darefl/importdataview/importdataview.h>
#include <darefl/mainwindow/actionmanager.h>
#include <darefl/mainwindow/mainbarwidget.h>
#include <darefl/mainwindow/mainwindow.h>
#include <darefl/mainwindow/simulationview.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/settingsview/settingsview.h>
#include <darefl/welcomeview/welcomeview.h>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

namespace DaRefl
{

MainWindow::MainWindow()
    : m_models(std::make_unique<ApplicationModels>()), m_actionManager(new ActionManager(this))
{
    init_application();
    init_components();
    init_connections();
    setCentralWidget(m_barWidget);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (m_welcomeView->canCloseProject()) {
        write_settings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("quickrefl");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::init_components()
{
    m_welcomeView = new WelcomeView(m_models.get());
    m_importDataView = new ImportDataView(m_models.get());
    m_simView = new SimulationView(m_models.get());
    m_settingsView = new SettingsView(m_models.get());
    m_barWidget = new MainBarWidget;

    m_barWidget->addWidget(m_welcomeView, "Project");
    m_barWidget->addWidget(m_importDataView, "Data");
    m_barWidget->addWidget(m_simView, "Simulation");
    m_barWidget->addWidget(new QWidget, "Fitting", false);
    m_barWidget->addWidget(new QWidget, "Export", false);
    m_barWidget->addWidget(m_settingsView, "Settings");
    m_barWidget->setCurrentIndex(0);
}

//! Setup main connections.

void MainWindow::init_connections()
{
    // connect ActionManager signals with WelcomeView slots
    connect(m_actionManager, &ActionManager::createNewProjectRequest, m_welcomeView,
            &WelcomeView::onCreateNewProject);
    connect(m_actionManager, &ActionManager::openExistingProjectRequest, m_welcomeView,
            &WelcomeView::onOpenExistingProject);
    connect(m_actionManager, &ActionManager::saveCurrentProjectRequest, m_welcomeView,
            &WelcomeView::onSaveCurrentProject);
    connect(m_actionManager, &ActionManager::saveProjectAsRequest, m_welcomeView,
            &WelcomeView::onSaveProjectAs);
    connect(m_actionManager, &ActionManager::clearResentProjectListRequest, m_welcomeView,
            &WelcomeView::onClearRecentProjectsList);

    connect(m_welcomeView, &WelcomeView::recentProjectsListModified, m_actionManager,
            &ActionManager::setRecentProjectsList);

    m_welcomeView->updateNames();
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}

} // namespace DaRefl
