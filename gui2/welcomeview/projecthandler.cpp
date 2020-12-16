// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/welcomeview/projecthandler.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/welcomeview/recentprojectsettings.h"
#include "gui2/welcomeview/recentprojectwidget.h"
#include "gui2/welcomeview/userinteractor.h"
#include "mvvm/factories/projectmanagerfactory.h"
#include "mvvm/project/project_types.h"
#include "mvvm/widgets/widgetutils.h"
#include <QMainWindow>

using namespace ModelView;

namespace DaRefl {

ProjectHandler::ProjectHandler(ApplicationModels* models, QWidget* parent)
    : QObject(parent)
    , m_recentProjectSettings(std::make_unique<RecentProjectSettings>())
    , m_userInteractor(std::make_unique<UserInteractor>(m_recentProjectSettings.get(), parent))
    , m_models(models) {
    initProjectManager();
    updateRecentProjectNames();
}

ProjectHandler::~ProjectHandler() = default;

//! Update names (name of the current project, recent project name list, notifies the world).

void ProjectHandler::updateNames() {
    updateCurrentProjectName();
    updateRecentProjectNames();
}

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool ProjectHandler::canCloseProject() const {
    return m_projectManager->closeCurrentProject();
}

void ProjectHandler::onCreateNewProject() {
    if (m_projectManager->createNewProject())
        updateNames();
}

void ProjectHandler::onOpenExistingProject(const QString& dirname) {
    if (m_projectManager->openExistingProject(dirname.toStdString()))
        updateNames();
}

void ProjectHandler::onSaveCurrentProject() {
    if (m_projectManager->saveCurrentProject())
        updateNames();
}

void ProjectHandler::onSaveProjectAs() {
    if (m_projectManager->saveProjectAs())
        updateNames();
}

void ProjectHandler::clearRecentProjectsList() {
    m_recentProjectSettings->clearRecentProjectsList();
    updateNames();
}

void ProjectHandler::initProjectManager() {
    auto modified_callback = [this]() { updateCurrentProjectName(); };
    auto models_callback = [this]() { return m_models->persistent_models(); };
    ProjectContext project_context{modified_callback, models_callback};

    auto select_dir_callback = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir_callback = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto answer_callback = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    UserInteractionContext user_context{select_dir_callback, create_dir_callback, answer_callback};

    m_projectManager = CreateProjectManager(project_context, user_context);
}

//! Updates the name of the current project on main window, notifies the world.

void ProjectHandler::updateCurrentProjectName() {
    const auto current_project_dir = QString::fromStdString(m_projectManager->currentProjectDir());
    const auto is_modified = m_projectManager->isModified();

    // set main window title
    auto title = ModelView::Utils::ProjectWindowTitle(current_project_dir, is_modified);
    if (auto main_window = ModelView::Utils::FindMainWindow(); main_window)
        main_window->setWindowTitle(title);

    currentProjectModified(current_project_dir, is_modified);
}

//! Update recent project list in settings, notifies the world.

void ProjectHandler::updateRecentProjectNames() {
    m_recentProjectSettings->addToRecentProjects(
        QString::fromStdString(m_projectManager->currentProjectDir()));
    recentProjectsListModified(m_recentProjectSettings->recentProjects());
}

} // namespace DaRefl
