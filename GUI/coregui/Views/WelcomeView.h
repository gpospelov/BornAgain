// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/WelcomeView.h
//! @brief     Declares class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
    WelcomeView(MainWindow *parent);

public slots:
    void onWebLinkClicked(const QUrl &url);
    void onNewUser();
    void updateRecentProjectPanel();
    void setNotificationText(const QString &text);

private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void generateRecentProjectList();
    QString getCurrentProjectFancyName();
    void setCurrentProjectName(const QString &name);

    QPushButton *m_newProjectButton;
    QPushButton *m_openProjectButton;
    QPushButton *m_newUsertButton;
    MainWindow *m_mainWindow;
    ProjectManager *m_projectManager;
    QSignalMapper *m_signalMapper;
    QVBoxLayout *m_recentProjectLayout;
    FancyLabel *m_currentProName;
    QLabel *m_updateNotification;
};

#endif // WELCOMEVIEW_H
