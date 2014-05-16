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

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    WelcomeView(MainWindow *parent);

public slots:
    void onWebLinkClicked(const QUrl &url);
    //void onNewProject();
    //void onOpenProject();
    void onNewUser();

private:
    QPushButton *newProjectButton;
    QPushButton *openProjectButton;
    QPushButton *newUsertButton;
    MainWindow *m_mainWindow;
    ProjectManager *m_projectManager;
    void generateRecentProjectList(QVBoxLayout *layout);
    QSignalMapper *m_signalMapper;
};

#endif // WELCOMEVIEW_H
