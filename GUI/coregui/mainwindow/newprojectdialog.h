// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/newprojectdialog.h
//! @brief     Declares class NewProjectDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <QString>
#include <QLineEdit>

class QLabel;
class QPushButton;
class QStatusBar;
class QPalette;


//! new project dialog window
class BA_CORE_API_ NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    NewProjectDialog(QWidget *parent = 0, const QString &workingDirectory = QString(),
                     const QString &projectName = QString());

    QString getWorkingDirectory() const;
    void setWorkingDirectory(const QString &text);

    void setProjectName(const QString &text);

    QString getProjectFileName() const;

private slots:
    void onBrowseDirectory();
    void checkIfProjectPathIsValid(const QString &dirname);
    void checkIfProjectNameIsValid(const QString &projectName);
    void createProjectDir();

private:
    QString getProjectName() const { return m_projectNameEdit->text(); }

    void setValidProjectName(bool status);
    void setValidProjectPath(bool status);
    void updateWarningStatus();

    QLineEdit *m_projectNameEdit;
    QLineEdit *m_workDirEdit;
    QPushButton *m_browseButton;
    QLabel *m_warningLabel;
    QPushButton *m_cancelButton;
    QPushButton *m_createButton;

    bool m_valid_projectName;
    bool m_valid_projectPath;
};

#endif // NEWPROJECTDIALOG_H
