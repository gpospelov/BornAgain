// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_PROJECTHANDLER_H
#define DAREFL_WELCOMEVIEW_PROJECTHANDLER_H

#include "darefl_export.h"
#include <QObject>
#include <memory>
#include <vector>

class QWidget;

namespace ModelView {
class ProjectManagerInterface;
}

namespace DaRefl {

class RecentProjectSettings;
class UserInteractor;
class ApplicationModels;
class RecentProjectWidget;

//! Main class to coordinate all activity on user's request to create new project,
//! open existing one, or choose one of recent projects on disk.

class DAREFLCORE_EXPORT ProjectHandler : public QObject {
    Q_OBJECT

public:
    explicit ProjectHandler(ApplicationModels* models, QWidget* parent);
    ~ProjectHandler() override;

signals:
    void currentProjectModified(const QString& project_dir, bool is_modified);
    void recentProjectsListModified(const QStringList& projects);

public slots:
    void updateNames();
    bool canCloseProject() const;
    void onCreateNewProject();
    void onOpenExistingProject(const QString& dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

    void clearRecentProjectsList();

private:
    void initProjectManager();
    void updateCurrentProjectName();
    void updateRecentProjectNames();

    std::unique_ptr<RecentProjectSettings> m_recentProjectSettings;
    std::unique_ptr<UserInteractor> m_userInteractor;
    std::unique_ptr<ModelView::ProjectManagerInterface> m_projectManager;
    ApplicationModels* m_models{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_WELCOMEVIEW_PROJECTHANDLER_H
