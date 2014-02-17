#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QStatusBar;


//! new project dialog window
class NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    NewProjectDialog(QWidget *parent = 0);

private slots:
    void setDirectory();

private:
    QLabel *m_nameLabel;
    QLineEdit *m_nameEdit;
    QLabel *m_createinLabel;
    QLineEdit *m_createinEdit;
    QPushButton *m_browseButton;
    QPushButton *m_cancelButton;
    QPushButton *m_createButton;
};


#endif
