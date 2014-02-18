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


    void setProjectName(const QString &text) { return m_projectNameEdit->setText(text); }
    void setProjectPath(const QString &text) { return m_projectPathEdit->setText(text); }

    QString getProjectName() { return m_projectNameEdit->text(); }
    QString getProjectPath() { return m_projectPathEdit->text(); }

private slots:
    void setDirectory();
    void checkIfProjectPathIsValid(const QString &dirname);
    void checkIfProjectNameIsValid(const QString &projectName);
    void createProjectDir();

private:
    void setValidProjectName(bool status);
    void setValidProjectPath(bool status);
    void updateWarningStatus();

    QLineEdit *m_projectNameEdit;
    QLineEdit *m_projectPathEdit;
    QPushButton *m_browseButton;
    QLabel *m_warningLabel;
    QPushButton *m_cancelButton;
    QPushButton *m_createButton;

    bool m_valid_projectName;
    bool m_valid_projectPath;

};


#endif
