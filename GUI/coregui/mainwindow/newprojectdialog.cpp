#include "newprojectdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QDir>
#include <QFileDialog>

#include <iostream>

NewProjectDialog::NewProjectDialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumSize(480, 280);
    setWindowTitle("New project");



    m_nameLabel = new QLabel(tr("Project name:"));
    m_nameEdit = new QLineEdit;
    m_nameLabel->setBuddy(m_nameEdit);

    m_createinLabel = new QLabel(tr("Create in:"));
    m_createinEdit = new QLineEdit;
    m_createinEdit->setText(QDir::homePath());
    m_createinLabel->setBuddy(m_createinEdit);

    m_browseButton = new QPushButton(tr("Browse"));
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(setDirectory()));

    m_createButton = new QPushButton(tr("Create"));
    m_cancelButton = new QPushButton(tr("Cancel"));

//    m_statusBar = new QStatusBar;


    QGroupBox *projectGroup = new QGroupBox(tr("Project name and location"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_nameLabel, 0, 0);
    layout->addWidget(m_nameEdit, 0, 1);
    layout->addWidget(m_createinLabel, 1, 0);
    layout->addWidget(m_createinEdit, 1, 1);
    layout->addWidget(m_browseButton,1,2);

    projectGroup->setLayout(layout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_createButton);
    buttonsLayout->addWidget(m_cancelButton);
//    buttonsLayout->setMargin(0);
//    buttonsLayout->setSpacing(0);
//    layout->addLayout(buttonsLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(projectGroup);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);
//    mainLayout->addWidget(m_statusBar);

    setLayout(mainLayout);



}


void NewProjectDialog::setDirectory()
{

//    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;


    std::cout << "XXX " << m_createinEdit->text().toStdString() << std::endl;

    QString directory = QFileDialog::getExistingDirectory(this,
                                "AAA",
                               "/home/pospelov",
                                QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    std::cout << "XXX 2.1" << m_createinEdit->text().toStdString();

    if (!directory.isEmpty())
        m_createinEdit->setText(directory);


}





