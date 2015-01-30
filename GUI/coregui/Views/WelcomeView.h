// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/WelcomeView.h
//! @brief     Defines class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include <QString>
#include "qpushbutton.h"
#include <QCommandLinkButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSignalMapper>



class BA_CORE_API_ WelcomeView : public QWidget
{
    Q_OBJECT

public:
    WelcomeView(MainWindow *parent);

public slots:
    void onWebLinkClicked(const QUrl &url);
    //void onNewProject();
    //void onOpenProject();
    void onNewUser();
    void updateRecentProjectPanel();

private:
    QPushButton *newProjectButton;
    QPushButton *openProjectButton;
    QPushButton *newUsertButton;
    MainWindow *m_mainWindow;
    ProjectManager *m_projectManager;
    void generateRecentProjectList();
    QSignalMapper *m_signalMapper;
    QVBoxLayout *m_recentProjectLayout;
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
};

#endif // WELCOMEVIEW_H
