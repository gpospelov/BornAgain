#include "WelcomeView.h"
#include "DesignerHelper.h"
#include "mainwindow_constants.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QSizePolicy>
#include <QDebug>
#include "stringutils.h"


ContainerWidget::ContainerWidget(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setObjectName("containerWidget");
    setContentsMargins(0,30,0,0);
    setFixedWidth(800);
    setStyleSheet(QString::fromUtf8("ContainerWidget#containerWidget\n"
    "{\n"
    "    border-left: 1px solid gray;\n"
    "    border-right: 1px solid gray;\n"
    "    background-color:white;\n"
    "}\n"
    ""));
}

QSize ContainerWidget::sizeHint() const
{
    return QSize(800,800);
}


WelcomeView::WelcomeView(MainWindow *parent)
    : m_mainWindow(parent)
{

    QColor bgColor(240,240,240,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    m_projectManager = m_mainWindow->getProjectManager();
    Q_ASSERT(m_projectManager);

    QFont buttonFont;
    buttonFont.setPointSize(DesignerHelper::getLabelFontSize());
    buttonFont.setBold(false);

    int buttonHeight = 45;
    int buttonWidth = 140;

    newProjectButton = new QPushButton(tr("New Project"));
    //newProjectButton->setIcon(QIcon(":/images/main_simulation.png"));
    newProjectButton->setMinimumWidth(buttonWidth);
    newProjectButton->setMinimumHeight(buttonHeight);
    newProjectButton->setFont(buttonFont);

    openProjectButton = new QPushButton(tr("Open Project"));
    //openProjectButton->setIcon(QIcon(":/images/main_simulation.png"));
    openProjectButton->setMinimumWidth(buttonWidth);
    openProjectButton->setMinimumHeight(buttonHeight);
    openProjectButton->setFont(buttonFont);

    newUsertButton = new QPushButton(tr("New to BornAgain?"));
    //newUsertButton->setIcon(QIcon(":/images/main_simulation.png"));
    newUsertButton->setMinimumWidth(buttonWidth);
    newUsertButton->setMinimumHeight(buttonHeight);
    newUsertButton->setFont(buttonFont);




    QVBoxLayout *buttonLayout = new QVBoxLayout;
    //buttonLayout->setContentsMargins(0,0,0,0);

    buttonLayout->addWidget(newProjectButton);
    buttonLayout->addWidget(openProjectButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(newUsertButton);

    QHBoxLayout *buttonPanel = new QHBoxLayout;
    buttonPanel->setContentsMargins(30,0,30,0);
    buttonPanel->addLayout(buttonLayout);





    m_recentProjectLayout = new QVBoxLayout;
    m_recentProjectLayout->setContentsMargins(30,0,0,0);
    //generateRecentProjectList();


    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *itemContainerLayout = new QHBoxLayout;
    itemContainerLayout->addLayout(buttonPanel);
    itemContainerLayout->addWidget(line);
    itemContainerLayout->addLayout(m_recentProjectLayout);
    itemContainerLayout->addStretch(1);



    QWidget *itemContainerWidget = new QWidget;
    //QFrame *itemContainerWidget = new QFrame;
    itemContainerWidget->setLayout(itemContainerLayout);
    itemContainerWidget->setFixedHeight(350);
    //itemContainerWidget->setStyleSheet("border: 1px solid red");

    QVBoxLayout *containerLayout = new QVBoxLayout;
    containerLayout->setMargin(0);
    containerLayout->addWidget(itemContainerWidget);
    containerLayout->addStretch(1);

    ContainerWidget *containerWidget = new ContainerWidget;
    containerWidget->setLayout(containerLayout);

//    containerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    containerWidget->setObjectName("containerWidget");
//    containerWidget->setFixedWidth(800);
//    containerWidget->setContentsMargins(0,30,0,0);
//    containerWidget->setLayout(containerLayout);
    containerWidget->setStyleSheet(QString::fromUtf8("#containerWidget\n"
    "{\n"
    "    border-left: 1px solid gray;\n"
    "    border-right: 1px solid gray;\n"
    "    background-color:white;\n"
    "}\n"
    ""));

    // main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addStretch(1);
    mainLayout->addWidget(containerWidget);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(newProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(newProject()));
    connect(openProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(openProject()));
    connect(newUsertButton, SIGNAL(clicked()), this, SLOT(onNewUser()));    
}

void WelcomeView::generateRecentProjectList()
{
    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getLabelFontSize());
    titleFont.setBold(true);
    QLabel *recentProLabel = new QLabel("Recent Projects:");
    recentProLabel->setFont(titleFont);

    m_recentProjectLayout->addWidget(recentProLabel);

    QCommandLinkButton *slotButtons[Constants::MAX_RECENT_PROJECTS];
    //QLabel *myLabel[count];
    m_signalMapper = new QSignalMapper(this);

    int i = 0;
    foreach(QString file, m_projectManager->getRecentProjects() ) {
        //hasRecentProjects = true;

        QFont font;
        //font.setPointSize(9);
        font.setPointSize(DesignerHelper::getLabelFontSize());
        font.setBold(false);
        //font.underline();

        QPalette palette;
        palette.setColor(QPalette::ButtonText,QColor(41,73,150));

        slotButtons[i] = new QCommandLinkButton;
        slotButtons[i]->setText(Utils::withTildeHomePath(file));
        slotButtons[i]->setFont(font);
        slotButtons[i]->setPalette(palette);
        //slotButtons[i]->setDescription("Recent description");
        slotButtons[i]->setFixedHeight(30);
        m_signalMapper->setMapping(slotButtons[i], file);
        connect(slotButtons[i], SIGNAL(clicked()), m_signalMapper, SLOT (map()));
        m_recentProjectLayout->addWidget(slotButtons[i]);

        i++;

        if(i == Constants::MAX_RECENT_PROJECTS)
        {
            break;
        }
    }

    m_recentProjectLayout->addStretch();

    connect(m_signalMapper, SIGNAL(mapped(QString)),
            m_projectManager, SLOT(openProject(QString)));
}

void WelcomeView::onWebLinkClicked(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

void WelcomeView::onNewUser()
{
    QUrl url(tr("http://apps.jcns.fz-juelich.de/doku/sc/bornagain:start"));
    QDesktopServices::openUrl(url);
}

void WelcomeView::updateRecentProjectPanel()
{
    qDebug() << "WelcomeView::updateRecentProjectPanel called";
    this->clearLayout(m_recentProjectLayout);
    this->generateRecentProjectList();
}

void WelcomeView::clearLayout(QLayout* layout, bool deleteWidgets)
{
    if(layout)
    {
        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    delete widget;
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }

}
