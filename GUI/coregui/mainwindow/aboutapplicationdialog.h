#ifndef ABOUTAPPLICATIONDIALOG_H
#define ABOUTAPPLICATIONDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <QString>


class QLabel;
class QPushButton;
class QStatusBar;
class QPalette;


//! new project dialog window
class BA_CORE_API_ AboutApplicationDialog : public QDialog
{
    Q_OBJECT
public:
    AboutApplicationDialog(QWidget *parent = 0);


private:
    QPushButton *m_closeButton;

};


#endif
