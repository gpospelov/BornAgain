// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/WelcomeView.h
//! @brief     Defines class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include "WinDllMacros.h"
#include <QLabel>

class QPushButton;
class MainWindow;
class ProjectManager;
class QSignalMapper;
class QVBoxLayout;
class FancyLabel;

class BA_CORE_API_ WelcomeView : public QWidget
{
    Q_OBJECT
public:
    WelcomeView(MainWindow* parent);

public slots:
    void onWebLinkClicked(const QUrl& url);
    void onNewUser();
    void updateRecentProjectPanel();
    void setNotificationText(const QString& text);

private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void generateRecentProjectList();
    QString currentProjectFancyName();
    void setCurrentProjectName(const QString& name);
    ProjectManager* projectManager();

    QPushButton* m_newProjectButton;
    QPushButton* m_openProjectButton;
    QPushButton* m_newUsertButton;
    MainWindow* m_mainWindow;
    QSignalMapper* m_signalMapper;
    QVBoxLayout* m_recentProjectLayout;
    FancyLabel* m_currentProName;
    QLabel* m_updateNotification;
};

#endif // WELCOMEVIEW_H
