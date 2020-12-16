// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_RECENTPROJECTSETTINGS_H
#define DAREFL_WELCOMEVIEW_RECENTPROJECTSETTINGS_H

#include "darefl_export.h"
#include <QStringList>

namespace gui2 {

//! Collection of settings for RecentProjectWidget. Used to save last directory selected
//! by the user, and list of recent projects. Relies on QSettings machinery.

class DAREFLCORE_EXPORT RecentProjectSettings {
public:
    RecentProjectSettings();
    ~RecentProjectSettings();

    QString currentWorkdir() const;

    void updateWorkdirFromSelection(const QString& dirname);

    QStringList recentProjects();

    void addToRecentProjects(const QString& dirname);

    void clearRecentProjectsList();

private:
    void writeSettings();
    void readSettings();

    QString m_currentWorkdir;
    QStringList m_recentProjects;
};

} // namespace gui2

#endif // DAREFL_WELCOMEVIEW_RECENTPROJECTSETTINGS_H
