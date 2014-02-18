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
//    , m_nameLabel(0)
    , m_projectNameEdit(0)
//    , m_parentDirLabel(0)
    , m_parentDirEdit(0)
    , m_browseButton(0)
    , m_warningLabel(0)
    , m_cancelButton(0)
    , m_createButton(0)
    , m_valid_projectName(true)
    , m_valid_parentDir(true)

{
    setMinimumSize(480, 280);
    setWindowTitle("New project");

    QLabel *nameLabel = new QLabel(tr("Project name:"));
    m_projectNameEdit = new QLineEdit;
    m_projectNameEdit->setText("Untitled");
    connect(m_projectNameEdit, SIGNAL(textEdited(QString)), this, SLOT(checkIfProjectNameIsValid(QString)));
    nameLabel->setBuddy(m_projectNameEdit);

    QLabel *parentDirLabel = new QLabel(tr("Create in:"));
    m_parentDirEdit = new QLineEdit;
    m_parentDirEdit->setText(QDir::homePath());
    connect(m_parentDirEdit, SIGNAL(textEdited(QString)), this, SLOT(checkIfParentDirIsValid(QString)));
    parentDirLabel->setBuddy(m_parentDirEdit);

    m_browseButton = new QPushButton(tr("Browse"));
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(setDirectory()));

    m_warningLabel = new QLabel();

    m_createButton = new QPushButton(tr("Create"));
    m_cancelButton = new QPushButton(tr("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QGroupBox *projectGroup = new QGroupBox(tr("Project name and location"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(m_projectNameEdit, 0, 1);
    layout->addWidget(parentDirLabel, 1, 0);
    layout->addWidget(m_parentDirEdit, 1, 1);
    layout->addWidget(m_browseButton,1,2);

    projectGroup->setLayout(layout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_createButton);
    buttonsLayout->addWidget(m_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(projectGroup);
    mainLayout->addWidget(m_warningLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}


void NewProjectDialog::setDirectory()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                "AAA",
                               "/home/pospelov",
                                QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty()) {
        checkIfParentDirIsValid(dirname);
    }

}


void NewProjectDialog::checkIfParentDirIsValid(const QString &dirname)
{
    if(QFile::exists(dirname)) {
        setValidParentDir(true);
        m_parentDirEdit->setText(dirname);
    } else {
        setValidParentDir(false);
    }
    updateWarningStatus();

}



void NewProjectDialog::checkIfProjectNameIsValid(const QString &projectName)
{

    QDir projectDir = getParentDirName() + "/" + projectName;
    if(projectDir.exists()) {
        setValidProjectName(false);
    } else {
        setValidProjectName(true);
    }
    updateWarningStatus();
}


void NewProjectDialog::setValidProjectName(bool status)
{
    m_valid_projectName = status;
    QPalette palette;
    if(m_valid_projectName) {
        palette.setColor(QPalette::Text, Qt::black);
    } else {
        palette.setColor(QPalette::Text,Qt::darkRed);
    }
    m_projectNameEdit->setPalette(palette);
}


void NewProjectDialog::setValidParentDir(bool status)
{
    m_valid_parentDir = status;
    QPalette palette;
    if(m_valid_parentDir) {
        palette.setColor(QPalette::Text, Qt::black);
    } else {
        palette.setColor(QPalette::Text,Qt::darkRed);
    }
    m_parentDirEdit->setPalette(palette);
}



void NewProjectDialog::updateWarningStatus()
{
    if(m_valid_parentDir && m_valid_projectName) {
        m_createButton->setEnabled(true);
        m_warningLabel->setText("");
    } else if(!m_valid_parentDir ) {
        m_createButton->setEnabled(false);
        m_warningLabel->setText("<font color='darkRed'> The path '"+getParentDirName()+"' does not exist. </font>");
    } else if(!m_valid_projectName ) {
        m_createButton->setEnabled(false);
        m_warningLabel->setText("<font color='darkRed'> The directory '"+getProjectName()+"' already exists. </font>");
    }
}


