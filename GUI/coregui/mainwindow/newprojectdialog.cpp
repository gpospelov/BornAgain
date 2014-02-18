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
    , m_projectNameEdit(0)
    , m_projectPathEdit(0)
    , m_browseButton(0)
    , m_warningLabel(0)
    , m_cancelButton(0)
    , m_createButton(0)
    , m_valid_projectName(true)
    , m_valid_projectPath(true)

{
    setMinimumSize(480, 280);
    setWindowTitle("New project");

    QLabel *nameLabel = new QLabel(tr("Project name:"));
    m_projectNameEdit = new QLineEdit;
    m_projectNameEdit->setText("Untitled");
    connect(m_projectNameEdit, SIGNAL(textEdited(QString)), this, SLOT(checkIfProjectNameIsValid(QString)));
    nameLabel->setBuddy(m_projectNameEdit);

    QLabel *parentDirLabel = new QLabel(tr("Create in:"));
    m_projectPathEdit = new QLineEdit;
    m_projectPathEdit->setText(QDir::homePath());
    connect(m_projectPathEdit, SIGNAL(textEdited(QString)), this, SLOT(checkIfProjectPathIsValid(QString)));
    parentDirLabel->setBuddy(m_projectPathEdit);

    m_browseButton = new QPushButton(tr("Browse"));
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(setDirectory()));

    m_warningLabel = new QLabel();

    m_createButton = new QPushButton(tr("Create"));
    connect(m_createButton, SIGNAL(clicked()), this, SLOT(createProjectDir()));
    m_cancelButton = new QPushButton(tr("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QGroupBox *projectGroup = new QGroupBox(tr("Project name and location"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(m_projectNameEdit, 0, 1);
    layout->addWidget(parentDirLabel, 1, 0);
    layout->addWidget(m_projectPathEdit, 1, 1);
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


//! calls directory selection dialog
void NewProjectDialog::setDirectory()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                "Select directory",
                                getProjectPath(),
                                QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty()) {
        checkIfProjectPathIsValid(dirname);
    }

}


//! checks if ProjectPath is valid. Corresponding directory should exists.
void NewProjectDialog::checkIfProjectPathIsValid(const QString &dirname)
{
    if(QFile::exists(dirname)) {
        setValidProjectPath(true);
        m_projectPathEdit->setText(dirname);
    } else {
        setValidProjectPath(false);
    }
    updateWarningStatus();
}


//! checks if project name is valid. There should not be the directory with such
//! name in ProjectPath
void NewProjectDialog::checkIfProjectNameIsValid(const QString &projectName)
{
    QDir projectDir = getProjectPath() + "/" + projectName;
    if(projectDir.exists()) {
        setValidProjectName(false);
    } else {
        setValidProjectName(true);
    }
    updateWarningStatus();
}


//! sets flags wether project name is valid and then updates color of LineEdit
//! and warning message
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


//! sets flags wether project path is valid and then updates color of LineEdit
//! and warning message
void NewProjectDialog::setValidProjectPath(bool status)
{
    m_valid_projectPath = status;
    QPalette palette;
    if(m_valid_projectPath) {
        palette.setColor(QPalette::Text, Qt::black);
    } else {
        palette.setColor(QPalette::Text,Qt::darkRed);
    }
    m_projectPathEdit->setPalette(palette);
}


//! updates warning label depending on validity of project name and path
void NewProjectDialog::updateWarningStatus()
{
    if(m_valid_projectPath && m_valid_projectName) {
        m_createButton->setEnabled(true);
        m_warningLabel->setText("");
    } else if(!m_valid_projectPath ) {
        m_createButton->setEnabled(false);
        m_warningLabel->setText("<font color='darkRed'> The path '"+getProjectPath()+"' does not exist. </font>");
    } else if(!m_valid_projectName ) {
        m_createButton->setEnabled(false);
        m_warningLabel->setText("<font color='darkRed'> The directory '"+getProjectName()+"' already exists. </font>");
    }
}

//! creates directory with selected ProjectName in selected ProjectPath
void NewProjectDialog::createProjectDir()
{
    QDir parentDir = getProjectPath();
    if( !parentDir.mkdir(getProjectName()) ) {
        m_warningLabel->setText("<font color='darkRed'> Can't make subdirectory' '"+getProjectName()+"' in '."+getProjectPath()+"' </font>");
    } else {
        close();
    }
}

