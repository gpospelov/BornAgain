#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>

class QLabel;
class QPushButton;
class QStatusBar;
class QPalette;


//! new project dialog window
class NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    NewProjectDialog(QWidget *parent = 0);

private slots:
    void setDirectory();
    void checkIfParentDirIsValid(const QString &dirname);
    void checkIfProjectNameIsValid(const QString &projectName);

    QString getProjectName() { return m_projectNameEdit->text(); }
    QString getParentDirName() { return m_parentDirEdit->text(); }

private:
    void setValidProjectName(bool status);
    void setValidParentDir(bool status);
    void updateWarningStatus();

//    QLabel *m_nameLabel;
    QLineEdit *m_projectNameEdit;
//    QLabel *m_parentDirLabel;
    QLineEdit *m_parentDirEdit;
    QPushButton *m_browseButton;
    QLabel *m_warningLabel;
    QPushButton *m_cancelButton;
    QPushButton *m_createButton;

    bool m_valid_projectName;
    bool m_valid_parentDir;

};


#endif
