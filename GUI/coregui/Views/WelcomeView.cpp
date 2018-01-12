// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/WelcomeView.cpp
//! @brief     Implements class WelcomeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "WelcomeView.h"
#include "DesignerHelper.h"
#include "FancyLabel.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectdocument.h"
#include "projectmanager.h"
#include "qstringutils.h"
#include <QCommandLinkButton>
#include <QDesktopServices>
#include <QSignalMapper>
#include <QUrl>
#include <QVBoxLayout>

namespace
{
const int buttonHeight = 45;
const int buttonWidth = 140;
}

WelcomeView::WelcomeView(MainWindow* parent)
    : m_mainWindow(parent)
{
    QColor bgColor(240, 240, 240, 255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    // button layout
    QFont buttonFont;
    buttonFont.setPointSize(DesignerHelper::getLabelFontSize());
    buttonFont.setBold(false);

    m_newProjectButton = new QPushButton("New Project");
    m_newProjectButton->setMinimumWidth(buttonWidth);
    m_newProjectButton->setMinimumHeight(buttonHeight);
    m_newProjectButton->setFont(buttonFont);
    m_newProjectButton->setToolTip("Create new project");
    m_newProjectButton->setAttribute(Qt::WA_MacShowFocusRect, false);

    m_openProjectButton = new QPushButton("Open Project");
    m_openProjectButton->setMinimumWidth(buttonWidth);
    m_openProjectButton->setMinimumHeight(buttonHeight);
    m_openProjectButton->setFont(buttonFont);
    m_openProjectButton->setToolTip("Open existing project");

    m_newUsertButton = new QPushButton("New to BornAgain?");
    m_newUsertButton->setMinimumWidth(buttonWidth);
    m_newUsertButton->setMinimumHeight(buttonHeight);
    m_newUsertButton->setFont(buttonFont);
    m_newUsertButton->setToolTip("Open BornAgain web site");

    QVBoxLayout* buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(m_newProjectButton);
    buttonLayout->addWidget(m_openProjectButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_newUsertButton);

    QHBoxLayout* buttonPanel = new QHBoxLayout;
    buttonPanel->setContentsMargins(30, 0, 30, 0);
    buttonPanel->addLayout(buttonLayout);

    // current project layout
    QVBoxLayout* currentProjectLayout = new QVBoxLayout;
    currentProjectLayout->setContentsMargins(30, 0, 0, 0);
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel* currentProLabel = new QLabel("Current Project:");
    currentProLabel->setFont(titleFont);

    m_currentProName = new FancyLabel("Untitled");
    currentProjectLayout->addWidget(currentProLabel);
    currentProjectLayout->addWidget(m_currentProName);

    // recent project layout
    m_recentProjectLayout = new QVBoxLayout;
    m_recentProjectLayout->setContentsMargins(30, 0, 0, 0);

    // project layout
    QVBoxLayout* projectLayout = new QVBoxLayout;
    projectLayout->addLayout(currentProjectLayout);
    projectLayout->addSpacing(15);
    projectLayout->addLayout(m_recentProjectLayout);

    // update notification label
    m_updateNotification = new QLabel(this);
    m_updateNotification->setText("");
    m_updateNotification->setContentsMargins(40, 10, 0, 0);
    m_updateNotification->setOpenExternalLinks(true);
    m_updateNotification->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_updateNotification->setTextFormat(Qt::RichText);

    // assembling all together
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout* itemContainerLayout = new QHBoxLayout;
    itemContainerLayout->addLayout(buttonPanel);
    itemContainerLayout->addWidget(line);
    //    itemContainerLayout->addLayout(m_recentProjectLayout);
    itemContainerLayout->addLayout(projectLayout);
    itemContainerLayout->addStretch(1);

    QWidget* itemContainerWidget = new QWidget;
    itemContainerWidget->setLayout(itemContainerLayout);
    itemContainerWidget->setFixedHeight(430);

    QVBoxLayout* containerLayout = new QVBoxLayout;
    containerLayout->setMargin(0);
    containerLayout->addWidget(itemContainerWidget);
    containerLayout->addWidget(m_updateNotification);
    containerLayout->addStretch(1);

    QWidget* containerWidget = new QWidget;
    containerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    containerWidget->setObjectName("containerWidget");
    containerWidget->setMaximumWidth(800);
    containerWidget->setContentsMargins(0, 30, 0, 0);
    containerWidget->setStyleSheet(QString::fromUtf8("QWidget#containerWidget\n"
                                                     "{\n"
                                                     "    border-left: 1px solid gray;\n"
                                                     "    border-right: 1px solid gray;\n"
                                                     "    background-color:white;\n"
                                                     "}\n"));
    containerWidget->setLayout(containerLayout);

    auto mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(containerWidget);
    mainLayout->addWidget(new QWidget);
    setLayout(mainLayout);

    connect(m_newProjectButton, &QPushButton::clicked,
            projectManager(), &ProjectManager::newProject);
    connect(m_openProjectButton, &QPushButton::clicked, [=](){projectManager()->openProject();});
    connect(m_newUsertButton, &QPushButton::clicked,
            this, &WelcomeView::onNewUser);
    connect(projectManager(), &ProjectManager::modified,
            this, &WelcomeView::updateRecentProjectPanel);

    updateRecentProjectPanel();
}

void WelcomeView::generateRecentProjectList()
{
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel* recentProLabel = new QLabel("Recent Projects:");
    recentProLabel->setFont(titleFont);

    setCurrentProjectName(currentProjectFancyName());
    m_recentProjectLayout->addWidget(recentProLabel);

    QCommandLinkButton* slotButtons[Constants::MAX_RECENT_PROJECTS];
    m_signalMapper = new QSignalMapper(this);

    int i(0);
    foreach (QString file, projectManager()->recentProjects()) {
        QFont font;
        font.setPointSize(DesignerHelper::getLabelFontSize());
        font.setBold(false);

        QPalette palette;
        palette.setColor(QPalette::ButtonText, QColor(41, 73, 150));

        slotButtons[i] = new QCommandLinkButton;
        slotButtons[i]->setText(GUI_StringUtils::withTildeHomePath(file));
        slotButtons[i]->setFont(font);
        slotButtons[i]->setPalette(palette);
        slotButtons[i]->setFixedHeight(30);
        m_signalMapper->setMapping(slotButtons[i], file);
        connect(slotButtons[i], SIGNAL(clicked()), m_signalMapper, SLOT(map()));
        m_recentProjectLayout->addWidget(slotButtons[i]);

        i++;

        if (i == Constants::MAX_RECENT_PROJECTS)
            break;
    }

    m_recentProjectLayout->addStretch();

    connect(m_signalMapper,
            static_cast<void (QSignalMapper::*)(const QString&)>(&QSignalMapper::mapped),
            projectManager(), &ProjectManager::openProject);
}

//! returns current project name suited for displaying on current project layout
QString WelcomeView::currentProjectFancyName()
{
    QString result("Untitled");
    if (ProjectDocument* projectDocument = projectManager()->document()) {
        if (projectDocument->hasValidNameAndPath())
            result = GUI_StringUtils::withTildeHomePath(projectDocument->projectFileName());
        else
            result = projectDocument->projectName();
    }
    return result;
}

//! updates label with current project name in picturesque manner
void WelcomeView::setCurrentProjectName(const QString& name)
{
    m_currentProName->setTextAnimated(name);
}

ProjectManager*WelcomeView::projectManager()
{
    return m_mainWindow->projectManager();
}

void WelcomeView::onWebLinkClicked(const QUrl& url)
{
    QDesktopServices::openUrl(url);
}

void WelcomeView::onNewUser()
{
    QDesktopServices::openUrl(QUrl("http://www.bornagainproject.org"));
}

void WelcomeView::updateRecentProjectPanel()
{
    clearLayout(m_recentProjectLayout);
    generateRecentProjectList();
    update();
}

void WelcomeView::clearLayout(QLayout* layout, bool deleteWidgets)
{
    if (layout) {
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (deleteWidgets) {
                if (QWidget* widget = item->widget())
                    delete widget;
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }
}

void WelcomeView::setNotificationText(const QString& text)
{
    m_updateNotification->setText(text);
}
