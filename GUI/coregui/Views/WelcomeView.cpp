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
#include "LayoutUtils.h"
#include <QCommandLinkButton>
#include <QDesktopServices>
#include <QSignalMapper>
#include <QUrl>
#include <QVBoxLayout>

namespace
{
const int buttonHeight = 45;
const int buttonWidth = 140;

const QString centralWidgetStyle = "QWidget#containerWidget "
    "{border-left: 1px solid gray; border-right: 1px solid gray;background-color:white;}";
}

WelcomeView::WelcomeView(MainWindow* parent)
    : m_mainWindow(parent)
    , m_newProjectButton(nullptr)
    , m_openProjectButton(nullptr)
    , m_newUsertButton(nullptr)
    , m_currentProjectLabel(nullptr)
    , m_recentProjectLayout(nullptr)
    , m_updateNotification(nullptr)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(240, 240, 240, 255));
    setAutoFillBackground(true);
    setPalette(palette);

    auto centralWidgetLayout = new QVBoxLayout;
    centralWidgetLayout->setMargin(0);
    centralWidgetLayout->addWidget(createProjectWidget());
    centralWidgetLayout->addWidget(createNotificationLabel());
    centralWidgetLayout->addStretch(1);

    auto centralWidget = new QWidget;
    centralWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    centralWidget->setObjectName("containerWidget");
    centralWidget->setMaximumWidth(800);
    centralWidget->setContentsMargins(0, 30, 0, 0);
    centralWidget->setStyleSheet(centralWidgetStyle);
    centralWidget->setLayout(centralWidgetLayout);

    auto mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(centralWidget);
    mainLayout->addWidget(new QWidget);
    setLayout(mainLayout);

    connect(m_newProjectButton, &QPushButton::clicked,
            projectManager(), &ProjectManager::newProject);
    connect(m_openProjectButton, &QPushButton::clicked, [=](){projectManager()->openProject();});
    connect(m_newUsertButton, &QPushButton::clicked, this, &WelcomeView::onNewUser);
    connect(projectManager(), &ProjectManager::modified,
            this, &WelcomeView::updateRecentProjectPanel);

    updateRecentProjectPanel();
}

void WelcomeView::generateRecentProjectList()
{
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    auto recentProLabel = new QLabel("Recent Projects:");
    recentProLabel->setFont(titleFont);

    setCurrentProjectName(currentProjectFancyName());
    m_recentProjectLayout->addWidget(recentProLabel);

    m_signalMapper.reset(new QSignalMapper(this));

    for (const auto& file : projectManager()->recentProjects()) {
        QFont font;
        font.setPointSize(DesignerHelper::getLabelFontSize());
        font.setBold(false);

        QPalette palette;
        palette.setColor(QPalette::ButtonText, QColor(41, 73, 150));

        auto button = new QCommandLinkButton;
        button->setText(GUI_StringUtils::withTildeHomePath(file));
        button->setFont(font);
        button->setPalette(palette);
        button->setFixedHeight(30);
        m_signalMapper->setMapping(button, file);
        connect(button, SIGNAL(clicked()), m_signalMapper.get(), SLOT(map()));
        m_recentProjectLayout->addWidget(button);
    }

    m_recentProjectLayout->addStretch();

    connect(m_signalMapper.get(),
            static_cast<void (QSignalMapper::*)(const QString&)>(&QSignalMapper::mapped),
            projectManager(), &ProjectManager::openProject);
}

//! returns current project name suited for displaying on current project layout
QString WelcomeView::currentProjectFancyName()
{
    QString result("Untitled");
    if (auto projectDocument = projectManager()->document()) {
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
    m_currentProjectLabel->setTextAnimated(name);
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
    LayoutUtils::clearLayout(m_recentProjectLayout);
    generateRecentProjectList();
    update();
}

void WelcomeView::setNotificationText(const QString& text)
{
    m_updateNotification->setText(text);
}

QWidget* WelcomeView::createProjectWidget()
{
    auto layout = new QHBoxLayout;
    layout->addLayout(createButtonLayout());
    layout->addWidget(createSeparationFrame());
    layout->addLayout(createProjectLayout());
    layout->addStretch(1);

    auto result = new QWidget;
    result->setLayout(layout);
    result->setFixedHeight(430);

    return result;
}

QBoxLayout* WelcomeView::createButtonLayout()
{
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

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(m_newProjectButton);
    buttonLayout->addWidget(m_openProjectButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_newUsertButton);

    auto result = new QHBoxLayout;
    result->setContentsMargins(30, 0, 30, 0);
    result->addLayout(buttonLayout);

    return result;
}

QBoxLayout* WelcomeView::createCurrentProjectLayout()
{
    auto result = new QVBoxLayout;
    result->setContentsMargins(30, 0, 0, 0);

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);
    auto label = new QLabel("Current Project:");
    label->setFont(titleFont);

    m_currentProjectLabel = new FancyLabel("Untitled");
    result->addWidget(label);
    result->addWidget(m_currentProjectLabel);

    return result;
}

QBoxLayout* WelcomeView::createRecentProjectLayout()
{
    m_recentProjectLayout = new QVBoxLayout;
    m_recentProjectLayout->setContentsMargins(30, 0, 0, 0);
    return m_recentProjectLayout;
}

QBoxLayout* WelcomeView::createProjectLayout()
{
    auto result = new QVBoxLayout;
    result->addLayout(createCurrentProjectLayout());
    result->addSpacing(15);
    result->addLayout(createRecentProjectLayout());
    return result;
}

QLabel* WelcomeView::createNotificationLabel()
{
    m_updateNotification = new QLabel(this);
    m_updateNotification->setText("");
    m_updateNotification->setContentsMargins(40, 10, 0, 0);
    m_updateNotification->setOpenExternalLinks(true);
    m_updateNotification->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_updateNotification->setTextFormat(Qt::RichText);
    return m_updateNotification;
}

QFrame* WelcomeView::createSeparationFrame()
{
    auto result = new QFrame;
    result->setFrameShape(QFrame::VLine);
    result->setFrameShadow(QFrame::Sunken);
    return result;
}

