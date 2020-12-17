//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/welcomeview/recentprojectwidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_WELCOMEVIEW_RECENTPROJECTWIDGET_H
#define BORNAGAIN_GUI2_WELCOMEVIEW_RECENTPROJECTWIDGET_H

#include "darefl_export.h"
#include <QWidget>
#include <memory>
#include <vector>

class QBoxLayout;

namespace gui2 {

class ProjectPaneWidget;

//! Widget with the name of current project and collection of recent projects.
//! Occupies left part of WelcomeView.

class DAREFLCORE_EXPORT RecentProjectWidget : public QWidget {
    Q_OBJECT

public:
    explicit RecentProjectWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void setCurrentProject(const QString& project_dir, bool is_modified);

    void setRecentProjectsList(const QStringList& projects);

signals:
    void projectSelected(const QString& project_dir);

private:
    QBoxLayout* createCurrentProjectLayout() const;
    QBoxLayout* createRecentProjectLayout();
    QWidget* createRecentProjectScrollArea();

    ProjectPaneWidget* m_currentProjectPane;
    std::vector<ProjectPaneWidget*> m_recentProjectPanes;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_WELCOMEVIEW_RECENTPROJECTWIDGET_H
