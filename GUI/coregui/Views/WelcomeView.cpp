#include "WelcomeView.h"
#include "qdebug.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include "stringutils.h"


WelcomeView::WelcomeView(MainWindow *parent)
    : m_mainWindow(parent)
{

    m_projectManager = m_mainWindow->getProjectManager();
    Q_ASSERT(m_projectManager);

    newProjectButton = new QPushButton(tr("New Project"));
    newProjectButton->setMinimumWidth(150);
    newProjectButton->setMinimumHeight(50);

    openProjectButton = new QPushButton(tr("Open Project"));
    openProjectButton->setMinimumWidth(150);
    openProjectButton->setMinimumHeight(50);

    newUsertButton = new QPushButton(tr("New to BornAgain?"));
    newUsertButton->setMinimumWidth(150);
    newUsertButton->setMinimumHeight(50);




    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(newProjectButton);
    buttonLayout->addWidget(openProjectButton);
    buttonLayout->addWidget(newUsertButton);
    buttonLayout->addStretch();

    QHBoxLayout *buttonPanel = new QHBoxLayout;
    buttonPanel->addStretch();
    buttonPanel->addLayout(buttonLayout);


    m_recentProjectLayout = new QVBoxLayout;
    //generateRecentProjectList();


    QGroupBox *recentProjectsBox = new QGroupBox(tr("Recent Projects:"));
    recentProjectsBox->setLayout(m_recentProjectLayout);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonPanel);
    mainLayout->addWidget(line);
    mainLayout->addWidget(recentProjectsBox);
    mainLayout->addStretch(1);
    setLayout(mainLayout);


    connect(newProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(newProject()));
    connect(openProjectButton, SIGNAL(clicked()), m_projectManager, SLOT(openProject()));
    connect(newUsertButton, SIGNAL(clicked()), this, SLOT(onNewUser()));    
}

void WelcomeView::generateRecentProjectList()
{

    int count = m_projectManager->getRecentProjects().size();
    bool hasRecentProjects = false;

    //QCommandLinkButton *slotButtons[count];
    QLabel *myLabel[count];
    m_signalMapper = new QSignalMapper(this);

    int i = 0;
    foreach(QString file, m_projectManager->getRecentProjects() ) {
        hasRecentProjects = true;

        /*slotButtons[i] = new QCommandLinkButton;
        slotButtons[i]->setText(Utils::withTildeHomePath(file));
        slotButtons[i]->setText("<a href=\"#\">Click Here!</a>");
        //slotButtons[i]->setDescription("Recent description");
        slotButtons[i]->setFixedHeight(35);
        m_signalMapper->setMapping(slotButtons[i], file);
        connect(slotButtons[i], SIGNAL(clicked()), m_signalMapper, SLOT (map()));
        m_recentProjectLayout->addWidget(slotButtons[i]);*/

        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        //font.underline();

        QString labelText;
        labelText.append("<a href=\"#\" style=\"text-decoration:none;\">");
        labelText.append( Utils::withTildeHomePath(file));
        labelText.append("</a>");

        myLabel[i] = new QLabel;
        myLabel[i]->setText(labelText);
        myLabel[i]->setTextFormat(Qt::RichText);
        myLabel[i]->setTextInteractionFlags(Qt::TextBrowserInteraction);
        //myLabel->setOpenExternalLinks(true);
        myLabel[i]->setFont(font);
        myLabel[i]->setFixedHeight(20);

        m_signalMapper->setMapping(myLabel[i], file);
        connect(myLabel[i], SIGNAL(linkActivated(QString)), m_signalMapper, SLOT (map()));

        m_recentProjectLayout->addWidget(myLabel[i]);


        i++;
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
